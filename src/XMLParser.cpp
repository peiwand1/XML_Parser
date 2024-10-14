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
#include <sstream>

XMLParser::XMLParser() :
		doc(), parentOrder(), isInsideElement(false)
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

		while (file.get(c))
		{
			//read char by char to determine what it is
			parseByChar(c, tagContent);
		}

		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}
}

void XMLParser::parseByChar(char c, std::string &tagContent)
{
	//read char by char to determine what it is
	if (!isInsideElement)
	{
		if (c == '<') // start of tag found
		{
			//check if the root xml element has been made and the read text isn't just whitespace
			if (parentOrder.size() > 0
					&& tagContent.find_first_not_of(" \t\n\v\f\r")
							!= std::string::npos)
			{
//				std::cout << "test: " << tagContent << "." << std::endl;
				parentOrder.back()->setTextContent(tagContent); // TODO put this in the correct spot
			}
			isInsideElement = true;
			tagContent = "";
//			std::cout << "< found, reading tag..." << std::endl;
		}
		else
		{
			// look for text between open and close tags,
			tagContent += c;
		}
	}
	else
	{
		if (c == '>')
		{
			isInsideElement = false;
//			std::cout << tagContent << std::endl;
//			std::cout << "> found, analysing tag." << std::endl << std::endl;

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

	std::list<std::string> strl = splitString(tagContent, ' ');

	if (tagContent.back() == '/') // empty tag <name />
	{
		parentOrder.push_back(new XMLElement(strl.front()));

		setParentChildRelations();
		setAttributes(tagContent);

		setDocumentRoot();
		parentOrder.pop_back();
	}
	else // opening tag, so create an html element
	{
		parentOrder.push_back(new XMLElement(strl.front()));

		setParentChildRelations();
		setAttributes(tagContent);

		setDocumentRoot();
	}

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

std::list<std::string> XMLParser::splitString(const std::string &str,
		char delimiter)
{
	std::stringstream ss(str);
	std::string token;
	std::list<std::string> tokens;
	while (getline(ss, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void XMLParser::setAttributes(const std::string &str)
{
//	std::cout << __PRETTY_FUNCTION__ << " " << str << std::endl;

	// if no spaces you can be sure there are no attributes
	if (str.find(' ') == std::string::npos)
		return;

	// split str on spaces. will always contain element name, so remove that
	std::list<std::string> strl = splitString(str, ' ');
	strl.pop_front();

	// if 0, no attributes exist
	// if 1 and that 1 is "/", no attributes exist
	if (strl.size() == 0 || (strl.size() == 1 && strl.back() == "/"))
		return;

	// for each token, split into key value pair and add attribute
	for (std::string s : strl)
	{
		if (str.find('=') == std::string::npos)
			continue;
//		std::cout << s << std::endl;
		// TODO this currently won't work as intended if there is a '=' in the value
		std::list<std::string> tokens = splitString(s, '=');
		std::string val = tokens.back();
		val = val.substr(1, val.size() - 2);
		parentOrder.back()->addAttribute(tokens.front(), val);
	}
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

