#include <iostream>
#include <string>

// Fausse session : un drapeau "trame ouverte" et des compteurs
class Session {
public:
    bool ouverte = false;
    int debuts = 0, fins = 0, refus = 0;

    bool Wait() {
        if (ouverte) { ++refus; return false; }
        return true;
    }
    bool Begin() {
        if (ouverte) { ++refus; return false; }
        ouverte = true;
        ++debuts;
        return true;
    }
    bool End() {
        if (!ouverte) { ++refus; return false; }
        ouverte = false;
        ++fins;
        return true;
    }
};

// Termine la trame dans son destructeur, sur tous les chemins de sortie
class GardeTrame {
public:
    explicit GardeTrame(Session& session) : session_(session) {}
    ~GardeTrame() { session_.End(); }
    GardeTrame(const GardeTrame&) = delete;             // pas de copie : pas de double fin
    GardeTrame& operator=(const GardeTrame&) = delete;

private:
    Session& session_;
};

struct Bilan {
    Session session;
    int images = 0;
};

static Bilan jouerSansGarde(const std::string& signes) {
    Bilan b;
    for (char signe : signes) {
        bool etat = b.session.Wait();
        b.session.Begin();
        char c = signe;
        if (!etat && (c == 'N' || c == 'C')) c = 'V';
        if (c == 'C') continue;  // saute la fin de trame
        if (c == 'R') break;     // saute la fin de trame
        if (c == 'N') ++b.images;
        b.session.End();         // fin de trame en bas du corps de boucle
    }
    return b;
}

static Bilan jouerAvecGarde(const std::string& signes) {
    Bilan b;
    for (char signe : signes) {
        bool etat = b.session.Wait();
        b.session.Begin();
        GardeTrame garde(b.session);  // End sera appele a la sortie du corps
        char c = signe;
        if (!etat && (c == 'N' || c == 'C')) c = 'V';
        if (c == 'C') continue;
        if (c == 'R') break;
        if (c == 'N') ++b.images;
    }
    return b;
}

static void afficher(const char* nom, const Bilan& b) {
    std::cout << nom << " DEBUTS " << b.session.debuts << " FINS " << b.session.fins
              << " REFUS " << b.session.refus << " IMAGES " << b.images
              << " OUVERTE " << (b.session.ouverte ? "OUI" : "NON") << "\n";
}

int main() {
    int t = 0;
    std::cin >> t;
    std::string signes;
    if (t > 0) std::cin >> signes;

    afficher("SANS", jouerSansGarde(signes));
    afficher("AVEC", jouerAvecGarde(signes));
    return 0;
}
