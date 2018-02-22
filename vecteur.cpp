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
}

/*template <typename T>
Vecteur <T>:: Vecteur(int a)
{
	t = new T*[a];
	int length = a;
	int i = 0;
}*/

template <typename T>
Vecteur <T>:: ~Vecteur(){
	delete t;
}

template <typename T>
bool Vecteur <T>:: add_donne(T donne)
{
	if ((i + 1) == length)
	{
		int j = 0;
		T *f = t;
		t = new T [2*length];
		for (j = 0; j < length; j++)
		{
			t[j] = f[j];
		}
		length *= 2;
		delete [] f;
	}

	t[i] = donne;
	i++;

	return true;
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
}

template <typename T>
T Vecteur <T>:: gets_donne(int index)
{
	if (t[index] != 0)
	{
		return t[index];
	}
	else
		return 0;
}

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
