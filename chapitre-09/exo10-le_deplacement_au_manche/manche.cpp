#include <iostream>
#include <set>
#include <string>

int main() {
    long long v = 0;
    int t = 0;
    std::cin >> v >> t;

    // Avant et droite au sol (az, dz inclus) pour chaque lacet k
    const int avantX[4]  = {0, -1, 0, 1};
    const int avantZ[4]  = {-1, 0, 1, 0};
    const int droiteX[4] = {1, 0, -1, 0};
    const int droiteZ[4] = {0, -1, 0, 1};

    long long decX = 0, decZ = 0;  // decalage du monde : la tete n'est jamais modifiee
    int diagonales = 0;

    for (int f = 1; f <= t; ++f) {
        int k = 0, n = 0;
        std::cin >> k >> n;
        std::set<std::string> tenues;
        for (int i = 0; i < n; ++i) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        int x = 0, y = 0;
        if (tenues.count("F_DROITE")) x += 1;
        if (tenues.count("F_GAUCHE")) x -= 1;
        if (tenues.count("F_HAUT")) y += 1;
        if (tenues.count("F_BAS")) y -= 1;
        if (x != 0 && y != 0) ++diagonales;

        int lacet = k % 4;
        decX += v * (y * avantX[lacet] + x * droiteX[lacet]);
        decZ += v * (y * avantZ[lacet] + x * droiteZ[lacet]);

        std::cout << f << " " << x << "," << y << " " << decX << " " << decZ << "\n";
    }

    std::cout << "DECALAGE " << decX << " " << decZ << "\n";
    std::cout << "DIAGONALES " << diagonales << "\n";
    return 0;
}
