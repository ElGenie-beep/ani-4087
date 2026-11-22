#include <iostream>
using namespace std;

int main()
{
    long long hz, ipd, N;
    cin >> hz >> ipd >> N;
    long long x, y, z, k0, dk, vx;
    cin >> x >> y >> z >> k0 >> dk >> vx;

    // Periode en nanosecondes entieres ; a 1 Hz ou moins on prend 72 Hz
    if (hz <= 1)
        hz = 72;
    long long p = 1000000000LL / hz;
    cout << "PERIODE " << p << "\n";

    // Droite de la tete en (x, z) pour un lacet de 0, 1, 2, 3
    const long long droiteX[4] = {1, 0, -1, 0};
    const long long droiteZ[4] = {0, -1, 0, 1};
    long long demi = ipd / 2;

    for (long long t = 1; t <= N; t++)
    {
        long long lacet = ((k0 + (t - 1) * dk) % 4 + 4) % 4;
        long long tx = x + (t - 1) * vx;

        long long gx = tx - demi * droiteX[lacet];
        long long gz = z - demi * droiteZ[lacet];
        long long dx = tx + demi * droiteX[lacet];
        long long dz = z + demi * droiteZ[lacet];

        long long instant = t * p;

        cout << t << " G " << gx << " " << y << " " << gz
             << " D " << dx << " " << y << " " << dz
             << " I " << instant << "\n";
    }
    return 0;
