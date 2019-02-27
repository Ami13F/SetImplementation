#pragma once
#include "Repository.h"
#include "Persoana.h"
#include "Validator.h"
class Service {
private:
	Repository& multime;
	ValidatorPersoana val;
public:
	Service(Repository& multime, ValidatorPersoana val) :multime{ multime }, val{ val } {};
	void adauga_service(const string nume, const string prenume, const int cnp, const int nr_carti);

	bool cauta_service(const int cnp);

	Persoana persoana_service(const int cnp);

	int size() {
		return multime.size();
	};

	~Service() {};
};

void testService();