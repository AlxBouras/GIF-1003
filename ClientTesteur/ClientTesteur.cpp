/**
 * \file ClientTesteur.cpp
 * \brief Implantation des tests unitaires de la classe Client
 * \author Alexandre Bouras, 111 149 065
 * \date 2018-04-06
 */

#include<gtest/gtest.h>
#include "Client.h"
#include "Epargne.h"
#include "Cheque.h"
#include "Date.h"
using namespace banque;

/**
 * \brief Test du Constructeur Client(int p_noFolio, const std::string& p_nom, const std::string& p_prenom,
									  const std::string& p_telephone, const util::Date& p_dateNaissance)
 *        cas valide:
 *        		ConstructeurAvecParametres: Client avec paramètres noFolio:1000, nom: "Doe", prenom: "John",
 *        									telephone: "819 555-5555" et dateNaissance: 1, 1, 1970
 *
 *        		ConstructeurAvecEspaceDansNom: Client avec paramètres noFolio:1000, nom: "Do e", prenom: "John",
 *        										 telephone: "819 555-5555" et dateNaissance: 1, 1, 1970
 *
 *        		ConstructeurAvecEspaceDansPrenom: Client avec paramètres noFolio:1000, nom: "Do e", prenom: "Joh n",
 *        										  telephone: "819 555-5555" et dateNaissance: 1, 1, 1970
 *
 *        cas invalides:
 *        			p_noFolio = 999
 *        			p_noFolio = 10000
 *        			p_nom vide
 *        			p_nom Doe1
 *        			p_nom Doe&
 *        			p_prenom vide
 *        			p_prenom John2
 *        			p_prenom John!
 *        			p_telephone vide
 *        			p_telephone = "555 555-5555"
 *        			p_telephone = "819-555-5555"
 *        			p_telephone = "819 555 5555"
 *        			p_telephone = "819 555-555"
 *        			p_telephone = "a819 555-5555"
 *        			p_telephone = "819 555*-5555"
 *        			p_telephone = "819 555-5555&"
 *        			p_telephone = "819  555-5555"
 *        			p_telephone = "819 555- 5555"
 *        			p_telephone = "819 555-5555 "
 *        			p_telephone = "819 5551-5555"
 *        			p_telephone = "819 555-55551"
 *        			p_telephone = "819 55-5555"
 *        			p_dateNaissance 31, 12, 1969
 *        			p_dateNaissance 1, 1, 2038
 */
TEST(Client, ConstructeurAvecParametres)
{
	Client testClient(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));
	ASSERT_EQ(1000, testClient.reqNoFolio());
	ASSERT_EQ("Doe", testClient.reqNom());
	ASSERT_EQ("John", testClient.reqPrenom());
	ASSERT_EQ("819 555-5555", testClient.reqTelephone());
	ASSERT_EQ(util::Date(1, 1, 1970).reqDateFormatee(), testClient.reqDateDeNaissance());
}
TEST(Client, ConstructeurAvecEspaceDansNom)
{
	Client testClient(1000, "Do e", "John", "819 555-5555", util::Date(1, 1, 1970));
	ASSERT_EQ(1000, testClient.reqNoFolio());
	ASSERT_EQ("Do e", testClient.reqNom());
	ASSERT_EQ("John", testClient.reqPrenom());
	ASSERT_EQ("819 555-5555", testClient.reqTelephone());
	ASSERT_EQ(util::Date(1, 1, 1970).reqDateFormatee(), testClient.reqDateDeNaissance());
}
TEST(Client, ConstructeurAvecEspaceDansPrenom)
{
	Client testClient(1000, "Do e", "Joh n", "819 555-5555", util::Date(1, 1, 1970));
	ASSERT_EQ(1000, testClient.reqNoFolio());
	ASSERT_EQ("Do e", testClient.reqNom());
	ASSERT_EQ("Joh n", testClient.reqPrenom());
	ASSERT_EQ("819 555-5555", testClient.reqTelephone());
	ASSERT_EQ(util::Date(1, 1, 1970).reqDateFormatee(), testClient.reqDateDeNaissance());
}
// cas invalides
TEST(Client, ConstructeurAvecNoFolioInvalide1)
{
	ASSERT_THROW(Client testClient(999, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecNoFolioInvalide2)
{
	ASSERT_THROW(Client testClient(10000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecNomInvalide1)
{
	ASSERT_THROW(Client testClient(1000, "", "John", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecNomInvalide2)
{
	ASSERT_THROW(Client testClient(1000, "Doe1", "John", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecNomInvalide3)
{
	ASSERT_THROW(Client testClient(1000, "Doe&", "John", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecPrenomInvalide1)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecPrenomInvalide2)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John2", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecPrenomInvalide3)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John!", "819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide1)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide2)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "555 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide3)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819-555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide4)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555 5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide5)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555-555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide6)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "a819 555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide7)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555*-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide8)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555-5555&", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide9)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819  555-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide10)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555- 5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide11)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555-5555 ", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide12)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 5551-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide13)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555-55551", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecTelephoneInvalide14)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 55-5555", util::Date(1, 1, 1970)), PreconditionException);
}
TEST(Client, ConstructeurAvecDateDeNaissanceInvalide1)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555-5555", util::Date(31, 12, 1969)), PreconditionException);
}
TEST(Client, ConstructeurAvecDateDeNaissanceInvalide2)
{
	ASSERT_THROW(Client testClient(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 2038)), PreconditionException);
}

