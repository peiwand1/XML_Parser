/*
 * Tokenizer.h
 *
 *  Created on: 9 Oct 2024
 *      Author: Peiwand
 */

#ifndef XMLTOKENIZER_H_
#define XMLTOKENIZER_H_

#include <string>

enum class TokenType {
    StartTag,
    EndTag,
    AttributeKey,
    AttributeValue,
    Text,
    Comment,
    CData,
    Declaration,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

class XMLTokenizer {
public:
    XMLTokenizer();
    virtual ~XMLTokenizer();

    Token nextToken();

private:
    Token readTag();
    Token readAttribute();
    Token readText();
};

#endif /* XMLTOKENIZER_H_ */
