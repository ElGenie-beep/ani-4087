#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

static bool estCaractereDeMot(char c)
{
    return isalnum(static_cast<unsigned char>(c)) || c == '_';
}

// Vrai si "nom" apparait en entier dans le texte (pas colle a une lettre, un chiffre ou _)
static bool contientNom(const string& texte, const string& nom)
{
    if (nom.empty())
        return false;
    size_t pos = 0;
    while ((pos = texte.find(nom, pos)) != string::npos)
    {
        bool avantOk = (pos == 0) || !estCaractereDeMot(texte[pos - 1]);
        size_t fin = pos + nom.size();
        bool apresOk = (fin >= texte.size()) || !estCaractereDeMot(texte[fin]);
        if (avantOk && apresOk)
            return true;
        pos++;
    }
    return false;
}

static bool contientUnNom(const string& texte, const vector<string>& noms)
{
    for (const string& nom : noms)
        if (contientNom(texte, nom))
            return true;
    return false;
}

static bool estCommentaire(const string& texte)
{
    size_t i = 0;
    while (i < texte.size() && (texte[i] == ' ' || texte[i] == '\t'))
        i++;
    return texte.compare(i, 2, "//") == 0;
}

int main()
{
    string etiquette;
    int k = 0;
    cin >> etiquette >> k;
    vector<string> backend(k);
    for (int i = 0; i < k; i++)
        cin >> backend[i];

    int m = 0;
    cin >> etiquette >> m;
    vector<string> definis(m);
    for (int i = 0; i < m; i++)
        cin >> definis[i];

    int N = 0;
    cin >> N;

    int decisions = 0;
    int fuites = 0;
    int nbDefinis = 0;

    for (int num = 1; num <= N; num++)
    {
        string zone, texte;
        cin >> zone;
        getline(cin, texte);
        if (!texte.empty() && texte.back() == '\r')
            texte.pop_back();

        if (estCommentaire(texte))
            continue;

        if (contientUnNom(texte, backend))
        {
            if (zone == "INIT")
            {
                decisions++;
            }
            else if (zone == "BOUCLE" || zone == "SCENE")
            {
                fuites++;
                cout << "FUITE " << num << " " << zone << "\n";
            }
        }

        if (zone != "FABRIQUE" && contientUnNom(texte, definis))
        {
            nbDefinis++;
            cout << "DEFINI " << num << " " << zone << "\n";
        }
    }

    cout << "DECISIONS " << decisions << "\n";
    cout << "FUITES " << fuites << "\n";
    cout << "DEFINIS " << nbDefinis << "\n";
    if (fuites == 0 && nbDefinis == 0)
        cout << "ABSTRACTION TENUE\n";
    else
        cout << "ABSTRACTION FUIT\n";
    return 0;
}

//Resultat
//FUITE 7 BOUCLE
//DECISIONS 2
//FUITES 1
//DEFINIS 0
//ABSTRACTION FUIT
