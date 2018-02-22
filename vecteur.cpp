/********
 * Fichier: vecteur.cpp
 * Auteurs: phak3004, torc1401
 * Date: 21 février 2018
 * Description: détails de la classe vecteur en template
********/

#include "vecteur.h"

template <typename T>
Vecteur <T>:: Vecteur()
{
	length = 1;
	t = new T [length];
	i = 0;
	currentPos = 0;
}

template <typename T>
Vecteur <T>:: ~Vecteur(){
	delete t;
}

template <typename T>
void Vecteur<T>::operator += (const T donne) {

	if ((i + 1) == length)
	{
		double_size();
	}

	t[i] = donne;
	i++;
	currentPos = i;
}

template <typename T>
void Vecteur <T>::double_size()
{
	int j;
	T *f = t;
	length *= 2;
	t = new T[2 * length];
	for (j = 0; j < i; j++)
	{
		t[j] = f[j];
	}
	delete[] f;
}

template <typename T>
int Vecteur <T>:: capacite()
{
	return length;
}

template <typename T>
int Vecteur <T>:: nb_donne()
{
	return i;
}

template <typename T>
bool Vecteur <T>:: est_vide()
{
	if (i == 0)
	{
		return true;
	}
	else
		return false;
}

template <typename T>
void Vecteur <T>:: empty()
{
	i = 0;
	currentPos = 0;
}

template <typename T>
void Vecteur <T>::setpos(int pos)
{
	currentPos = pos;
}

template <typename T>
Vecteur <T>& Vecteur <T>::operator++()
{
	if(currentPos+1 < i)
		currentPos++;
	return *this;
}

template <typename T>
Vecteur <T>& Vecteur <T>::operator--()
{
	if (currentPos > 0)
		currentPos--;
	return *this;
}

template <typename T>
T Vecteur <T>::get_current()
{
	return t[currentPos];
}

template <typename T>
int Vecteur <T>::get_pos()
{
	return currentPos;
}

/*template <typename T>
const T Vecteur <T> ::operator[](const int index) {
	return t[index-1];
}*/

template <typename T>
const T& Vecteur <T> ::operator[](const int index) {
	return t[index];
}


/*template <typename T>
const int& Vecteur <T> ::operator[](const int index, const T donne) {
	t[index] = donne;
}*/

template <typename T>
T Vecteur <T>:: rm_donne(int index)
{
	int j = 0;
	T *adresse = 0;
	adresse = t[index];
	if (t[index] != 0)
	{
		for (j = index; j < i; j++)
		{
			t[j] = t[(j + 1)];
		}
		t[i] = 0;
		i--;
		return adresse;
	}
	else
		return 0;
}

/*void Vecteur :: afficher(ostream & s)
{
	int k = 0;
	for (k = 0; k < i; k++)
	{
		t[k]->afficher(s);
	}
}*/
