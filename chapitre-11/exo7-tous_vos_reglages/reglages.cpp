#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Reglage
{
    string nom;
    bool ecrit = false;
    bool env = false;
    bool lit = false;
    bool getenv_ = false;
};

int main()
{
    int R = 0;
    cin >> R;
    vector<Reglage> reglages;

    for (int i = 0; i < R; i++)
    {
        string nom, action;
        cin >> nom >> action;

        int idx = -1;
        for (size_t j = 0; j < reglages.size(); j++)
            if (reglages[j].nom == nom)
                idx = (int)j;
        if (idx == -1)
        {
            Reglage r;
            r.nom = nom;
            reglages.push_back(r);
            idx = (int)reglages.size() - 1;
        }

        if (action == "ECRIT")
            reglages[idx].ecrit = true;
        else if (action == "ENV")
            reglages[idx].env = true;
        else if (action == "LIT")
            reglages[idx].lit = true;
        else if (action == "GETENV")
            reglages[idx].getenv_ = true;
    }

    int menu = 0;
    for (const Reglage& r : reglages)
    {
        string classe;
        if (r.getenv_)
            classe = "CACHE";
        else if (!r.lit)
            classe = "FANTOME";
        else if (!r.ecrit && !r.env)
            classe = "CONSTANTE";
        else
        {
            classe = "MENU";
            menu++;
        }
        cout << r.nom << " " << classe << "\n";
    }
    cout << "MENU " << menu << " SUR " << reglages.size() << "\n";
    return 0;
}

