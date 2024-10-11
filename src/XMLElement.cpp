/*
 * XMLElement.cpp
 *
 *  Created on: 8 Oct 2024
 *      Author: Peiwand
 */

#include "XMLElement.h"
#include <iostream>

XMLElement::XMLElement(std::string aName) :
				name(aName),
				textContent(""),
				attributes(),
				parent(nullptr),
				children()
{
	// TODO Auto-generated constructor stub
//	std::cout << __PRETTY_FUNCTION__ << " " << name << std::endl;

}

XMLElement::XMLElement(const XMLElement &anXMLObj) :
				name(anXMLObj.name),
				textContent(anXMLObj.textContent),
				attributes(anXMLObj.attributes),
				parent(anXMLObj.parent),
				children(anXMLObj.children)
{
	// TODO use getters instead of directly accessing values

}

XMLElement::~XMLElement()
{
	// TODO Auto-generated destructor stub
}

const std::string& XMLElement::getName() const
{
	return name;
}

void XMLElement::setName(const std::string& aName)
{
	name = aName;
}

const std::string& XMLElement::getTextContent() const
{
	return textContent;
}

void XMLElement::setTextContent(const std::string& aTextContent)
{
	textContent = aTextContent;
}

const std::map<std::string, std::string>& XMLElement::getAttributes() const
{
	return attributes;
}

const std::string& XMLElement::getAttribute(const std::string& anAttributeKey) const
{
	return attributes.at(anAttributeKey);
}

void XMLElement::addAttribute(const std::string& aKey, const std::string& aValue)
{
	attributes.insert({aKey, aValue});
}

XMLElement* XMLElement::getParent() const
{
	return parent;
}

void XMLElement::setParent(XMLElement *aParent)
{
//	std::cout << "setting " << aParent->getName() << " as parent of " << name << std::endl;
	parent = aParent;
}

const std::vector<XMLElement*>& XMLElement::getChildren() const
{
	return children;
}

void XMLElement::addChild(XMLElement *aChild)
{
//	std::cout << "adding " << aChild->getName() << " as child of " << name << std::endl;
	children.push_back(aChild);
}

XMLElement& XMLElement::operator=(const XMLElement &other)
{
	if (this != &other)
	{
		//TODO data = other.data;
	}
	return *this;
}
