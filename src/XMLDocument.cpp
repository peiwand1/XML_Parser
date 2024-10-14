/*
 * XMLDocument.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Peiwand
 */

#include "XMLDocument.h"
#include <iostream>

XMLDocument::XMLDocument() :
		version(""), encoding(""), root(nullptr)
{
	// TODO Auto-generated constructor stub

}

XMLDocument::~XMLDocument()
{
	// TODO Auto-generated destructor stub
}

const XMLElement* XMLDocument::getRoot() const
{
	return root;
}

void XMLDocument::setRoot(XMLElement *aRoot)
{
	root = aRoot;
}

const std::string& XMLDocument::getEncoding() const
{
	return encoding;
}
void XMLDocument::setEncoding(const std::string &anEncoding)
{
	encoding = anEncoding;
}

const std::string& XMLDocument::getVersion() const
{
	return version;
}

void XMLDocument::setVersion(const std::string &aVersion)
{
	version = aVersion;
}

void XMLDocument::printTree()
{
	std::cout << "<?xml version=\"" << version << "\" encoding=\"" << encoding << "\"?>" << std::endl;
	printElement(root);
}

void XMLDocument::printElement(XMLElement *anElement, unsigned int depth)
{
	unsigned int nextDepth = depth + 1;
	std::string spaces(depth * 2, ' ');
	std::string attrStr = "";

	// prepare string of attribute data
	std::map<std::string, std::string> attr = anElement->getAttributes();
	if (attr.size() > 0)
	{
		for (const auto &kv : attr)
		{
			attrStr = attrStr + " " + kv.first + "=\"" + kv.second + "\"";
		}
	}

	// if no children and no text content, print empty tag
	// else print full tag
	if (anElement->getChildren().size() == 0
			&& anElement->getTextContent().empty())
	{
		std::cout << spaces << "<" << anElement->getName() << attrStr << " />"
				<< std::endl;
	}
	else
	{
		std::cout << spaces << "<" << anElement->getName() << attrStr << ">"
				<< std::endl;

		for (XMLElement *child : anElement->getChildren())
		{
			printElement(child, nextDepth);
		}

		if (!anElement->getTextContent().empty())
		{
			std::cout << spaces << "  " << anElement->getTextContent()
					<< std::endl;
		}

		std::cout << spaces << "</" << anElement->getName() << ">" << std::endl;
	}
}
