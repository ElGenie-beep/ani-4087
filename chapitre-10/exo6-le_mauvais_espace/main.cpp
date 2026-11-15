#include <iostream>
struct Pose {
    long long x, y, z;
    int k;
};

// Tourne (x, z) de k quarts de tour ; y ne tourne pas
static void tourner(long long x, long long z, int k, long long& rx, long long& rz) {
    switch (k % 4) {
        case 0: rx = x;  rz = z;  break;
        case 1: rx = z;  rz = -x; break;
        case 2: rx = -x; rz = -z; break;
        default: rx = -z; rz = x; break;
    }
}

// Ancre composee avec une pose : passage de LOCAL a STAGE
static Pose composer(const Pose& a, const Pose& p) {
    long long rx = 0, rz = 0;
    tourner(p.x, p.z, a.k, rx, rz);
    return Pose{a.x + rx, a.y + p.y, a.z + rz, (a.k + p.k) % 4};
}

int main() {
    Pose ancre = {0, 0, 0, 0};
    std::cin >> ancre.x >> ancre.y >> ancre.z >> ancre.k;

    int n = 0;
    std::cin >> n;

    int justes = 0, fausses = 0;
    for (int i = 1; i <= n; ++i) {
        char d = 'S', c = 'S';
        Pose p = {0, 0, 0, 0};
        std::cin >> d >> c >> p.x >> p.y >> p.z >> p.k;

        Pose vraie = (d == 'S') ? p : composer(ancre, p);
        Pose crue = (c == 'S') ? p : composer(ancre, p);

        long long dx = crue.x - vraie.x;
        long long dy = crue.y - vraie.y;
        long long dz = crue.z - vraie.z;
        int dk = (crue.k - vraie.k + 4) % 4;

        if (dx == 0 && dy == 0 && dz == 0 && dk == 0) ++justes;
        else ++fausses;

        std::cout << i << " CRU " << crue.x << " " << crue.y << " " << crue.z
                  << " " << crue.k << "\n";
        std::cout << i << " ECART " << dx << " " << dy << " " << dz << " "
                  << dk << "\n";
    }

    std::cout << "JUSTES " << justes << "\n";
    std::cout << "FAUSSES " << fausses << "\n";
    return 0;
}

//RESULTAT EXECUTION

//1 CRU 100 1700 -200 0
//1 ECART 0 0 0 0
//2 CRU 100 3400 -200 0
//2 ECART 0 1700 0 0
//3 CRU 0 0 0 0
//3 ECART 0 -1700 0 0
//4 CRU 50 1700 -300 1
//4 ECART 0 0 0 0
//JUSTES 2
//FAUSSES 2
