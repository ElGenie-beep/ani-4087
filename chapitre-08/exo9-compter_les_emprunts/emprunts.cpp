// Exo 9 : compter les emprunts

#include <iostream>
#include <string>

int main() {
    int n = 0;      // nombre d'images de la chaîne (1 à 4)
    int total = 0;  // nombre de trames
    std::cin >> n >> total;

    bool empruntee = false;  // une image est-elle encore empruntée ?

    int reussies = 0;
    int refusees = 0;
    int liberations = 0;
    int premiereFuite = 0;  // 0 = aucune fuite pour l'instant

    for (int t = 1; t <= total; ++t) {
        std::string mot;
        std::cin >> mot;

        // Chaque trame commence par un emprunt
        if (empruntee) {
            // Refusé : une image est encore empruntée. La trame s'arrête là,
            // elle n'a rien emprunté donc elle ne rend rien.
            ++refusees;
            std::cout << t << " BLOQUEE\n";
            continue;
        }
        ++reussies;
        empruntee = true;

        if (mot == "normal") {
            // On dessine puis on rend l'image
            empruntee = false;
            ++liberations;
            std::cout << t << " OK\n";
        } else if (mot == "sortie") {
            // On sort juste après l'emprunt SANS rendre l'image : c'est la fuite
            if (premiereFuite == 0) {
                premiereFuite = t;
            }
            std::cout << t << " FUITE\n";
        } else if (mot == "double") {
            // Un second emprunt, refusé : il ne coûte rien à la chaîne,
            // mais il se compte. Puis on rend l'image.
            ++refusees;
            empruntee = false;
            ++liberations;
            std::cout << t << " DOUBLE\n";
        }
    }

    // Bilan. Chaque emprunt réussi devrait avoir sa libération : l'écart
    // vaut le nombre d'images jamais rendues.
    std::cout << "REUSSIES " << reussies << "\n";
    std::cout << "REFUSEES " << refusees << "\n";
    std::cout << "LIBERATIONS " << liberations << "\n";
    std::cout << "ECART " << (reussies - liberations) << "\n";
    if (premiereFuite == 0) {
        std::cout << "PREMIERE FUITE AUCUNE\n";
    } else {
        std::cout << "PREMIERE FUITE " << premiereFuite << "\n";
    }
    return 0;
}
