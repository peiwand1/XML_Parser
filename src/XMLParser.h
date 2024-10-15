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
#include <map>

class XMLParser
{
public:
	XMLParser();
	virtual ~XMLParser();

	void parse(const std::string& fileName);
	void print();
private:
	XMLDocument doc;

	/**
	 * keeps track of order that XML objects are found in,
	 * once it's closing tag is found it is removed from the list
	 */
	std::vector<XMLElement*> parentOrder;

	bool isInsideElement;
	std::string readStr;

	void parseByChar(char c);
	void handleXMLInside();
	void setParentChildRelations();
	void setAttributes(const std::string &str);
	void setDocumentRoot();
	void handleClosingTag();
	void handleMetaData();
	void handleComment();
	void handleXMLElement();
	std::map<std::string, std::string> extractAttrKeyValuePairs(
			const std::string &str);
};

#endif /* XMLPARSER_H_ */
