#include <iostream>
#include <set>
#include <string>

int main() {
    // Tout est lu en 64 bits non signés : une poignée peut aller
    unsigned long long n = 0;  // nombre d'images de la chaîne (1 à 4)
    int total = 0;             // nombre d'ordres
    std::cin >> n >> total;

    // Les emplacements de la chaîne : 4 au maximum, tous à 0 au départ
    unsigned long long emplacements[4] = {0, 0, 0, 0};

    // Les textures qui existent en ce moment
    std::set<unsigned long long> textures;

    const unsigned long long maxSur32Bits = 4294967295UL;

    int mortes = 0;
    int larges = 0;

    for (int k = 0; k < total; ++k) {
        std::string ordre;
        std::cin >> ordre;

        if (ordre == "cree") {
            unsigned long long h = 0;
            std::cin >> h;
            textures.insert(h);  // sans effet si elle existe déjà
        } else if (ordre == "detruit") {
            unsigned long long h = 0;
            std::cin >> h;
            textures.erase(h);  // sans effet si elle n'existe pas
            // Attention : on ne vide PAS l'emplacement qui la contient
        } else if (ordre == "set") {
            unsigned long long i = 0;
            unsigned long long h = 0;
            std::cin >> i >> h;
            if (i >= n) {
                // Index hors de la chaîne : on ignore
                std::cout << "SET IGNORE " << i << "\n";
            } else {
                emplacements[i] = h;
                if (h > maxSur32Bits) {
                    ++larges;  // une poignée qui ne tient pas sur 32 bits
                }
            }
        } else if (ordre == "get") {
            unsigned long long i = 0;
            std::cin >> i;
            // Hors de la chaîne, on rend 0
            const unsigned long long h = (i >= n) ? 0 : emplacements[i];

            if (h == 0) {
                std::cout << "GET " << i << " 0 VIDE\n";
            } else if (textures.count(h) > 0) {
                // On vérifie l'existence AU MOMENT du get
                std::cout << "GET " << i << " " << h << " VIVANTE\n";
            } else {
                std::cout << "GET " << i << " " << h << " MORTE\n";
                ++mortes;
            }
        }
    }

    // Bilan, affiché même si total vaut 0
    std::cout << "MORTES " << mortes << "\n";
    std::cout << "LARGES " << larges << "\n";
    return 0;
}

 // Resultat execution 
//  SET IGNORE 2
// GET 0 7 VIVANTE
// GET 1 140737488355328 VIVANTE
// GET 0 7 MORTE
// GET 3 0 VIDE
// MORTES 1
// LARGES 1
