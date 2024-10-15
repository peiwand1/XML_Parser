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

	/**
	 * starts processing a given file to interpret it's XML content
	 * @param fileName
	 */
	void parse(const std::string& fileName);

	/**
	 * prints the XML tree
	 */
	void print();
private:
	XMLDocument doc;

	/**
	 * keeps track of order that XML objects are found in,
	 * once it's closing tag is found it is removed from the list
	 */
	std::vector<XMLElement*> parentOrder;

	/**
	 * tracks if parser is in or outside of <> brackets
	 */
	bool isInsideElement;

	/**
	 * tracks the text that is currently being parsed
	 */
	std::string readStr;

	/**
	 * receives chars one by one from the file and decides what action should be taken to parse it
	 * @param c
	 */
	void parseByChar(char c);

	/**
	 * handles the various cases inside <> brackets
	 */
	void handleXMLInside();

	/**
	 * sets the parent/child relation based on the last 2 XMLElements in vector parentOrder
	 * the last object in this list is set as the child of the second to last item
	 */
	void setParentChildRelations();

	/**
	 * takes a string that contains attributes,
	 * then separates this and sets the attributes on the XMLElement
	 * @param str
	 */
	void setAttributes(const std::string &str);

	/**
	 * sets the root XMLElement in XMLDocument
	 */
	void setDocumentRoot();

	/**
	 * updates parentOrder when a closing tag is encountered
	 * also throws error if closing tag has a different name from opening tag
	 */
	void handleClosingTag();

	/**
	 * reads and sets metadata (xml version and encoding)
	 * throws when syntax is wrong
	 */
	void handleMetaData();

	/**
	 * performs syntax check when a comment is encountered
	 * throws when syntax is wrong
	 */
	void handleComment();

	/**
	 *
	 */
	void handleXMLElement();

	/**
	 * separates attribute strings into key value pairs
	 * @param str that contains at least 1 attribute
	 * @return map containing pairs of attribute name and attribute value
	 */
	std::map<std::string, std::string> extractAttrKeyValuePairs(
			const std::string &str);
};

#endif /* XMLPARSER_H_ */
