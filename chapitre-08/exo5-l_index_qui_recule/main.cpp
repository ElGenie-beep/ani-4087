// Exo 5 : l'index qui recule
// Pour chaque chaîne (n images, r libérations déjà faites), on calcule
// l'index de la dernière image relâchée de trois façons :
//   - juste     : (prochaine + n - 1) % n   (l'écriture du moteur)
//   - signe     : (prochaine - 1) % n en int
//   - nonsigne  : (prochaine - 1) % n en uint32_t
// Puis on compte combien de fois chaque écriture se trompe.

#include <cstdint>
#include <iostream>

int main() {
    int total = 0;
    std::cin >> total;  // nombre de lignes à traiter

    long long refusees = 0;
    long long fauxSigne = 0;
    long long fauxNonSigne = 0;

    for (int i = 0; i < total; ++i) {
        // r peut dépasser un milliard : on lit tout sur 64 bits
        long long n = 0;
        long long r = 0;
        std::cin >> n >> r;

        // Une chaîne a entre 1 et 4 images, sinon elle n'existe pas
        if (n == 0 || n > 4) {
            std::cout << n << " " << r << " REFUSEE\n";
            ++refusees;
            continue;
        }

        // La prochaine image, calculée sur 64 bits
        const long long prochaine = r % n;

        // L'écriture du moteur : on ajoute n avant de reculer d'un cran,
        // donc le nombre reste positif même quand prochaine vaut 0
        const long long juste = (prochaine + n - 1) % n;

        // Écriture signée : quand prochaine vaut 0, on obtient -1,
        // et en C++ le reste d'un nombre négatif est négatif ou nul
        const int prochaineInt = static_cast<int>(prochaine);
        const int nInt = static_cast<int>(n);
        const int signe = (prochaineInt - 1) % nInt;

        // Écriture non signée : 0 - 1 donne 4294967295, qui "boucle"
        // et ne tombe juste que par chance (selon n)
        const std::uint32_t prochaineU = static_cast<std::uint32_t>(prochaine);
        const std::uint32_t nU = static_cast<std::uint32_t>(n);
        const std::uint32_t nonsigne = (prochaineU - 1u) % nU;

        std::cout << n << " " << r << " " << prochaine << " " << juste << " "
                  << signe << " " << nonsigne << "\n";

        // On compare chaque écriture à la bonne, en 64 bits signés
        if (static_cast<long long>(signe) != juste) {
            ++fauxSigne;
        }
        if (static_cast<long long>(nonsigne) != juste) {
            ++fauxNonSigne;
        }
    }

    // Bilan, affiché même si total vaut 0
    std::cout << "REFUSEES " << refusees << "\n";
    std::cout << "FAUX SIGNE " << fauxSigne << "\n";
    std::cout << "FAUX NON SIGNE " << fauxNonSigne << "\n";
    return 0;
}


// Résultat de l'exécution 
 // | Set-Content -Path entree.txt -Encoding ASCII; Get-Content entree.txt | .\programme.exe }
 // 3 0 0 2 -1 0
 // 3 1 1 0 0 0
 // 3 3 0 2 -1 0
// 2 4 0 1 -1 1
// 4 8 0 3 -1 3
// 1 5 0 0 0 0
// REFUSEES 0
// FAUX SIGNE 4
// FAUX NON SIGNE 2
