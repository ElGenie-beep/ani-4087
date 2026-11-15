#include <iostream>
#include <string>

int main() {
    int n = 0, t = 0;
    std::cin >> n >> t;

    if (n < 1 || n > 4) {
        std::cout << "CHAINE REFUSEE\n";
        return 0;
    }

    std::string signes;
    if (t > 0) {
        std::cin >> signes;
    }

    int prochaine = 0;  // index de l'image a emprunter (anneau)
    int fins = 0, rendues = 0, sautees = 0;

    for (int i = 1; i <= t; ++i) {
        ++fins;  // une fin de trame par image, rendue ou non
        if (signes[i - 1] == '1') {
            std::cout << i << " OUI 1 " << (i - 1) << " " << prochaine << "\n";
            prochaine = (prochaine + 1) % n;
            ++rendues;
        } else {
            std::cout << i << " NON 0\n";
            ++sautees;
        }
    }

    std::cout << "FINS " << fins << "\n";
    std::cout << "RENDUES " << rendues << "\n";
    std::cout << "SAUTEES " << sautees << "\n";
    std::cout << "PROCHAINE " << prochaine << "\n";
    return 0;
}


 //Resultat execution 
 //1 OUI 1 0 0
 //2 OUI 1 1 1
 //3 NON 0
 //4 NON 0
 //5 OUI 1 4 2
 //6 OUI 1 5 0
 //FINS 6
 //RENDUES 4
 //SAUTEES 2
 //PROCHAINE 1
