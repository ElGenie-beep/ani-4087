#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Action {
    std::string nom;
    std::string usage;
};

// Lit une table et ses images, affiche le resultat, renvoie les lignes d'images.
// Seule la table (usage -> commande) vient de l'entree : le code ne nomme aucun bouton.
static std::vector<std::string> jouerTable(int numero,
                                           const std::vector<Action>& actions) {
    int u = 0;
    std::cin >> u;
    std::map<std::string, std::string> table;
    for (int i = 0; i < u; ++i) {
        std::string usage, commande;
        std::cin >> usage >> commande;
        table[usage] = commande;
    }

    std::cout << "TABLE " << numero << "\n";
    for (const Action& a : actions) {
        if (table.count(a.usage) == 0) {
            std::cout << "INACTIVE " << a.nom << "\n";
        }
    }

    int t = 0;
    std::cin >> t;
    std::vector<bool> avant(actions.size(), false);  // rien n'est appuye au depart
    std::vector<std::string> images;

    for (int f = 1; f <= t; ++f) {
        int k = 0;
        std::cin >> k;
        std::set<std::string> tenues;
        for (int j = 0; j < k; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        std::string ligne = std::to_string(f);
        bool aucune = true;
        for (std::size_t j = 0; j < actions.size(); ++j) {
            bool appuyee = false;
            std::map<std::string, std::string>::const_iterator it =
                table.find(actions[j].usage);
            if (it != table.end()) {
                appuyee = tenues.count(it->second) > 0;
            }
            if (appuyee && !avant[j]) {
                ligne += " " + actions[j].nom;
                aucune = false;
            }
            avant[j] = appuyee;
        }
        if (aucune) ligne += " -";

        std::cout << ligne << "\n";
        images.push_back(ligne);
    }
    return images;
}

int main() {
    int a = 0;
    std::cin >> a;
    std::vector<Action> actions(a);
    for (int i = 0; i < a; ++i) {
        std::cin >> actions[i].nom >> actions[i].usage;
    }

    std::vector<std::string> premiere = jouerTable(1, actions);
    std::vector<std::string> seconde = jouerTable(2, actions);

    std::cout << "IDENTIQUES " << (premiere == seconde ? "OUI" : "NON") << "\n";
    return 0;
}
