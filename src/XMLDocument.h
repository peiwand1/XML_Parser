/*
 * XMLDocument.h
 *
 *  Created on: 9 Oct 2024
 *      Author: Peiwand
 *
 *  Stores the parsed XML document
 */

#ifndef XMLDOCUMENT_H_
#define XMLDOCUMENT_H_

#include "XMLElement.h"
#include <string>

class XMLDocument
{
public:
	XMLDocument();
	virtual ~XMLDocument();

private:
	std::string version;
	std::string encoding;
	XMLElement* root;
};

#endif /* XMLDOCUMENT_H_ */
