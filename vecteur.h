/********
 * Fichier: vecteur.h
 * Auteurs: phak3004, torc1401
 * Date: 21 février 2018
 * Description: definition de la classe vecteur en template
********/

#ifndef VECTEUR
#define VECTEUR

#include <iostream>
//#include "forme.h"

//#define Forme Forme

//using namespace std;

template <typename T>
class Vecteur
{
	public:
	Vecteur();
	//Vecteur(int a);
	~Vecteur();

	bool add_donne(T donne);
	int capacite();
	int nb_donne();
	bool est_vide();
	void empty();
	T rm_donne(int index);
	T gets_donne(int index);
	//void afficher(ostream & s);

	private:
	int i;
	int length;
	int donne;
	int index;
	T *t;
};

#endif
