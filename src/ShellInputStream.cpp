#include "ShellInputStream.h"

#include <stdexcept>



ShellInputStream::ShellInputStream(std::string& cmd)
{
    open(cmd);
}

void ShellInputStream::open(std::string &cmd)
{
    shellStream = popen(cmd.c_str(), "r");
}

void ShellInputStream::close()
{
    pclose(shellStream);
}

bool ShellInputStream::hasNext()
{
    nextCharIndex = currentCharIndex + 1;
    return (lastChar = fgetc(shellStream)) != EOF;
}

char ShellInputStream::nextChar()
{
    currentCharIndex++;
    if(!(currentCharIndex == nextCharIndex))
        if(!hasNext())
            throw std::runtime_error("ShellInputStream: can't return a next char");

    return lastChar;
}

std::string ShellInputStream::nextString()
{
    std::string str;
    while (hasNext()) {
        char c = nextChar();
        if(c == '\n') break;
        str+=c;
    }
    return str;
}
