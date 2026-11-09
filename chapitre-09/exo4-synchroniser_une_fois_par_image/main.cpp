#include <iostream>

int main() {
    int t = 0;
    std::cin >> t;

    int current = 0, changed = 0, active = 0;
    int pPrecedent = 0;
    int appuisReels = 0, saisies = 0, refusees = 0;

    for (int i = 1; i <= t; ++i) {
        int p = 0, s = 0, f = 0;
        std::cin >> p >> s >> f;

        if (p == 1 && pPrecedent == 0) ++appuisReels;
        pPrecedent = p;

        for (int j = 0; j < s; ++j) {
            if (f == 0) {
                ++refusees;  // refuse : rien ne change
            } else {
                changed = (p != current) ? 1 : 0;
                current = p;
                active = 1;
            }
        }

        bool saisit = (current == 1 && changed == 1);
        if (saisit) ++saisies;

        std::cout << i << " " << current << " " << changed << " " << active
                  << " " << (saisit ? "SAISIT" : "-") << "\n";
    }

    std::cout << "APPUIS REELS " << appuisReels << "\n";
    std::cout << "SAISIES " << saisies << "\n";
    std::cout << "SYNC REFUSEES " << refusees << "\n";
    return 0;
}

  // Resultat execution
 // 1 0 0 1 -
 // 2 1 1 1 SAISIT
 // 3 1 1 1 SAISIT
 // 4 1 0 1 -
 // 5 0 0 1 -
 // 6 1 0 1 -
 // 7 1 0 1 -
 // 8 1 0 1 -
 // APPUIS REELS 2
 // SAISIES 2
 // SYNC REFUSEES 2
