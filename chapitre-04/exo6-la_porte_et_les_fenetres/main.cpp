#include <iostream>
#include <string>
using namespace std;

int main() {
    long long W, H, seuil;
    cin >> W >> H >> seuil;

    int n;
    cin >> n;

    int ok = 0;
    int aReprendre = 0;

    for (int i = 0; i < n; i++) {
        string nom;
        long long u, y, l, h, e, d;
        cin >> nom >> u >> y >> l >> h >> e >> d;

        long long saillie = d + e / 2;
        long long arriere = d - e / 2;
        string verdict;

        if (u - l / 2 < -W / 2 || u + l / 2 > W / 2 ||
            y - h / 2 < 0 || y + h / 2 > H) {
            verdict = "DEBORDE";
        } else if (saillie <= 0) {
            verdict = "INVISIBLE";
        } else if (saillie < seuil) {
            verdict = "CLIGNOTE";
        } else if (arriere > seuil) {
            verdict = "DECOLLE";
        } else {
            verdict = "OK";
        }

        if (verdict == "OK") ok++;
        else aReprendre++;

        cout << nom << " " << saillie << " " << verdict << "\n";
    }

    cout << "OK " << ok << "\n";
    cout << "A REPRENDRE " << aReprendre << "\n";
    return 0;
}
