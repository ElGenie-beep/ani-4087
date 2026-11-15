#include <cmath>
#include <iostream>

// Tourne (x, z) de k quarts de tour ; y ne tourne pas
static void tourner(long long x, long long z, int k, long long& rx, long long& rz) {
    switch (k % 4) {
        case 0: rx = x;  rz = z;  break;
        case 1: rx = z;  rz = -x; break;
        case 2: rx = -x; rz = -z; break;
        default: rx = -z; rz = x; break;
    }
}

int main() {
    long long ax = 0, ay = 0, az = 0;
    int ak = 0;
    std::cin >> ax >> ay >> az >> ak;

    long long ex = 0, ey = 0, ez = 0;
    std::cin >> ex >> ey >> ez;

    int n = 0;
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        char e = '-';
        long long x = 0, y = 0, z = 0, w = 0, h = 0;
        int k = 0;
        std::cin >> e >> x >> y >> z >> k >> w >> h;

        // Sans espace precise ('-'), le panneau est dans LOCAL
        bool stage = (e == 'S');
        long long cx = x, cy = y, cz = z;
        int ck = k % 4;
        if (!stage) {
            long long rx = 0, rz = 0;
            tourner(x, z, ak, rx, rz);
            cx = ax + rx;
            cy = ay + y;
            cz = az + rz;
            ck = (ak + k) % 4;
        }

        std::cout << "PANNEAU " << i << " " << (stage ? "STAGE" : "LOCAL") << "\n";

        const long long coinX[4] = {-w / 2, w / 2, w / 2, -w / 2};
        const long long coinY[4] = {-h / 2, -h / 2, h / 2, h / 2};
        for (int c = 0; c < 4; ++c) {
            long long rx = 0, rz = 0;
            tourner(coinX[c], 0, ck, rx, rz);
            std::cout << (cx + rx) << " " << (cy + coinY[c]) << " " << (cz + rz) << "\n";
        }

        double dx = static_cast<double>(cx - ex);
        double dy = static_cast<double>(cy - ey);
        double dz = static_cast<double>(cz - ez);
        long long d = std::llround(std::sqrt(dx * dx + dy * dy + dz * dz));
        std::cout << "DISTANCE " << d << "\n";
    }

    std::cout << "PANNEAUX " << n << "\n";
    return 0;
}

//Resultat execution

//PANNEAU 1 STAGE
//-150 1500 -1500
//150 1500 -1500
//150 1700 -1500
//-150 1700 -1500
//DISTANCE 1503
//PANNEAU 2 LOCAL
//-150 3200 -1500
//150 3200 -1500
//150 3400 -1500
//-150 3400 -1500
//DISTANCE 2193
//PANNEAUX 2
