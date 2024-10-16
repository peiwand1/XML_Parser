/*
 * XMLParser.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Peiwand
 */

#include "XMLParser.h"
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

void XMLParser::parse(const std::string &fileName, std::size_t bufferSize)
{
	std::ifstream file;

	file.open(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file: " + fileName);
	}

	// read a buffer of chars from file, do this until whole file is read
	std::vector<char> buffer(bufferSize);
	while (file.read(buffer.data(), bufferSize))
	{
		processChunk(std::string(buffer.data(), file.gcount()));
	}

	// process any remaining data (if less than bufferSize was read)
	if (file.gcount() > 0)
	{
		processChunk(std::string(buffer.data(), file.gcount()));
	}

	file.close();
}

void XMLParser::processChunk(const std::string &buffer)
{
	// read through buffer by char
	for (const char &c : buffer)
	{
		parseByChar(c);
	}
}

void XMLParser::parseByChar(char c)
{
	// handle char based on whether the text is inside or outside <> brackets
	if (!isInsideElement)
	{
		if (c == '<') // start of tag found
		{
			// check if the root xml element has been made and the read text isn't just whitespace
			if (parentOrder.size() > 0
					&& !std::all_of(readStr.begin(), readStr.end(), isspace))
			{
				// remove CR from line endings before setting textcontent, XML only uses LF
				readStr.erase(std::remove(readStr.begin(), readStr.end(), '\r'),
						readStr.end());
				parentOrder.back()->setTextContent(readStr);
			}
			isInsideElement = true;
			readStr = "";
		}
		else
		{
			// look for text between open and close tags
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
	if (std::isspace(readStr.front()))
	{
		throw std::runtime_error(
				"XML Element can't start with whitespace: " + readStr);
	}

	if (readStr.front() == '/') // closing tag </name>
	{
		handleClosingTag();
	}
	else if (readStr.front() == '?') // prolog
	{
		handleMetaData();
	}
	else if (readStr.front() == '!') // comment
	{
		handleComment();
	}
	else
	{
		handleXMLElement();
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
		// throw exception, closing tag had different name than opening tag
		throw std::runtime_error(
				"Closing tag '" + parentOrder.back()->getName()
						+ "' expected inplace of '"
						+ readStr.substr(1, readStr.size() - 1) + "'");
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

		auto pos = attributes.find("version");
		if (pos != attributes.end())
		{
			// warning relating to program functionality
			if (attributes.at("version") != "1.0")
			{
				std::cerr
						<< "Warning: program is only intended to work with XML 1.0, results might be unexpected"
						<< std::endl;
			}
			doc.setVersion(attributes.at("version"));
		}

		pos = attributes.find("encoding");
		if (pos != attributes.end())
		{
			// warning relating to program functionality
			if (attributes.at("encoding") != "UTF-8")
			{
				std::cerr
						<< "Warning: program is only intended to work with UTF-8 encoding, results might be unexpected"
						<< std::endl;
			}
			doc.setEncoding(attributes.at("encoding"));
		}
	}
	else
	{
		// throw exception, formatting wrong
		throw std::runtime_error(
				"Metadata found, but syntax was wrong: " + readStr);
	}
}

void XMLParser::handleComment()
{
	// check if tag starts and ends with correct symbols
	if (readStr.substr(0, 3) == "!--"
			&& readStr.substr(readStr.size() - 2) == "--")
	{
		// comment can't have 2 dashes in the middle, skip dashes at start and end
		bool firstDash = false;
		for (std::size_t i = 3; i < readStr.size() - 2; ++i)
		{
			char c = readStr[i];

			if (c == '-' && firstDash)
			{
				// found 2 dashes in a row
				// throw, can't have -- in comment
				throw std::runtime_error(
						"Double dashes found in comment, this is not allowed: "
								+ readStr);
			}
			else if (c == '-')
			{
				firstDash = true;
			}
			else
			{
				firstDash = false;
			}
		}
	}
	else
	{
		// throw exception, formatting wrong
		throw std::runtime_error("Comment not formatted correctly: " + readStr);
	}
}

void XMLParser::checkNameLegality(std::string &name)
{
	std::string illegalStartChars = "-.1234567890"; // chars that a name can't start with
	auto pos = illegalStartChars.find(name.front());
	if (pos != std::string::npos)
	{
		// first char is '-', '.' or a digit
		throw std::runtime_error(
				"name: " + name + " starts with an illegal character '"
						+ illegalStartChars.at(pos) + "'");
	}

	std::string illegalNameChars = "!\"#$%&'()*+,/;<=>?@[\\]^`{|}~"; // chars that can't be used in name
	for (char c : name)
	{
		pos = illegalNameChars.find(c);
		if (pos != std::string::npos)
		{
			//contains illegal char
			throw std::runtime_error(
					"name: " + name + " contains an illegal character '"
							+ illegalNameChars.at(pos) + "'");
		}
	}
}

void XMLParser::handleXMLElement()
{
	// separate element name from attributes
	std::string name = readStr;
	std::string attr = "";
	auto pos = readStr.find(' ');
	if (pos != std::string::npos)
	{
		name = readStr.substr(0, pos);
		attr = readStr.substr(pos + 1); // +1 to skip the space char
	}
	checkNameLegality(name);

	parentOrder.push_back(new XMLElement(name));

	setParentChildRelations();
	if (attr.size() > 0)
	{
		setAttributes(attr);
	}
	setDocumentRoot();

	// if '/' at end, that doubles as a closing tag
	if (readStr.back() == '/')
	{
		parentOrder.pop_back(); // empty tag <name />
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
	char quoteChar = '\0'; // will be overwritten by the opening quote, either " or '

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
					checkNameLegality(attrName);
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

