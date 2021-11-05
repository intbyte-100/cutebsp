#include <string>

#pragma once


class ShellInputStream
{
private:
    FILE* shellStream;
    char lastChar;
    short currentCharIndex;
    short nextCharIndex;

public:
    ShellInputStream(std::string& cmd);
    void open(std::string& cmd);
    void close();
    bool hasNext();
    char nextChar();
    std::string nextString();
};


