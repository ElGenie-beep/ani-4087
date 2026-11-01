// Exo 2 : deux chaînes (une par oeil)
// acceptée ou refusée, puis on fait le bilan à la fin.

#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;  // nombre de chaînes à examiner

    // Les compteurs du bilan. Ils ne bougent que pour une chaîne ACCEPTÉE.
    long long acceptees = 0;
    long long occupes = 0;   // somme des images des chaînes acceptées
    long long gauche = 0;
    long long droit = 0;
    long long sansNom = 0;

    for (int i = 0; i < n; ++i) {
        long long largeur = 0;
        long long hauteur = 0;
        long long images = 0;
        int oeil = 0;  // 0 = gauche, 1 = droit
        std::string nom;
        std::cin >> largeur >> hauteur >> images >> oeil >> nom;

        // Le "-" veut dire "pas de nom". À l'écran on écrit SANS-NOM,
        // mais je garde le booléen pour compter SANS NOM dans le bilan.
        const bool pasDeNom = (nom == "-");
        const std::string affiche = pasDeNom ? "SANS-NOM" : nom;

        // Attention à l'ordre : la taille se contrôle AVANT le nombre
        // d'images (0 x 0 avec 0 image => TAILLE, pas IMAGES).
        if (largeur == 0 || hauteur == 0) {
            std::cout << "REFUSEE " << affiche << " TAILLE\n";
        } else if (images == 0 || images > 4) {
            // le maximum est 4, et 0 image n'a pas de sens non plus
            std::cout << "REFUSEE " << affiche << " IMAGES\n";
        } else {
            // Chaîne acceptée : on l'affiche puis on met à jour le bilan
            std::cout << "CHAINE " << affiche << " " << largeur << " " << hauteur
                      << " " << images << " " << (oeil == 0 ? "GAUCHE" : "DROIT")
                      << "\n";
            ++acceptees;
            occupes += images;
            if (oeil == 0) {
                ++gauche;
            } else {
                ++droit;
            }
            if (pasDeNom) {
                ++sansNom;
            }
        }
    }

    // Bilan. Même si n vaut 0, ces six lignes s'affichent (avec des 0).
    std::cout << "ACCEPTEES " << acceptees << "\n";
    // Chaque chaîne acceptée réserve un tableau fixe de 4 emplacements,
    // quel que soit son nombre d'images (c'est le prix du "zéro allocation").
    std::cout << "EMPLACEMENTS " << 4 * acceptees << "\n";
    std::cout << "OCCUPES " << occupes << "\n";
    std::cout << "GAUCHE " << gauche << "\n";
    std::cout << "DROIT " << droit << "\n";
    std::cout << "SANS NOM " << sansNom << "\n";
    return 0;
}


// Résultat de l'exécution  
// CHAINE oeil-gauche 1440 1584 1 GAUCHE
// CHAINE oeil-droit 1440 1584 1 DROIT
// REFUSEE essai TAILLE
// REFUSEE SANS-NOM IMAGES
// ACCEPTEES 2
// EMPLACEMENTS 8
// OCCUPES 2
// GAUCHE 1
// DROIT 1
// SANS NOM 0
