#include <iostream>

static long long absolu(long long v) {
    return v < 0 ? -v : v;
}

int main() {
    long long w = 0;
    int t = 0;
    std::cin >> w >> t;

    int fausses = 0;
    long long pireCasque = 0, pireSimulateur = 0;

    for (int i = 1; i <= t; ++i) {
        long long p = 0, s = 0, a = 0;
        char m = 'R';
        std::cin >> p >> s >> a >> m;

        // lacet du rendu = w * P ; pose soumise = w * P (R) ou w * S (F)
        long long casque = (m == 'R') ? 0 : w * (s - p);
        long long simulateur = w * (a - p);

        if (casque != 0) ++fausses;
        if (absolu(casque) > pireCasque) pireCasque = absolu(casque);
        if (absolu(simulateur) > pireSimulateur) pireSimulateur = absolu(simulateur);

        std::cout << i << " CASQUE " << casque << " SIMULATEUR " << simulateur << "\n";
    }

    std::cout << "FAUSSES " << fausses << "\n";
    std::cout << "PIRE CASQUE " << pireCasque << "\n";
    std::cout << "PIRE SIMULATEUR " << pireSimulateur << "\n";
    return 0;
}

//RESULTAT EXECUTION
//1 CASQUE 0 SIMULATEUR 180
//2 CASQUE -360 SIMULATEUR 0
//3 CASQUE -450 SIMULATEUR 720
//4 CASQUE 0 SIMULATEUR 0
//FAUSSES 2
//PIRE CASQUE 450
//PIRE SIMULATEUR 720
