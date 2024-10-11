/*
 * XMLParser.h
 *
 *  Created on: 9 Oct 2024
 *      Author: Peiwand
 *
 *
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include "XMLDocument.h"
#include "XMLElement.h"
#include <string>
#include <vector>
#include <list>

class XMLParser
{
public:
	XMLParser();
	virtual ~XMLParser();

	void parse(std::string fileName);
	void print();
private:
	XMLDocument doc;

	/**
	 * keeps track of order that XML objects are found in,
	 * once it's closing tag is found it is removed from the list
	 */
	std::vector<XMLElement*> parentOrder;

	bool parseByChar(char c, bool &tagOpened, std::string &tagContent);
	void handleXMLCreation(const std::string &tagContent);
	void setParentChildRelations();
	void setAttributes(const std::string &tagContent);
	void setDocumentRoot();
	std::list<std::string> splitString(const std::string &tagContent,
			char delimiter);
};

#endif /* XMLPARSER_H_ */
