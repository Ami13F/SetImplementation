#pragma once
#include "Persoana.h"
#include "set.h"

class Repository {

	Set<Persoana>multime;

public:

	Repository() = default;

	void adaugaRepo(const Persoana p);

	/*
	Param-->  cnp: Intreg
	Returneaza true daca elementul exita in  multime
	Fals altfel.
	*/
	bool cautaRepo(const int cnp);

	int size() {
		return multime.getDim();
	}

	/*
	Param--> cnp: Int
	Retureaza elementul gasit in multime
	Arunca exceptie daca nu exista.
	*/
	Persoana persoana(const int cnp);

	~Repository() {
		multime.goleste();
	};


};


class ExceptieRepository {
private:
	string msg;
public:
	ExceptieRepository(string mesaj) :msg{ mesaj } {};

	string getMsg() {
		return msg;
	};

};

void testRepository();