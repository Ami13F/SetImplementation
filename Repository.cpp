#include "Repository.h"
#include <cassert>

void Repository::adaugaRepo(const Persoana p)
{
	try {
		multime.adauga(p);
	}
	catch (Exceptie&) {
		throw ExceptieRepository("Persoana exista deja");}
}

bool Repository::cautaRepo(const int cnp)
{
	auto it = multime.cauta(Persoana("", "", cnp, 0));
	return it != multime.ultimElem();
}

Persoana Repository::persoana(const int cnp)
{
	auto it = multime.cauta(Persoana("", "", cnp, 0));
	if (it == multime.ultimElem()) {
		throw ExceptieRepository("Nu exista persoana");
	}
	Persoana p = it.element();
	return p;

}

void testRepository()
{
	Repository repo;

	Persoana p{ "Ana","Cristina",13,42 };
	assert(repo.cautaRepo(13) == false);
	repo.adaugaRepo(p);
	assert(repo.cautaRepo(13) == true);

	//incercam sa adaugam de 2 ori
	try {
		repo.adaugaRepo(p);}
	catch (ExceptieRepository&) {
		assert(true);
	}
	auto per = repo.persoana(13);
	assert(per.getCnp() == 13);
	//cauta o persoana care nu exista
	try {
		repo.persoana(43);}
	catch (ExceptieRepository&) {
		assert(true);
	}
}
