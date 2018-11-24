#pragma once

#include <string>
#include <vector>
#include "State.h"


namespace RegexFA {

	class RegexNFA {

	public:
		RegexNFA(State* start, std::vector<State>&& states);
		bool Match(const std::string& input);

	private:
		std::vector<State> states_;
		State* start_;

		void AddState(std::vector<const State*>& vec, const State* state);
		std::vector<const State*> AdvanceStates(std::vector<const State*>& states, const char c);
		bool IsMatch(const std::vector<const State*>& states);

	};

}
