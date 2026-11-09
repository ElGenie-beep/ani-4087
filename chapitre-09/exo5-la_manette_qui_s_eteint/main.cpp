#include <iostream>
#include <string>

int main() {
    int t = 0;
    std::cin >> t;

    std::string signes;
    if (t > 0) {
        std::cin >> signes;
    }

    bool avec = false;    // version AVEC le test de active
    bool sans = false;    // version SANS le test de active
    bool tombe = false;   // l'objet de la version SANS est par terre
    int precedent = 0;    // current avant l'image 1
    int prisesAvec = 0, prisesSans = 0, chutesSans = 0;
    int coinces = 0, differences = 0;

    for (int i = 0; i < t; ++i) {
        char c = signes[i];
        int active = (c == 'x') ? 0 : 1;
        int current = (c == '1') ? 1 : 0;
        int changed = (current != precedent) ? 1 : 0;
        precedent = current;

        // Version AVEC : rien ne change si l'action est inactive
        if (active == 1) {
            if (current == 1 && changed == 1) {
                avec = true;
                ++prisesAvec;
            } else if (current == 0 && changed == 1) {
                avec = false;
            }
        }

        // Version SANS : pas de test de active
        if (current == 1 && changed == 1) {
            if (!tombe) {
                sans = true;
                ++prisesSans;
            }
        } else if (current == 0 && changed == 1) {
            if (active == 0 && sans) {
                ++chutesSans;
                tombe = true;
            }
            sans = false;
        }

        if (c == '0' && avec) ++coinces;
        if (avec != sans) ++differences;

        std::cout << (i + 1) << " " << (avec ? "TENU" : "LIBRE") << " "
                  << (sans ? "TENU" : "LIBRE") << "\n";
    }

    std::cout << "PRISES AVEC " << prisesAvec << "\n";
    std::cout << "PRISES SANS " << prisesSans << "\n";
    std::cout << "CHUTES SANS " << chutesSans << "\n";
    std::cout << "COINCES AVEC " << coinces << "\n";
    std::cout << "DIFFERENCES " << differences << "\n";
    return 0;
}

// Resultat d'execution
//PS C:\Users\EL GENIE\Desktop\Rihen 1\chapitre-09\exo5-la_manette_qui_s_eteint> "9`n011xx0011" | .\programme.exe
//1 LIBRE LIBRE
//2 TENU TENU
//3 TENU TENU
//4 TENU LIBRE
//5 TENU LIBRE
//6 TENU LIBRE
//7 TENU LIBRE
//8 TENU LIBRE
//9 TENU LIBRE
//PRISES AVEC 2
//PRISES SANS 1
//CHUTES SANS 1
//COINCES AVEC 2
//DIFFERENCES 6
//PS C:\Users\EL GENIE\Desktop\Rihen 1\chapitre-09\exo5-la_manette_qui_s_eteint> "0" | .\programme.exe
//>> "3`n1x1" | .\programme.exe
//PRISES AVEC 0
//PRISES SANS 0
//CHUTES SANS 0
//COINCES AVEC 0
//DIFFERENCES 0
//1 TENU TENU
//2 TENU LIBRE
//3 TENU LIBRE
//PRISES AVEC 2
//PRISES SANS 1
//CHUTES SANS 1
//COINCES AVEC 0
//DIFFERENCES 2
