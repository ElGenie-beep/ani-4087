#include <iostream>
#include <string>
#include <vector>
using namespace std;

static void retirerCR(string& s)
{
    if (!s.empty() && s.back() == '\r')
        s.pop_back();
}

static bool estMajChiffreOuTiret(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static bool estLettreChiffreOuTiret(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9') || c == '_';
}

// Commence par // une fois ôtés les espaces et tabulations du début
static bool estCommentaire(const string& ligne)
{
    size_t i = 0;
    while (i < ligne.size() && (ligne[i] == ' ' || ligne[i] == '\t'))
        i++;
    return ligne.compare(i, 2, "//") == 0;
}

int main()
{
    string ligne;
    getline(cin, ligne);
    retirerCR(ligne);
    int N = ligne.empty() ? 0 : stoi(ligne);

    vector<string> fichier(N);
    for (int i = 0; i < N; i++)
    {
        getline(cin, fichier[i]);
        retirerCR(fichier[i]);
    }

    // Longueur de l'en-tête : le bloc du haut qui commence par //
    int e = 0;
    while (e < N && estCommentaire(fichier[e]))
        e++;

    // Variables annoncées, dans l'ordre de première apparition, une seule fois
    vector<string> variables;
    for (int i = 0; i < e; i++)
    {
        const string& l = fichier[i];
        size_t pos = 0;
        while ((pos = l.find("NK_", pos)) != string::npos)
        {
            bool avantOk = (pos == 0) || !estLettreChiffreOuTiret(l[pos - 1]);
            size_t fin = pos + 3;
            while (fin < l.size() && estMajChiffreOuTiret(l[fin]))
                fin++;
            bool auMoinsUnSigne = fin > pos + 3;
            bool suiviDeEgal = fin < l.size() && l[fin] == '=';

            if (avantOk && auMoinsUnSigne && suiviDeEgal)
            {
                string nom = l.substr(pos, fin - pos);
                bool dejaVu = false;
                for (const string& v : variables)
                    if (v == nom)
                        dejaVu = true;
                if (!dejaVu)
                    variables.push_back(nom);
            }
            pos++;
        }
    }

    cout << "ENTETE " << e << "\n";
    cout << "IGNOREES " << (N - e) << "\n";
    if (variables.empty())
        cout << "VARIABLE AUCUNE\n";
    else
        for (const string& v : variables)
            cout << "VARIABLE " << v << "\n";

    long long part = (N == 0) ? 0 : (100LL * e) / N;
    cout << "PART " << part << "\n";
    return 0;
}

//Resultat
//ENTETE 6
//IGNOREES 3
//VARIABLE NK_XR_LOADER
//PART 66
