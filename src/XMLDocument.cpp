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

void XMLDocument::printTree()
{
	printElement(root);
}

void XMLDocument::printElement(XMLElement *anElement, unsigned int depth)
{
	unsigned int nextDepth = depth + 1;
	std::string spaces(depth * 2, ' ');
	std::string attrStr = "";

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
