#include <iostream>
#include <string>
#include <vector>
#include <string.h>

#include "simple_int_set.h"

using namespace std;

/**
* check valid operand text started with { and ended with }
* @param[in]	str 		text to be checked for valid integer set
- started with { and ended with }
* @return true if the operand text is valid
*/
bool check_valid_operand(string str) {
	/* TODO: implements here. */
	vector<int> space;
	// space의 위치를 기억할 벡터
	size_t found = str.find_first_of(" ");
	while (found != string::npos) {
		found = str.find_first_of(" ", found + 1);
		space.push_back(found);
	}

	space.erase(space.end() - 1);

	size_t first = 2;

	for (int i = 0; i<space.size(); i++) {
		string number = str.substr(first, space[i] - first);

		//cout << stoi(number) << endl;

		if (stoi(number) <= 0) {
			number = str.substr(first + 1, space[i] - first - 1);
		}

		for (int j = 0; j<number.length(); j++) {
			if (isdigit(number[j]) == 0) {
				return false;
			}
		}
		first = space[i] + 1;
	}
	return true;
}

int main(void) {

	bool	is_valid_input;
	size_t	set_open_index, set_close_index, operator_index;
	string 	inputs, str_integer_set;
	SimpleIntSet operands[2];
	SimpleIntSet resultSet;

	while (true) {
		/* initialize variables. */
		is_valid_input = false;
		operator_index = string::npos;
		set_open_index = string::npos;
		set_close_index = string::npos;

		getline(cin, inputs);

		/* An input of Single character of '0' terminates this process */
		if (inputs == "0") {
			break;
		}

		/* Parse the input text and extract the left operand. */
		set_open_index = inputs.find("{");
		set_close_index = inputs.find("}");

		str_integer_set = inputs.substr(set_open_index,
			set_close_index - set_open_index + 1);

		if (check_valid_operand(str_integer_set)) {
			operands[0].Initialize(str_integer_set);
			is_valid_input = true;
		}

		/* Parse the input text and the operator type. */
		operator_index = inputs.find_first_of("+-*", set_close_index);

		/* Parse the input text and extract the right operand. */
		set_open_index = inputs.find("{", operator_index);
		set_close_index = inputs.find("}", operator_index);

		str_integer_set = inputs.substr(set_open_index,
			set_close_index - set_open_index + 1);


		if (check_valid_operand(str_integer_set)) {
			operands[1].Initialize(str_integer_set);
			is_valid_input &= true;
		}

		if (!is_valid_input || operator_index == string::npos
			|| set_open_index <= operator_index) {
			break;
		}

		/* extracts the operation type from inputs. */
		switch (inputs.at(operator_index)) {
		default:
			break;
		case '+':
			/* TODO: Using operator overlading. */
			resultSet = operands[0] + operands[1];
			break;
		case '-':
			/* TODO: Using operator overlading. */
			resultSet = operands[0] - operands[1];
			break;
		case '*':
			/* TODO: Using operator overlading. */
			resultSet = operands[0] * operands[1];
			break;
		}

		resultSet.Print();
		operands[0].set_clear();
		operands[1].set_clear();
		resultSet.set_clear();

	}

	return 0;
}
