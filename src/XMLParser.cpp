/*
 * XMLParser.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Peiwand
 */

#include "XMLParser.h"
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>

XMLParser::XMLParser() :
		doc(), parentOrder()
{

}

XMLParser::~XMLParser()
{
	// TODO Auto-generated destructor stub
}

void XMLParser::parse(std::string fileName)
{
	std::ifstream file;

	file.open(fileName);
	if (file.is_open())
	{
		char c;
		std::string tagContent = "";
		bool tagOpened = false;

		while (file.get(c))
		{
			//read char by char to determine what it is
			parseByChar(c, tagOpened, tagContent);
		}

		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}
}

bool XMLParser::parseByChar(char c, bool &tagOpened, std::string &tagContent)
{
	//read char by char to determine what it is
	if (!tagOpened)
	{
		if (c == '<') // start of tag found
		{
//			parentOrder.back()->setTextContent(tagContent);

			tagOpened = true;
			tagContent = "";
			std::cout << "< found, reading tag..." << std::endl;
		}
		else
		{
			// look for text between open and close tags,
			// TODO make sure not to store unneeded whitespace
			tagContent += c;
		}
	}
	else
	{
		if (c == '>')
		{
			tagOpened = false;
			std::cout << tagContent << std::endl;
			std::cout << "> found, analysing tag." << std::endl << std::endl;

			handleXMLCreation(tagContent);
			// reset tagName
			tagContent = "";
		}
		else
		{
			// TODO implement checking for attributes, currently they are treated as part of the name
			tagContent += c;
		}
	}
	return tagOpened;
}

void XMLParser::handleXMLCreation(const std::string &tagContent)
{
	if (tagContent.front() == '/') // closing tag </name>
	{
		// check if name matches that of latest parent in order
		// pop back if same
		// throw exception otherwise
		parentOrder.pop_back();
		return;
	}
	else if (tagContent.back() == '/') // empty tag <name />
	{
		//remove / at end along with any trailing spaces
		std::string str = tagContent;
		str.pop_back();
		std::string::iterator end_pos = std::remove(str.begin(), str.end(),
				' ');
		str.erase(end_pos, str.end());
		parentOrder.push_back(new XMLElement(str));

		// TODO figure out a good way to handle this, can't pop it until functions at end are executed
		// will have to pop it at some point after that to maintain proper tree
		// parentOrder.pop_back();
	}
	else // opening tag, so create an html element
	{
		// TODO make XMLElement object and set the found text as name/attributes
		parentOrder.push_back(new XMLElement(tagContent));
	}

	setParentChildRelations();
	setAttributes(tagContent);

	setDocumentRoot();
}

void XMLParser::setParentChildRelations()
{
	if (parentOrder.size() > 1)
	{
		XMLElement *parent = parentOrder.at(parentOrder.size() - 2);
		XMLElement *child = parentOrder.back();

		parent->addChild(child);
		child->setParent(parent);
	}
}

void XMLParser::setAttributes(const std::string &tagContent)
{
	// TODO
	// break up string into components
	// will always contain name
	// if no spaces you can be sure there are no attributes
	// if spaces there could be an arbitrary amount of attributes
	// it is also possible that the space only implies an empty tag
}

void XMLParser::setDocumentRoot()
{
	if (doc.getRoot() == nullptr) // will only happen when the first XML element is found
	{
		doc.setRoot(parentOrder.front());
	}
}

void XMLParser::print()
{
	doc.printTree();
}

