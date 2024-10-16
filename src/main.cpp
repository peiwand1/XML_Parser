/*
 * main.cpp
 *
 *  Created on: 9 Oct 2024
 *      Author: Peiwand
 */

#include "XMLParser.h"
#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		XMLParser parser;
		parser.parse("XML.txt");

		parser.print();
	} catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
