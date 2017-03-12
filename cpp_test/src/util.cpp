#include "util.h"

// Util functions
const std::string toUpper(const std::string& str)
{
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

const int tokenise(const std::string& str, StringVector& tokens, char separator /*= ' '*/)
{
    std::stringstream ss(str);
    std::string tok;
    while (std::getline(ss, tok, separator))
    {
        tokens.push_back(tok);
    }
    return int(tokens.size());
}

StringVector tokenise(const std::string& str, char separator /*= ' '*/)
{
    StringVector tokens;
    std::stringstream ss(str);
    std::string tok;
    while (std::getline(ss, tok, separator))
    {
        tokens.push_back(tok);
    }
    return tokens;
}

const char * WHITESPACE = " \t\v\n\f\r\b\a";

std::string trimStart(const std::string& str, const char *whitespace /*= WHITESPACE*/)
{
    size_t wss = str.find_first_not_of(whitespace);
    if (wss != std::string::npos)
        return str.substr(wss);
    else
        return std::string("");
}

std::string trimEnd(const std::string& str, const char *whitespace /*= WHITESPACE*/)
{
    size_t wss = str.find_last_not_of(whitespace);
    if (wss != std::string::npos)
        return str.substr(0, wss+1);
    else
        return std::string("");
}

std::string trim(const std::string& str, const char *whitespace /*= WHITESPACE*/)
{
    return trimEnd(trimStart(str, WHITESPACE), WHITESPACE);
}

const std::string oneArg(const std::string& cmd, std::string& remainder,
                         const char *whitespace /*= WHITESPACE*/)
{
    std::string orig(trim(cmd));

    if (orig.empty())
    {
        remainder.assign("");
        return std::string("");
    }

    size_t wsPos = orig.find_first_of(whitespace);
    if (wsPos == std::string::npos)
    {
        // there is only one arg
        remainder.assign("");
        return orig;
    }
    else
    {
        remainder.assign(trimStart(orig.substr(wsPos+1)));
        return orig.substr(0, wsPos);
    }
}
