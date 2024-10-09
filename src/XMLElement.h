/*
 * XMLObj.h
 *
 *  Created on: 8 Oct 2024
 *      Author: Peiwand
 *
 *  Represents a single XML element
 */

#ifndef XMLELEMENT_H_
#define XMLELEMENT_H_

#include <vector>
#include <map>
#include <string>

class XMLElement
{
public:
	XMLElement(std::string aName);
	XMLElement(const XMLElement &anXMLObj);
	virtual ~XMLElement();

	XMLElement& operator=(const XMLElement &other);
	//TODO add move constructor and -assignment operator
private:
	std::string name;
	std::string textContent;
	std::map<std::string, std::string> attributes;

	XMLElement *parent;
	XMLElement *previous;
	XMLElement *next;
	std::vector<XMLElement*> children;

	const std::string& getName() const;
	void setName(const std::string aName);
	const std::string& getTextContent() const;
	void setTextContent(const std::string aTextContent);
	const std::map<std::string, std::string>& getAttributes() const;
	const std::string& getAttribute(std::string anAttribute) const;
	void addAttribute(const std::string aKey, const std::string aValue);

	XMLElement& getParent() const;
	XMLElement& getPrev() const;
	XMLElement& getNext() const;
	const std::vector<XMLElement*>& getChildren() const;
};

#endif /* XMLELEMENT_H_ */
