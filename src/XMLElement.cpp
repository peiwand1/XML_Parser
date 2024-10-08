/*
 * XMLObj.cpp
 *
 *  Created on: 8 Oct 2024
 *      Author: Peiwand
 */

#include "XMLElement.h"

XMLElement::XMLElement(std::string aName) :
				name(aName),
				textContent(""),
				attributes(),
				parent(),
				previous(),
				next(),
				children()
{
	// TODO Auto-generated constructor stub

}

XMLElement::XMLElement(const XMLElement &anXMLObj) :
				name(anXMLObj.name),
				textContent(anXMLObj.textContent),
				attributes(anXMLObj.attributes),
				parent(anXMLObj.parent),
				previous(anXMLObj.previous),
				next(anXMLObj.next),
				children(anXMLObj.children)
{
	// TODO use getters instead of directly accessing values

}

XMLElement::~XMLElement()
{
	// TODO Auto-generated destructor stub
}

XMLElement& XMLElement::operator=(const XMLElement &other)
{
	if (this != &other)
	{
		//TODO data = other.data;
	}
	return *this;
}
