/**
 * \file validationFormat.cpp
 * \brief TP1: définition des fonctions validerFormatNom, validerTelephone, validerFormatFichier
 * \author Alexandre Bouras, 111 149 065
 * \version 2.0
 * \date 25/02/2018
 */

#include <iostream>
#include <cstring>
#include <stdio.h>
#include "validationFormat.h"

using namespace std;

namespace util
{

/**
 * \brief fonction qui valide le format d'un nom et valide qu'il est non vide
 * \param[in] p_nom est une chaîne de caractères (string) qui représente un nom
 * \return un booléen: true si le format du nom est valide et non vide, false sinon
 */
bool validerFormatNom(const std::string& p_nom)
{
	bool nomEstValide = true;

	// validation qu'un nom est non vide.
	if (p_nom.empty())
	{
		nomEstValide = false;
	}

	// validation que le nom ne contient que des lettres et des espaces.
	unsigned int i = 0;
	while (nomEstValide == true and i < p_nom.length())
	{
		if (isalpha(p_nom[i]) == 0 and isspace(p_nom[i]) == 0)
		{
			nomEstValide = false;
		}
		else
		{
			i++;
		}
	}
	return nomEstValide;
}

/**
 * \brief fonction qui valide le format d'un numéro de téléhone selon le standard national canadien CCC CCC-CCCC
 * \param[in] p_telephone est une chaîne de caractères (string) qui représente un numéro de téléphone
 * \return un booléen: true si le format du numéro de téléphone est valide, false sinon
 */
bool validerTelephone(const std::string& p_telephone)
{
	bool telephoneEstValide = true;
	const string LISTECODESREGIONAUX[33] =
	{ "403", "780", "604", "236", "250", "778", "902", "204", "506", "902",
	  "905", "519", "289", "705", "613", "807", "416", "647", "438",
	  "514", "450", "579", "418", "581", "819", "306", "709", "867",
	  "800", "866", "877", "888", "855" };

	// validation que le numéro de téléphone n'est pas différent de 12 caractères (incluant l'espace et le tiret)
	// selon le format national CCC CCC-CCCC.
	if (p_telephone.length() != 12)
	{
		telephoneEstValide = false;
	}

	// validation du code régional, selon la liste des codes régionaux ou
	// si celui-ci a le format 9xx (il commence par 9).
	int longueurListe = sizeof(LISTECODESREGIONAUX) / sizeof(string);
	int i = 0;
	while (i < longueurListe and telephoneEstValide == true)
	{
		string premierChiffreCodeRegional = p_telephone.substr(0, 1);
		string codeRegional = p_telephone.substr(0, 3);
		if (premierChiffreCodeRegional == "9")
		{
			i = longueurListe + 1;
		}
		if (codeRegional == LISTECODESREGIONAUX[i])
		{
			i = longueurListe + 1;
		}
		else
		{
			i++;
			if (i == longueurListe)
			{
				telephoneEstValide = false;
			}
		}
	}

	// validation que le numéro de téléphone ne contient que des chiffres, un espace et un tiret,
	// selon le format national CCC CCC-CCCC.
	unsigned int j = 0;
	while (telephoneEstValide == true and j < p_telephone.length())
	{
		if (j < 3 and isdigit(p_telephone[j]) != 1)
		{
			telephoneEstValide = false;
		}
		if (j == 3 and isspace(p_telephone[j]) == 0)
		{
			telephoneEstValide = false;
		}
		if (3 < j and j < 7 and isdigit(p_telephone[j]) != 1)
		{
			telephoneEstValide = false;
		}
		if (strncmp(&p_telephone[7], "-", 1) != 0)
		{
			telephoneEstValide = false;
		}
		if (7 < j and j < 12 and isdigit(p_telephone[j]) != 1)
		{
			telephoneEstValide = false;
		}
		else
			j++;
	}

	return telephoneEstValide;
}

/**
 * \brief fonction qui valide le format d'un fichier
 * \param[in] p_is est le flux d'entrée (istream) qui contient les données d'un fichier
 * \pre le numéro de folio existe dans le fichier et est du bon format
 * \pre les informations relatives aux comptes qui sont dans le fichier existent et sont du bon format
 * \return un booléen: true si le format du fichier est valide, false sinon
 */
bool validerFormatFichier(std::istream& p_is)
{
	bool fichierEstValide = true;
	char ligne[256] = "";

	// validation des deux premières lignes du fichier (nom, prénom) et que celles-ci sont non nulles.
	for (int i = 0; i < 2; i++)
	{
		p_is.getline(ligne, 255);
		if (validerFormatNom(ligne) != true)
		{
			fichierEstValide = false;
		}
	}

	// validation que la troisième ligne du fichier (date de naissance) est sous le format jj mm aaaa
	// (on les considère comme 3 entiers séparés) et que ces 3 entiers ne sont pas nuls.
	p_is.getline(ligne, 255);
	char* date = strtok(ligne, " ");
	char* entiersDates[3] =
	{ 0, 0, 0 };

	// boucle afin d'extraire les 3 entiers de la chaîne de caractères.
	int m = 0;
	while (date != NULL)
	{
		entiersDates[m] = date;
		m++;
		date = strtok(NULL, " ");
	}

	// stockage des chaînes dans des variables et comparaisons de leur valeur
	char* jour = entiersDates[0];
	char* mois = entiersDates[1];
	char* annee = entiersDates[2];

	if (strcmp(jour, "0") == 0 or strcmp(mois, "0") == 0
			or strcmp(annee, "0") == 0)
	{
		fichierEstValide = false;
	}

	// validation de la quatrième ligne du fichier (téléphone).
	p_is.getline(ligne, 255);
	if (validerTelephone(ligne) != true)
	{
		fichierEstValide = false;
	}

	// saut de la cinquième ligne du fichier (folio), aucune validation.
	p_is.ignore(255, '\n');

	// validation de la sixième ligne du fichier (type de compte : cheque ou epargne)
	// ou si aucun type de compte et fin de fichier : valide.
	p_is.getline(ligne, 255);
	string ligne6 = string(ligne);

	if (p_is.peek() == EOF and ligne6.empty())
	{
		fichierEstValide = true;
	}

	else if (strcmp(ligne, "cheque") != 0 and strcmp(ligne, "epargne") != 0)
	{
		fichierEstValide = false;
	}

	// boucle : saut de 6 lignes si le type de compte est cheque, saut de 5 lignes si le type est epargne,
	// jusqu'à la fin du fichier.
	while (p_is.peek() != EOF and fichierEstValide == true)
	{
		if (strcmp(ligne, "cheque") == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				p_is.ignore(255, '\n');
			}
			p_is.getline(ligne, 255);
		}
		else if (strcmp(ligne, "epargne") == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				p_is.ignore(255, '\n');
			}
			p_is.getline(ligne, 255);
		}
		else
		{
			fichierEstValide = false;
		}
	}
	return fichierEstValide;
}

}    // namespace util

