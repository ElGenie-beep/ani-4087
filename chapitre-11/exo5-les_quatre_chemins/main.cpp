#include <iostream>
#include <string>
using namespace std;

int main()
{
    int K;
    if (!(cin >> K) || K == 0)
    {
        cout << "AUCUNE MACHINE\n";
        return 0;
    }

    for (int i = 1; i <= K; i++)
    {
        string D, V, L, R, B, G;
        cin >> D >> V >> L >> R >> B >> G;

        int chargees = 0;
        int liberees = 0;
        bool casque = false;

        if (D == "SIMULATEUR")
        {
            cout << i << " BACKEND SIMULATEUR DEMANDE\n";
        }
        else
        {
            bool bibliotheque = false;
            bool entree = false;
            string source;
            bool sansEntree = false;

            // Regle 2 : la variable d'environnement
            if (V == "ABSENT")
            {
                cout << i << " VARIABLE IGNOREE\n";
            }
            else if (V != "-")
            {
                cout << i << " VARIABLE CHARGEE\n";
                chargees++;
                bibliotheque = true;
                if (V == "BON")
                {
                    entree = true;
                    source = "VARIABLE";
                }
                else
                {
                    sansEntree = true;
                }
            }

            // Regle 3 : le loader standard, seulement si rien n'est charge
            if (!bibliotheque)
            {
                if (L == "ABSENT")
                {
                    cout << i << " LOADER ABSENT\n";
                }
                else
                {
                    cout << i << " LOADER CHARGE\n";
                    chargees++;
                    bibliotheque = true;
                    if (L == "BON")
                    {
                        entree = true;
                        source = "LOADER";
                    }
                    else
                    {
                        sansEntree = true;
                    }
                }
            }

            // Regle 4 : une bibliotheque sans point d'entree est liberee
            if (sansEntree)
            {
                cout << i << " SANS_ENTREE\n";
                liberees++;
                bibliotheque = false;
            }

            // Regle 5 : la decouverte directe
            if (!entree)
            {
                cout << i << " DIRECT " << R << "\n";
                if (R == "NEGO_KO" || R == "BON")
                {
                    chargees++;
                    bibliotheque = true;
                }
                if (R == "BON")
                {
                    entree = true;
                    source = "DIRECT";
                }
            }

            // Regle 6 : le backend, puis la liaison
            if (!entree)
            {
                cout << i << " BACKEND INDISPONIBLE\n";
                if (bibliotheque)
                {
                    liberees++;
                    bibliotheque = false;
                }
            }
            else
            {
                cout << i << " BACKEND OPENXR " << source << "\n";
                if (B == "NON")
                {
                    cout << i << " LIAISON ECHOUEE\n";
                    liberees++;
                    bibliotheque = false;
                }
                else
                {
                    casque = true;
                }
            }
        }

        // Regle 7 : le niveau
        if (casque)
            cout << i << " NIVEAU 1 CASQUE\n";
        else if (G == "OUI")
            cout << i << " NIVEAU 2 SIMULATEUR CARTE\n";
        else
            cout << i << " NIVEAU 3 SIMULATEUR LOGICIEL\n";

        // Regle 8 : le bilan
        cout << i << " CHARGEES " << chargees << " LIBEREES " << liberees << "\n";
    }
    return 0;
}

//resultat
//1 LOADER CHARGE
//1 BACKEND OPENXR LOADER
//1 NIVEAU 1 CASQUE
//1 CHARGEES 1 LIBEREES 0
//2 VARIABLE CHARGEE
//2 SANS_ENTREE
//2 DIRECT BON
//2 BACKEND OPENXR DIRECT
//2 LIAISON ECHOUEE
//2 NIVEAU 2 SIMULATEUR CARTE
//2 CHARGEES 2 LIBEREES 2
//3 BACKEND SIMULATEUR DEMANDE
//3 NIVEAU 3 SIMULATEUR LOGICIEL
//3 CHARGEES 0 LIBEREES 0
