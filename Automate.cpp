
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct transition {

	int etat_D;
	char Symb;
	int etat_A;
} Trans;

typedef struct automate {

	std::string alphabet;
	int Etat_I;
	int nbEf;
	int* tab_EtatF;
	int NbTrans;
	Trans* Tab_trans;

} AFD;
AFD lecture() {
	AFD M;

	cout << "\nDonner alphabet \n" ;
	std::cin >> M.alphabet;

	cout << "\nDonner etat initial : \n" ;
	cin >> M.Etat_I;

	cout << "\nDonne nombre d'etats finaux :\n";
	cin >> M.nbEf;

	M.tab_EtatF = new int[M.nbEf];
	if (M.tab_EtatF == nullptr) {
		cout << "\nErreur d'allocation m�moire pour les �tats finaux\n" << endl;
		std::exit(1);
	}
	cout << "\nDonner les valeurs des etats finaux : \n";
	for (int i = 0; i < M.nbEf; i++) {
		cin >> M.tab_EtatF[i];
	}

	cout << "\nDonner le nombre de transitions : \n";
	cin >> M.NbTrans;
	M.Tab_trans = new Trans[M.NbTrans];
	if (M.Tab_trans == nullptr) {
		cout << "\nErreur d'allocation m�moire pour les transitions.\n" << endl;
		std::exit(1);
	}
	cout << "\nRemplir les transitions (format : etat_D symbole etat_A) : \n";
	for (int i = 0; i < M.NbTrans; i++) {
		std::cin >> M.Tab_trans[i].etat_D >> M.Tab_trans[i].Symb >> M.Tab_trans[i].etat_A;
	}
	return M;
}
void afficher(AFD M) {
	cout << "\nL'alphabet  : \n" << M.alphabet;
	cout << "\nL'etat initial  : " << M.Etat_I;
	for (int i = 0; i < M.nbEf; i++) {
		cout << "\n L'etats final["<< i + 1 <<"] est :" << M.tab_EtatF[i] << endl;
	}
	cout << "\n La transition de automate est : \n" ;
	for (int i = 0; i < M.NbTrans; i++) {
		cout << "transition["<< i + 1 <<"] est :"<< M.Tab_trans[i].etat_D <<"---- -"<< M.Tab_trans[i].Symb <<"---- - " << M.Tab_trans[i].etat_A << endl;

	}


}
int existe_trans(AFD M, int e, char s) {
	for (int i = 0; i < M.NbTrans; i++) {
		if (M.Tab_trans[i].etat_D == e && M.Tab_trans[i].Symb == s) {
			return M.Tab_trans[i].etat_A;
		}
     }
	return -1;
}
int is_final1(AFD M, int e) {
	for (int i = 0; i < M.nbEf; i++) {
		if (M.tab_EtatF[i] == e) {
			return 1;
		}
	}
	return 0;
}
int accepter(AFD M, std::string &m) {
	int etat_actuel = M.Etat_I;

	//for (int i = 0; m[i] != '\0'; i++) {
	for (size_t i = 0; i < m.length(); ++i) {
		char symbole = m[i];
		int etat_suivant = existe_trans(M, etat_actuel, symbole);

		if (etat_suivant == -1) {
			return 0;
		}
		etat_actuel = etat_suivant;
	}
	return is_final1(M, etat_actuel);
}



int main() {
	std::string alpha;
	AFD M;
	M = lecture();
	afficher(M);
	cout << "donner un mot" << endl;
	std::cin >> alpha;

	if (accepter(M, alpha)) {
		std::cout << "le mot est accepte";
	}
	else
		std::cout << "rejete";

	delete[] M.tab_EtatF;
	delete[] M.Tab_trans;

	return 0;
}
