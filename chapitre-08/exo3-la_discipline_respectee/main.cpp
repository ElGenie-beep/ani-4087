#include <iostream>
#include <string>

int main() {
    unsigned int n = 0;  // nombre d'images de la chaîne (1 à 4)
    int total = 0;       // nombre d'ordres
    std::cin >> n >> total;

    unsigned int prochaine = 0;  // la prochaine image à prêter
    bool empruntee = false;      // une image est-elle empruntée ?
    unsigned int courante = 0;   // l'image actuellement empruntée
    bool dessinee = false;       // a-t-on dessiné dans l'image empruntée ?

    // Ce qu'il faut savoir sur la dernière image rendue
    bool renduePuisPasSoumise = false;  // un release a eu lieu depuis le dernier submit accepté
    bool derniereVide = false;          // la dernière image rendue n'a reçu aucun draw

    int soumises = 0;
    int refus = 0;
    int horsEmprunt = 0;

    for (int i = 0; i < total; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "acquire") {
            if (empruntee) {
                // Double emprunt : refusé
                std::cout << "ACQUIRE REFUSE\n";
                ++refus;
            } else {
                empruntee = true;
                courante = prochaine;
                dessinee = false;  // nouvelle image, rien dessiné dedans
                std::cout << "ACQUIRE " << courante << "\n";
            }
        } else if (ordre == "draw") {
            if (empruntee) {
                dessinee = true;
                std::cout << "DRAW " << courante << "\n";
            } else {
                // On dessine sans avoir emprunté : on le compte à part
                std::cout << "DRAW HORS EMPRUNT\n";
                ++horsEmprunt;
            }
        } else if (ordre == "release") {
            if (!empruntee) {
                // Rendre ce qui n'est pas emprunté : refusé,
                // et la prochaine image n'avance pas
                std::cout << "RELEASE REFUSE\n";
                ++refus;
            } else {
                derniereVide = !dessinee;  // image rendue sans aucun draw ?
                prochaine = (prochaine + 1) % n;
                empruntee = false;
                renduePuisPasSoumise = true;
                std::cout << "RELEASE OK\n";
            }
        } else if (ordre == "submit") {
            if (empruntee) {
                // On ne soumet pas pendant qu'on dessine encore
                std::cout << "SUBMIT REFUSE EMPRUNTEE\n";
                ++refus;
            } else if (!renduePuisPasSoumise) {
                // Rien de neuf à envoyer depuis la dernière soumission
                std::cout << "SUBMIT REFUSE RIEN\n";
                ++refus;
            } else {
                // La dernière image relâchée : on recule d'un cran
                const unsigned int j = (prochaine + n - 1) % n;
                std::cout << "SUBMIT " << j;
                if (derniereVide) {
                    std::cout << " VIDE";
                }
                std::cout << "\n";
                ++soumises;
                renduePuisPasSoumise = false;
            }
        }
    }

    // Bilan, affiché même si total vaut 0
    std::cout << "SOUMISES " << soumises << "\n";
    std::cout << "REFUS " << refus << "\n";
    std::cout << "HORS EMPRUNT " << horsEmprunt << "\n";
    return 0;
}

// RESULTAT EXECUTION 
// ACQUIRE 0
// DRAW 0
// RELEASE OK
// SUBMIT 0
// ACQUIRE 1
// ACQUIRE REFUSE
// DRAW 1
// SUBMIT REFUSE EMPRUNTEE
// RELEASE OK
// SUBMIT 1
// SUBMIT REFUSE RIEN
// DRAW HORS EMPRUNT
// SOUMISES 2
// REFUS 3
// HORS EMPRUNT 1
