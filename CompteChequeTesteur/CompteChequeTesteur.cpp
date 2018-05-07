/**
 * \file CompteChequeTesteur.cpp
 * \brief Implantation des tests unitaires de la classe Cheque
 * \author Alexandre Bouras, 111 149 065
 * \date 2018-03-19
 */

#include<gtest/gtest.h>
#include "Cheque.h"
#include "Date.h"
using namespace banque;

/**
 * \brief Test du Constructeur Cheque(int p_noCompte, double p_tauxInteret, double p_solde,
		   	   	   	   	   	   	   	  int p_nombreTransactions, double p_tauxInteretMinimum,
		   	   	   	   	   	   	   	  const std::string& p_description)
 *        cas valides:
 *        			ConstructeurAvecParametres: Compte avec paramètres noCompte: 20,
 *        										tauxInteret: 0.1, solde: 500, nombreTransactions: 0,
 *        										tauxInteretMinimum: 0.1 et description: "Cheque"
 *
 *        			ConstructeurAvecTauxInteretMinimumParDefaut: Compte avec paramètres
 *        														 noCompte: 20, tauxInteret: 0.1,
 *        														 solde: 500 et nombreTransactions: 0
 *
 *        			ConstructeurAvecDescriptionParDefaut: Compte avec paramètres noCompte: 20,
 *        												  tauxInteret: 0.1, solde: 500, nombreTransactions: 0,
 *        												  tauxInteretMinimum: 0.1
 *
 *        cas invalides:
 *        			p_tauxInteret = 0.09 (inférieur au tauxInteretMinimum)
 *        			p_nombreTransactions = -1
 *        			p_nombreTransactions = 41
 *        			p_tauxInteretMinimum = 0.11 (supérieur au tauxInteret)
 */
TEST(Cheque, ConstructeurAvecParametres)
{
	Cheque testCheque(20, 0.1, 500, 0, 0.1 ,"Cheque");
	ASSERT_EQ(20, testCheque.reqNoCompte());
	ASSERT_EQ(0.1, testCheque.reqTauxInteret());
	ASSERT_EQ(500, testCheque.reqSolde());
	ASSERT_EQ(0, testCheque.reqNombreTransactions());
	ASSERT_EQ(0.1, testCheque.reqTauxInteretMinimum());
	ASSERT_EQ("Cheque", testCheque.reqDescription());
}
TEST(Cheque, ConstructeurAvecTauxInteretMinimumParDefaut)
{
	Cheque testCheque(20, 0.1, 500, 0);
	ASSERT_EQ(20, testCheque.reqNoCompte());
	ASSERT_EQ(0.1, testCheque.reqTauxInteret());
	ASSERT_EQ(500, testCheque.reqSolde());
	ASSERT_EQ(0, testCheque.reqNombreTransactions());
	ASSERT_EQ(0.1, testCheque.reqTauxInteretMinimum());
	ASSERT_EQ("Cheque", testCheque.reqDescription());
}
TEST(Cheque, ConstructeurAvecDescriptionParDefaut)
{
	Cheque testCheque(20, 0.1, 500, 0, 0.1);
	ASSERT_EQ(20, testCheque.reqNoCompte());
	ASSERT_EQ(0.1, testCheque.reqTauxInteret());
	ASSERT_EQ(500, testCheque.reqSolde());
	ASSERT_EQ(0, testCheque.reqNombreTransactions());
	ASSERT_EQ(0.1, testCheque.reqTauxInteretMinimum());
	ASSERT_EQ("Cheque", testCheque.reqDescription());
}
// cas invalides
TEST(Cheque, ConstructeurTauxInteretInvalide)
{
	ASSERT_THROW(Cheque testCheque(20, 0.09, 500, 0, 0.1 ,"Cheque"), PreconditionException);
}
TEST(Cheque, ConstructeurNombreTransactionsInvalide1)
{
	ASSERT_THROW(Cheque testCheque(20, 0.09, 500, -1, 0.1 ,"Cheque"), PreconditionException);
}
TEST(Cheque, ConstructeurNombreTransactionsInvalide2)
{
	ASSERT_THROW(Cheque testCheque(20, 0.09, 500, 41, 0.1 ,"Cheque"), PreconditionException);
}
TEST(Cheque, ConstructeurTauxInteretMinimumInvalide)
{
	ASSERT_THROW(Cheque testCheque(20, 0.1, 500, 0, 0.11 ,"Cheque"), PreconditionException);
}

