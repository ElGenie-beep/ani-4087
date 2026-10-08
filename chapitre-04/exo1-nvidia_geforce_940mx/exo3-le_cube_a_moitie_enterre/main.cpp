#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    int aCorriger = 0;
    long long pire = 0;

    for (int i = 0; i < n; i++) {
        string nom;
        long long e, y;
        cin >> nom >> e >> y;

        long long bas = y - e / 2;
        long long haut = y + e / 2;
        string verdict;

        if (haut <= 0) {
            verdict = "SOUS LE SOL";
        } else if (bas < 0) {
            verdict = "ENTERRE";
        } else if (bas == 0) {
            verdict = "POSE";
        } else {
            verdict = "FLOTTE";
        }

        if (verdict != "POSE") aCorriger++;

        long long ecart = bas < 0 ? -bas : bas;
        if (ecart > pire) pire = ecart;

        cout << nom << " " << bas << " " << haut << " " << verdict << " " << e / 2 << "\n";
    }

    cout << "A CORRIGER " << aCorriger << "\n";
    cout << "PIRE " << pire << "\n";
    return 0;
}
