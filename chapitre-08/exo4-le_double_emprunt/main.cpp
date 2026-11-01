// Exo 4 : le double emprunt
// On simule AcquireImage, ReleaseImage et GetLastReleasedIndex sur une chaîne
// d'échange. Le point clé : un emprunt refusé ne touche PAS la variable de
// l'appelant, elle garde sa valeur d'avant.

#include <cstdint>
#include <iostream>
#include <string>

int main() {
    unsigned int n = 0;  // nombre d'images de la chaîne (1 à 4)
    std::uint32_t v = 0;  // valeur de départ des 26 variables (32 bits non signés)
    int total = 0;        // nombre d'ordres
    std::cin >> n >> v >> total;

    // Une variable par lettre de a à z, toutes à v au départ
    std::uint32_t variables[26];
    for (int i = 0; i < 26; ++i) {
        variables[i] = v;
    }

    unsigned int prochaine = 0;  // la prochaine image à prêter
    bool empruntee = false;      // est-ce qu'une image est déjà empruntée ?

    for (int i = 0; i < total; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "acquire") {
            char lettre = 'a';
            std::cin >> lettre;
            const int rang = lettre - 'a';  // 'a' -> 0, 'b' -> 1, ...

            if (empruntee) {
                // Refusé : on ne touche pas à la variable
                std::cout << "ACQUIRE FAUX " << lettre << " " << variables[rang] << "\n";
            } else {
                variables[rang] = prochaine;
                empruntee = true;
                std::cout << "ACQUIRE VRAI " << lettre << " " << variables[rang] << "\n";
            }
        } else if (ordre == "release") {
            if (!empruntee) {
                // On ne peut pas rendre ce qui n'est pas emprunté,
                // et la prochaine image n'avance pas
                std::cout << "RELEASE FAUX\n";
            } else {
                prochaine = (prochaine + 1) % n;
                empruntee = false;
                std::cout << "RELEASE VRAI\n";
            }
        } else if (ordre == "last") {
            // On recule d'un cran, en ajoutant n avant le modulo
            // pour ne jamais passer par un nombre négatif
            const unsigned int j = (prochaine + n - 1) % n;
            std::cout << "LAST " << j << "\n";
        }
    }

    // Bilan, affiché même si total vaut 0
    std::cout << "EMPRUNTEE " << (empruntee ? "OUI" : "NON") << "\n";
    std::cout << "PROCHAINE " << prochaine << "\n";
    return 0;
}


// Résultat de l'exécution
// LAST 2
// ACQUIRE VRAI a 0
// ACQUIRE FAUX b 99
// RELEASE VRAI
// RELEASE FAUX
// LAST 0
// ACQUIRE VRAI a 1
// ACQUIRE FAUX b 99
// LAST 0
// EMPRUNTEE OUI
// PROCHAINE 1
