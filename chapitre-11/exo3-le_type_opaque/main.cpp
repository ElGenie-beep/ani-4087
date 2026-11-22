#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

static bool finitPar(const string& s, const string& suffixe)
{
    return s.size() >= suffixe.size() &&
           s.compare(s.size() - suffixe.size(), suffixe.size(), suffixe) == 0;
}

int main()
{
    int E;
    cin >> E;
    set<string> externes;
    for (int i = 0; i < E; i++)
    {
        string nom;
        cin >> nom;
        externes.insert(nom);
    }

    int F;
    cin >> F;
    vector<string> ordre;
    map<string, vector<string>> inclusions;
    for (int i = 0; i < F; i++)
    {
        string nom;
        int k;
        cin >> nom >> k;
        vector<string> liste(k);
        for (int j = 0; j < k; j++)
            cin >> liste[j];
        ordre.push_back(nom);
        inclusions[nom] = liste;
    }

    int touchees = 0;
    int unites = 0;

    for (const string& unite : ordre)
    {
        if (!finitPar(unite, ".cpp"))
            continue;
        unites++;

        queue<string> file;
        set<string> vus;
        map<string, string> parent;
        string trouve;

        vus.insert(unite);
        file.push(unite);

        while (!file.empty() && trouve.empty())
        {
            string courant = file.front();
            file.pop();

            auto it = inclusions.find(courant);
            if (it == inclusions.end())
                continue;

            for (const string& suivant : it->second)
            {
                if (vus.count(suivant))
                    continue;
                vus.insert(suivant);
                parent[suivant] = courant;

                if (externes.count(suivant))
                {
                    trouve = suivant;
                    break;
                }
                if (inclusions.count(suivant))
                    file.push(suivant);
            }
        }

        if (trouve.empty())
        {
            cout << unite << " NON\n";
        }
        else
        {
            touchees++;
            vector<string> chemin;
            string cur = trouve;
            while (cur != unite)
            {
                chemin.push_back(cur);
                cur = parent[cur];
            }
            chemin.push_back(unite);
            reverse(chemin.begin(), chemin.end());

            cout << unite << " OUI ";
            for (size_t i = 0; i < chemin.size(); i++)
            {
                if (i > 0)
                    cout << ">";
                cout << chemin[i];
            }
            cout << "\n";
        }
    }

    cout << "TOUCHEES " << touchees << " SUR " << unites << "\n";
    return 0;
}

//Resultat 
//main.cpp NON
//NkXrOpenXRBackend.cpp OUI NkXrOpenXRBackend.cpp>openxr.h
//TOUCHEES 1 SUR 2
