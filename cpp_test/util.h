#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <exception>

// Util functions
typedef std::vector<std::string> StringVector;

const std::string toUpper(const std::string& str);
const StringVector toUpper(const StringVector& strings);
const int tokenise(const std::string& str, StringVector& tokens, char separator = ' ');

extern const char * WHITESPACE;

std::string trimStart(const std::string& str, const char *whitespace = WHITESPACE);
std::string trimEnd(const std::string& str, const char *whitespace = WHITESPACE);
std::string trim(const std::string& str, const char *whitespace = WHITESPACE);
