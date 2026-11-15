#include <iostream>
#include <string>

int main() {
    int k = 0, n = 0;
    std::cin >> k >> n;

    bool ouverte = false;           // drapeau "trame ouverte"
    int index[2] = {0, 0};          // index d'image de chaque chaine (0 = G, 1 = D)
    bool empruntee[2] = {false, false};
    int journal = 0, avertissements = 0, silencieux = 0;

    for (int i = 1; i <= n; ++i) {
        std::string appel;
        std::cin >> appel;
        std::cout << i << " " << appel << " ";

        if (appel == "wait") {
            if (ouverte) {
                std::cout << "REFUSE\n";
                ++journal;
            } else {
                std::cout << "OK\n";
            }
        } else if (appel == "begin") {
            if (ouverte) {
                std::cout << "REFUSE\n";
                ++journal;
            } else {
                std::cout << "OK\n";
                ouverte = true;
            }
        } else if (appel == "acquire") {
            std::string oeil;
            std::cin >> oeil;
            int e = (oeil == "G") ? 0 : 1;
            if (empruntee[e]) {
                std::cout << "REFUSE\n";
                ++silencieux;
            } else {
                std::cout << "OK " << index[e] << "\n";
                empruntee[e] = true;
            }
        } else if (appel == "release") {
            std::string oeil;
            std::cin >> oeil;
            int e = (oeil == "G") ? 0 : 1;
            if (!empruntee[e]) {
                std::cout << "REFUSE\n";
                ++silencieux;
            } else {
                std::cout << "OK\n";
                empruntee[e] = false;
                index[e] = (index[e] + 1) % k;
            }
        } else if (appel == "end") {
            std::string a;
            std::cin >> a;
            bool projection = (a != "-");
            bool renseigne[2] = {false, false};
            if (projection) {
                std::string b;
                std::cin >> b;
                renseigne[0] = (a == "1");
                renseigne[1] = (b == "1");
            }

            if (!ouverte) {
                std::cout << "REFUSE AUCUNE\n";
                ++journal;
            } else {
                ouverte = false;  // la trame se ferme dans tous les cas
                int bloque = -1;
                if (projection) {
                    for (int e = 0; e < 2 && bloque < 0; ++e) {
                        if (renseigne[e] && empruntee[e]) bloque = e;
                    }
                }
                if (bloque >= 0) {
                    std::cout << "REFUSE ACQUISE " << (bloque == 0 ? "G" : "D") << "\n";
                    ++journal;
                } else {
                    std::cout << "OK";
                    if (projection) {
                        if (!renseigne[0]) {
                            std::cout << (avertissements >= 0 ? " AVERT G" : "");
                            ++avertissements;
                        }
                        if (!renseigne[1]) {
                            std::cout << (renseigne[0] ? " AVERT D" : " D");
                            ++avertissements;
                        }
                    }
                    std::cout << "\n";
                }
            }
        }
    }

    std::cout << "JOURNAL " << journal << "\n";
    std::cout << "AVERTISSEMENTS " << avertissements << "\n";
    std::cout << "SILENCIEUX " << silencieux << "\n";
    return 0;
}

//Resultat execution

//1 wait OK
//2 begin OK
//3 acquire OK 0
//4 release OK
//5 acquire OK 0
//6 release OK
//7 end OK
//8 wait OK
//9 begin OK
//10 acquire OK 1
//11 release OK
//12 end OK AVERT D
//JOURNAL 0
//AVERTISSEMENTS 1
//SILENCIEUX 0
