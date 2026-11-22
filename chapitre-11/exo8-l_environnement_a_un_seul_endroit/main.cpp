#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

static void retirerCR(string& s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();
}

// Lit un nombre a partir de p : espaces, signe facultatif, chiffres. ok = false s'il n'y a aucun chiffre.
static long long lireNombre(const string& s, size_t& p, bool& ok)
{
    while (p < s.size() && s[p] == ' ')
        p++;
    size_t q = p;
    bool negatif = false;
    if (q < s.size() && (s[q] == '+' || s[q] == '-'))
    {
        negatif = (s[q] == '-');
        q++;
    }
    if (q >= s.size() || !isdigit(static_cast<unsigned char>(s[q])))
    {
        ok = false;
        return 0;
    }
    long long v = 0;
    while (q < s.size() && isdigit(static_cast<unsigned char>(s[q])))
    {
        v = v * 10 + (s[q] - '0');
        q++;
    }
    p = q;
    ok = true;
    return negatif ? -v : v;
}

static long long nombreSimple(const string& s)
{
    size_t p = 0;
    bool ok = false;
    return lireNombre(s, p, ok);
}

// NON si le premier signe est 0 ou si la valeur vaut exactement "false", sinon OUI
static bool interrupteur(const string& v)
{
    return !(v[0] == '0' || v == "false");
}

int main()
{
    string ligne;

    // Ligne 1 : BACKEND HZ DEMI PROFONDEUR LISTE LATENCE
    getline(cin, ligne);
    retirerCR(ligne);
    istringstream l1(ligne);
    string backend, demiTxt, profTxt, listeTxt;
    long long hz = 0, latence = 0;
    l1 >> backend >> hz >> demiTxt >> profTxt >> listeTxt >> latence;
    bool demi = (demiTxt == "OUI");
    bool profondeur = (profTxt == "OUI");
    bool liste = (listeTxt == "OUI");

    // Ligne 2 : chemin du loader (peut contenir des espaces)
    string loader;
    getline(cin, loader);
    retirerCR(loader);

    // Ligne 3 : LIBRE ou FIXE lacet tangage x y z
    getline(cin, ligne);
    retirerCR(ligne);
    istringstream l3(ligne);
    string modePose;
    l3 >> modePose;
    bool fixe = (modePose == "FIXE");
    long long pose[5] = {0, 0, 0, 0, 0};
    if (fixe)
        for (int i = 0; i < 5; i++)
            l3 >> pose[i];

    // Variables d'environnement
    int M = 0;
    getline(cin, ligne);
    retirerCR(ligne);
    if (!ligne.empty())
        M = stoi(ligne);

    int appliquees = 0;
    int ignorees = 0;

    for (int i = 0; i < M; i++)
    {
        string entree;
        getline(cin, entree);
        retirerCR(entree);

        string nom = entree;
        string valeur;
        size_t egal = entree.find('=');
        if (egal != string::npos)
        {
            nom = entree.substr(0, egal);
            valeur = entree.substr(egal + 1);
        }

        bool applique = false;

        if (!valeur.empty())
        {
            if (nom == "NK_XR_BACKEND")
            {
                if (valeur == "openxr")
                {
                    backend = "OPENXR";
                    applique = true;
                }
            }
            else if (nom == "NK_XR_HZ")
            {
                hz = nombreSimple(valeur);
                applique = true;
            }
            else if (nom == "NK_XR_SIM_LATENCY_MS")
            {
                latence = nombreSimple(valeur);
                applique = true;
            }
            else if (nom == "NK_XR_HALF_RATE")
            {
                demi = interrupteur(valeur);
                applique = true;
            }
            else if (nom == "NK_XR_DEPTH_LAYER")
            {
                profondeur = interrupteur(valeur);
                applique = true;
            }
            else if (nom == "NK_XR_LIST_EXT")
            {
                liste = interrupteur(valeur);
                applique = true;
            }
            else if (nom == "NK_XR_OPENXR_LOADER")
            {
                loader = valeur;
                applique = true;
            }
            else if (nom == "NK_XR_SIM_POSE")
            {
                vector<long long> nombres;
                size_t p = 0;
                while (nombres.size() < 5 && p < valeur.size())
                {
                    bool ok = false;
                    long long v = lireNombre(valeur, p, ok);
                    if (!ok)
                        break;
                    nombres.push_back(v);
                    while (p < valeur.size() && (valeur[p] == ',' || valeur[p] == ' '))
                        p++;
                }
                if (nombres.size() == 5)
                {
                    fixe = true;
                    for (int k = 0; k < 5; k++)
                        pose[k] = nombres[k];
                    applique = true;
                }
            }
        }

        if (applique)
            appliquees++;
        else
            ignorees++;
    }

    cout << "BACKEND " << backend << "\n";
    cout << "HZ " << hz << "\n";
    cout << "DEMI " << (demi ? "OUI" : "NON") << "\n";
    cout << "PROFONDEUR " << (profondeur ? "OUI" : "NON") << "\n";
    cout << "LISTE " << (liste ? "OUI" : "NON") << "\n";
    cout << "LOADER " << loader << "\n";
    cout << "LATENCE " << latence << "\n";
    if (fixe)
    {
        cout << "POSE FIXE";
        for (int k = 0; k < 5; k++)
            cout << " " << pose[k];
        cout << "\n";
    }
    else
    {
        cout << "POSE LIBRE\n";
    }
    cout << "APPLIQUEES " << appliquees << "\n";
    cout << "IGNOREES " << ignorees << "\n";
    return 0;
}

//Resultat
//BACKEND OPENXR
//HZ 90
//DEMI OUI
//PROFONDEUR OUI
//LISTE NON
//LOADER -
//LATENCE 0
//POSE LIBRE
//APPLIQUEES 3
//IGNOREES 3
