/**
 * \file CompteTesteur.cpp
 * \brief Implantation des tests unitaires de la classe Compte
 *        Compte étant une classe abstraite, on crée une classe concrète
 *        dérivée de cette classe afin de pouvoir effectuer les tests
 * \author Alexandre Bouras, 111 149 065
 * \version 1.0
 * \date 4 avril 2018
 */

#include<gtest/gtest.h>
#include "Compte.h"
#include "Date.h"
using namespace banque;

/**
 * \class CompteDeTest
 * \brief classe de test permettant de tester la classe abstraite Compte
 */
class CompteDeTest: public Compte
{
public:
	CompteDeTest(int p_noCompte, double p_tauxInteret, double p_solde,
			   	 const std::string& p_description)
	:Compte(p_noCompte, p_tauxInteret, p_solde, p_description)
	{
	}
	//méthode doit être implantée car la classe est concrète
	virtual double calculerInteret() const
	{
		return (reqTauxInteret() / 100) * reqSolde();
	}
	//méthode doit être implantée car la classe est concrète
	virtual Compte* clone() const
	{
		return new CompteDeTest(*this);
	}
};

/**
 * \brief Test du Constructeur Compte(int p_noCompte, double p_tauxInteret, double p_solde,
			   	 	 	 	 	 	  const std::string& p_description)
 *        cas valide: ConstructeurAvecParametres: Compte avec paramètres noCompte: 1,
 *        			  tauxInteret: 2, solde: 100 et description: "test"
 *        cas invalides:
 *        			p_noCompte = -1
 *        			p_description vide
 *
 */
TEST(Compte, ConstructeurAvecParametres)
{
	CompteDeTest compteTest(1, 2, 100, "test");
	ASSERT_EQ(1, compteTest.reqNoCompte());
	ASSERT_EQ(2, compteTest.reqTauxInteret());
	ASSERT_EQ(100, compteTest.reqSolde());
	ASSERT_EQ("test", compteTest.reqDescription());

}
// cas invalides
TEST(Compte, ConstructeurNoCompteInvalide)
{
	ASSERT_THROW(CompteDeTest compteTest(-1, 2, 100, "test");, PreconditionException);
}
TEST(Compte, ConstructeurDescriptionInvalide)
{
	ASSERT_THROW(CompteDeTest compteTest(1, 2, 100, "");, PreconditionException);
}

/**
 * \class UnCompte
 * \brief Fixture UnCompte pour la création d'un objet Compte pour les tests
 */
class UnCompte: public ::testing::Test
{
public:
	UnCompte() :
		t_compte(1, 2, 100, "test")
	{
	}

	CompteDeTest t_compte;
};

/**
 * \brief Test de la méthode int reqNoCompte() const
 *        cas valide reqNoCompte : Numéro du Compte par défaut est 1 , vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, reqNoCompte)
{
	ASSERT_EQ(1, t_compte.reqNoCompte());
}

/**
 * \brief Test de la méthode double reqTauxInteret() const
 *        cas valide reqTauxInteret : Compte par défaut a un taux d'intérêt de 2 (2%), vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, reqTauxInteret)
{
	ASSERT_EQ(2, t_compte.reqTauxInteret());
}

/**
 * \brief Test de la méthode double reqSolde() const
 *        cas valide reqSolde : Compte par défaut a un solde de 100, vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, reqSolde)
{
	ASSERT_EQ(100, t_compte.reqSolde());
}

/**
 * \brief Test de la méthode string& reqDescription() const
 *        cas valide reqDescription : Compte par défaut a une descritpion "test", vérification du retour
 *        cas invalide: Aucun d'identifié
 */
TEST_F(UnCompte, reqDescription)
{
	ASSERT_EQ("test", t_compte.reqDescription());
}

