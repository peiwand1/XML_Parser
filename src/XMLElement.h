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
	/**
	 * constructor
	 * @param aName
	 */
	XMLElement(std::string aName);

	/**
	 * copy constructor
	 * @param anXMLObj
	 */
	XMLElement(const XMLElement &anXMLObj);

	/**
	 * move constructor
	 * @param anXMLObj
	 */
	XMLElement(XMLElement &&anXMLObj);

	virtual ~XMLElement();
	//TODO add move constructor and -assignment operator

	const std::string& getName() const;
	void setName(const std::string &aName);
	const std::string& getTextContent() const;
	void setTextContent(const std::string &aTextContent);

	/**
	 * get all attributes
	 * @return
	 */
	const std::map<std::string, std::string>& getAttributes() const;

	/**
	 * get attribute by name
	 * @param anAttributeKey
	 * @return
	 */
	const std::string& getAttribute(const std::string &anAttributeKey) const;

	/**
	 * add new attribute
	 * @param aKey
	 * @param aValue
	 */
	void addAttribute(const std::string &aKey, const std::string &aValue);

	/**
	 * if called on root object will return nullptr
	 * @return parent
	 */
	XMLElement* getParent() const;
	void setParent(XMLElement *aParent);

	/**
	 *
	 * @return vector of pointers to each child
	 */
	const std::vector<XMLElement*>& getChildren() const;

	/**
	 * add a new XMLElement pointer to children
	 * @param aChild
	 */
	void addChild(XMLElement *aChild);

	/**
	 * copy assignment operator
	 * @param other
	 * @return
	 */
	XMLElement& operator=(const XMLElement &other);

	/**
	 * move assignment operator
	 * @param other
	 * @return
	 */
	XMLElement& operator=(XMLElement&& other);
private:
	std::string name;
	std::string textContent;
	std::map<std::string, std::string> attributes;

	XMLElement *parent;
	std::vector<XMLElement*> children;
};

#endif /* XMLELEMENT_H_ */
