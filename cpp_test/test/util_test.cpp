/**
 */
#include <gtest/gtest.h>
#include <algorithm>

#include "util.h"

//const std::string toUpper(const std::string& str);
TEST(GenieUtilsTest, toUpperTest)
{
	ASSERT_STREQ(toUpper("test").c_str(), "TEST");
	ASSERT_STREQ(toUpper("TEST").c_str(), "TEST");
	ASSERT_STREQ(toUpper("test a longer string").c_str(), "TEST A LONGER STRING");
	ASSERT_STREQ(toUpper("").c_str(), "");
	ASSERT_STREQ(toUpper("this\tis\t a\nlonger t3st").c_str(), "THIS\tIS\t A\nLONGER T3ST");
	ASSERT_STREQ(toUpper("1234567890").c_str(), "1234567890");
}

void dumpStringVector(const StringVector& sv) {
	std::for_each(sv.begin(), sv.end(), [](std::string s) { std::cerr << ": " << s << std::endl; });
}

//const int tokenise(const std::string& str, StringVector& tokens, char separator = ' ');
bool TokeniseTest(const std::string& srcString, const int numTokens,
				  const StringVector& expectedTokens, const char separator = ' ')
{
	StringVector tokens;
	int count = tokenise(srcString, tokens, separator);
	std::cerr << "expected.size() = " << expectedTokens.size() << ", tokens.size() = " << tokens.size() << std::endl;
	dumpStringVector(expectedTokens);
	dumpStringVector(tokens);
	return (count == numTokens) && (tokens == expectedTokens);
}

TEST(GenieUtilsTest, int_tokeniseTest)
{
	StringVector dummy;
	ASSERT_TRUE(TokeniseTest("two tokens", 2, makeStringVector(dummy, {"two", "tokens"}), ' '));
}

/*
StringVector tokenise(const std::string& str, char separator = ' ');

const std::string oneArg(const std::string& cmd, std::string& remainder,
                         const char *whitespace = WHITESPACE);

std::string trimStart(const std::string& str, const char *whitespace = WHITESPACE);
std::string trimEnd(const std::string& str, const char *whitespace = WHITESPACE);
std::string trim(const std::string& str, const char *whitespace = WHITESPACE);
 */


int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