/**
 * \brief Test de la méthode string reqDateOuverture() const
 *        cas valide reqDateOuverture : Compte par défaut a la date d'ouverture de sa création, vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, reqDateOuverture)
{
	util::Date uneDate = util::Date();
	ASSERT_EQ(uneDate.reqDateFormatee(), t_compte.reqDateOuverture());
}

/**
 * \brief Test de la méthode virtual std::string reqNomFormate() const
 *        cas valide reqNomFormate: Créer le flux d'affichage attendu et vérification
 *        							s'il est le méme que celui construit par la méthode
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, reqCompteFormate)
{
	std::ostringstream os1,os2;
	os1	<< "numero \t\t\t: " << t_compte.reqNoCompte() << std::endl
		<< "Description \t\t: " << t_compte.reqDescription() << std::endl
	    << "Date d'ouverture \t: " << t_compte.reqDateOuverture() << std::endl
	    << "Taux d'intérêt \t\t: " << t_compte.reqTauxInteret() << std::endl
		<< "Solde \t\t\t: " << t_compte.reqSolde() << " $" << std::endl;

	os2 << t_compte.reqCompteFormate();

	ASSERT_EQ(os1.str(), os2.str());
}

/**
 * \brief Test de la méthode void asgTauxInteret(const double p_tauxInteret)
 *        cas valide asgTauxInteret : Compte par défaut a un taux d'intérêt de 2 (2%), vérification de l'assignation
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, asgTauxInteret)
{
	ASSERT_EQ(2, t_compte.reqTauxInteret());
	t_compte.asgTauxInteret(1.5);
	ASSERT_EQ(1.5, t_compte.reqTauxInteret());
}

/**
 * \brief Test de la méthode void asgSolde(const double p_solde)
 *        cas valide asgSolde : Compte par défaut a un solde de 100.50, vérification de l'assignation
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, asgSolde)
{
	ASSERT_EQ(100, t_compte.reqSolde());
	t_compte.asgSolde(1000.5);
	ASSERT_EQ(1000.5, t_compte.reqSolde());
}

/**
 * \brief Test de la méthode void asgDescription(const double p_description)
 *        cas valide asgDescription : Compte par défaut a une descritpion "test", vérification de l'assignation
 *        cas invalides:
 *        			p_description vide
 */
TEST_F(UnCompte, asgDescription)
{
	ASSERT_EQ("test", t_compte.reqDescription());
	t_compte.asgDescription("un compte");
	ASSERT_EQ("un compte", t_compte.reqDescription());
}
// cas invalides
TEST_F(UnCompte, asgDescriptionInvalide)
{
	ASSERT_THROW(t_compte.asgDescription(""), PreconditionException);
}

/**
 * \brief Test de la méthode virtual double calculerInteret() const = 0
 *        cas valide calculerInteret : Compte par défaut a un solde de 100 et
 *        							   un taux d'intérêt de 2 (2%), vérification du calcul
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnCompte, calculerInteret)
{
	ASSERT_EQ(2, t_compte.calculerInteret());
}

/**
 * \brief Test de la méthode virtual Compte* clone() const
 *        cas valides:
 *        		cloneCompte : Compte par défaut a un solde de 100 et
 *        					  un taux d'intérêt de 2 (2%), vérification
 *        					  que le clone possède les mêmes attributs
 *
 *        		cloneComptePtr : Vérification que le pointeur du compte par défaut
 *        						 et du clone ont des adresses différentes
 *
 *        cas invalides:Aucun d'identifié
 */
TEST_F(UnCompte, cloneCompte)
{
	Compte* clone = t_compte.clone();;
	ASSERT_EQ(t_compte.reqNoCompte(), clone->reqNoCompte());
	ASSERT_EQ(t_compte.reqTauxInteret(), clone->reqTauxInteret());
	ASSERT_EQ(t_compte.reqSolde(), clone->reqSolde());
	ASSERT_EQ(t_compte.reqDescription(), clone->reqDescription());
	ASSERT_EQ(t_compte.reqDateOuverture(), clone->reqDateOuverture());
}
TEST_F(UnCompte, cloneComptePtr)
{
	Compte* clone = t_compte.clone();
	Compte* ptr_compte = &t_compte;
	ASSERT_NE(ptr_compte, clone);
}
