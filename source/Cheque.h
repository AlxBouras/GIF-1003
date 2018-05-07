/**
 * \file Cheque.h
 * \brief Fichier qui contient l'interface de la classe dérivée Cheque qui sert au maintien et
 * 		  à la manipulation des informations de comptes chèques.
 * \author Alexandre Bouras, 111 149 065
 * \version 1.0
 * \date 26/03/2018
 */

#ifndef CHEQUE_H_
#define CHEQUE_H_

#include "Compte.h"

namespace banque
{
/**
 * \class Cheque
 * \brief Cette classe dérivée sert à la création d'un compte chèque et au maintien et à la
 * 		  manipulation des informations du compte chèque.
 *
 * 	            La classe maintient dans un état cohérent ces renseignements.
 *             	Elle valide ce qu'on veut lui assigner.
 *              <p>
 *              La classe n'accepte que des comptes valides, c'est la
 *              responsabilité de l'utilisateur de la classe de s'en assurer.
 *              <p>
 *              Attributs:  int m_nombreTransactions 	le nombre de transactions effectués au compte chèque;
 *                          double m_tauxInteretMinimum	le taux d'intérêt minimum du compte chèque;
 *
 *							De plus, la classe utilise les attributs suivants, qui sont ceux de la
 *							classe Compte, de laquelle Cheque est dérivée:
 *
 *							int m_noCompte			le numéro du compte;
 *                          double m_tauxInteret	le taux d'intérêt du compte;
 *                          double m_solde			le solde du compte;
 *                          string m_description	la description du compte;
 *                          Date m_dateOuverture	la date d'ouverture du compte
 *
 * \invariant m_nombreTransactions >= 0 et m_nombreTransactions <= 40.
 * \invariant m_tauxInteret > m_tauxInteretMinimum.
 */
class Cheque: public Compte
{
public:
	Cheque(int p_noCompte, double p_tauxInteret, double p_solde,
		   int p_nombreTransactions, double p_tauxInteretMinimum = 0.1,
		   const std::string& p_description="Cheque");

	// Accesseurs
	double reqTauxInteretMinimum() const;
	int reqNombreTransactions() const;
	virtual std::string reqCompteFormate() const;

	// Mutateurs
	void asgNombreTransactions (int p_nombreTransactions);
	virtual void asgTauxInteret(const double p_tauxInteret);

	virtual double calculerInteret() const;
	virtual Compte* clone() const;

private:
	int m_nombreTransactions;
	double m_tauxInteretMinimum;

	void verifieInvariant() const;
};

} // namespace banque



#endif /* CHEQUE_H_ */
