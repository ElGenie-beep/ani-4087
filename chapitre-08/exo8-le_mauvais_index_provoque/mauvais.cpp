// Exo 8 : le mauvais index, provoqué

#include <iostream>
#include <string>
#include <vector>

int main() {
    long long n = 0;   // nombre d'images de la chaîne (1 à 4)
    long long T = 0;   // nombre de trames
    long long x0 = 0;  // position de départ de la caméra (mm)
    long long v = 0;   // pas de la caméra à chaque trame (mm)
    std::cin >> n >> T >> x0 >> v;

    std::string modes;  // une lettre par trame : A, P ou D
    if (T > 0) {
        std::cin >> modes;
    }

    // Chaque emplacement garde le numéro de la dernière trame peinte dedans,
    // 0 au départ (rien n'y a encore été peint)
    std::vector<long long> emplacement(static_cast<size_t>(n), 0);
    long long prochaine = 0;  // la prochaine image à emprunter

    bool precedenteMontree = false; 
    long long positionPrecedente = 0;

    bool auMoinsUnSaut = false;
    long long sautMin = 0;
    long long sautMax = 0;

    for (long long t = 1; t <= T; ++t) {
        const char mode = modes[static_cast<size_t>(t - 1)];

        // 1) On emprunte la prochaine image et on y peint la trame t
        const long long empruntee = prochaine;
        emplacement[static_cast<size_t>(empruntee)] = t;

        // 2) En mode P, l'index soumis est lu ICI, avant la libération
        long long soumis = 0;
        if (mode == 'P') {
            soumis = (prochaine + n - 1) % n;
        }

        // 3) On rend l'image : la prochaine avance d'un cran
        prochaine = (prochaine + 1) % n;

        // 4) En mode D, l'index soumis est lu ICI, après la libération.
        //    En mode A, on soumet simplement l'index emprunté.
        if (mode == 'D') {
            soumis = (prochaine + n - 1) % n;
        } else if (mode == 'A') {
            soumis = empruntee;
        }

        // 5) La trame montrée est celle que garde l'emplacement soumis
        const long long f = emplacement[static_cast<size_t>(soumis)];

        if (f == 0) {
            // Rien n'a jamais été peint dans cet emplacement : écran noir
            std::cout << t << " NOIR -\n";
            precedenteMontree = false;
        } else {
            // La position montrée est celle de la caméra à la trame f
            const long long position = x0 + v * f;
            std::cout << t << " " << position << " ";

            if (t == 1 || !precedenteMontree) {
                std::cout << "-\n";
            } else {
                const long long saut = position - positionPrecedente;
                std::cout << saut << "\n";
                if (!auMoinsUnSaut) {
                    sautMin = saut;
                    sautMax = saut;
                    auMoinsUnSaut = true;
                } else {
                    if (saut < sautMin) {
                        sautMin = saut;
                    }
                    if (saut > sautMax) {
                        sautMax = saut;
                    }
                }
            }
            precedenteMontree = true;
            positionPrecedente = position;
        }
    }

    // Bilan : seul un saut qui varie fait trembler l'image
    if (!auMoinsUnSaut) {
        std::cout << "SAUTS AUCUN\n";
    } else {
        std::cout << "SAUT MIN " << sautMin << "\n";
        std::cout << "SAUT MAX " << sautMax << "\n";
        std::cout << "TREMBLE " << (sautMin != sautMax ? "OUI" : "NON") << "\n";
    }
    return 0;
}

