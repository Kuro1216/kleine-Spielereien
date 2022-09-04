#ifndef _TOKEN_H
#define _TOKEN_H

#include "list.h"

class Tokenizer {
private:
    unsigned int _pos;
    List<std::string> _tokens;

public:
    Tokenizer(std::string data, std::string separators);
    int countTokens();
    std::string nextToken();
    bool hasMoreTokens();
};

#endif
