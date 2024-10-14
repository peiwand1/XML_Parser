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

	const XMLElement* getRoot() const;
	void setRoot(XMLElement *aRoot);

	/**
	 * prints the entire XML tree to console starting from root
	 */
	void printTree();
private:
	std::string version;
	std::string encoding;
	XMLElement *root;

	/**
	 * recursively prints XML elements and their children
	 * @param anElement
	 * @param depth, used for indentation
	 */
	void printElement(XMLElement *anElement, unsigned int depth = 0);
};

#endif /* XMLDOCUMENT_H_ */
