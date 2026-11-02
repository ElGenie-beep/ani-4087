#include <iostream>
#include <string>
#include <vector>

int main() {
    // La fenêtre, le nombre de tampons de commandes, le nombre d'ordres
    long long largeurFenetre = 0;
    long long hauteurFenetre = 0;
    int tampons = 0;  // F : 1, 2 ou 3
    int total = 0;
    std::cin >> largeurFenetre >> hauteurFenetre >> tampons >> total;

    // Au départ : rien n'est allumé, aucune cible, on dessine vers la fenêtre,
    // et la zone de rendu vaut la taille de la fenêtre
    bool offscreenAllume = false;
    int destination = 0;  // 0 = la fenêtre, k = la cible numéro k
    long long zoneLargeur = largeurFenetre;
    long long zoneHauteur = hauteurFenetre;

    // Les cibles créées : on range leurs tailles, la cible k est à l'index k
    // (l'index 0 est inutilisé pour que les numéros commencent à 1)
    std::vector<long long> ciblesLargeur(1, 0);
    std::vector<long long> ciblesHauteur(1, 0);

    // Un tampon est "pris" si son travail ne s'est jamais terminé
    std::vector<bool> pris(tampons, false);

    int numeroImage = 0;  // les images sont numérotées à partir de 1
    int imagesAffichees = 0;
    bool fige = false;    // une fois bloqué, plus rien n'agit

    for (int i = 0; i < total; ++i) {
        std::string ordre;
        std::cin >> ordre;

        // On lit toujours les arguments, même figé, pour rester synchronisé
        // avec le flux d'entrée
        if (ordre == "allume") {
            std::string nom;
            std::cin >> nom;
            if (!fige && nom == "OFFSCREEN") {
                offscreenAllume = true;
            }
        } else if (ordre == "cible") {
            long long w = 0;
            long long h = 0;
            std::cin >> w >> h;
            if (fige) {
                continue;
            }
            if (!offscreenAllume) {
                // Sans le bon sous-système, la cible n'existe pas
                std::cout << "CIBLE NULLE\n";
            } else {
                ciblesLargeur.push_back(w);
                ciblesHauteur.push_back(h);
                const int numero = static_cast<int>(ciblesLargeur.size()) - 1;
                std::cout << "CIBLE " << numero << " " << w << " " << h << "\n";
            }
        } else if (ordre == "vers") {
            long long k = 0;
            std::cin >> k;
            if (fige) {
                continue;
            }
            const long long nombreDeCibles =
                static_cast<long long>(ciblesLargeur.size()) - 1;
            if (k == 0 || (k >= 1 && k <= nombreDeCibles)) {
                destination = static_cast<int>(k);
            } else {
                // Cible inconnue : on refuse et on ne change rien
                std::cout << "VERS REFUSE\n";
            }
        } else if (ordre == "taille") {
            long long w = 0;
            long long h = 0;
            std::cin >> w >> h;
            if (!fige) {
                zoneLargeur = w;
                zoneHauteur = h;
            }
        } else if (ordre == "image") {
            if (fige) {
                continue;
            }
            ++numeroImage;
            const int tampon = (numeroImage - 1) % tampons;

            if (pris[tampon]) {
                // Le moteur veut réutiliser son tampon, le trouve encore
                // en cours, et attend pour toujours
                std::cout << "BLOQUE " << numeroImage << "\n";
                fige = true;
            } else {
                if (destination == 0) {
                    std::cout << "IMAGE " << numeroImage << " FENETRE\n";
                } else {
                    std::cout << "IMAGE " << numeroImage << " CIBLE " << destination
                              << "\n";
                    // La zone dépasse la cible en largeur OU en hauteur :
                    // Rien d'autre ne le montre pour l'instant.
                    if (zoneLargeur > ciblesLargeur[destination] ||
                        zoneHauteur > ciblesHauteur[destination]) {
                        pris[tampon] = true;
                    }
                }
                ++imagesAffichees;
            }
        }
    }

    // Bilan, affiché même si total vaut 0
    std::cout << "IMAGES " << imagesAffichees << "\n";
    std::cout << "ETAT " << (fige ? "BLOQUE" : "LIBRE") << "\n";
    return 0;
}


// resultat execution 
// IMAGE 1 FENETRE
// CIBLE NULLE
// CIBLE 1 640 720
// IMAGE 2 CIBLE 1
// IMAGE 3 CIBLE 1
// BLOQUE 4
// IMAGES 3
// ETAT BLOQUE
