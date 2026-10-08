#include <iostream>
#include <string>
using namespace std;

long long absolu(long long v) {
    return v < 0 ? -v : v;
}

int main() {
    int n;
    cin >> n;

    int deplaces = 0;
    long long pire = 0;

    for (int i = 0; i < n; i++) {
        string nom;
        long long tx, ty, tz, sx, sy, sz;
        cin >> nom >> tx >> ty >> tz >> sx >> sy >> sz;

        long long x = sx * tx / 1000;
        long long y = sy * ty / 1000;
        long long z = sz * tz / 1000;

        long long ecart = absolu(tx - x);
        if (absolu(ty - y) > ecart) ecart = absolu(ty - y);
        if (absolu(tz - z) > ecart) ecart = absolu(tz - z);

        if (ecart != 0) deplaces++;
        if (ecart > pire) pire = ecart;

        cout << nom << " " << x << " " << y << " " << z << " " << ecart << "\n";
    }

    cout << "DEPLACES " << deplaces << "\n";
    cout << "PIRE " << pire << "\n";
    return 0;
}
