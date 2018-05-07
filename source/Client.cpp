/**
 * \file Client.cpp
 * \brief Implantation de la classe Client
 * \author Alexandre Bouras, 111 149 065
 * \version 2.0
 * \date 19/03/2018
 */

#include "Client.h"
#include "validationFormat.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace util;

namespace banque
{
/**
 * \brief constructeur avec paramètres
 * 		  On construit un objet Client a partir de valeurs passées en paramètres.
 * \param[in] p_noFolio est un entier (int) qui représente le numéro de folio du client
 * \param[in] p_nom est une chaîne de caractères (string) qui représente le nom du client
 * \param[in] p_prenom est une chaîne de caractères (string) qui représente le prénom du client
 * \param[in] p_telephone est une chaîne de caractères (string) qui représente le numéro de téléphone du client
 * \pre p_noFolio doit correspondre à un numéro compris dans l'intervalle [1000, 10000[
 * \pre p_nom, p_prenom doivent correspondre à un nom, prénom avec le bon format (uniquement des lettres; les espaces sont permis)
 * \pre p_telephone doit correspondre à un numéro de télphone avec le bon format (CCC CCC-CCCC) et un indicatif régional valide
 * \pre p_dateNaissance doit correspondre à une date valide dont l'année est comprise dans l'intervalle [1970, 2037]
 * \post m_noFolio prend la valeur de p_noFolio
 * \post m_nom prend la valeur de p_nom
 * \post m_prenom prend la valeur de p_prenom
 * \post m_telephone prend la valeur de p_telephone
 * \post m_dateNaissance prend la valeur de p_dateNaissance
 */
Client::Client(int p_noFolio, const string& p_nom, const std::string& p_prenom,
        	   const std::string& p_telephone, const util::Date& p_dateNaissance)
: m_noFolio(p_noFolio), m_nom(p_nom), m_prenom(p_prenom), m_telephone(p_telephone),
  m_dateNaissance(p_dateNaissance.reqJour(), p_dateNaissance.reqMois(), p_dateNaissance.reqAnnee())
{
	PRECONDITION(p_noFolio >= 1000);
	PRECONDITION(p_noFolio < 10000);
	PRECONDITION(util::validerFormatNom(p_nom));
	PRECONDITION(util::validerFormatNom(p_prenom));
	PRECONDITION(util::validerTelephone(p_telephone));
	PRECONDITION(Date::validerDate(p_dateNaissance.reqJour(), p_dateNaissance.reqMois(),
								   p_dateNaissance.reqAnnee()));

	POSTCONDITION(m_noFolio == p_noFolio);
	POSTCONDITION(m_nom == p_nom);
	POSTCONDITION(m_prenom == p_prenom);
	POSTCONDITION(m_telephone == p_telephone);
	POSTCONDITION(m_dateNaissance == p_dateNaissance);

	INVARIANTS();
}

/**
 * \brief destructeur: responsable de désalouer tous les comptes du client
 * 		  dans le vecteur m_vComptes
 * \return aucun retour
 */
Client::~Client()
{
	for (unsigned i = 0; i < m_vComptes.size(); i++)
		{
			delete m_vComptes[i];
		}
}

/**
 * \brief retourne le numéro de folio du client
 * \return un entier (int) qui représente le numéro de folio du client
 */
int Client::reqNoFolio() const
{
    return m_noFolio;
}

/**
 * \brief retourne le nom du client
 * \return une chaîne de caractères (string) qui représente le nom du client
 */
const string& Client::reqNom() const
{
    return m_nom;
}

/**
 * \brief retourne le prénom du client
 * \return une chaîne de caractères (string) qui représente le prénom du client
 */
const string& Client::reqPrenom() const
{
    return m_prenom;
}

/**
 * \brief retourne la date d'ouverture du dossier du client
 * \return un objet Date qui représente la date d'ouverture du dossier client
 */
string Client::reqDateDeNaissance() const
{
    return m_dateNaissance.reqDateFormatee();
}

/**
 * \brief retourne le numéro de téléphone du client
 * \return une chaîne de caractères (string) qui représente le numéro de téléphone du client
 */
const string& Client::reqTelephone() const
{
    return m_telephone;
}

/**
 * \brief retourne les informations d'un objet Client formatés dans une chaîne de caractères (string)
 * \return les informations d'un objet Client dans une chaîne de caractères
 */
string Client::reqClientFormate() const
{
    ostringstream os;
    os  << "Client no de folio : " << reqNoFolio() << endl
        << reqPrenom() << " " << reqNom() << endl
        << "Date de naissance : " << reqDateDeNaissance() << endl
        << reqTelephone() << endl;

    return os.str();
}

/**
 * \brief retourne les informations des objets (Compte ou ses dérivés) contenus dans la liste (vector)
 * 		  de comptes du client formatés dans une chaîne de caractères (string)
 * \return les informations des objets Compte (ou ses dérivés) du client dans une chaîne de caractères
 */
string Client::reqReleves() const
{
	ostringstream os;
	os	<< reqClientFormate();

	for (unsigned i = 0; i < m_vComptes.size(); i++)
	{
		os << m_vComptes[i]->reqCompteFormate();
	}

	return os.str();
}

/**
 * \brief assigne un numéro de téléphone au dossier client
 * \param[in] p_telephone est une chaîne de caractères (string)
 * 			  qui représente un numéro de téléphone du client
 * \pre p_telephone doit correspondre à un numéro de télphone avec le bon format (CCC CCC-CCCC)
 * 		et un indicatif régional valide
 * \post m_telephone prend la valeur de p_telephone
 * \return aucun retour
 */
void Client::asgTelephone(const string& p_telephone)
{
	PRECONDITION(util::validerTelephone(p_telephone));
    m_telephone = p_telephone;
	POSTCONDITION(m_telephone == p_telephone);
	INVARIANTS();
}

/**
 * \brief surcharge de l'opérateur ==
 * \param[in] p_client qui est un objet Client
 * \return un booléen indiquant si tous les attributs de deux objets
 * \	   Client sont égaux
 */
bool Client::operator ==(const Client& p_client) const
{
    bool estEgal = false;

    if (m_noFolio == p_client.m_noFolio and m_nom == p_client.m_nom
        and m_prenom == p_client.m_prenom and m_telephone == p_client.m_telephone
        and m_dateNaissance == p_client.m_dateNaissance)
    {
        estEgal = true;
    }

    return estEgal;
}

/**
 * \brief surcharge de l'opérateur <
 * \param[in] p_client qui est un objet Client
 * \return un booléen indiquant si le numéro de l'objet Client passé en paramètre
 * \	   est plus petit que le numéro du client courant
 */
bool Client::operator <(const Client& p_client) const
{
    return m_noFolio < p_client.m_noFolio;
}

/**
 * \brief ajoute un compte à la liste (vector) de comptes du client si ce compte n'est pas déjà présent
 * \param[in] p_nouveauCompte est un objet Compte (ou un objet d'une classe dérivée de Compte),
 * 			  qui représente un nouveau compte d'un client
 * \post la liste (vector) de compte du client contient p_nouveauCompte.
 * \return aucun retour
 */
void Client::ajouterCompte (const Compte& p_nouveauCompte)
{
	if (compteEstDejaPresent(p_nouveauCompte.reqNoCompte()) == false)
	{
		m_vComptes.push_back(p_nouveauCompte.clone());
	}

	POSTCONDITION(compteEstDejaPresent(p_nouveauCompte.reqNoCompte()) == true)

}

bool Client::compteEstDejaPresent(int p_noCompte) const
{
	bool estPresent = false;

	for (unsigned i = 0; i < m_vComptes.size(); i++)
	{
		if(m_vComptes[i]->reqNoCompte() == p_noCompte)
		{
			estPresent = true;
		}
	}

	return estPresent;
}

/**
 * \brief Teste les invariants de la classe Client. L'invariant de cette classe s'assure que l'objet client est valide
 */
void Client::verifieInvariant() const
{
	INVARIANT(m_noFolio >= 1000);
	INVARIANT(m_noFolio < 10000);
	INVARIANT(util::validerFormatNom(m_nom));
	INVARIANT(util::validerFormatNom(m_prenom));
	INVARIANT(util::validerTelephone(m_telephone));
	INVARIANT(Date::validerDate(m_dateNaissance.reqJour(), m_dateNaissance.reqMois(),
							 	m_dateNaissance.reqAnnee()))
}

} // namespace banque
