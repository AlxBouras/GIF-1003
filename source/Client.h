/**
 * \file Client.h
 * \brief Fichier qui contient l'interface de la classe Client qui sert au maintien et à la manipulation des informations clients.
 * \author Alexandre Bouras, 111 149 065
 * \version 2.0
 * \date 19/03/2018
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <vector>
#include "Date.h"
#include "ContratException.h"
#include "Compte.h"

namespace banque
{
/**
 * \class Client
 * \brief Cette classe sert à la création d'un dossier client et au maintien et à la manipulation des informations clients.
 *
 * 	            La classe maintient dans un état cohérent ces renseignements.
 *             	Elle valide ce qu'on veut lui assigner.
 *              <p>
 *              La classe n'accepte que des clients valides, c'est la
 *              responsabilité de l'utilisateur de la classe de s'en assurer.
 *              <p>
 *              Attributs:  int m_noFolio			le numéro de folio du client;
 *                          string m_nom			le nom du client;
 *                          string m_prenom			le prénom du client;
 *                          string m_telephone		le numéro de télphone du client;
 *                          Date m_dateNaissance	la date de naissance du client
 * \invariant m_noFolio >= 1000 et m_noFolio < 10000;
 * \invariant m_nom et m_prenom doivent être dans un format valide selon la fonction validerFormatNom;
 * \invariant m_telephone doit être dans un format valide selon la fonction validerTelephone;
 * \invariant m_dateNaissance.reqAnnee >= 1970 et m_dateNaissance.reqAnnee <= 2037
 */
class Client
{
public:
	Client(int p_noFolio, const std::string& p_nom, const std::string& p_prenom,
			const std::string& p_telephone, const util::Date& p_dateNaissance);
	~Client();

	// Accesseurs
	int reqNoFolio() const;
	const std::string& reqNom() const;
	const std::string& reqPrenom() const;
	std::string reqDateDeNaissance() const;
	const std::string& reqTelephone() const;
	std::string reqClientFormate() const;
	std::string reqReleves() const;

	// Mutateur
	void asgTelephone(const std::string& p_telephone);

	// Surdéfinition d'opérateurs
	bool operator ==(const Client& p_client) const;
	bool operator <(const Client& p_client) const;

	void ajouterCompte (const Compte& p_nouveauCompte);

	bool compteEstDejaPresent(int p_noCompte) const;
private:
	int m_noFolio;
	std::string m_nom;
	std::string m_prenom;
	std::string m_telephone;
	util::Date m_dateNaissance;

	std::vector<Compte*> m_vComptes;

	//bool compteEstDejaPresent(int p_noCompte) const;
	void verifieInvariant() const;

	// Opérateur d'assignation et constructeur copie déclarés pour empêcher leur utilisation
	const Client& operator= (const Client& p_client);
	Client (const Client& p_client);
};

} // namespace banque

#endif /* CLIENT_H_ */
