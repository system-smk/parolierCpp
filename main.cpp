#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>
#include <set>


void clr(){
	std::cout << "\033[2J \033[H" << std::endl;
}


void retourPhrases(std::string phrase){
	std::cout << phrase << std::endl;
}

std::vector<std::string> lireFichier(const std::string& nomFichier) {
    	std::ifstream fichier(nomFichier);
    	std::vector<std::string> lignes;
    	std::string ligne;
    	while (std::getline(fichier, ligne)) {
        	if (!ligne.empty())
            	lignes.push_back(ligne);
    	}
    	return lignes;
}

std::string auHasard(const std::vector<std::string>& liste) {
    	if (liste.empty()) return "[vide]";
    	std::random_device rd;                         // source d’aléa
    	std::mt19937 gen(rd());                        // moteur (Mersenne Twister)
    	std::uniform_int_distribution<> dist(0, liste.size() - 1); // distribution uniforme
    	return liste[dist(gen)];
}

int main() {
    	std::srand(std::time(nullptr)); // Initialiser l'aléatoire avec time
	std::set<std::string> phrasesRejetees;
	std::ifstream fichierRejets("phrases_rejetees.txt");
	std::string ligne;
	while (std::getline(fichierRejets, ligne)) {
    		if (!ligne.empty()) {
        	phrasesRejetees.insert(ligne);
	    	}
	}

    //  Charger les catégories
    	std::vector<std::string> sujets = lireFichier("sujets.txt");
    	std::vector<std::string> verbes = lireFichier("verbes.txt");
    	std::vector<std::string> complements = lireFichier("complements.txt");


	std::string reponse = "n";
	while (true){
    // Assembler la phrase
		std::string phrase;
		do{
    			phrase = auHasard(sujets) + " " +
                        	 auHasard(verbes) + " " +
                         	 auHasard(complements) + ".";
		} while (phrasesRejetees.count(phrase) > 0);
    		std::cout << phrase << std::endl;
    		std::cout << "Est-elle correcte ? (o/n) : ";
		std::getline(std::cin, reponse);
		if (reponse == "o") {
        		std::cout << "Phrase acceptée ✅\n";
    		} else if (reponse == "n") {
        		std::ofstream rejets("phrases_rejetees.txt", std::ios::app);
        		rejets << phrase << "\n";
        		std::cout << "Phrase rejetée ❌\n\n";
    		} else if (reponse == "q") {
        		std::cout << "Fin de la génération.\n";
        		break;
    		}
	}
    	return 0;
}
