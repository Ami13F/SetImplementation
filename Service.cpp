#include "Service.h"
#include <string>
#include <cassert>

void Service::adauga_service(const string nume, const string prenume, const int cnp, const int nr_carti) {
	const auto cnpS = std::to_string(cnp);
	val.validareIntreg(cnpS);
	Persoana p(nume, prenume, cnp, nr_carti);
	multime.adaugaRepo(p);
}

bool Service::cauta_service(const int cnp)
{
	return multime.cautaRepo(cnp);
}

Persoana Service::persoana_service(const int cnp)
{
	return multime.persoana(cnp);
}



void testService() {

	Repository repo;
	ValidatorPersoana val;
	Service ser{ repo,val };
	ser.adauga_service("Ala", "Bala", 123434, 1);
	assert(ser.size() == 1);

	assert(ser.cauta_service(123434) == true);

	assert(ser.persoana_service(123434).getNume() == "Ala");


}