/**
 * \class UnCompteCheque
 * \brief Fixture UnCompteCheque pour la création d'un objet Cheque pour les tests
 */
class UnCompteCheque: public ::testing::Test
{
public:
	UnCompteCheque() :
		t_cheque(20, 0.1, 500, 0, 0.1 ,"Cheque")
	{
	}

	Cheque t_cheque;
};

/**
 * \brief Test de la méthode double reqTauxInteretMinimum() const
 *        cas valide reqTauxInteretMinimum : Compte par défaut a un taux d'intérêt de 0.1 (0.1%), vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompteCheque, reqTauxInteretMinimum)
{
	ASSERT_EQ(0.1, t_cheque.reqTauxInteretMinimum());
}

/**
 * \brief Test de la méthode int reqNombreTransactions() const
 *        cas valide reqNombreTransactions : Compte par défaut a 0 transactions, vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompteCheque, reqNombreTransactions)
{
	ASSERT_EQ(0, t_cheque.reqNombreTransactions());
}

/**
 * \brief Test de la méthode virtual std::string reqNomFormate() const
 *        cas valide reqNomFormate: Créer le flux d'affichage attendu et vérification
 *        							s'il est le méme que celui construit par la méthode
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompteCheque, reqCompteFormate)
{
	std::ostringstream os1,os2;
	os1 << "Compte Cheque" << std::endl
		<< t_cheque.Compte::reqCompteFormate()
		<< "nombre de transactions \t: " << t_cheque.reqNombreTransactions() << std::endl
		<< "Taux d'interet minimum \t: " << t_cheque.reqTauxInteretMinimum() << std::endl
		<< "Interet \t\t: " << t_cheque.calculerInteret() << " $" << std::endl;

	os2 << t_cheque.reqCompteFormate();

	ASSERT_EQ(os1.str(), os2.str());
}

/**
 * \brief Test de la méthode void asgNombreTransactions(int p_nombreTransactions)
 *        cas valide asgNombreTransactions : Compte par défaut a 0 transactions, vérification de l'assignation
 *        cas invalides:
 *        			p_nombreTransactions = -1
 *        			p_nombreTransactions = 41
 */
TEST_F(UnCompteCheque, asgNombreTransactions)
{
	ASSERT_EQ(0, t_cheque.reqNombreTransactions());
	t_cheque.asgNombreTransactions(20);
	ASSERT_EQ(20, t_cheque.reqNombreTransactions());
}
// cas invalides
TEST_F(UnCompteCheque, asgNombreTransactionsInvalide1)
{
	ASSERT_THROW(t_cheque.asgNombreTransactions(-1), PreconditionException);
}
TEST_F(UnCompteCheque, asgNombreTransactionsInvalide2)
{
	ASSERT_THROW(t_cheque.asgNombreTransactions(41), PreconditionException);
}

/**
 * \brief Test de la méthode void asgTauxInteret(const double p_tauxInteret)
 *        cas valide asgTauxInteret : Compte par défaut a un taux d'intérêt de 0.1 (0.1%),
 *        							  et un taux d'intérêt minimum de 0.1 (0.1%),
 *        							  vérification de l'assignation
 *        cas invalides:
 *        			p_tauxInteret = 0.09
 */
