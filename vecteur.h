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

	//bool add_donne(T donne);
	void operator+=(T donne);
	void double_size();
	int capacite();
	int nb_donne();
	bool est_vide();
	void empty();
	T rm_donne(int index);

	//T& operator ++ ();
	//T& operator -- ();

	int get_pos();

	//const T operator [] (const int index);			  // set donnee en overload

	const T& operator [] (const int index);           // gets donnee en overload

	//T get_current();
	//void afficher(ostream & s);

	private:
	int i;
	int length;
	int donne;
	int index;
	int currentPos;
	T *t;
};

#endif
