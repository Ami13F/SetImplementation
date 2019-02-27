#include "Validator.h"
#include <cassert>
#include <iostream>


void ValidatorPersoana::validate(const Persoana & p)
{
	vector<string>msgs;

	if (p.getCnp() <= 0) { msgs.push_back(" Id negativ!"); }

	if (p.getNrCarti() < 0) { msgs.push_back(" Nr carti invalid!"); }

	if (p.getNume() == "") { msgs.push_back(" Nume invalid"); }

	if (p.getPrenume() == "") { msgs.push_back(" Prenume invalid"); }

	if (size(msgs) > 0)
		throw ValidatorException(msgs); 
}

void ValidatorPersoana::validareIntreg(const string intreg)
{
	vector<string>err;
	if (intreg == "") {
		err.push_back("Numar invalid");
		throw ValidatorException(err);
	}
	for (const auto c : intreg) {
		if (c<'0' || c>'9') {
			err.push_back("Numar invalid");
			throw ValidatorException(err);
		}
	}
}
void testValidator()
{
	ValidatorPersoana v;
	//prenume invalid
	Persoana p1 = Persoana{ "Ion","",143,3 };
	try {
		v.validate(p1);	assert(false); 	}
	catch (ValidatorException&) {
		assert(true);}

	//nume invalid
	Persoana p2 = Persoana{ "","Dan",143,3 };
	try {
		v.validate(p2); assert(false);	}
	catch (ValidatorException&) {
		assert(true);}

	//cnp invalid
	Persoana p3 = Persoana{ "Ion","Bot",-123,3 };
	try {
		v.validate(p3); assert(false); 	}
	catch (ValidatorException&) {
		assert(true);}

	//numar invalid
	try {
		v.validareIntreg("das243"); assert(false); 	}
	catch (ValidatorException&) {
		assert(true);}

	//nr vid
	try {
		v.validareIntreg(""); assert(false); 	}
	catch (ValidatorException&) {
		assert(true);}
}
