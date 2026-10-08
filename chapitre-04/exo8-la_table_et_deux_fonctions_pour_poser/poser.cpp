#include <iostream>
#include <string>
using namespace std;

struct Point {
    long long x, y, z;
};

Point PoserAuSol(long long sy, long long x, long long z) {
    return {x, sy / 2, z};
}

Point PoserSurTable(long long sy, long long hauteurDessus, long long x, long long z) {
    return {x, hauteurDessus + sy / 2, z};
}

void Afficher(const string& nom, const Point& p) {
    cout << nom << " " << p.x << " " << p.y << " " << p.z << "\n";
}

int main() {
    long long L, P, H, ep, pied, tx, tz;
    cin >> L >> P >> H >> ep >> pied >> tx >> tz;

    Afficher("PLATEAU", PoserSurTable(ep, H - ep, tx, tz));

    long long dx = L / 2 - pied;
    long long dz = P / 2 - pied;
    long long hauteurPied = H - ep;
    Afficher("PIED", PoserAuSol(hauteurPied, tx - dx, tz - dz));
    Afficher("PIED", PoserAuSol(hauteurPied, tx + dx, tz - dz));
    Afficher("PIED", PoserAuSol(hauteurPied, tx - dx, tz + dz));
    Afficher("PIED", PoserAuSol(hauteurPied, tx + dx, tz + dz));

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string nom, ou;
        long long sx, sy, sz, x, z;
        cin >> nom >> sx >> sy >> sz >> x >> z >> ou;
        if (ou == "TABLE") Afficher(nom, PoserSurTable(sy, H, x, z));
        else Afficher(nom, PoserAuSol(sy, x, z));
    }
    return 0;
}
