#include <cmath>
#include <iostream>
#include <string>
using namespace std;

int main() {
    const string faces[5] = {"SOL", "FOND", "ENTREE", "GAUCHE", "DROIT"};
    const double normales[5][3] = {
        {0, 1, 0}, {0, 0, 1}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}
    };

    long long ambiante;
    int n;
    cin >> ambiante >> n;

    for (int i = 0; i < n; i++) {
        string nom;
        double dx, dy, dz, intensite;
        cin >> nom >> dx >> dy >> dz >> intensite;

        double longueur = sqrt(dx * dx + dy * dy + dz * dz);
        long long maxi = 0;
        long long mini = 0;

        for (int f = 0; f < 5; f++) {
            double c = -(normales[f][0] * dx + normales[f][1] * dy + normales[f][2] * dz) / longueur;
            if (c < 0) c = 0;
            long long lumiere = llround(ambiante + intensite * c);

            if (f == 0 || lumiere > maxi) maxi = lumiere;
            if (f == 0 || lumiere < mini) mini = lumiere;

            cout << nom << " " << faces[f] << " " << lumiere << "\n";
        }
        cout << nom << " CONTRASTE " << maxi - mini << "\n";
    }
    return 0;
}
