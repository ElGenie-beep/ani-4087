#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

vector<string> ordrePourPlateforme(const string& plateforme) {
    if (plateforme == "WINDOWS") return {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
    if (plateforme == "MACOS")   return {"METAL", "OPENGL", "SOFTWARE"};
    if (plateforme == "IOS")     return {"METAL", "SOFTWARE"};
    if (plateforme == "ANDROID") return {"VULKAN", "OPENGL", "SOFTWARE"};
    return {"VULKAN", "OPENGL", "SOFTWARE"};
}

string choisirApi(const vector<string>& ordre, const set<string>& supportees) {
    for (const string& api : ordre) {
        if (api == "SOFTWARE" || supportees.find(api) != supportees.end()) {
            return api;
        }
    }
    return "SOFTWARE";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const map<string, string> noms = {
        {"VULKAN", "Vulkan"},
        {"DX12", "DirectX 12"},
        {"DX11", "DirectX 11"},
        {"OPENGL", "OpenGL"},
        {"METAL", "Metal"},
        {"SOFTWARE", "Software"}
    };

    int n;
    cin >> n;

    int nbIgnorees = 0;
    int nbLogiciel = 0;
    set<string> differentes;

    for (int i = 0; i < n; i++) {
        string nom, plateforme;
        int k;
        cin >> nom >> plateforme >> k;

        set<string> supportees;
        for (int j = 0; j < k; j++) {
            string api;
            cin >> api;
            supportees.insert(api);
        }

        const vector<string> ordre = ordrePourPlateforme(plateforme);
        const set<string> dansOrdre(ordre.begin(), ordre.end());

        for (const string& api : supportees) {
            if (dansOrdre.find(api) == dansOrdre.end()) {
                nbIgnorees++;
            }
        }

        const string choisie = choisirApi(ordre, supportees);
        if (choisie == "SOFTWARE") nbLogiciel++;

        const string& lisible = noms.at(choisie);
        differentes.insert(lisible);
        cout << nom << " " << lisible << "\n";
    }

    cout << "IGNOREES " << nbIgnorees << "\n";
    cout << "LOGICIEL " << nbLogiciel << "\n";
    cout << "DIFFERENTES " << differentes.size() << "\n";
    return 0;
}
