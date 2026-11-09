#include <iostream>
#include <string>

int main() {
    int n = 0;
    std::cin >> n;

    int bonnes = 0, longues = 0, muettes = 0;
    long long temps = 0;

    for (int i = 1; i <= n; ++i) {
        long long a = 0, d = 0, f = 0;
        std::cin >> a >> d >> f;

        long long amplitude = a;
        if (amplitude < 0) amplitude = 0;
        if (amplitude > 100) amplitude = 100;

        std::string duree = (d > 0) ? std::to_string(d) : "MIN";
        std::string frequence = (f > 0) ? std::to_string(f) : "DEFAUT";
        if (d > 0) temps += d;

        std::string verdict;
        if (amplitude == 0) {
            verdict = "MUETTE";
            ++muettes;
        } else if (d < 50) {
            verdict = "BREVE";
        } else if (d <= 200) {
            verdict = "BONNE";
            ++bonnes;
        } else {
            verdict = "LONGUE";
            ++longues;
        }

        std::cout << i << " " << amplitude << " " << duree << " "
                  << frequence << " " << verdict << "\n";
    }

    std::cout << "BONNES " << bonnes << "\n";
    std::cout << "LONGUES " << longues << "\n";
    std::cout << "MUETTES " << muettes << "\n";
    std::cout << "TEMPS " << temps << "\n";
    return 0;
}

//Resultat d'execution
//PS C:\Users\EL GENIE\Desktop\Rihen 1\chapitre-09\exo6-la_vibration> "5`n60 200 100`n20 100000 1`n150 80 0`n-5 0 120`n50 30 80" | .\programme.exe
//1 60 200 100 BONNE
//2 20 100000 1 LONGUE
//3 100 80 DEFAUT BONNE
//4 0 MIN 120 MUETTE
//5 50 30 80 BREVE
//BONNES 2
//LONGUES 1
//MUETTES 1
//TEMPS 100310
//PS C:\Users\EL GENIE\Desktop\Rihen 1\chapitre-09\exo6-la_vibration> "0" | .\programme.exe
//>> "2`n0 200 50`n100 50 0" | .\programme.exe
//>> "1`n100 201 5" | .\programme.exe
//BONNES 0
//LONGUES 0
//MUETTES 0
//TEMPS 0
//1 0 200 50 MUETTE
//2 100 50 DEFAUT BONNE
//BONNES 1
//LONGUES 0
//MUETTES 1
//TEMPS 250
//1 100 201 5 LONGUE
//BONNES 0
//LONGUES 1
//MUETTES 0
//TEMPS 201
