#pragma once

#include <string>
#include "RegexNFA.h"


namespace RegexFA {

	RegexNFA PostfixToNFA(const std::string& postfix_regex);

}

