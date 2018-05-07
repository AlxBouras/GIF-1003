/**
 * \file Compte.cpp
 * \brief Implantation de la classe Compte
 * \author Alexandre Bouras, 111 149 065
 * \version 1.0
 * \date 19/03/2018
 */

#include "Compte.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace util;
namespace banque
{
/**
 * \brief constructeur avec paramètres
 * 		  On construit un objet Compte a partir de valeurs passées en paramètres.
 * \param[in] p_noCompte est un entier (int) qui représente le numéro de compte.
 * \param[in] p_tauxInteret est un nombre réel (double) qui représente le taux d'intérêt du compte.
 * \param[in] p_solde est un entier (int) qui représente le solde du compte.
 * \param[in] p_description est une chaîne de caractères (string) qui représente la description du compte.
 * \pre p_noCompte doit être >= 0.
 * \pre p_description ne doit pas être une chaîne de caractères vide.
 * \post m_noCompte prend la valeur de p_noCompte.
 * \post m_tauxInteret prend la valeur de p_tauxInteret.
 * \post m_solde prend la valeur de p_solde.
 * \post m_description prend la valeur de p_description.
 */
Compte::Compte(int p_noCompte, double p_tauxInteret, double p_solde,
		   const std::string& p_description)
: m_noCompte(p_noCompte), m_tauxInteret(p_tauxInteret), m_solde(p_solde), m_description(p_description)
{
	PRECONDITION(p_noCompte >= 0);
	PRECONDITION(!(p_description.empty()));

	m_dateOuverture = Date();

	POSTCONDITION(m_noCompte == p_noCompte);
	POSTCONDITION(m_tauxInteret == p_tauxInteret);
	POSTCONDITION(m_solde == p_solde);
	POSTCONDITION(m_description == p_description);

	INVARIANTS();
}

/**
 * \brief retourne le numéro de compte
 * \return un entier (int) qui représente le numéro de compte
 */
int Compte::reqNoCompte() const
{
	return m_noCompte;
}

/**
 * \brief retourne le taux d'intérêt du compte
 * \return un réel (double) qui représente le taux d'intérêt du compte
 */
double Compte::reqTauxInteret() const
{
	return m_tauxInteret;
}

/**
 * \brief retourne le solde du compte
 * \return un réel (double) qui représente le solde du compte
 */
double Compte::reqSolde() const
{
	return m_solde;
}

/**
 * \brief retourne la description du compte
 * \return une chaîne de caractères (string) qui représente la description du compte
 */
const string& Compte::reqDescription() const
{
	return m_description;
}

/**
 * \brief retourne la date d'ouverture du compte
 * \return un objet Date qui représente la date d'ouverture du compte
 */
string Compte::reqDateOuverture() const
{
	return m_dateOuverture.reqDateFormatee();
}

/**
 * \brief retourne les informations d'un objet Compte formatés dans une chaîne de caractères (string)
 * \return les informations d'un objet Compte dans une chaîne de caractères
 */
string Compte::reqCompteFormate() const
{
	ostringstream os;
	os  << "numero \t\t\t: " << reqNoCompte() << endl
	    << "Description \t\t: " << reqDescription() << endl
	    << "Date d'ouverture \t: " << reqDateOuverture() << endl
	    << "Taux d'intérêt \t\t: " << reqTauxInteret() << endl
		<< "Solde \t\t\t: " << reqSolde() << " $" << endl;

	return os.str();
}

/**
 * \brief assigne un taux d'intérêt au compte
 * \param[in] p_tauxInteret est un réel (double) qui représente un taux d'intérêt
 * \post m_tauxInteret prend la valeur de p_tauxInteret
 * \return aucun retour
 */
void Compte::asgTauxInteret(const double p_tauxInteret)
{
	m_tauxInteret = p_tauxInteret;
	POSTCONDITION(m_tauxInteret == p_tauxInteret);

	INVARIANTS();
}

/**
 * \brief assigne un solde au compte
 * \param[in] p_solde est un réel (double) qui représente le solde du compte
 * \post m_solde prend la valeur de p_solde
 * \return aucun retour
 */
void Compte::asgSolde(const double p_solde)
{
	m_solde = p_solde;
	POSTCONDITION(m_solde == p_solde);

	INVARIANTS();
}

/**
 * \brief assigne une description au compte
 * \param[in] p_description est une chaîne de caractères (string)
 * 			  qui représente une description du compte
 * \pre p_solde ne doit pas être une chaîne de caractères vide
 * \post m_description prend la valeur de p_description
 * \return aucun retour
 */
void Compte::asgDescription(const std::string& p_description)
{
	PRECONDITION(!(p_description.empty()));
	m_description = p_description;
	POSTCONDITION(m_description == p_description);

	INVARIANTS();
}

/**
 * \brief Teste les invariants de la classe Compte. L'invariant de cette classe s'assure que l'objet compte est valide
 */
void Compte::verifieInvariant() const
{
	INVARIANT(m_noCompte >= 0);
	INVARIANT(!(m_description.empty()));
}

} // namespace banque
