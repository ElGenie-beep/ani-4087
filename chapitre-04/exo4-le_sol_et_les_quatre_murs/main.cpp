#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Rect {
    long long xmin, xmax, zmin, zmax;
};

int main() {
    long long L, e;
    cin >> L >> e;

    int n;
    cin >> n;

    vector<Rect> murs;

    for (int i = 0; i < n; i++) {
        string nom;
        long long cx, cz, sx, sz;
        cin >> nom >> cx >> cz >> sx >> sz;

        Rect r;
        r.xmin = cx - sx / 2;
        r.xmax = cx + sx / 2;
        r.zmin = cz - sz / 2;
        r.zmax = cz + sz / 2;
        murs.push_back(r);

        cout << nom << " " << r.xmin << " " << r.xmax << " " << r.zmin << " " << r.zmax << "\n";
    }

    long long h = L / 2;

    const string noms[4] = {"FOND_GAUCHE", "FOND_DROIT", "ENTREE_GAUCHE", "ENTREE_DROIT"};
    const Rect angles[4] = {
        {-h - e, -h, -h - e, -h},
        {h, h + e, -h - e, -h},
        {-h - e, -h, h, h + e},
        {h, h + e, h, h + e}
    };

    int trous = 0;

    for (int a = 0; a < 4; a++) {
        bool bouche = false;
        for (const Rect& m : murs) {
            if (m.xmin <= angles[a].xmin && m.xmax >= angles[a].xmax &&
                m.zmin <= angles[a].zmin && m.zmax >= angles[a].zmax) {
                bouche = true;
                break;
            }
        }
        if (!bouche) trous++;
        cout << noms[a] << " " << (bouche ? "BOUCHE" : "TROU") << "\n";
    }

    cout << "TROUS " << trous << "\n";
    return 0;
}
