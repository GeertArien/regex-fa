#include "RegexNFA.h"
#include <algorithm>
#include "State.h"


namespace RegexFA {

	RegexNFA::RegexNFA(State* start, std::vector<State>&& states) : start_(start), states_(std::move(states))
	{ }

	bool RegexNFA::Match(const std::string& input) const {
		std::vector<const State*> current_states{ start_ };

		for(const auto& c : input){
			current_states = AdvanceStates(current_states, c);
			AddState(current_states, start_);
		}

		for (const auto state : current_states) {
			if (state->IsMatch(State::Condition::Match)) {
				return true;
			}
		}

		return false;
	}

	void RegexNFA::AddState(std::vector<const State*>& vec, const State* state) {
		if(state == nullptr || std::find(vec.begin(), vec.end(), state) != vec.end()) {
			return;
		}

		if(state->IsMatch(State::Condition::Split)) {
			AddState(vec, state->out);
			AddState(vec, state->out1);
		}
		else {
			vec.push_back(state);
		}
	}

	std::vector<const State*> RegexNFA::AdvanceStates(std::vector<const State*>& states, const char c) {
		std::vector<const State*> output;
		for(const auto& state : states) {
			if (state->IsMatch(State::Condition::Match)) {
				AddState(output, state);
			}
			else if (state->IsMatch(c)) {
				AddState(output, state->out);
			}
		}
		return output;
	}

}