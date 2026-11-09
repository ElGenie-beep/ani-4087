#include <iostream>
#include <string>

int main() {
    int t = 0;
    std::cin >> t;

    std::string signes;
    if (t > 0) {
        std::cin >> signes;
    }

    int appuis = 0, relaches = 0, fauxRelaches = 0, tenues = 0;
    int precedent = 0;  // current avant l'image 1

    for (int i = 0; i < t; ++i) {
        char c = signes[i];
        int active = (c == 'x') ? 0 : 1;
        int current = (c == '1') ? 1 : 0;
        int changed = (current != precedent) ? 1 : 0;
        precedent = current;

        if (current == 1 && changed == 1) ++appuis;
        if (current == 0 && changed == 1) {
            ++relaches;
            if (active == 0) ++fauxRelaches;
        }
        if (current == 1) ++tenues;

        std::cout << (i + 1) << " " << current << " " << changed << " "
                  << active << "\n";
    }

    std::cout << "APPUIS " << appuis << "\n";
    std::cout << "RELACHES " << relaches << "\n";
    std::cout << "FAUX RELACHES " << fauxRelaches << "\n";
    std::cout << "TENUES " << tenues << "\n";
    return 0;
}


// Resultat execution
// 1 0 0 1
// 2 1 1 1
// 3 1 0 1
// 4 1 0 1
// 5 0 1 1
// 6 0 0 0
// 7 1 1 1
// 8 0 1 0
// APPUIS 2
// RELACHES 2
// FAUX RELACHES 1
// TENUES 4
