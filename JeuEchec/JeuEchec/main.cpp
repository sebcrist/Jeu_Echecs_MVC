// Sebastian Cristescu (2286066) et Raphael Labruguiere (2276313)
// Projet Final - Projet d'echecs

#include "JeuEchec.h"
#include "JeuEchecVue.h"
#include <QtWidgets/QApplication>

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	// cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.
	
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
	#endif
	//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}

namespace vue
{
    class JeuEchecVue;
}
namespace controlleur
{
    class JeuEchecControlleur;
}

/* 
Les warnings générés par le compilateur sont des résultats de la fusion entre le projet et la bilbiothèque du cours,
ce qui fait en sorte qu'ils ne proviennent pas de notre code.


De plus, les parties du CodeCoverage qui ne sont pas/peut utilisées dans le fichier .codecoverage ne sont pas inutiles,
mais elles ne sont simplement pas utilisées dans cette instanciation du jeu d'échec (exemple: si il n,y a pas de Cavalier,
il est normal que la classe Cavalier soit 100% inutilisée ainsi que la partie représentant un Cavalier dans la
methode genererMouvement ne soit donc pas utiliser également). C'est également le cas avec vérifierRois, qui n'est pas utilisé
car elle est seulement utilisée si on essaye de mettre plus de 2 rois ( ce qu'on a pas fait car c'est contre la nature des echecs.
*/

int main(int argc, char *argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);
 
    controlleur::JeuEchecControlleur jeuLogique;
    jeuLogique.initialiser();
    
    vue::JeuEchecVue jeuVue;
    jeuVue.initialiser(&jeuLogique);



    jeuVue.show();

    return app.exec();
}
