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
		doc(), parentOrder(), isInsideElement(false), readStr("")
{

}

XMLParser::~XMLParser()
{
}

void XMLParser::parse(std::string fileName)
{
	std::ifstream file;

	file.open(fileName);
	if (file.is_open())
	{
		char c;
		std::string readStr = "";

		while (file.get(c))
		{
			//read char by char to determine what it is
			parseByChar(c);
		}

		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}
}

void XMLParser::parseByChar(char c)
{
	//read char by char to determine what it is
	if (!isInsideElement)
	{
		if (c == '<') // start of tag found
		{
			//check if the root xml element has been made and the read text isn't just whitespace
			if (parentOrder.size() > 0
					&& !std::all_of(readStr.begin(), readStr.end(), isspace))
			{
				// TODO replace line endings with LF (omit CR if it's there)
				parentOrder.back()->setTextContent(readStr);
			}
			isInsideElement = true;
			readStr = "";
		}
		else
		{
			// look for text between open and close tags,
			readStr += c;
		}
	}
	else
	{
		if (c == '>')
		{
			isInsideElement = false;

			handleXMLInside();
			// reset tagName
			readStr = "";
		}
		else
		{
			// read text that is between < > brackets
			readStr += c;
		}
	}
}

void XMLParser::handleXMLInside()
{
	if (readStr.front() == '/') // closing tag </name>
	{
		handleClosingTag();
		return;
	}
	else if (readStr.front() == '?') // prolog
	{
		handleMetaData();
		return;
	}
	else if (readStr.front() == '!') // comment
	{
		// TODO check if comment syntax is accurate
		return;
	}

	// isolate element name from string
	std::string name = readStr;
	std::string attr = "";
	auto pos = readStr.find(' ');
	if (pos != std::string::npos)
	{
		name = readStr.substr(0, pos);
		attr = readStr.substr(pos + 1); // +1 to skip the space char
	}

	parentOrder.push_back(new XMLElement(name));

	setParentChildRelations();
	if (attr.size() > 0)
	{
		setAttributes(attr);
	}
	setDocumentRoot();

	if (readStr.back() == '/')
	{
		parentOrder.pop_back(); // empty tag <name />
	}
}

void XMLParser::handleClosingTag()
{
	// check if name matches that of latest parent in order
	if (readStr.substr(1, readStr.size() - 1) == parentOrder.back()->getName())
	{
		parentOrder.pop_back();
	}
	else
	{
		// TODO throw exception, closing tag had different name than opening tag
		//throw "Closing tag '" + parentOrder.back()->getName() + "' expected inplace of '" + readStr.substr(1, readStr.size()-1) + "'";
	}
}

void XMLParser::handleMetaData()
{
	// check if tag starts and ends with correct symbols
	if (readStr.substr(0, 4) == "?xml" && readStr.back() == '?')
	{
		// split "?xml " from string
		std::string attrStr = readStr.substr(5);
		std::map<std::string, std::string> attributes =
				extractAttrKeyValuePairs(attrStr);

//		std::cout << attributes.at("version") << std::endl;
//		std::cout << attributes.at("encoding") << std::endl;

		auto pos = attributes.find("version");
		if (pos != attributes.end())
		{
			doc.setVersion(attributes.at("version"));
		}

		pos = attributes.find("encoding");
		if (pos != attributes.end())
		{
			doc.setEncoding(attributes.at("encoding"));
		}
	}
	else
	{
		// TODO throw exception, formatting wrong
	}
}

void XMLParser::setParentChildRelations()
{
	if (parentOrder.size() > 1)
	{
		XMLElement *parent = parentOrder.at(parentOrder.size() - 2); // second to last item
		XMLElement *child = parentOrder.back(); // last item

		parent->addChild(child);
		child->setParent(parent);
	}
}

void XMLParser::setAttributes(const std::string &str)
{
	// if no equals sign, there are no attributes
	if (str.find('=') == std::string::npos)
		return;

	std::map<std::string, std::string> attributes = extractAttrKeyValuePairs(
			str);

	for (const auto &kv : attributes)
	{
		parentOrder.back()->addAttribute(kv.first, kv.second);
	}
}

void XMLParser::setDocumentRoot()
{
	if (doc.getRoot() == nullptr) // will only happen when the first XML element is found
	{
		doc.setRoot(parentOrder.front());
	}
}

std::map<std::string, std::string> XMLParser::extractAttrKeyValuePairs(
		const std::string &str)
{
	std::map<std::string, std::string> attributes;
	std::string attrName, attrValue;
	bool inName = true, inValue = false, insideQuotes = false;
	char quoteChar = '\0';

	for (std::size_t i = 0; i < str.size(); ++i)
	{
		char c = str[i];
		// ignore leading spaces
		if (std::isspace(c) && !inValue && !insideQuotes)
		{
			continue;
		}
		if (inName)
		{
			if (c == '=')
			{
				// end of attribute name
				inName = false;
				inValue = true;
				continue;
			}
			else
			{
				attrName += c;
			}
		}
		else if (inValue)
		{
			if (!insideQuotes)
			{
				// first quote encountered, can be " or ', remember this for closing the quote
				if (c == '"' || c == '\'')
				{
					insideQuotes = true;
					quoteChar = c;
				}
			}
			else
			{
				// End quote found
				if (c == quoteChar)
				{
					insideQuotes = false;
					inValue = false;

					// store the attribute name and value
					attributes[attrName] = attrValue;

					attrName = "";
					attrValue = "";
					inName = true; // expect another attribute name next
				}
				else
				{
					attrValue += c;
				}
			}
		}
	}
	return attributes;
}

void XMLParser::print()
{
	doc.printTree();
}

