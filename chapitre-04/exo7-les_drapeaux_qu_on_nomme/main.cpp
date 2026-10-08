#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct Dependance {
    string nom;
    unsigned long long valeur;
    vector<string> besoins;
};

int main() {
    const vector<pair<string, unsigned long long>> simples = {
        {"RENDER2D", 1}, {"RENDER3D", 2}, {"TEXT", 4}, {"UI", 8},
        {"SHADOW", 16}, {"POST_PROCESS", 32}, {"VFX", 64},
        {"ANIMATION", 128}, {"OVERLAY", 256}, {"SIMULATION", 512},
        {"OFFSCREEN", 1024}, {"RAYTRACING", 2048}, {"GPU_CULLING", 4096}
    };

    map<string, unsigned long long> valeurs;
    for (const auto& p : simples) valeurs[p.first] = p.second;
    valeurs["NONE"] = 0;
    valeurs["2D_ESSENTIALS"] = 1 | 4;
    valeurs["3D_BASE"] = 2 | 16 | 32;
    valeurs["DEBUG"] = 256 | 512;
    valeurs["ALL"] = 4294967295ULL;

    const vector<Dependance> dependances = {
        {"TEXT", 4, {"RENDER2D"}},
        {"UI", 8, {"RENDER2D", "TEXT"}},
        {"SHADOW", 16, {"RENDER3D"}},
        {"OVERLAY", 256, {"RENDER2D", "TEXT"}}
    };

    int n;
    cin >> n;

    unsigned long long valeur = 0;

    for (int i = 0; i < n; i++) {
        string nom;
        cin >> nom;
        map<string, unsigned long long>::const_iterator it = valeurs.find(nom);
        if (it == valeurs.end()) {
            cout << "INCONNU " << nom << "\n";
        } else {
            valeur |= it->second;
        }
    }

    if (n == 0) valeur = valeurs["ALL"];

    cout << "VALEUR " << valeur << "\n";
    cout << "HEXA 0x" << hex << uppercase << setfill('0') << setw(8) << valeur << dec << nouppercase << setfill(' ') << "\n";

    for (const Dependance& d : dependances) {
        if ((valeur & d.valeur) == 0) continue;
        for (const string& besoin : d.besoins) {
            if ((valeur & valeurs[besoin]) == 0) {
                cout << "MANQUE " << d.nom << " " << besoin << "\n";
            }
        }
    }

    int allumes = 0;
    for (const auto& p : simples) {
        if (valeur & p.second) allumes++;
    }

    cout << "ALLUMES " << allumes << "\n";
    cout << "ETEINTS " << 13 - allumes << "\n";
    return 0;
}
