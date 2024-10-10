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
	std::list<XMLElement*> parentOrder;

	bool parseByChar(char c, bool &tagOpened, std::string &tagContent);
};

#endif /* XMLPARSER_H_ */
