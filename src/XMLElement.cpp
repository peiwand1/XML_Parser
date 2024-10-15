/*
 * XMLElement.cpp
 *
 *  Created on: 8 Oct 2024
 *      Author: Peiwand
 */

#include "XMLElement.h"
#include <iostream>

XMLElement::XMLElement(std::string aName) :
		name(aName), textContent(""), attributes(), parent(nullptr), children()
{
}

XMLElement::XMLElement(const XMLElement &anXMLObj) :
				name(anXMLObj.name),
				textContent(anXMLObj.textContent),
				attributes(anXMLObj.attributes),
				parent(anXMLObj.parent),
				children(anXMLObj.children)
{
}

XMLElement::XMLElement(XMLElement &&other) noexcept :
				name(std::move(other.name)),
				textContent(std::move(other.textContent)),
				attributes(std::move(other.attributes)),
				parent(other.parent),
				children(std::move(other.children))
{
	other.parent = nullptr;
	other.children.clear();
}

XMLElement::~XMLElement()
{
}

const std::string& XMLElement::getName() const
{
	return name;
}

void XMLElement::setName(const std::string &aName)
{
	name = aName;
}

const std::string& XMLElement::getTextContent() const
{
	return textContent;
}

void XMLElement::setTextContent(const std::string &aTextContent)
{
	if (textContent.size() > 0)
	{
		textContent = textContent + " " + aTextContent;
	}
	else
	{
		textContent = aTextContent;
	}
}

const std::map<std::string, std::string>& XMLElement::getAttributes() const
{
	return attributes;
}

const std::string& XMLElement::getAttribute(
		const std::string &anAttributeKey) const
{
	return attributes.at(anAttributeKey);
}

void XMLElement::addAttribute(const std::string &aKey,
		const std::string &aValue)
{
	attributes.insert(
	{ aKey, aValue });
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
		name = other.name;
		textContent = other.textContent;
		attributes = other.attributes;
		parent = other.parent;
		children = other.children;
	}
	return *this;
}

XMLElement& XMLElement::operator=(XMLElement &&other) noexcept
{
	if (this != &other)
	{
		name = std::move(other.name);
		textContent = std::move(other.textContent);
		attributes = std::move(other.attributes);

		parent = other.parent;
		children = std::move(other.children);

		other.parent = nullptr;
		other.children.clear();
	}

	return *this;
}
