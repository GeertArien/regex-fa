#pragma once


namespace RegexFA {

	struct State final {

	public:
		enum class Condition : int {
			Split = 256,
			Match = 257,
		};

		State() = default;
		State(int c_p, State* out_p, State* out1_p) : condition(c_p), out(out_p), out1(out1_p) { }
		State(Condition c_p, State* out_p, State* out1_p) : condition(static_cast<int>(c_p)), out(out_p), out1(out1_p)
		{ }

		bool IsMatch(int c) const
		{ return condition == c; }
		bool IsMatch(Condition c) const
		{ return condition == static_cast<int>(c); }

		int condition = -1;
		State* out = nullptr;
		State* out1 = nullptr;
	};

}
