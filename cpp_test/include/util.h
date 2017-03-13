#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <initializer_list>

// Util functions
typedef std::vector<std::string> StringVector;

extern const char * WHITESPACE;

const StringVector& makeStringVector(StringVector& outVector, std::initializer_list<std::string> ilist);

const std::string toUpper(const std::string& str);
const int tokenise(const std::string& str, StringVector& tokens, char separator = ' ');
StringVector tokenise(const std::string& str, char separator = ' ');

const std::string oneArg(const std::string& cmd, std::string& remainder,
                         const char *whitespace = WHITESPACE);

//template<class T>
//const std::string toString(const T& val);

std::string trimStart(const std::string& str, const char *whitespace = WHITESPACE);
std::string trimEnd(const std::string& str, const char *whitespace = WHITESPACE);
std::string trim(const std::string& str, const char *whitespace = WHITESPACE);
