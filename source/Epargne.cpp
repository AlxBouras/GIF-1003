/**
 * \file Epargne.cpp
 * \brief Implantation de la classe Epargne
 * \author Alexandre Bouras, 111 149 065
 * \version 1.0
 * \date 26/03/2018
 */

#include "Epargne.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace util;
namespace banque
{
/**
 * \brief constructeur avec paramètres
 * 		  On construit un objet Epargne a partir de valeurs passées en paramètres.
 * \param[in] p_noCompte est un entier (int) qui représente le numéro de compte.
 * \param[in] p_tauxInteret est un nombre réel (double) qui représente le taux d'intérêt du compte épargne.
 * \param[in] p_solde est un entier (int) qui représente le solde du compte épargne.
 * \param[in] p_description est une chaîne de caractères (string) qui représente la description du compte épargne.
 * \pre p_tauxInteret doit être >= 0.1 et <= 3.5.
 */

Epargne::Epargne(int p_noCompte, double p_tauxInteret, double p_solde, const string& p_description)
:Compte::Compte(p_noCompte, p_tauxInteret, p_solde, p_description)
{
	PRECONDITION(p_tauxInteret >= 0.1);
	PRECONDITION(p_tauxInteret <= 3.5);
	INVARIANTS();
}

/**
 * \brief retourne les informations d'un objet Epargne formatés dans une chaîne de caractères (string)
 * \return les informations d'un objet Epargne dans une chaîne de caractères
 */
string Epargne::reqCompteFormate() const
{
	ostringstream os;
	os  << "Compte Epargne" << endl
		<< Compte::reqCompteFormate()
		<< "Interet \t\t: " << calculerInteret() << " $" << endl;

	return os.str();
}

/**
 * \brief assigne un taux d'intérêt au compte épargne
 * \param[in] p_tauxInteret est un réel (double) qui représente un taux d'intérêt
 * \pre p_tauxInteret doit être >= 0.1 et <= 3.5.
 * \return aucun retour
 */
void Epargne::asgTauxInteret(const double p_tauxInteret)
{
	PRECONDITION(p_tauxInteret >= 0.1);
	PRECONDITION(p_tauxInteret <= 3.5);
	Compte::asgTauxInteret(p_tauxInteret);
	INVARIANTS();
}

/**
 * \brief retourne les intérêts accumulés du compte épargne en dollars
 * \return un réel (double) qui représente le montant des intérêts du compte
 */
double Epargne::calculerInteret() const
{
	return (reqTauxInteret() / 100) * reqSolde();
}

/**
 * \brief retourne une copie allouée sur le monceau de l'objet Epargne courant.
 * \return un objet Epargne qui est une copie allouée sur le monceau de l'objet Epargne courant.
 */
Compte* Epargne::clone() const
{
	return new Epargne(*this); // Appel du constructeur copie
}

/**
 * \brief Teste les invariants de la classe Compte. L'invariant de cette classe s'assure que l'objet compte est valide
 */
void Epargne::verifieInvariant() const
{
	INVARIANT(reqTauxInteret() >= 0.1);
	INVARIANT(reqTauxInteret() <= 3.5);
}

} // namespace banque