TEST_F(UnCompteCheque, asgTauxInteret)
{
	ASSERT_EQ(0.1, t_cheque.reqTauxInteret());
	t_cheque.asgTauxInteret(2);
	ASSERT_EQ(2, t_cheque.reqTauxInteret());
}
// cas invalides
TEST_F(UnCompteCheque, asgDescriptionInvalide)
{
	ASSERT_THROW(t_cheque.asgTauxInteret(0.09), PreconditionException);
}

/**
 * \brief Test de la méthode virtual double calculerInteret() const
 *        cas valides:
 *        		calculerInteret1: Compte par défaut a un solde de 500, 0 transactions et
 *        						  un taux d'intérêt et un taux d'intérêt minimum de 0.1 (0.1%),
 *        						  vérification du calcul
 *
 *        		calculerInteret2: Modification du solde à -100 et du taux d'intérêt a 1%,
 *        						  transactions et un taux d'intérêt minimum de 0.1 (0.1%),
 *        						  vérification du calcul
 *
 *        		calculerInteret3: Modification du solde à -100, du taux d'intérêt a 1% et des
 *        						  transactions à 11  avec un taux d'intérêt minimum de 0.1 (0.1%),
 *        						  vérification du calcul
 *
 *        		calculerInteret4: Modification du solde à -100, du taux d'intérêt a 1% et des
 *       						  transactions à 26  avec un taux d'intérêt minimum de 0.1 (0.1%),
 *        						  vérification du calcul
 *
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompteCheque, calculerInteret1)
{
	ASSERT_EQ(0, t_cheque.calculerInteret());
}
TEST_F(UnCompteCheque, calculerInteret2)
{
	t_cheque.asgSolde(-100);
	t_cheque.asgTauxInteret(1);
	ASSERT_EQ(0.1, t_cheque.calculerInteret());
}
TEST_F(UnCompteCheque, calculerInteret3)
{
	t_cheque.asgSolde(-100);
	t_cheque.asgTauxInteret(1);
	t_cheque.asgNombreTransactions(11);
	ASSERT_EQ(0.4, t_cheque.calculerInteret());
}
TEST_F(UnCompteCheque, calculerInteret4)
{
	t_cheque.asgSolde(-100);
	t_cheque.asgTauxInteret(1);
	t_cheque.asgNombreTransactions(26);
	ASSERT_EQ(0.8, t_cheque.calculerInteret());
}
TEST_F(UnCompteCheque, calculerInteret5)
{
	t_cheque.asgSolde(-100);
	t_cheque.asgTauxInteret(1);
	t_cheque.asgNombreTransactions(36);
	ASSERT_EQ(1, t_cheque.calculerInteret());
}

/**
 * \brief Test de la méthode virtual Compte* clone() const
 *        cas valides:
 *        		cloneCompteCheque :  Compte par défaut a un solde de 500, 0 transactions et
 *        						     un taux d'intérêt et un taux d'intérêt minimum de 0.1 (0.1%),
 *        						  	 vérification que le clone possède les mêmes attributs
 *
 *				cloneCompteChequePtr : Vérification que le pointeur du compte par défaut
 *        							   et du clone ont des adresses différentes
 *
 *        cas invalides:Aucun d'identifié
 */
TEST_F(UnCompteCheque, cloneCompteCheque)
{
	Compte* clone = t_cheque.clone();
	ASSERT_EQ(t_cheque.reqNoCompte(), clone->reqNoCompte());
	ASSERT_EQ(t_cheque.reqTauxInteret(), clone->reqTauxInteret());
	ASSERT_EQ(t_cheque.reqSolde(), clone->reqSolde());
	ASSERT_EQ(t_cheque.reqDateOuverture(), clone->reqDateOuverture());
	ASSERT_EQ(t_cheque.reqDescription(), clone->reqDescription());
}
TEST_F(UnCompteCheque, cloneCompteChequePtr)
{
	Compte* clone = t_cheque.clone();
	Compte* ptr_compte = &t_cheque;
	ASSERT_NE(ptr_compte, clone);
}
