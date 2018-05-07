/**
 * \file Compte.h
 * \brief Fichier qui contient l'interface de la classe de base Compte qui sert au maintien et
 * 		  à la manipulation des informations de comptes.
 * \author Alexandre Bouras, 111 149 065
 * \version 1.0
 * \date 19/03/2018
 */

#ifndef COMPTE_H_
#define COMPTE_H_

#include <string>
#include "Date.h"
#include "ContratException.h"

namespace banque
{
/**
 * \class Compte
 * \brief Cette classe abstraite sert à la création de classes dérivées correspondant à des types de comptes bancaires
 * 		  et au maintien et à la manipulation des informations de comptes créés avec celle-ci.
 *
 *	            La classe maintient dans un état cohérent ces renseignements.
 *             	Elle valide ce qu'on veut lui assigner.
 *              <p>
 *              La classe n'accepte que des comptes valides, c'est la
 *              responsabilité de l'utilisateur de la classe de s'en assurer.
 *              <p>
 *              Attributs:  int m_noCompte			le numéro du compte;
 *                          double m_tauxInteret	le taux d'intérêt du compte;
 *                          double m_solde			le solde du compte;
 *                          string m_description	la description du compte;
 *                          Date m_dateOuverture	la date d'ouverture du compte
 * \invariant m_noCompte >= 0;
 * \invariant (!(m_description.empty());
 */
class Compte
{
public:
	Compte(int p_noCompte, double p_tauxInteret, double p_solde,
		   const std::string& p_description);
	virtual ~Compte() {};

	// Accesseurs
	int reqNoCompte() const;
	double reqTauxInteret() const;
	double reqSolde() const;
	const std::string& reqDescription() const;
	std::string reqDateOuverture() const;
	virtual std::string reqCompteFormate() const;

	// Mutateurs
	virtual void asgTauxInteret(const double p_tauxInteret);
	void asgSolde(const double p_solde);
	void asgDescription(const std::string& p_description);

	virtual double calculerInteret() const = 0;
	virtual Compte* clone() const = 0;

private:
	int m_noCompte;
	double m_tauxInteret;
	double m_solde;
	std::string m_description;
	util::Date m_dateOuverture;

	void verifieInvariant() const;
};

} // namespace banque

#endif /* COMPTE_H_ */
