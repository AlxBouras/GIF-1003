/**
 * \file Epargne.h
 * \brief Fichier qui contient l'interface de la classe dérivée Epargne qui sert au maintien et
 * 		  à la manipulation des informations de comptes épargnes.
 * \author Alexandre Bouras, 111 149 065
 * \version 1.0
 * \date 26/03/2018
 */

#ifndef EPARGNE_H_
#define EPARGNE_H_

#include "Compte.h"

namespace banque
{
/**
 * \class Epargne
 * \brief Cette classe dérivée sert à la création d'un compte épargne et au maintien et à la
 * 		  manipulation des informations du compte épargne.
 *
 * 	            La classe maintient dans un état cohérent ces renseignements.
 *             	Elle valide ce qu'on veut lui assigner.
 *              <p>
 *              La classe n'accepte que des comptes valides, c'est la
 *              responsabilité de l'utilisateur de la classe de s'en assurer.
 *              <p>
 *              Attributs:	La classe ne possède aucun attribut propre, il s'agit des attributs
 *              			de la classe Compte, de laquelle Epargne est dérivée:
 *
 *              		  	int m_noCompte			le numéro du compte;
 *                          double m_tauxInteret	le taux d'intérêt du compte;
 *                          double m_solde			le solde du compte;
 *                          string m_description	la description du compte;
 *                          Date m_dateOuverture	la date d'ouverture du compte
 * \invariant m_tauxInteret >= 0.1 et m_tauxInteret <= 3.5
 */
class Epargne: public Compte
{
public:
	Epargne(int p_noCompte, double p_tauxInteret, double p_solde,
			 const std::string& p_description="Epargne");

	// Accesseur
	virtual std::string reqCompteFormate() const;

	// Mutateur
	virtual void asgTauxInteret(const double p_tauxInteret);

	virtual double calculerInteret() const;
	virtual Compte* clone() const;

private:
	void verifieInvariant() const;
};

} // namespace banque

#endif /* EPARGNE_H_ */
