#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

#include "Persoana.h"
#include "Repository.h"
#include <assert.h>
#include <iostream>
#include "set.h"
#include <unordered_set>
#include "Service.h"

void testeSet() {

	testConstructor();
	testAdauga();
	testSterge();
	testGoleste();
	testIterator();
	testParcurgere();
}

void teste() {

	testPersoana();
	testeSet();
	testRepository();
	testService();
	testValidator();
}

int main() {

	teste();

	_CrtDumpMemoryLeaks();

	return 0;
}