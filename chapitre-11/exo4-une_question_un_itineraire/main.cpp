#include <iostream>
#include <string>
using namespace std;

static void retirerCR(string& s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();
}

int main()
{
    string ligne;
    getline(cin, ligne);
    retirerCR(ligne);
    int K = ligne.empty() ? 0 : stoi(ligne);

    for (int i = 1; i <= K; i++)
    {
        string registre;
        getline(cin, registre);
        retirerCR(registre);

        getline(cin, ligne);
        retirerCR(ligne);
        int L = stoi(ligne);

        string texte;
        for (int j = 0; j < L; j++)
        {
            string l;
            getline(cin, l);
            retirerCR(l);
            texte += l;
            texte += '\n';
        }

        if (registre == "-")
        {
            cout << i << " REGISTRE AUCUN\n";
            continue;
        }

        cout << i << " MANIFESTE " << registre << "\n";

        if (L == -1)
        {
            cout << i << " ECHEC ILLISIBLE\n";
            continue;
        }

        const string cle = "\"library_path\"";
        size_t p = texte.find(cle);
        if (p == string::npos)
        {
            cout << i << " ECHEC CLE\n";
            continue;
        }

        size_t deuxPoints = texte.find(':', p + cle.size());
        if (deuxPoints == string::npos)
        {
            cout << i << " ECHEC DEUX_POINTS\n";
            continue;
        }

        size_t debut = texte.find('"', deuxPoints + 1);
        if (debut == string::npos)
        {
            cout << i << " ECHEC GUILLEMET\n";
            continue;
        }
        size_t fin = texte.find('"', debut + 1);
        if (fin == string::npos)
        {
            cout << i << " ECHEC GUILLEMET\n";
            continue;
        }

        string brut = texte.substr(debut + 1, fin - debut - 1);
        string valeur;
        for (size_t k = 0; k < brut.size(); k++)
        {
            if (brut[k] == '\\' && k + 1 < brut.size() && brut[k + 1] == '\\')
                continue;
            valeur += brut[k];
        }

        if (valeur.empty())
        {
            cout << i << " ECHEC VIDE\n";
            continue;
        }

        bool absolu = (valeur.size() >= 2 && valeur[1] == ':')
                      || valeur[0] == '\\' || valeur[0] == '/';

        cout << i << " VALEUR " << valeur << "\n";
        if (absolu)
        {
            cout << i << " ABSOLU\n";
            cout << i << " CHARGE " << valeur << "\n";
        }
        else
        {
            size_t sep = registre.find_last_of("\\/");
            string dossier = registre.substr(0, sep + 1);
            cout << i << " RELATIF\n";
            cout << i << " CHARGE " << dossier << valeur << "\n";
        }
    }
    return 0;
}
//resultat
//1 MANIFESTE C:\Rt\oculus.json
//1 VALEUR .\bin\RtVr64.dll
//1 RELATIF
//1 CHARGE C:\Rt\.\bin\RtVr64.dll
//2 REGISTRE AUCUN
