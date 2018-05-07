/**
 * \file Cheque.cpp
 * \brief Implantation de la classe Cheque
 * \author Alexandre Bouras, 111 149 065
 * \version 1.0
 * \date 26/03/2018
 */

#include "Cheque.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace util;

namespace banque
{
/**
 * \brief constructeur avec paramètres
 * 		  On construit un objet Cheque a partir de valeurs passées en paramètres.
 * \param[in] p_noCompte est un entier (int) qui représente le numéro de compte.
 * \param[in] p_tauxInteret est un nombre réel (double) qui représente le taux d'intérêt du compte chèque.
 * \param[in] p_solde est un entier (int) qui représente le solde du compte chèque.
 * \param[in] p_nombreTransactions est un entier (int) qui représente le nombre de transactions du compte chèque.
 * \param[in] p_tauxInteretMinimum est un nombre réel (double) qui représente le taux d'intérêt minimum du compte chèque.
 * \param[in] p_description est une chaîne de caractères (string) qui représente la description du compte chèque.
 * \pre m_nombreTransactions doit être >= 0.
 * \pre m_nombreTransactions doit être <= 40.
 * \pre m_tauxInteret doit être >= m_tauxInteretMinimum (donc garder sa relation d'ordre).
 * \post m_nombreTransactions prend la valeur de p_nombreTransactions.
 * \post m_tauxInteretMinimum prend la valeur de p_tauxInteretMinimum.
 */
Cheque::Cheque(int p_noCompte, double p_tauxInteret, double p_solde,
		   	   int p_nombreTransactions, double p_tauxInteretMinimum, const std::string& p_description)
:Compte(p_noCompte, p_tauxInteret, p_solde, p_description), m_nombreTransactions(p_nombreTransactions),
 m_tauxInteretMinimum(p_tauxInteretMinimum)
{
	PRECONDITION(p_nombreTransactions >= 0);
	PRECONDITION(p_nombreTransactions <= 40);
	PRECONDITION(p_tauxInteret >= p_tauxInteretMinimum);

	POSTCONDITION(m_nombreTransactions == p_nombreTransactions);
	POSTCONDITION(m_tauxInteretMinimum == p_tauxInteretMinimum);
	INVARIANTS();
}

/**
 * \brief retourne le taux d'intérêt minimum du compte chèque
 * \return un réel (double) qui représente le taux d'intérêt minimum du compte chèque
 */
double Cheque::reqTauxInteretMinimum() const
{
	return m_tauxInteretMinimum;
}

/**
 * \brief retourne le nombre de transactions du compte chèque
 * \return un entier (int) qui représente le nombre de transactions du compte chèque
 */
int Cheque::reqNombreTransactions() const
{
	return m_nombreTransactions;
}

/**
 * \brief retourne les informations d'un objet Cheque formatés dans une chaîne de caractères (string)
 * \return les informations d'un objet Cheque dans une chaîne de caractères
 */
string Cheque::reqCompteFormate() const
{
	ostringstream os;
	os  << "Compte Cheque" << endl
		<< Compte::reqCompteFormate()
		<< "nombre de transactions \t: " << reqNombreTransactions() << endl
		<< "Taux d'interet minimum \t: " << reqTauxInteretMinimum() << endl
		<< "Interet \t\t: " << calculerInteret() << " $" << endl;

	return os.str();
}

/**
 * \brief assigne un nombre de transactions au compte chèque
 * \param[in] p_nombreTransactions est un entier (int) qui représente un
 * 			  nombre de transactions
 * \post m_nombreTransactions prend la valeur de p_nombreTransactions
 * \return aucun retour
 */
void Cheque::asgNombreTransactions (int p_nombreTransactions)
{
	PRECONDITION(p_nombreTransactions >= 0);
	PRECONDITION(p_nombreTransactions <= 40);
	m_nombreTransactions = p_nombreTransactions;
	POSTCONDITION(m_nombreTransactions == p_nombreTransactions);
	INVARIANTS();

}

/**
 * \brief assigne un taux d'intérêt au compte chèque
 * \param[in] p_tauxInteret est un réel (double) qui représente un taux d'intérêt
 * \pre m_tauxInteret doit être >= m_tauxInteretMinimum (donc garder sa relation d'ordre).
 * \return aucun retour
 */
void Cheque::asgTauxInteret(const double p_tauxInteret)
{
	PRECONDITION(p_tauxInteret >= m_tauxInteretMinimum);
	Compte::asgTauxInteret(p_tauxInteret);
	INVARIANTS();
}

/**
 * \brief retourne les intérêts dûs sur un solde négatif, en dollars;
 * 		  aucun intérêt si le solde du compte chèque est positif
 * \return un réel (double) qui représente le montant des intérêts du compte
 */
double Cheque::calculerInteret() const
{
	double interets = 0.0;

	if (reqSolde() < 0)
	{
		if (reqNombreTransactions() < 11)
		{
			interets = -((reqTauxInteretMinimum() / 100) * reqSolde());
		}
		if (reqNombreTransactions() > 10 and reqNombreTransactions() < 26)
		{
			interets = -((reqTauxInteret() * 0.40 / 100) * reqSolde());
		}
		if (reqNombreTransactions() > 25 and reqNombreTransactions() < 36)
		{
			interets = -((reqTauxInteret() * 0.80 / 100) * reqSolde());
		}
		if (reqNombreTransactions() > 35)
		{
			interets = -((reqTauxInteret() / 100) * reqSolde());
		}
	}

	return interets;
}

/**
 * \brief retourne une copie allouée sur le monceau de l'objet Cheque courant.
 * \return un objet Cheque qui est une copie allouée sur le monceau de l'objet Cheque courant.
 */
Compte* Cheque::clone() const
{
	return new Cheque(*this); // Appel du constructeur copie
}

/**
 * \brief Teste les invariants de la classe Compte. L'invariant de cette classe s'assure que l'objet compte est valide
 */
void Cheque::verifieInvariant() const
{
	INVARIANT(m_nombreTransactions >= 0);
	INVARIANT(m_nombreTransactions <= 40);
	INVARIANT(reqTauxInteret() >= m_tauxInteretMinimum);
}

} // namespace banque
