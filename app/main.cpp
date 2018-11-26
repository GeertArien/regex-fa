#include <iostream>
#include <Argument.h>
#include <Parser.h>
#include "../source/RegexNFA.h"
#include "../source/NFABuilder.h"


using namespace RegexFA;


int main(int argc, const char** argv) {
	CMD::Argument show_help(CMD::Argument::Type::Bool, "--help", "show help", false);
	CMD::Argument regex(CMD::Argument::Type::String, "--regex", "regular expression", std::string(), true);
	CMD::Argument output(CMD::Argument::Type::String, "--input", "input string", std::string(), true);

	CMD::Parser cmd_parser("--regex ab.b.a. --input abbaba");
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