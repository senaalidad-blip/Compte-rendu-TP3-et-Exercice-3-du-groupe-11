// ============================================================
//  Gestion d'un personnel universitaire
//  Notions : heritage, classe abstraite, methodes virtuelles,
//            redefinition (override), polymorphisme, liaison dynamique
//  Compilation : g++ -std=c++17 -Wall -Wextra -o personnel main.cpp
//  Execution   : ./personnel   (Windows : personnel.exe)
// ============================================================

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// ------------------------------------------------------------
//  Classe mere ABSTRAITE : Employe
//  calculerSalaire() est virtuelle pure (= 0) : chaque categorie
//  a sa propre regle, donc Employe ne peut pas etre instanciee.
// ------------------------------------------------------------
class Employe {
protected:
    string matricule;
    string nom;
    string prenom;
    double salaireBase;

public:
    Employe(const string& matricule, const string& nom,
            const string& prenom, double salaireBase)
        : matricule(matricule), nom(nom), prenom(prenom), salaireBase(salaireBase) {}

    // Destructeur virtuel : indispensable pour detruire correctement
    // un objet derive a travers un pointeur de type Employe*.
    virtual ~Employe() = default;

    // Methode virtuelle pure : rend la classe abstraite.
    virtual double calculerSalaire() const = 0;

    // Methode virtuelle avec corps : affichage commun, completee par les classes filles.
    virtual void afficher() const {
        cout << "Matricule      : " << matricule << "\n"
             << "Nom            : " << nom << "\n"
             << "Prenom         : " << prenom << "\n"
             << "Salaire de base: " << salaireBase << " FCFA\n";
    }
};

// ------------------------------------------------------------
//  Classe derivee : Enseignant
//  Salaire = base + heures supplementaires + indemnite de recherche
// ------------------------------------------------------------
class Enseignant : public Employe {
private:
    int nbHeuresSup;
    double tauxHeureSup;
    double indemniteRecherche;

public:
    Enseignant(const string& matricule, const string& nom, const string& prenom,
               double salaireBase, int nbHeuresSup, double tauxHeureSup,
               double indemniteRecherche)
        : Employe(matricule, nom, prenom, salaireBase),
          nbHeuresSup(nbHeuresSup),
          tauxHeureSup(tauxHeureSup),
          indemniteRecherche(indemniteRecherche) {}

    double calculerSalaire() const override {
        return salaireBase + nbHeuresSup * tauxHeureSup + indemniteRecherche;
    }

    void afficher() const override {
        cout << "[ENSEIGNANT]\n";
        Employe::afficher();
        cout << "Heures sup.    : " << nbHeuresSup << " h x " << tauxHeureSup << " FCFA\n"
             << "Indem. recherche: " << indemniteRecherche << " FCFA\n"
             << "Salaire total  : " << calculerSalaire() << " FCFA\n";
    }
};

// ------------------------------------------------------------
//  Classe derivee : AgentAdministratif
//  Salaire = base + prime de rendement + prime de responsabilite
// ------------------------------------------------------------
class AgentAdministratif : public Employe {
private:
    double primeRendement;
    double primeResponsabilite;

public:
    AgentAdministratif(const string& matricule, const string& nom, const string& prenom,
                       double salaireBase, double primeRendement,
                       double primeResponsabilite)
        : Employe(matricule, nom, prenom, salaireBase),
          primeRendement(primeRendement),
          primeResponsabilite(primeResponsabilite) {}

    double calculerSalaire() const override {
        return salaireBase + primeRendement + primeResponsabilite;
    }

    void afficher() const override {
        cout << "[AGENT ADMINISTRATIF]\n";
        Employe::afficher();
        cout << "Prime rendement: " << primeRendement << " FCFA\n"
             << "Prime responsab.: " << primeResponsabilite << " FCFA\n"
             << "Salaire total  : " << calculerSalaire() << " FCFA\n";
    }
};

// ------------------------------------------------------------
//  Classe derivee : Technicien
//  Salaire = base + prime de risque + prime d'astreinte
// ------------------------------------------------------------
class Technicien : public Employe {
private:
    double primeRisque;
    double primeAstreinte;

public:
    Technicien(const string& matricule, const string& nom, const string& prenom,
               double salaireBase, double primeRisque, double primeAstreinte)
        : Employe(matricule, nom, prenom, salaireBase),
          primeRisque(primeRisque),
          primeAstreinte(primeAstreinte) {}

    double calculerSalaire() const override {
        return salaireBase + primeRisque + primeAstreinte;
    }

    void afficher() const override {
        cout << "[TECHNICIEN]\n";
        Employe::afficher();
        cout << "Prime de risque: " << primeRisque << " FCFA\n"
             << "Prime astreinte: " << primeAstreinte << " FCFA\n"
             << "Salaire total  : " << calculerSalaire() << " FCFA\n";
    }
};

// ------------------------------------------------------------
//  Programme principal : collection polymorphe
// ------------------------------------------------------------
int main() {
    cout << fixed << setprecision(0);

    // Employe e;  // ERREUR de compilation : Employe est abstraite

    // Collection contenant plusieurs categories d'employes.
    // unique_ptr : la memoire est liberee automatiquement.
    vector<unique_ptr<Employe>> personnel;

    personnel.push_back(make_unique<Enseignant>(
        "ENS001", "ADJOVI", "Marc", 450000, 20, 5000, 75000));
    personnel.push_back(make_unique<Enseignant>(
        "ENS002", "HOUNKPE", "Sylvie", 520000, 12, 6000, 90000));
    personnel.push_back(make_unique<AgentAdministratif>(
        "ADM001", "KPADE", "Julien", 300000, 40000, 25000));
    personnel.push_back(make_unique<AgentAdministratif>(
        "ADM002", "DOSSOU", "Awa", 320000, 35000, 30000));
    personnel.push_back(make_unique<Technicien>(
        "TEC001", "AGBO", "Ibrahim", 280000, 30000, 20000));
    personnel.push_back(make_unique<Technicien>(
        "TEC002", "SANNI", "Grace", 290000, 25000, 15000));

    cout << "========== LISTE DU PERSONNEL ==========\n\n";

    double masseSalariale = 0;
    for (const auto& e : personnel) {
        e->afficher();                      // liaison dynamique
        masseSalariale += e->calculerSalaire();  // liaison dynamique
        cout << "----------------------------------------\n";
    }

    cout << "\nNombre d'employes : " << personnel.size() << "\n"
         << "Masse salariale   : " << masseSalariale << " FCFA\n";

    return 0;
}
