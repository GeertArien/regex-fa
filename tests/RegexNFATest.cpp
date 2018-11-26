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
