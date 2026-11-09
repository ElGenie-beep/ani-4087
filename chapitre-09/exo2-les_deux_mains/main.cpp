#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Liaison {
    std::string main;
    std::string commande;
};

static int axe(const std::set<std::string>& tenues, const std::string& plus,
               const std::string& moins) {
    int v = 0;
    if (tenues.count(plus)) v += 1;
    if (tenues.count(moins)) v -= 1;
    return v;
}

int main() {
    // Table du simulateur : usage -> (main, commande)
    const std::map<std::string, Liaison> table = {
        {"SELECT", {"DROITE", "SOURIS_G"}},
        {"GRAB", {"DROITE", "SOURIS_D"}},
        {"MENU", {"GAUCHE", "TAB"}},
        {"MOVE", {"GAUCHE", "FLECHES"}},
        {"AIM_POSE", {"DROITE", "AUCUNE"}},
        {"GRIP_POSE", {"DROITE", "AUCUNE"}},
        {"HAPTIC", {"DROITE", "AUCUNE"}},
        {"SELECT_LEFT", {"GAUCHE", "SOURIS_M"}},
        {"GRAB_LEFT", {"GAUCHE", "MAJ_G"}},
        {"AIM_POSE_LEFT", {"GAUCHE", "AUCUNE"}},
        {"GRIP_POSE_LEFT", {"GAUCHE", "AUCUNE"}},
        {"HAPTIC_LEFT", {"GAUCHE", "AUCUNE"}},
        {"MOVE_RIGHT", {"DROITE", "IJKL"}}
    };
    const std::set<std::string> touchesTete = {"Z", "Q", "S", "D", "W", "A"};

    int a = 0, t = 0;
    std::cin >> a >> t;

    std::vector<std::string> commandes;
    int droite = 0, gauche = 0;
    for (int i = 0; i < a; ++i) {
        std::string nom, usage;
        std::cin >> nom >> usage;
        const Liaison& l = table.at(usage);
        commandes.push_back(l.commande);
        if (l.main == "DROITE") ++droite; else ++gauche;
        std::cout << nom << " " << l.main << " " << l.commande << "\n";
    }

    int imagesTete = 0;
    for (int f = 1; f <= t; ++f) {
        int k = 0;
        std::cin >> k;
        std::set<std::string> tenues;
        for (int j = 0; j < k; ++j) {
            std::string c;
            std::cin >> c;
            tenues.insert(c);
        }

        bool teteBouge = false;
        for (const std::string& c : tenues) {
            if (touchesTete.count(c)) teteBouge = true;
        }
        if (teteBouge) ++imagesTete;

        std::string ligne = std::to_string(f);
        for (const std::string& cmd : commandes) {
            std::string valeur;
            if (cmd == "AUCUNE") {
                valeur = "-";
            } else if (cmd == "FLECHES") {
                valeur = std::to_string(axe(tenues, "F_DROITE", "F_GAUCHE")) + "," +
                         std::to_string(axe(tenues, "F_HAUT", "F_BAS"));
            } else if (cmd == "IJKL") {
                valeur = std::to_string(axe(tenues, "L", "J")) + "," +
                         std::to_string(axe(tenues, "I", "K"));
            } else {
                valeur = tenues.count(cmd) ? "1" : "0";
            }
            ligne += " " + valeur;
        }
        std::cout << ligne << "\n";
    }

    std::cout << "DROITE " << droite << "\n";
    std::cout << "GAUCHE " << gauche << "\n";
    std::cout << "TETE " << imagesTete << "\n";
    return 0;
}



  // Resultat d'execution
  // tirer DROITE SOURIS_G
  // saisir_g GAUCHE MAJ_G
  // avancer GAUCHE FLECHES
  // vibrer DROITE AUCUNE
  // 1 0 0 0,0 -
  // 2 1 0 0,1 -
  // 3 0 1 -1,0 -
  // 4 0 0 0,0 -
  // DROITE 2
  // GAUCHE 2
  // TETE 1
