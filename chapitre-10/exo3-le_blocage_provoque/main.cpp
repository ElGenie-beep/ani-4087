#include <iostream>
#include <string>

int main() {
    std::string p;
    int t = 0;
    std::cin >> p >> t;

    std::string signes;
    if (t > 0) {
        std::cin >> signes;
    }

    bool ouverte = false;  // drapeau "trame ouverte"
    int rendues = 0, perdues = 0, erreurs = 0;
    int premierRefus = 0;  // 0 = AUCUN

    for (int i = 1; i <= t; ++i) {
        bool runtimeRend = (signes[i - 1] == '1');
        bool rendre = false;  // etat neuf

        // WaitFrame
        bool waitOk = !ouverte;
        if (waitOk) {
            rendre = runtimeRend;
        } else {
            ++erreurs;
            if (premierRefus == 0) premierRefus = i;
        }

        // BeginFrame
        bool beginOk = !ouverte;
        if (beginOk) {
            ouverte = true;
        } else {
            ++erreurs;
        }

        if (rendre) ++rendues;
        else if (runtimeRend) ++perdues;

        // EndFrame
        std::string e = "-";
        if (p == "TOUJOURS" || rendre) {
            if (ouverte) {
                ouverte = false;
                e = "OK";
            } else {
                e = "REFUSE";
                ++erreurs;
            }
        }

        std::cout << i << " " << (waitOk ? "OK" : "REFUSE") << " "
                  << (beginOk ? "OK" : "REFUSE") << " "
                  << (rendre ? "OUI" : "NON") << " " << e << "\n";
    }

    std::cout << "RENDUES " << rendues << "\n";
    std::cout << "PERDUES " << perdues << "\n";
    std::cout << "ERREURS " << erreurs << "\n";
    if (premierRefus == 0) std::cout << "PREMIER REFUS AUCUN\n";
    else std::cout << "PREMIER REFUS " << premierRefus << "\n";
    return 0;
}

//Resultat execution
//1 OK OK OUI OK
//2 OK OK OUI OK
//3 OK OK NON -
//4 REFUSE REFUSE NON -
//5 REFUSE REFUSE NON -
//6 REFUSE REFUSE NON -
//RENDUES 2
//PERDUES 2
//ERREURS 6
//PREMIER REFUS 4
