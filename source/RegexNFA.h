#pragma once

#include <string>
#include <vector>
#include "State.h"


namespace RegexFA {

	class RegexNFA {

	public:
		RegexNFA(State* start, std::vector<State>&& states);
		bool Match(const std::string& input) const;

	private:
		std::vector<State> states_;
		State* start_;

		static void AddState(std::vector<const State*>& vec, const State* state);
		static std::vector<const State*> AdvanceStates(std::vector<const State*>& states, const char c);

	};

}
