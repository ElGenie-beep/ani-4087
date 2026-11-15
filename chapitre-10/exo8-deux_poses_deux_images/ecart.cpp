#include <cmath>
#include <iostream>

int main() {
    long long n = 0, d = 0;
    std::cin >> n >> d;

    long long sommePos = 0, sommeAngle = 0;
    for (long long i = 1; i <= n; ++i) {
        long long x1 = 0, z1 = 0, a1 = 0, x2 = 0, z2 = 0, a2 = 0;
        std::cin >> x1 >> z1 >> a1 >> x2 >> z2 >> a2;

        long long dx = x2 - x1, dz = z2 - z1;
        long long p = std::llround(std::sqrt(static_cast<double>(dx * dx + dz * dz)));
        long long a = a2 - a1;
        if (a < 0) a = -a;  // ecart de lacet sans son signe

        sommePos += p;
        sommeAngle += a;
        std::cout << i << " POSITION " << p << " ANGLE " << a << "\n";
    }

    if (n == 0 || d == 0) {
        std::cout << "AUCUNE\n";
        return 0;
    }

    std::cout << "MOYENNE POSITION " << sommePos / n << "\n";
    std::cout << "MOYENNE ANGLE " << sommeAngle / n << "\n";
    std::cout << "VITESSE " << sommeAngle / (n * d) << "\n";
    return 0;
}
