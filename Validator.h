#pragma once
#include "Persoana.h"
#include <vector>
using std::vector;

class ValidatorException {
	vector<string>msgs;

public:
	ValidatorException() = default;
	ValidatorException(vector<string> err) : msgs{ err } {};

};


class ValidatorPersoana {
public:
	ValidatorPersoana() = default;
	void validate(const Persoana& p);
	void validareIntreg(const string intreg);

};

void testValidator();