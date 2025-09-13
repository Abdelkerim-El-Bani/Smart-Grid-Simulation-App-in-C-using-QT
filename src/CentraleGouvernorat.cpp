#include "/home/kerim/Documents/MiniProjet/include/CentraleGouvernorat.h"
using namespace std;



 CentraleGouvernorat::CentraleGouvernorat(){};
void CentraleGouvernorat::ajouterLiaison(int idCentrale, int idGouvernorat) {
    liaisonGouvToCentrale[idGouvernorat].insert(idCentrale);
}



set<int> CentraleGouvernorat::getCentralesParGouvernorat(int idGouvernorat) const {
    auto it = liaisonGouvToCentrale.find(idGouvernorat);
    if (it != liaisonGouvToCentrale.end()) {
        return it->second;
    }
    return {};
}
set<int> CentraleGouvernorat::afficherGouvernoratsParCentrale(int idCentrale) const {
    set<int> result;
    
    for (const auto& [idGouv, centrales] : liaisonGouvToCentrale) {
        if (centrales.find(idCentrale) != centrales.end()) {
            result.insert(idGouv);
        }
    }

    return result;
}

