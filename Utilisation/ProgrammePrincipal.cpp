/**
 * \file programmePrincipal.cpp
 * \brief Programme pour créer un dossier client et modifier son numéro de téléphone
 * \author Alexandre Bouras, 111 149 065
 * \version 2.0
 * \date 09/04/2018
 */

#include <iostream>
#include <sstream>
#include "Client.h"
#include "Epargne.h"
#include "Cheque.h"
#include "Date.h"
#include "validationFormat.h"

using namespace std;
using namespace banque;
using namespace util;

int main()
{
	 // affichage de l'interface pour la création d'un objet Client
	    cout << "Bienvenue à l'outil client" << endl
	         << "----------------------------------------" << endl;

	    // on demande à l'utilisateur de saisir un # de folio, on valide la valeur entrée
	    // et on demande une saisie tant que le # entré n'est pas valide
	    int noFolio = 0;
	    while (1000 > noFolio or noFolio > 9999)
	    {
	        cout << "Entrez le numero de folio du client [1000, 10000[ :" << endl;
	        cin >> noFolio;
	        if (1000 > noFolio or noFolio > 9999)
	        {
	            cout << "Le numero de folio n'est pas entre 1000 et 10000 exclusivement" << endl;
	            cout << endl;
	        }
	    }
	    cin.ignore();

	    // on demande à l'utilisateur de saisir un prénom et on valide son format
	    // et on demande une saisie tant que le format du prénom entré n'est pas valide
	    string prenom = "";
	    bool prenomEstValide = false;
	    char buffer[256];
	    while (prenomEstValide == false)
	    {
	    	cout << endl
	             << "Entrez le prénom :" << endl;
	        cin.getline(buffer, 255);
	        prenom = buffer;

	        prenomEstValide = validerFormatNom(prenom);
	        if (prenomEstValide != true)
	        {
	        	cout << "Le prénom n’est pas valide" << endl;

	        }
	    }

	    // on demande à l'utilisateur de saisir un nom et on valide son format
	    // et on demande une saisie tant que le format du nom entré n'est pas valide
	    string nom = "";
	    bool nomEstValide = false;
	    while (nomEstValide == false)
	    {
	    	cout << endl
	        	 << "Entrez le nom :" << endl;
	        cin.getline(buffer, 255);
	        nom = buffer;

	        nomEstValide = validerFormatNom(nom);
	        if (nomEstValide != true)
	        {
	        	cout << "Le nom n’est pas valide" << endl;
	        }
	     }

	    // on demande à l'utilisateur de saisir un # de téléphone et on valide son format
	    // et on demande une saisie tant que le format ou le code régional du # entré n'est pas valide
	    string telephone = "";
	    bool telephoneEstValide = false;
	    while (telephoneEstValide == false)
	    {
	    	cout << endl
	    	     << "Entrez le numero de telephone XXX CCC-CCCC :" << endl;
	    	cin.getline(buffer, 255);
	    	telephone = buffer;

	        telephoneEstValide = validerTelephone(telephone);
	        if (telephoneEstValide != true)
	        {
	        	cout << "Le numero de telephone n'est pas valide" << endl;
	        }
	    }

	    // on demande à l'utilisateur de saisir une date de naissance et on valide son format
	    // et on demande une saisie tant que le format n'est pas valide
	    long jour = 0;
	    long mois = 0;
	    long annee = 0;
	    bool dateNaissanceEstValide = false;
	    while (dateNaissanceEstValide == false)
	    {
	    	cout << endl
	    	     << "Entrez la date de naissance (JJ, MM, AAAA), en commençant uniquement par le jour JJ :" << endl;
	    	cin.getline(buffer, 255);
	    	stringstream sstrJour(buffer);
	    	sstrJour >> jour;

	    	cout << endl
	    		 << "Entrez la date de naissance (JJ, MM, AAAA), continuez avec uniquement le mois MM :" << endl;
	    	cin.getline(buffer, 255);
	    	stringstream sstrMois(buffer);
	    	sstrMois >> mois;

	    	cout << endl
	    		 << "Entrez la date de naissance (JJ, MM, AAAA), terminez avec uniquement l'annee AAAA :" << endl;
	    	cin.getline(buffer, 255);
	    	stringstream sstrAnnee(buffer);
	    	sstrAnnee >> annee;

	    	dateNaissanceEstValide = Date::validerDate(jour, mois, annee);
	    	if (dateNaissanceEstValide != true)
	    	{
	    		cout << "La date de naissance n'est pas valide" << endl;
	    	}
	    }

	    // création d'un objet Client avec les informations fournies par l'utilisateur et affichage de l'objet
	    Client unClient(noFolio, nom, prenom, telephone, Date(jour, mois, annee));
	    cout << endl
	         << "Fichier client" << endl
	         << "------------------------------------------------" << endl
	         << unClient.reqClientFormate();
	    cout << endl;
	    cout << endl;


	    //-------------------------------------------------------------------------------------//


	    // affichage de l'interface pour la création des objets Cheque et Epargne
	    	    cout << "Bienvenue à l'outil des comptes" << endl
	    	         << "----------------------------------------" << endl;

	    // Demande de saisie des informations pour la création d'un objet Cheque
	    // on demande à l'utilisateur de saisir un # de compte, on valide la valeur entrée
	    // et on demande une saisie tant que le # entré n'est pas valide
	    int noCompte = -1;
	    while (0 > noCompte)
	    {
	        cout << "Entrez le numero de compte cheque :" << endl;
	        cin >> noCompte;
	        if (0 > noCompte)
	        {
	            cout << "Le numero de compte doit être égal ou supérieur à 0" << endl;
	            cout << endl;
	        }
	    }
	    cin.ignore();

	    // on demande à l'utilisateur de saisir un solde pour le compte
	    double solde = 0;
	    cout << "Entrez le solde du compte cheque :" << endl;
	    cin >> solde;
	    cin.ignore();

	    // on demande à l'utilisateur de saisir le taux d'interet du compte, on valide la valeur entrée
	    // et on demande une saisie tant que le taux entré n'est pas valide
	    double tauxInteretMinimum = 0.1;
	    do
	    {
	    	cout << "Entrez le taux d'interet minimum du compte (en %) :" << endl;
	    	cin >> tauxInteretMinimum;
	    	if (0 > tauxInteretMinimum)
	    	{
	    		cout << "Le taux d'interet minimum doit être égal ou supérieur à 0" << endl;
	    		cout << endl;
	    	}
	    } while (0 > tauxInteretMinimum);
	    cin.ignore();

	    // on demande à l'utilisateur de saisir le taux d'interet du compte, on valide la valeur entrée
	    // et on demande une saisie tant que le taux entré n'est pas valide
	    double tauxInteret = 0.1;
	    do
	    {
	    	cout << "Entrez le taux d'interet du compte (en %) :" << endl;
	    	cin >> tauxInteret;
	    	if (tauxInteretMinimum > tauxInteret)
	    	{
	    		cout << "Le taux d'interet doit être égal ou supérieur au taux d'intérêt minimum" << endl;
	    		cout << endl;
	    	}
	    } while (tauxInteretMinimum > tauxInteret);
	    cin.ignore();

	    // on demande à l'utilisateur de saisir le nombre de transactions du compte, on valide la valeur entrée
	    // et on demande une saisie tant que le taux entré n'est pas valide
	    double nombreTransactions = -1;
	    while (0 > nombreTransactions or nombreTransactions > 40)
	    {
	    	cout << "Entrez le nombre de transactions du compte :" << endl;
	    	cin >> nombreTransactions;
	    	if (0 > nombreTransactions or nombreTransactions > 40)
	    	{
	    	cout << "Le nombre de transactions doit être entre 0 et 40 inclusivement" << endl;
	    	cout << endl;
	    	}
	    }
	    cin.ignore();

	    // on demande à l'utilisateur de saisir une description et on valide son format
	    // et on demande une saisie tant que le format du prénom entré n'est pas valide
	    string description = "Cheque";
	    bool descriptionEstValide = false;
	    while (descriptionEstValide == false)
	    {
	    	cout << "Entrez la description du compte :" << endl;
	    	cin.getline(buffer, 255);
	    	description = buffer;

	    	descriptionEstValide = (!(description.empty()));
	    	if (descriptionEstValide != true)
	    	{
	    		cout << "La description n’est pas valide; elle ne doit pas être vide" << endl;
	    	 }
	    }

	    // création d'un objet Cheque avec les informations fournies par l'utilisateur et affichage de l'objet
	    Cheque unCompteCheque(noCompte, tauxInteret, solde, nombreTransactions, tauxInteretMinimum, description);
	    cout << endl
	    	 << "Affichage des informations du compte créé" << endl
	    	 << "------------------------------------------------" << endl
	    	 << unCompteCheque.reqCompteFormate();

	    //ajout de l'object Cheque créé dans la liste (vector) des comptes du client
	    unClient.ajouterCompte(unCompteCheque);


	    //-------------------------------------------------------------------------------------//


	    // Demande de saisie des informations pour la création d'un objet Epargne
	    // on demande à l'utilisateur de saisir un # de compte, on valide la valeur entrée
	    // et on demande une saisie tant que le # entré n'est pas valide
	    cout << endl;
	    int noCompteEpargne = -1;
	    while (0 > noCompteEpargne)
	    {
	        cout << "Entrez le numero de compte epargne :" << endl;
	        cin >> noCompteEpargne;
	        if (0 > noCompteEpargne)
	        {
	            cout << "Le numero de compte doit être égal ou supérieur à 0" << endl;
	            cout << endl;
	        }
	    }
	    cin.ignore();

	    // on demande à l'utilisateur de saisir un solde pour le compte
	    double soldeEpargne = 0;
	    cout << "Entrez le solde du compte epargne :" << endl;
	    cin >> soldeEpargne;
	    cin.ignore();

	    // on demande à l'utilisateur de saisir le taux d'interet du compte, on valide la valeur entrée
	    // et on demande une saisie tant que le taux entré n'est pas valide
	    double tauxInteretEpargne = 0.1;
	    do
	    {
	    	cout << "Entrez le taux d'interet du compte (en %) :" << endl;
	    	cin >> tauxInteretEpargne;
	    	if (0.1 > tauxInteretEpargne or tauxInteretEpargne > 3.5)
	    	{
	    		cout << "Le taux d'interet doit se situer entre 0.1 et 3.5" << endl;
	    		cout << endl;
	    	}
	    } while (0.1 > tauxInteretEpargne or tauxInteretEpargne > 3.5);
	    cin.ignore();

	    // on demande à l'utilisateur de saisir une description et on valide son format
	    // et on demande une saisie tant que le format du prénom entré n'est pas valide
	    string descriptionEpargne = "Epargne";
	    bool descriptionEstValideEpargne = false;
	    while (descriptionEstValideEpargne == false)
	    {
	    	cout << "Entrez la description du compte :" << endl;
	    	cin.getline(buffer, 255);
	    	descriptionEpargne = buffer;

	    	descriptionEstValideEpargne = (!(descriptionEpargne.empty()));
	    	if (descriptionEstValideEpargne != true)
	    	{
	    		cout << "La description n’est pas valide; elle ne doit pas être vide" << endl;
	    	 }
	    }

	    // création d'un objet Epargne avec les informations fournies par l'utilisateur et affichage de l'objet
	    Epargne unCompteEpargne(noCompteEpargne, tauxInteretEpargne, soldeEpargne, descriptionEpargne);
	    cout << endl
	    	 << "Affichage des informations du compte créé" << endl
	    	 << "------------------------------------------------" << endl
	    	 << unCompteEpargne.reqCompteFormate();

	    //ajout de l'object Cheque créé dans la liste (vector) des comptes du client
	    unClient.ajouterCompte(unCompteEpargne);

	    //affichage du relevé du client, soit les informations sur le client et sur chacun de ses comptes
	    cout << endl
	    	 << endl
	    	 << "Affichage du relevé client" << endl
	    	 << "------------------------------------------------" << endl
	    	 << unClient.reqReleves();

	    return 0;
}
