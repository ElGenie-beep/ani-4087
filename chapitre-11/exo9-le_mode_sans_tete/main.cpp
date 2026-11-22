#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    long long hz = 0;
    cin >> hz;

    // Pose : LIBRE ou FIXE lacet tangage x y z
    string mode;
    cin >> mode;
    long long pose[5] = {0, 0, 0, 1700, 0};
    if (mode == "FIXE")
        for (int i = 0; i < 5; i++)
            cin >> pose[i];

    int T = 0;
    cin >> T;

    vector<long long> a(T), b(T);
    for (int i = 0; i < T; i++)
        cin >> a[i];
    for (int i = 0; i < T; i++)
        cin >> b[i];

    // Periode en nanosecondes entieres ; a 1 Hz ou moins, le simulateur prend 72 Hz
    if (hz <= 1)
        hz = 72;
    long long periode = 1000000000LL / hz;

    cout << "PERIODE " << periode << "\n";
    cout << "POSE";
    for (int i = 0; i < 5; i++)
        cout << " " << pose[i];
    cout << "\n";

    int premierBrut = 0;
    int premierRelatif = 0;

    for (int t = 1; t <= T; t++)
    {
        long long predA = a[t - 1] + periode;
        long long predB = b[t - 1] + periode;
        long long predA1 = a[0] + periode;
        long long predB1 = b[0] + periode;

        long long brut = predB - predA;
        long long relatif = (predB - predB1) - (predA - predA1);
        long long scripte = (long long)t * periode;

        if (brut != 0 && premierBrut == 0)
            premierBrut = t;
        if (relatif != 0 && premierRelatif == 0)
            premierRelatif = t;

        cout << t << " BRUT " << brut
             << " RELATIF " << relatif
             << " SCRIPTE " << scripte << "\n";
    }

    if (premierBrut == 0)
        cout << "BRUT IDENTIQUE\n";
    else
        cout << "BRUT DIFFERENT " << premierBrut << "\n";

    if (premierRelatif == 0)
        cout << "RELATIF IDENTIQUE\n";
    else
        cout << "RELATIF DIFFERENT " << premierRelatif << "\n";

    return 0;
}

//Resultat
//PERIODE 11111111
//POSE 0 0 0 1700 0
//1 BRUT 4000000000 RELATIF 0 SCRIPTE 11111111
//2 BRUT 4000000000 RELATIF 0 SCRIPTE 22222222
//3 BRUT 3999999922 RELATIF -78 SCRIPTE 33333333
//4 BRUT 4000000667 RELATIF 667 SCRIPTE 44444444
//BRUT DIFFERENT 1
//RELATIF DIFFERENT 3
