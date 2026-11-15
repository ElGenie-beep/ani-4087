#include <iostream>
#include <string>

int main() {
    int t = 0;
    std::cin >> t;

    int justes = 0, fautives = 0;

    for (int img = 1; img <= t; ++img) {
        int n = 0;
        std::cin >> n;

        // Chaque image repart de zero
        bool attendu = false, commence = false, vues = false, fini = false;
        bool emprunte[2] = {false, false};
        int place = 0;
        std::string code;

        for (int p = 1; p <= n; ++p) {
            std::string appel;
            std::cin >> appel;
            if (place != 0) continue;  // apres la premiere faute, on ignore la suite

            std::string faute;
            if (fini) {
                faute = "APRES_END";
            } else if (appel == "WAIT") {
                if (commence) faute = "WAIT_APRES_BEGIN";
                else attendu = true;
            } else if (appel == "BEGIN") {
                if (commence) faute = "DOUBLE_BEGIN";
                else if (!attendu) faute = "BEGIN_SANS_WAIT";
                else commence = true;
            } else if (appel == "VUES") {
                if (!attendu) faute = "VUES_SANS_WAIT";
                else vues = true;
            } else if (appel == "PREND_G" || appel == "PREND_D") {
                int e = (appel == "PREND_G") ? 0 : 1;
                if (!commence) faute = "PREND_SANS_BEGIN";
                else if (!vues) faute = "PREND_SANS_VUES";
                else if (emprunte[e]) faute = "DOUBLE_PREND";
                else emprunte[e] = true;
            } else if (appel == "LACHE_G" || appel == "LACHE_D") {
                int e = (appel == "LACHE_G") ? 0 : 1;
                if (!emprunte[e]) faute = "LACHE_SANS_PREND";
                else emprunte[e] = false;
            } else if (appel == "END") {
                if (!commence) faute = "END_SANS_BEGIN";
                else if (emprunte[0] || emprunte[1]) faute = "END_IMAGE_PRISE";
                else fini = true;
            }

            if (!faute.empty()) {
                place = p;
                code = faute;
            }
        }

        if (place == 0 && !fini) {
            place = n + 1;
            code = "SANS_END";
        }

        if (place == 0) {
            std::cout << img << " OK\n";
            ++justes;
        } else {
            std::cout << img << " FAUTE " << place << " " << code << "\n";
            ++fautives;
        }
    }

    std::cout << "JUSTES " << justes << "\n";
    std::cout << "FAUTIVES " << fautives << "\n";
    return 0;
}

//Resultat execution

//1 OK
//2 OK
//3 FAUTE 7 END_IMAGE_PRISE
//4 FAUTE 1 VUES_SANS_WAIT
//JUSTES 2
//FAUTIVES 2
