#include "NFABuilder.h"


namespace {

	using namespace RegexFA;

	struct Frag final {
		Frag() = default;
		Frag(State* start_p, std::vector<State**> out_p) : start(start_p), out(std::move(out_p)) { }

		State* start = nullptr;
		std::vector<State**> out;
	};

	std::vector<State**> list1(State** outp) {
		return { outp };
	}

	std::vector<State**> append(const std::vector<State**>& v1, const std::vector<State**>& v2) {
		std::vector<State**> output;
		std::copy(v1.begin(), v1.end(), std::back_inserter(output));
		std::copy(v2.begin(), v2.end(), std::back_inserter(output));
		return output;
	}

	void patch(std::vector<State**>& list, State* s) {
		for (auto& state : list) {
			*state = s;
		}
	}

	template <typename T>
	State* AddState(std::vector<State>& states, T c, State* out, State* out1) {
		states.emplace_back(c, out, out1);
		return &*states.rbegin();
	}

}


namespace RegexFA {

	RegexNFA PostfixToNFA(const std::string& postfix_regex) {
		Frag stack[1000], *stackp, e1, e2, e;
		State* state = nullptr;
		std::vector<State> states;
		states.reserve(postfix_regex.size());

#define push(s) *stackp++ = s
#define pop()   *--stackp

		stackp = stack;

		for(const auto& c : postfix_regex) {

			switch(c) {

				case '.':
					e2 = pop();
					e1 = pop();
					patch(e1.out, e2.start);
					push(Frag(e1.start, e2.out));
					break;

				case '|':
					e2 = pop();
					e1 = pop();
					state = AddState(states, State::Condition::Split, e1.start, e2.start);
					push(Frag(state, append(e1.out, e2.out)));
					break;

				case '?':
					e = pop();
					state = AddState(states, State::Condition::Split, e.start, nullptr);
					push(Frag(state, append(e.out, list1(&state->out1))));
					break;

				case '*':
					e = pop();
					state = AddState(states, State::Condition::Split, e.start, nullptr);
					patch(e.out, state);
					push(Frag(state, list1(&state->out1)));
					break;

				case '+':
					e = pop();
					state = AddState(states, State::Condition::Split, e.start, nullptr);
					patch(e.out, state);
					push(Frag(e.start, list1(&state->out1)));
					break;

				default:
					state = AddState(states, c, nullptr, nullptr);
					push(Frag(state, list1(&state->out)));
					break;
			}
		}

		e = pop();
		State match(State::Condition::Match, nullptr, nullptr);
		patch(e.out, &match);
		states.shrink_to_fit();

		return {e.start, std::move(states)};
	}

}