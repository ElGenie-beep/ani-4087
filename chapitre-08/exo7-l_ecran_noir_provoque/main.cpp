#include <iostream>
#include <string>

int main() {
    int total = 0;  // nombre d'ordres
    std::cin >> total;

    // La première cible reçoit la poignée 101, la suivante 102, etc.
    unsigned long long prochainePoignee = 101;

    // Avant la première cible, la poignée courante vaut 0
    unsigned long long poigneeCourante = 0;

    // Ce que la chaîne a rangé à l'index 0 (rien au départ)
    unsigned long long indexZero = 0;

    int numeroImage = 0;
    int affichees = 0;
    int noires = 0;
    int perimees = 0;

    for (int i = 0; i < total; ++i) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "cible") {
            unsigned long long largeur = 0;
            unsigned long long hauteur = 0;
            std::cin >> largeur >> hauteur;
            // Nouvelle cible : elle remplace la précédente
            poigneeCourante = prochainePoignee;
            ++prochainePoignee;
            std::cout << "CIBLE " << poigneeCourante << " " << largeur << " "
                      << hauteur << "\n";
        } else if (ordre == "chaine") {
            // On détruit la chaîne et on en crée une neuve : son tableau
            // est plein de zéros, il faudra réenregistrer
            indexZero = 0;
        } else if (ordre == "enregistre") {
            // On range la poignée de la cible COURANTE, pas la première
            indexZero = poigneeCourante;
        } else if (ordre == "image") {
            ++numeroImage;
            // Le rendu est toujours juste. Ce qui compte, c'est ce que
            // la chaîne soumet : la valeur rangée à l'index 0.
            if (indexZero == 0) {
                std::cout << "IMAGE " << numeroImage << " NOIR\n";
                ++noires;
            } else if (indexZero == poigneeCourante) {
                std::cout << "IMAGE " << numeroImage << " AFFICHE " << indexZero << "\n";
                ++affichees;
            } else {
                // Une ancienne cible : la poignée existe mais n'est plus la bonne
                std::cout << "IMAGE " << numeroImage << " PERIMEE " << indexZero << "\n";
                ++perimees;
            }
        }
    }

    // Bilan, affiché même si total vaut 0
    std::cout << "AFFICHEES " << affichees << "\n";
    std::cout << "NOIRES " << noires << "\n";
    std::cout << "PERIMEES " << perimees << "\n";
    return 0;
}


  // resultat  execution
// CIBLE 101 1440 1584
// IMAGE 1 AFFICHE 101
// CIBLE 102 1600 1760
// IMAGE 2 NOIR
// IMAGE 3 AFFICHE 102
// AFFICHEES 2
// NOIRES 1
// PERIMEES 0

