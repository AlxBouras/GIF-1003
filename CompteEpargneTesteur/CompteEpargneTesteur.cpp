/**
 * \file CompteEpargneTesteur.cpp
 * \brief Implantation des tests unitaires de la classe Epargne
 * \author Alexandre Bouras, 111 149 065
 * \date 2018-03-19
 */

#include<gtest/gtest.h>
#include "Epargne.h"
#include "Date.h"
using namespace banque;

/**
 * \brief Test du Constructeur Epargne(int p_noCompte, double p_tauxInteret, double p_solde,
			   	 	 	 	 	 	  const std::string& p_description)
 *        cas valide:
 *        		ConstructeurAvecParametres: Compte avec paramètres noCompte: 10,
 *        			  						tauxInteret: 0.1, solde: 200 et description: "Epargne"
 *
 *        		ConstructeurAvecDescriptionParDefaut : Compte avec paramètres noCompte: 10,
 *        			  								tauxInteret: 0.1, solde: 200
 *        cas invalides:
 *        			p_tauxInteret = 0.09
 *        			p_tauxInteret = 3.51
 */
TEST(Epargne, ConstructeurAvecParametres)
{
	Epargne testEpargne(10, 0.1, 200, "Epargne");
	ASSERT_EQ(10, testEpargne.reqNoCompte());
	ASSERT_EQ(0.1, testEpargne.reqTauxInteret());
	ASSERT_EQ(200, testEpargne.reqSolde());
	ASSERT_EQ("Epargne", testEpargne.reqDescription());
}
TEST(Epargne, ConstructeurAvecDescriptionParDefaut)
{
	Epargne testEpargne(10, 0.1, 200);
	ASSERT_EQ(10, testEpargne.reqNoCompte());
	ASSERT_EQ(0.1, testEpargne.reqTauxInteret());
	ASSERT_EQ(200, testEpargne.reqSolde());
	ASSERT_EQ("Epargne", testEpargne.reqDescription());
}
// cas invalides
TEST(Epargne, ConstructeurTauxInteretInvalide1)
{
	ASSERT_THROW(Epargne testEpargne(10, 0.09, 200, "Epargne"), PreconditionException);
}
TEST(Epargne, ConstructeurTauxInteretInvalide2)
{
	ASSERT_THROW(Epargne testEpargne(10, 3.51, 200, "Epargne"), PreconditionException);
}

/**
 * \class UnCompteEpargne
 * \brief Fixture UnCompteEpargne pour la création d'un objet Epargne pour les tests
 */
class UnCompteEpargne: public ::testing::Test
{
public:
	UnCompteEpargne() :
		t_epargne(10, 0.1, 200, "Epargne")
	{
	}

	Epargne t_epargne;
};

/**
 * \brief Test de la méthode virtual std::string reqNomFormate() const
 *        cas valide reqNomFormate: Créer le flux d'affichage attendu et vérification
 *        							s'il est le méme que celui construit par la méthode
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompteEpargne, reqCompteFormate)
{
	std::ostringstream os1,os2;
	os1 << "Compte Epargne" << std::endl
		<< t_epargne.Compte::reqCompteFormate()
		<< "Interet \t\t: " << t_epargne.calculerInteret() << " $" << std::endl;

	os2 << t_epargne.reqCompteFormate();

	ASSERT_EQ(os1.str(), os2.str());
}

/**
 * \brief Test de la méthode void asgTauxInteret(const double p_tauxInteret)
 *        cas valide asgTauxInteret : Compte par défaut a un taux d'intérêt de 0.1 (0.1%),
 *        							  vérification de l'assignation
 *        cas invalides:
 *        			p_tauxInteret = 0.09
 *        			p_tauxInteret = 3.51
 */
TEST_F(UnCompteEpargne, asgTauxInteret)
{
	ASSERT_EQ(0.1, t_epargne.reqTauxInteret());
	t_epargne.asgTauxInteret(2);
	ASSERT_EQ(2, t_epargne.reqTauxInteret());
}
// cas invalides
TEST_F(UnCompteEpargne, asgTauxInteretInvalide1)
{
	ASSERT_THROW(t_epargne.asgTauxInteret(0.09), PreconditionException);
}
TEST_F(UnCompteEpargne, asgTauxInteretInvalide2)
{
	ASSERT_THROW(t_epargne.asgTauxInteret(3.51), PreconditionException);
}

/**
 * \brief Test de la méthode virtual double calculerInteret() const
 *        cas valide calculerInteret : Compte par défaut a un solde de 200 et
 *        							   un taux d'intérêt de 0.1 (0.1%), vérification du calcul
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompteEpargne, calculerInteret)
{
	ASSERT_EQ(0.2, t_epargne.calculerInteret());
}

/**
 * \brief Test de la méthode virtual Compte* clone() const
 *        cas valides:
 *        		cloneCompteEpargne : Compte par défaut a un solde de 200 et
 *        							 un taux d'intérêt de 0.1 (0.1%), vérification
 *        							 que le clone possède les mêmes attributs
 *
 *        		cloneCompteEpargnePtr : Vérification que le pointeur du compte par défaut
 *        								et du clone ont des adresses différentes
 *
 *        cas invalides:Aucun d'identifié
 */
TEST_F(UnCompteEpargne, cloneCompteEpargne)
{
	Compte* clone = t_epargne.clone();;
	ASSERT_EQ(t_epargne.reqNoCompte(), clone->reqNoCompte());
	ASSERT_EQ(t_epargne.reqTauxInteret(), clone->reqTauxInteret());
	ASSERT_EQ(t_epargne.reqSolde(), clone->reqSolde());
	ASSERT_EQ(t_epargne.reqDescription(), clone->reqDescription());
	ASSERT_EQ(t_epargne.reqDateOuverture(), clone->reqDateOuverture());
}
TEST_F(UnCompteEpargne, cloneCompteEpargnePtr)
{
	Compte* clone = t_epargne.clone();
	Compte* ptr_compte = &t_epargne;
	ASSERT_NE(ptr_compte, clone);
}
