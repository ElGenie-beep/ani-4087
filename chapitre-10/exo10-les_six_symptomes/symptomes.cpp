#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;

    int muettes = 0;
    for (int i = 1; i <= n; ++i) {
        std::string fin;
        int g = 1, d = 1;
        char instant = 'P', pose = 'R', espace = 'S';
        std::cin >> fin >> g >> d >> instant >> pose >> espace;

        // Symptomes sur un casque, dans l'ordre demande
        std::string symptomes;
        auto ajouter = [&symptomes](const std::string& s) {
            if (!symptomes.empty()) symptomes += " ";
            symptomes += s;
        };
        if (fin == "JAMAIS") ajouter("FIGE");
        else if (fin == "SI_RENDU") ajouter("NE_REPART_PAS");
        if (g == 0) ajouter("OEIL_NOIR_G");
        if (d == 0) ajouter("OEIL_NOIR_D");
        if (instant == 'N') ajouter("TREMBLE");
        if (pose == 'F') ajouter("DE_TRAVERS");
        if (espace == 'L') ajouter("DECALE");

        bool symptome = !symptomes.empty();
        std::cout << i << " CASQUE " << (symptome ? symptomes : "AUCUN") << "\n";

        // Le simulateur ecrit quelque chose si fin != TOUJOURS ou si g ou d vaut 0
        bool dit = (fin != "TOUJOURS") || g == 0 || d == 0;
        std::cout << i << " SIMULATEUR " << (dit ? "DIT" : "MUET") << "\n";

        if (symptome && !dit) ++muettes;
    }

    std::cout << "MUETTES " << muettes << "\n";
    return 0;
}
