#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

static vector<string> lireListe()
{
    int n = 0;
    cin >> n;
    vector<string> noms(n);
    for (int i = 0; i < n; i++)
        cin >> noms[i];
    return noms;
}

int main()
{
    vector<string> a = lireListe();
    vector<string> b = lireListe();
    set<string> ea(a.begin(), a.end());
    set<string> eb(b.begin(), b.end());

    int commun = 0;
    for (const string& n : ea)
        if (eb.count(n))
            commun++;
    cout << "DEUX " << commun << "\n";

    int d = 0;
    for (const string& n : a)
        if (!eb.count(n))
        {
            cout << "SEUL_A " << n << "\n";
            d++;
        }
    for (const string& n : b)
        if (!ea.count(n))
        {
            cout << "SEUL_B " << n << "\n";
            d++;
        }

    set<string> reunion = ea;
    reunion.insert(eb.begin(), eb.end());
    cout << "DIFFERENTES " << d << " SUR " << reunion.size() << "\n";
    return 0;
}
