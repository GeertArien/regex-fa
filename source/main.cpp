#include <iostream>
#include "cmd_line/CMDParser.h"
#include "regex/RegexNFA.h"
#include "regex/NFABuilder.h"


using namespace RegexFA;


int main(int argc, const char** argv) {
	CMDArgument show_help(CMDArgument::Type::Bool, "--help", "show help", false);
	CMDArgument regex(CMDArgument::Type::String, "--regex", "regular expression", std::string(), true);
	CMDArgument output(CMDArgument::Type::String, "--input", "input string", std::string(), true);

	CMDParser cmd_parser;

	if (!cmd_parser.Parse(argc, argv, { &show_help, &regex, &output })) {
		if (!show_help.GetBoolValue()) {
			std::vector<std::string> errors = cmd_parser.GetErrors();
			std::cerr << "Errors:" << std::endl;

			for (const auto& error : errors) {
				std::cerr << "- " << error << std::endl;
			}

			return 1;
		}
	}

	if (show_help.GetBoolValue()) {
//		PrintHelp({ &show_help, &input, &output, &lang });
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