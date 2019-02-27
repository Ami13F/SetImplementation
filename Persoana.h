#pragma once
#include <string>
using std::string;
class Persoana {
private:
	string nume;
	string prenume;
	int cnp;
	int nr_carti = 0;

public:
	Persoana() : nume{""}, prenume{""}, cnp{0}, nr_carti{0} {};
	Persoana(string nume, string prenume, int cnp, int nr_carti) :nume{ nume }, prenume{ prenume }, cnp{ cnp }, nr_carti{ nr_carti } {};


	/*
	->returneaza numele unei persoane(string);
	*/
	string getNume() const {
		return nume;
	}

	/*
	->returneaza prenumele unei persoane(string);
	*/
	string getPrenume() const {
		return prenume;
	}

	/*
	->returneaza cnp-ul unei persoane(int);
	*/
	int getCnp() const {
		return cnp;
	}

	/*
	->returneaza nr de carti imprumutate de o persoana(int);
	->initial va fi 0
	*/
	int getNrCarti() const {
		return nr_carti;
	}

	bool operator==(const Persoana& p)const {
		return p.getCnp() == this->getCnp();
	};

	bool operator!=(const Persoana& p) const {
		return p.getCnp() != this->getCnp();
	};

	~Persoana() {};

};


void testPersoana();