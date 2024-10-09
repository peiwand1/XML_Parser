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

XMLParser::XMLParser()
{
	// TODO Auto-generated constructor stub

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
		std::string tagName = "";
		bool tagOpened = false;

		while (file.get(c))
		{
			//read char by char to determine what it is
			if (!tagOpened)
			{
				if (c == '<') // start of tag found
				{
					tagOpened = true;
					std::cout << "< found, reading tag..." << std::endl;
				}

				// TODO also look for text between tags
			}
			else
			{
				if (c == '>')
				{
					tagOpened = false;
					std::cout << tagName << std::endl;
					std::cout << "> found, closing tag."
							<< std::endl << std::endl;

					// TODO make XMLElement object and set the found text as name/attributes
					// reset tagName
					tagName = "";
				}
//				else if (c == '/')
//				{
//					// if next char is > that means this is an empty tag
//					// if prev char is < that means this is a closing tag
//					// could maybe also differentiate by checking if tag name
//					// is before or after it
//				}
//				else if (c == ' ')
//				{
//					// likely indicating an attribute is about to show,
//					// could also indicate an empty tag if next char is / but the space isn't required there
//				}
				else
				{
					// TODO implement checking for attributes, currently they are treated as part of the name
					tagName += c;
				}
			}
		}

		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}
}
