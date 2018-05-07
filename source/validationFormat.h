/**
 * \file validationFormat.h
 * \brief TP1: déclarations des fonctions validerFormatNom, validerTelephone, validerFormatFichier
 * \author Alexandre Bouras, 111 149 065
 * \version 2.0
 * \date 25/02/2018
 */

#ifndef VALIDATIONFORMAT_H_
#define VALIDATIONFORMAT_H_

namespace util
{
bool validerFormatNom(const std::string& p_nom);
bool validerTelephone(const std::string& p_telephone);
bool validerFormatFichier(std::istream& p_is);
} // namespace util

#endif /* VALIDATIONFORMAT_H_ */
