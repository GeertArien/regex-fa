#include <catch.hpp>
#include "../source/RegexNFA.h"
#include "../source/NFABuilder.h"


using namespace  RegexFA;


TEST_CASE( "Regex concatenation", "[RegexNFA]" ) {
	RegexFA::RegexNFA nfa = PostfixToNFA("ab.");
	REQUIRE(nfa.Match("ab"));
	REQUIRE(!nfa.Match("ba"));
	REQUIRE(nfa.Match("aaaba"));

	nfa = PostfixToNFA("ab.c.d.");
	REQUIRE(!nfa.Match("ab"));
	REQUIRE(!nfa.Match("aaabbcdd"));
	REQUIRE(nfa.Match("aaabcda"));
}

TEST_CASE( "Regex 'or' operator", "[RegexNFA]" ) {
	RegexFA::RegexNFA nfa = PostfixToNFA("abc|.a.");
	REQUIRE(nfa.Match("aba"));
	REQUIRE(nfa.Match("aca"));
	REQUIRE(!nfa.Match("ada"));
	REQUIRE(!nfa.Match("abca"));
	REQUIRE(!nfa.Match("ab"));
}

TEST_CASE( "Regex 'match zero or one' operator", "[RegexNFA]" ) {
	RegexFA::RegexNFA nfa = PostfixToNFA("ab?.c.");
	REQUIRE(nfa.Match("abc"));
	REQUIRE(nfa.Match("ac"));
	REQUIRE(!nfa.Match("ab"));
	REQUIRE(!nfa.Match("abbc"));
	REQUIRE(!nfa.Match("bc"));
}

TEST_CASE( "Regex 'match zero or more' operator", "[RegexNFA]" ) {
	RegexFA::RegexNFA nfa = PostfixToNFA("ab*.c.");
	REQUIRE(nfa.Match("abc"));
	REQUIRE(nfa.Match("ac"));
	REQUIRE(nfa.Match("abbc"));
	REQUIRE(!nfa.Match("ab"));
	REQUIRE(!nfa.Match("bc"));
}

TEST_CASE( "Regex 'match one or more' operator", "[RegexNFA]" ) {
	RegexFA::RegexNFA nfa = PostfixToNFA("ab+.c.");
	REQUIRE(nfa.Match("abc"));
	REQUIRE(!nfa.Match("ac"));
	REQUIRE(nfa.Match("abbc"));
	REQUIRE(!nfa.Match("ab"));
	REQUIRE(!nfa.Match("bc"));
}