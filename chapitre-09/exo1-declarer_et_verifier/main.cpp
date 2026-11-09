#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Action {
    std::string nom;
    std::string type;
    int usage;
};

int main() {
    const std::map<std::string, int> usages = {
        {"SELECT", 0},        {"GRAB", 1},           {"MENU", 2},
        {"MOVE", 3},          {"AIM_POSE", 4},       {"GRIP_POSE", 5},
        {"HAPTIC", 6},        {"SELECT_LEFT", 7},    {"GRAB_LEFT", 8},
        {"AIM_POSE_LEFT", 9}, {"GRIP_POSE_LEFT", 10},
        {"HAPTIC_LEFT", 11},  {"MOVE_RIGHT", 12}
    };

    std::vector<Action> actions;
    std::set<std::string> noms;
    bool attache = false;
    unsigned long long k = 0;
    int doublons = 0;

    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string ordre;
        std::cin >> ordre;
        if (ordre == "cree") {
            std::string nom, type, usage;
            std::cin >> nom >> type >> usage;
            actions.push_back({nom, type, usages.at(usage)});
            if (!noms.insert(nom).second) {
                ++doublons;
            }
            std::cout << "ACTION " << actions.size() << " " << nom << " "
                      << type << " " << usages.at(usage) << "\n";
        } else if (ordre == "attache") {
            if (!attache) {
                attache = true;
                k = actions.size();
                std::cout << "ATTACHE " << k << "\n";
            } else {
                std::cout << "ATTACHE REFUSE\n";
            }
        } else if (ordre == "lit") {
            unsigned long long h = 0;
            std::cin >> h;
            if (h == 0 || h > actions.size()) {
                std::cout << "LIT " << h << " INVALIDE\n";
            } else if (!attache || h > k) {
                std::cout << "LIT " << h << " INCONNUE\n";
            } else {
                std::cout << "LIT " << h << " " << actions[h - 1].nom << "\n";
            }
        }
    }

    std::cout << "ACTIONS " << actions.size() << "\n";
    std::cout << "ATTACHEES " << k << "\n";
    std::cout << "NOMS EN DOUBLE " << doublons << "\n";
    return 0;
}

// Resultat execution

// ACTION 1 tirer BOOL 0
// ACTION 2 saisir BOOL 1
// ACTION 3 menu BOOL 2
// ACTION 4 avancer VEC2 3
// ATTACHE 4
// ACTION 5 paume POSE 5
// ATTACHE REFUSE
// LIT 0 INVALIDE
// LIT 2 saisir
// LIT 5 INCONNUE
// LIT 6 INVALIDE
// ACTIONS 5
// ATTACHEES 4
// NOMS EN DOUBLE 0
