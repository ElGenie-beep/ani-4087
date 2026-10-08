#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;

    int visibles = 0;
    int enPanne = 0;

    for (int i = 0; i < n; i++) {
        string nom;
        long long drapeaux, sx, sy, sz, distance, lumieres, ambiante, proche;
        cin >> nom >> drapeaux >> sx >> sy >> sz >> distance >> lumieres >> ambiante >> proche;

        long long faceAvant = distance - sz / 2;
        string verdict;

        if ((drapeaux & 2) == 0) {
            verdict = "RENDER3D ETEINT";
        } else if (sx == 0 || sy == 0 || sz == 0) {
            verdict = "ECHELLE NULLE";
        } else if (faceAvant <= 0) {
            verdict = "CAMERA DANS LE CUBE";
        } else if (faceAvant < proche) {
            verdict = "COUPE PAR LE PLAN PROCHE";
        } else if (lumieres == 0 && ambiante == 0) {
            verdict = "PAS DE LUMIERE";
        } else {
            verdict = "VISIBLE";
        }

        if (verdict == "VISIBLE") visibles++;
        else enPanne++;

        cout << nom << " " << verdict << "\n";
    }

    cout << "VISIBLES " << visibles << "\n";
    cout << "EN PANNE " << enPanne << "\n";
    return 0;
}