/**
 * \class UnClient
 * \brief Fixture UnCompteCheque pour la création d'un objet Client pour les tests
 */
class UnClient: public ::testing::Test
{
public:
	UnClient() :
		t_client(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970))
	{
	}

	Client t_client;
};

/**
 * \brief Test de la méthode int reqNoFolio() const
 *        cas valide reqNoFolio : Compte par défaut a un numéro de folio de 1000, vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, reqNoFolio)
{
	ASSERT_EQ(1000, t_client.reqNoFolio());
}

/**
 * \brief Test de la méthode const std::string& reqNom() const
 *        cas valide reqNom : Compte par défaut a un Nom "Doe", vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, reqNom)
{
	ASSERT_EQ("Doe", t_client.reqNom());
}

/**
 * \brief Test de la méthode const std::string& reqPrenom() const
 *        cas valide reqPrenom : Compte par défaut a un Prenom "John", vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, reqPrenom)
{
	ASSERT_EQ("John", t_client.reqPrenom());
}

/**
 * \brief Test de la méthode std::string reqDateDeNaissance() const
 *        cas valide reqDateDeNaissance : Compte par défaut a une date de naissance: 1, 1, 1970,
 *        								  vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, reqDateDeNaissance)
{
	ASSERT_EQ(util::Date(1, 1, 1970).reqDateFormatee(), t_client.reqDateDeNaissance());
}

/**
 * \brief Test de la méthode const std::string& reqTelephone() const
 *        cas valide reqTelephone : Compte par défaut a un numéro de téléphone
 *        							"819 555-5555", vérification du retour
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, reqTelephone)
{
	ASSERT_EQ("819 555-5555", t_client.reqTelephone());
}

/**
 * \brief Test de la méthode std::string reqClientFormate() const
 *        cas valide reqClientFormate: Créer le flux d'affichage attendu et vérification
 *        							s'il est le méme que celui construit par la méthode
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, reqClientFormate)
{
	std::ostringstream os1,os2;
	os1 << "Client no de folio : " << t_client.reqNoFolio() << std::endl
	    << t_client.reqPrenom() << " " << t_client.reqNom() << std::endl
	    << "Date de naissance : " << t_client.reqDateDeNaissance() << std::endl
	    << t_client.reqTelephone() << std::endl;

	os2 << t_client.reqClientFormate();

	ASSERT_EQ(os1.str(), os2.str());
}

/**
 * \brief Test de la méthode std::string reqReleves() const
 *        cas valide reqReleves: Créer le flux d'affichage attendu et vérification
 *        						 s'il est le méme que celui construit par la méthode
 *        						 (le vectuer m_vComptes est vide dans le client par défaut,
 *        						  donc le relevé affiche uniquement les informations du client)
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, reqReleves)
{
	std::ostringstream os1,os2;
	os1 << t_client.reqClientFormate();
	os2 << t_client.reqReleves();

	ASSERT_EQ(os1.str(), os2.str());
}

/**
 * \brief Test de la méthode void asgTelephone(const std::string& p_telephone)
 *        cas valide asgTelephone : Compte par défaut a un numéro de téléphone
 *        							"819 555-5555", vérification de l'assignation
 *        cas invalides:
 *        			p_telephone vide
 *        			p_telephone = "555 555-5555"
 *        			p_telephone = "819-555-5555"
 *        			p_telephone = "819 555 5555"
 *        			p_telephone = "819 555-555"
 *
 *        			p_telephone = "a819 555-5555"
 *        			p_telephone = "819 555*-5555"
 *        			p_telephone = "819 555-5555&"
 *        			p_telephone = "819  555-5555"
 *        			p_telephone = "819 555- 5555"
 *
 *        			p_telephone = "819 555-5555 "
 *        			p_telephone = "819 5551-5555"
 *        			p_telephone = "819 555-55551"
 *        			p_telephone = "819 55-5555"
 */
