#include <iostream>
#include <CMDArgument.h>
#include <CMDParser.h>
#include "regex/RegexNFA.h"
#include "regex/NFABuilder.h"


using namespace RegexFA;


int main(int argc, const char** argv) {
	CMDArgument show_help(CMDArgument::Type::Bool, "--help", "show help", false);
	CMDArgument regex(CMDArgument::Type::String, "--regex", "regular expression", std::string(), true);
	CMDArgument output(CMDArgument::Type::String, "--input", "input string", std::string(), true);

	CMDParser cmd_parser("--regex ab.b.a. --input abbaba");
	cmd_parser.SetArguments({ &show_help, &regex, &output });

	if (!cmd_parser.Parse(argc, argv)) {
		if (!show_help.GetBoolValue()) {
			cmd_parser.PrintErrors(std::cerr);
			return 1;
		}
	}

	if (show_help.GetBoolValue()) {
		cmd_parser.PrintHelp(std::cout);
	}
	else {
		RegexNFA nfa = PostfixToNFA(regex.GetStringValue());

		if (nfa.Match(output.GetStringValue())) {
			std::cout << "Match!" << std::endl;
		}
		else {
			std::cout << "No match!" << std::endl;
		}
	}

	return 0;
}