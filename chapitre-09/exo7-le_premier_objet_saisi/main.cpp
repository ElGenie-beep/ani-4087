#include <iostream>
#include <vector>

struct Pose {
    long long x;
    long long y;
    int k;
};

// Tourne le vecteur (u, v) de k quarts de tour
static void tourner(long long u, long long v, int k, long long& ru, long long& rv) {
    switch (k % 4) {
        case 0: ru = u;  rv = v;  break;
        case 1: ru = -v; rv = u;  break;
        case 2: ru = -u; rv = -v; break;
        default: ru = v; rv = -u; break;
    }
}

// A * B : position de A plus la position de B tournee de A.k
static Pose composer(const Pose& a, const Pose& b) {
    long long ru = 0, rv = 0;
    tourner(b.x, b.y, a.k, ru, rv);
    return Pose{a.x + ru, a.y + rv, (a.k + b.k) % 4};
}

static Pose inverse(const Pose& a) {
    int kp = (4 - a.k) % 4;
    long long ru = 0, rv = 0;
    tourner(-a.x, -a.y, kp, ru, rv);
    return Pose{ru, rv, kp};
}

int main() {
    int m = 0, t = 0;
    std::cin >> m >> t;

    std::vector<Pose> objets(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> objets[i].x >> objets[i].y >> objets[i].k;
    }

    int tenu = -1;             // index de l'objet tenu, -1 si aucun
    Pose attache = {0, 0, 0};
    int bPrecedent = 0;
    int saisies = 0, ratees = 0;

    for (int f = 1; f <= t; ++f) {
        Pose paume = {0, 0, 0};
        int b = 0;
        std::cin >> paume.x >> paume.y >> paume.k >> b;

        bool rate = false;
        if (b == 1 && bPrecedent == 0) {
            // appui : chercher l'objet le plus proche, a 150 mm au plus
            int meilleur = -1;
            long long meilleureDist = 0;
            for (int i = 0; i < m; ++i) {
                long long dx = objets[i].x - paume.x;
                long long dy = objets[i].y - paume.y;
                long long d2 = dx * dx + dy * dy;
                if (d2 <= 22500 && (meilleur == -1 || d2 < meilleureDist)) {
                    meilleur = i;
                    meilleureDist = d2;
                }
            }
            if (meilleur >= 0) {
                tenu = meilleur;
                attache = composer(inverse(paume), objets[meilleur]);
                ++saisies;
            } else {
                rate = true;
                ++ratees;
            }
        } else if (b == 0 && bPrecedent == 1) {
            tenu = -1;  // relachement : l'objet reste ou il est
        }
        bPrecedent = b;

        if (tenu >= 0) {
            objets[tenu] = composer(paume, attache);
            std::cout << f << " TIENT " << (tenu + 1) << " " << objets[tenu].x
                      << " " << objets[tenu].y << " " << objets[tenu].k << "\n";
        } else if (rate) {
            std::cout << f << " RATE\n";
        } else {
            std::cout << f << " LIBRE\n";
        }
    }

    std::cout << "SAISIES " << saisies << "\n";
    std::cout << "RATEES " << ratees << "\n";
    for (int i = 0; i < m; ++i) {
        std::cout << "OBJET " << (i + 1) << " " << objets[i].x << " "
                  << objets[i].y << " " << objets[i].k << "\n";
    }
    return 0;
}


 //Resultat d'execution
//PS C:\Users\EL GENIE\Desktop\Rihen 1\chapitre-09\exo7-le_premier_objet_saisi> "2 6`n100 0 0`n400 0 1`n0 0 0 0`n0 50 0 1`n0 150 1 1`n200 150 1 1`n200 150 1 0`n380 20 2 1" | .\programme.exe
//1 LIBRE
//2 TIENT 1 100 0 0
//3 TIENT 1 50 250 1
//4 TIENT 1 250 250 1
//5 LIBRE
//6 TIENT 2 400 0 1
//SAISIES 2
//RATEES 0
//OBJET 1 250 250 1
//OBJET 2 400 0 1