TEST_F(UnClient, asgTelephone)
{
	ASSERT_EQ("819 555-5555", t_client.reqTelephone());
	t_client.asgTelephone("514 555-5555");
	ASSERT_EQ("514 555-5555", t_client.reqTelephone());
}
// cas invalides
TEST_F(UnClient, asgTelephoneInvalide1)
{
	ASSERT_THROW(t_client.asgTelephone(""), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide2)
{
	ASSERT_THROW(t_client.asgTelephone("555 555-5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide3)
{
	ASSERT_THROW(t_client.asgTelephone("819-555-5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide4)
{
	ASSERT_THROW(t_client.asgTelephone("819 555 5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide5)
{
	ASSERT_THROW(t_client.asgTelephone("819 555-555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide6)
{
	ASSERT_THROW(t_client.asgTelephone("a819 555-5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide7)
{
	ASSERT_THROW(t_client.asgTelephone("819 555*-5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide8)
{
	ASSERT_THROW(t_client.asgTelephone("819 555-5555&"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide9)
{
	ASSERT_THROW(t_client.asgTelephone("819  555-5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide10)
{
	ASSERT_THROW(t_client.asgTelephone("819 555- 5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide11)
{
	ASSERT_THROW(t_client.asgTelephone("819 555-5555 "), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide12)
{
	ASSERT_THROW(t_client.asgTelephone("819 5551-5555"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide13)
{
	ASSERT_THROW(t_client.asgTelephone("819 555-55551"), PreconditionException);
}
TEST_F(UnClient, asgTelephoneInvalide14)
{
	ASSERT_THROW(t_client.asgTelephone("819 55-5555"), PreconditionException);
}

/**
 * \brief Test de la méthode bool operator ==(const Client& p_client) const
 *        cas valides:
 *        			SurdefinitionOperateurEgalite1 : Vérification que deux clients qui ont
 *        						   					 les mêmes paramètres sont bien égaux
 *
 *        			SurdefinitionOperateurEgalite2 : Vérification que deux clients qui
 *        											 n'ont pas le même noCompte ne
 *        											 sont pas égaux
 *
 * 	        		SurdefinitionOperateurEgalite3 : Vérification que deux clients qui
 *        											 n'ont pas le même Nom ne
 *        											 sont pas égaux
 *
 *					SurdefinitionOperateurEgalite4 : Vérification que deux clients qui
 *        											 n'ont pas le même Prenom ne
 *        											 sont pas égaux
 *
 *        			SurdefinitionOperateurEgalite5 : Vérification que deux clients qui
 *        											 n'ont pas le même Telephone ne
 *        											 sont pas égaux
 *
 *        			SurdefinitionOperateurEgalite6 : Vérification que deux clients qui
 *        											 n'ont pas la même dateDeNaissance
 *        											 ne sont pas égaux
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, SurdefinitionOperateurEgalite1)
{
	Client testClient1(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));
	Client testClient2(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));

	ASSERT_EQ(true, testClient1 == testClient2);
}
TEST_F(UnClient, SurdefinitionOperateurEgalite2)
{
	Client testClient1(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));
	Client testClient2(2000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));

	ASSERT_EQ(false, testClient1 == testClient2);
}
TEST_F(UnClient, SurdefinitionOperateurEgalite3)
{
	Client testClient1(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));
	Client testClient2(1000, "Do", "John", "819 555-5555", util::Date(1, 1, 1970));

	ASSERT_EQ(false, testClient1 == testClient2);
}
TEST_F(UnClient, SurdefinitionOperateurEgalite4)
{
	Client testClient1(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));
	Client testClient2(1000, "Doe", "Jon", "819 555-5555", util::Date(1, 1, 1970));

	ASSERT_EQ(false, testClient1 == testClient2);
}
TEST_F(UnClient, SurdefinitionOperateurEgalite5)
{
	Client testClient1(1000, "Doe", "John", "514 555-5555", util::Date(1, 1, 1970));
	Client testClient2(1000, "Doe", "Jon", "819 555-5555", util::Date(1, 1, 1970));

	ASSERT_EQ(false, testClient1 == testClient2);
}
TEST_F(UnClient, SurdefinitionOperateurEgalite6)
{
	Client testClient1(1000, "Doe", "John", "514 555-5555", util::Date(1, 1, 1970));
	Client testClient2(1000, "Doe", "Jon", "819 555-5555", util::Date(1, 1, 1980));

	ASSERT_EQ(false, testClient1 == testClient2);
}

/**
 * \brief Test de la méthode bool operator <(const Client& p_client) const
 *        cas valides:
 *        			SurdefOperateurInferieur1 : Vérification qu'un client dont le
 *        						   				noFolio est inférieur au noFolio
 *        						   				d'un autre client est bien inférieur
 *        						   				à cet autre client
 *
 *        			SurdefOperateurInferieur2 : Vérification qu'un client dont le
 *        						   				noFolio est supérieur au noFolio
 *        						   				d'un autre client n'est pas
 *        						   				à inférieur à cet autre client
 *
 *
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, SurdefOperateurInferieur1)
{
	Client testClient1(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));
	Client testClient2(2000, "Doe", "Jon", "819 555-5555", util::Date(1, 1, 1970));

	ASSERT_EQ(true, testClient1 < testClient2);
}
TEST_F(UnClient, SurdefOperateurInferieur2)
{
	Client testClient1(1000, "Doe", "John", "819 555-5555", util::Date(1, 1, 1970));
	Client testClient2(2000, "Doe", "Jon", "819 555-5555", util::Date(1, 1, 1970));

	ASSERT_EQ(false, testClient2 < testClient1);
}

/**
 * \brief Test de la méthode void ajouterCompte (const Compte& p_nouveauCompte)
 *        cas valide:
 *        		ajouterCompteEpargne : Client par défaut n'a aucun compte,
 *        							   vérification de l'ajout d'un compte
 *        							   Epargne dans la liste (vector) des
 *        							   comptes
 *
 *        		ajouterCompteCheque : Client par défaut n'a aucun compte,
 *        							  vérification de l'ajout d'un compte
 *        							  Cheque dans la liste (vector) des
 *        							  comptes
 *
 *        		ajouterDeuxComptes : Client par défaut n'a aucun compte,
 *        							 vérification de l'ajout d'un compte
 *        							 Cheque et Epargne dans la liste (vector)
 *        							 des comptes
 *
 *        		ajouterCompteExistant : Client par défaut n'a aucun compte,
 *        							 	ajout d'un compte Cheque dans la liste (vector)
 *        							 	des comptes et vérification qu'il n'est
 *        							 	pas possible d'ajouter un compte avec
 *        							 	le même noCompte dans la liste (vector)
 *
 *        cas invalides: Aucun d'identifié
 */
TEST_F(UnClient, ajouterCompteEpargne)
{
	ASSERT_EQ(t_client.reqClientFormate(), t_client.reqReleves());
	Epargne compteEpargne(1, 1, 500, "Epargne");
	t_client.ajouterCompte(compteEpargne);

	ASSERT_EQ(t_client.reqClientFormate() + compteEpargne.reqCompteFormate(), t_client.reqReleves());
}
TEST_F(UnClient, ajouterCompteCheque)
{
	Cheque compteCheque(10, 2, 100, 0, 0.1, "Cheque");
	t_client.ajouterCompte(compteCheque);
	ASSERT_EQ(t_client.reqClientFormate() + compteCheque.reqCompteFormate(), t_client.reqReleves());
}
TEST_F(UnClient, ajouterDeuxComptes)
{
	Cheque compteCheque(10, 2, 100, 0, 0.1, "Cheque");
	t_client.ajouterCompte(compteCheque);
	Epargne compteEpargne(1, 1, 500, "Epargne");
	t_client.ajouterCompte(compteEpargne);
	ASSERT_EQ(t_client.reqClientFormate() + compteCheque.reqCompteFormate() + compteEpargne.reqCompteFormate(),
			  t_client.reqReleves());
}
TEST_F(UnClient, ajouterCompteExistant)
{
	Cheque compteCheque1(10, 2, 100, 0, 0.1, "Cheque");
	Cheque compteCheque2(10, 2, 100, 0, 0.1, "Cheque");
	t_client.ajouterCompte(compteCheque1);
	t_client.ajouterCompte(compteCheque2);
	ASSERT_EQ(t_client.reqClientFormate() + compteCheque1.reqCompteFormate(), t_client.reqReleves());
}
