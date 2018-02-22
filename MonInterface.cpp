/*
*   Voir fichier d'entête pour informations.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: MonInterface.cpp 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/
#include <QStyleFactory>
#include "MonInterface.h"
#include "CommunicationFPGA.h"
#include "vecteur.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

MonInterface::MonInterface(const char * theName) : VisiTest(theName)
{
	if(!setFPGA())
		message("Erreur connection FPGA");

	donnee.typeTest = 1;
	n_archive = 0;
	//n_test = 0;

	donnee.registreSW = 1;
	donnee.retourSW = 1;

	donnee.registreLD = 1;
	donnee.valeurLD = 1;

	donnee.etatLD = 1;
	donnee.etatSW = 1;

	isrecording = false;
	isfile = true;
	
	resetTest();
	resetArchive();
}

MonInterface::~MonInterface(){
	if (!fpga.ecrireRegistre(donnee.registreLD, 0)) {
		std::cout << fpga.messageErreur() << endl;
	}
}

void MonInterface::testSuivant()
{	
	if (!fpga.estOk())
	{
		message(fpga.messageErreur());
	}
	else {
		message("test OK");
	}

	int lvaleur;

	switch(donnee.typeTest) 
	{
		case 1 :
			donnee.registreSW = SW;
			donnee.registreLD = LD;

			if (!fpga.lireRegistre(donnee.registreSW, lvaleur)) {
				message("erreur lecture test 1");
				std::cout << fpga.messageErreur() << endl;
			}

			fpga.sleep(100);

			if (!fpga.ecrireRegistre(donnee.registreLD, lvaleur))
				message("erreur ecriture test 1");

			fpga.sleep(100);

			donnee.retourSW = lvaleur;
			donnee.etatSW = lvaleur;

			donnee.valeurLD = lvaleur;
			donnee.etatLD = lvaleur;
			break;

		case 2 :

			lvaleur = 0;
			int lmasque, lres, n;
			n = 0;

			donnee.registreSW = SW;
			donnee.registreLD = LD;

			if (!fpga.lireRegistre(donnee.registreSW, lvaleur)) {
				message("erreur lecture test 2");
				std::cout << fpga.messageErreur() << endl;
			}

			fpga.sleep(100);
			
			for (unsigned int i = 0; i < sizeof(int) * 8; i++) {
				lmasque = 1 << (sizeof(int) * 8 - 1 - i);
				if ((lvaleur&lmasque) != 0)
					n++;
			}

			if (n % 2) {
				lres = 0;
			}
			else {
				lres = 255;
			}

			if (!fpga.ecrireRegistre(donnee.registreLD, lres))
				message("erreur ecriture test 2");

			fpga.sleep(100);

			donnee.retourSW = lvaleur;
			donnee.etatSW = lvaleur;

			donnee.valeurLD = lres;
			donnee.etatLD = lres;

			break;

		case 3 :
			int lNLC = 0, lVLC = 0, i;
			lvaleur = 0;

			donnee.registreSW = SW;
			donnee.registreLD = LD;

			if (!fpga.lireRegistre(donnee.registreSW, lvaleur)) {
				message("erreur lecture test 3");
				std::cout << fpga.messageErreur() << endl;
			}

			fpga.sleep(100);

			if (lvaleur != 0) {
				lNLC = ceil(log2(lvaleur + 1));

				for (i = 0; i < lNLC; i++) {
					lVLC += exp2(i);
				}
			}

			if (!fpga.ecrireRegistre(donnee.registreLD, lVLC))
				message("erreur ecriture test 3");

			fpga.sleep(100);

			donnee.retourSW = lvaleur;
			donnee.etatSW = lvaleur;

			donnee.valeurLD = lVLC;
			donnee.etatLD = lVLC;
			
			break;
	}

	if (isrecording) {

		archive += donnee;
		
		setArchive(donnee);
		n_archive++;
		setArchive(n_archive, n_archive);
		
	}

	setTest(donnee);

	if (donnee.typeTest == 3) {
		donnee.typeTest = 1;
	}
	else {
		donnee.typeTest++;
	}

}

bool MonInterface::setFPGA()
{
	int val;
	bool lOK = true;

	if (!fpga.estOk())
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	if (!fpga.lireRegistre(SW, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;

	if(!fpga.estOk())
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	if(!fpga.lireRegistre(SW, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}
	
	std::cout << "SW: " << hex << val << endl;

	if(!fpga.lireRegistre(BTN, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	std::cout << "BTN: "  << hex << val  << endl;

	val = 0xac;
	if(!fpga.ecrireRegistre(LD, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

    val = 0xa;
	if(!fpga.ecrireRegistre(AN3, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	val++;
	if(!fpga.ecrireRegistre(AN2, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	val++;
	if(!fpga.ecrireRegistre(AN1, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	val++;

	if(!fpga.ecrireRegistre(AN0, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	return 0;
	}

	std::cout << "SW: " << hex << val << endl;

	if (!fpga.lireRegistre(BTN, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	std::cout << "BTN: " << hex << val << endl;

	val = 0xac;
	if (!fpga.ecrireRegistre(LD, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	val = 0xa;
	if (!fpga.ecrireRegistre(AN3, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	val++;
	if (!fpga.ecrireRegistre(AN2, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	val++;
	if (!fpga.ecrireRegistre(AN1, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	val++;

	if (!fpga.ecrireRegistre(AN0, val))
	{
		std::cout << fpga.messageErreur() << endl;
		lOK = false;
		return lOK;
	}

	return lOK;
}

void MonInterface::demarrer() {
	isrecording = true;
}

void MonInterface::arreter() {
	isrecording = false;
}

void MonInterface::vider() {
	n_archive = 0;
	archive.empty();
	resetArchive();
}

void MonInterface::modeFile() {
	isfile = true;
}

void MonInterface::modePile() {
	isfile = false;
}

void MonInterface::premier() {
	setArchive(1, n_archive);
	setArchive(archive[0]);
	archive.setpos(0);
}

void MonInterface::dernier() {
	setArchive(n_archive, n_archive);
	setArchive(archive[n_archive-1]);
	archive.setpos(n_archive-1);
}

void MonInterface::precedent() {
	--archive;
	setArchive(archive.get_pos()+1, n_archive);
	setArchive(archive[archive.get_pos()]);
}

void MonInterface::suivant() {
	++archive;
	setArchive(archive.get_pos() + 1, n_archive);
	setArchive(archive[archive.get_pos()]);
}

/*void MonInterface::sauvegarder(char *nomFichier) {

}*/


