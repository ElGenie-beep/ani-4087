#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {
    const map<string, unsigned long long> valeurs = {
        {"RENDER2D", 1}, {"RENDER3D", 2}, {"TEXT", 4}, {"UI", 8},
        {"SHADOW", 16}, {"POST_PROCESS", 32}, {"ALL", 4294967295ULL}
    };

    long long medianes[2] = {0, 0};
    long long moyennes[2] = {0, 0};

    for (int c = 0; c < 2; c++) {
        string nom;
        int k;
        cin >> nom >> k;

        unsigned long long valeur = 0;
        for (int i = 0; i < k; i++) {
            string drapeau;
            cin >> drapeau;
            map<string, unsigned long long>::const_iterator it = valeurs.find(drapeau);
            if (it != valeurs.end()) valeur |= it->second;
        }

        vector<long long> temps(10);
        long long somme = 0;
        for (int i = 0; i < 10; i++) {
            cin >> temps[i];
            somme += temps[i];
        }
        sort(temps.begin(), temps.end());

        medianes[c] = (temps[4] + temps[5]) / 2;
        moyennes[c] = somme / 10;

        cout << nom << " VALEUR " << valeur << "\n";
        cout << nom << " MEDIANE " << medianes[c] << "\n";
        cout << nom << " MOYENNE " << moyennes[c] << "\n";
    }

    cout << "ECART MEDIANES " << medianes[0] - medianes[1] << "\n";
    cout << "ECART MOYENNES " << moyennes[0] - moyennes[1] << "\n";
    return 0;
}
