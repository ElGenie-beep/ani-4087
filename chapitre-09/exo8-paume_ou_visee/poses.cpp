#include <cmath>
#include <iostream>
#include <vector>

struct Vec {
    long long x, y, z;
};

// Position locale (repere de la tete) -> salle.
// cote = +1 pour la droite, -1 pour la gauche : x change de signe AVANT la rotation.
static Vec versSalle(long long lx, long long ly, long long lz, int cote,
                     const Vec& tete, int k) {
    long long x = lx * cote;
    long long z = lz;
    long long rx = 0, rz = 0;
    switch (k % 4) {
        case 0: rx = x;  rz = z;  break;
        case 1: rx = z;  rz = -x; break;
        case 2: rx = -x; rz = -z; break;
        default: rx = -z; rz = x; break;
    }
    return Vec{tete.x + rx, tete.y + ly, tete.z + rz};
}

static long long dist2(const Vec& a, const Vec& b) {
    long long dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

// Numero (a partir de 1) de l'objet le plus proche a 150 mm au plus, 0 sinon
static int plusProche(const Vec& p, const std::vector<Vec>& objets) {
    int meilleur = 0;
    long long meilleureDist = 0;
    for (std::size_t i = 0; i < objets.size(); ++i) {
        long long d = dist2(p, objets[i]);
        if (d <= 22500 && (meilleur == 0 || d < meilleureDist)) {
            meilleur = static_cast<int>(i) + 1;
            meilleureDist = d;
        }
    }
    return meilleur;
}

static void afficher(const char* etiquette, const Vec& p) {
    std::cout << etiquette << " " << p.x << " " << p.y << " " << p.z << "\n";
}

static void afficherSaisie(const char* etiquette, int j) {
    std::cout << etiquette << " ";
    if (j == 0) std::cout << "AUCUNE";
    else std::cout << j;
    std::cout << "\n";
}

int main() {
    int h = 0, m = 0;
    std::cin >> h >> m;

    std::vector<Vec> tetes(h);
    std::vector<int> lacets(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> tetes[i].x >> tetes[i].y >> tetes[i].z >> lacets[i];
    }
    std::vector<Vec> objets(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> objets[i].x >> objets[i].y >> objets[i].z;
    }

    for (int i = 0; i < h; ++i) {
        Vec paumeD = versSalle(180, -300, -250, 1, tetes[i], lacets[i]);
        Vec viseeD = versSalle(180, -250, -400, 1, tetes[i], lacets[i]);
        Vec paumeG = versSalle(180, -300, -250, -1, tetes[i], lacets[i]);
        Vec viseeG = versSalle(180, -250, -400, -1, tetes[i], lacets[i]);

        std::cout << "TETE " << (i + 1) << "\n";
        afficher("PAUME D", paumeD);
        afficher("VISEE D", viseeD);
        afficher("PAUME G", paumeG);
        afficher("VISEE G", viseeG);
        afficherSaisie("SAISIE PAUME", plusProche(paumeD, objets));
        afficherSaisie("SAISIE VISEE", plusProche(viseeD, objets));
    }

    // Ecart paume droite / visee droite (identique pour toutes les tetes)
    Vec origine = {0, 0, 0};
    Vec p = versSalle(180, -300, -250, 1, origine, 0);
    Vec v = versSalle(180, -250, -400, 1, origine, 0);
    long long e = std::llround(std::sqrt(static_cast<double>(dist2(p, v))));
    std::cout << "ECART " << e << "\n";
    return 0;
}
