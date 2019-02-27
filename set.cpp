#include "set.h"
#include <assert.h>

void testConstructor()
{
	Set<int> set1;

	assert(set1.getDim() == 0);

	Set<int>set2([](const int& t1, const int& t2) {return t1 > t2; });
	assert(set2.getDim() == 0);

}

void testAdauga()
{
	Set<int> setTest;


	assert(setTest.getDim() == 0);
	setTest.adauga(400);
	assert(setTest.getDim() == 1);
	try {
		setTest.adauga(400); assert(false);}
	catch (const Exceptie&) {
		assert(true);
	}
	for (int i = 0; i < 99; ++i) {
		setTest.adauga(i);
	}
	try{
		setTest.adauga(2); assert(false);	}
	catch (const Exceptie&) {
		assert(true);
	}

}

void testSterge()
{
	Set<int> setTest;
	//sterg din multime vida
	try {
		setTest.sterge(5);}
	catch (const Exceptie&) {
		assert(true);
	}
	//sterg element inexistent
	setTest.adauga(1); 
	try {
		setTest.sterge(5);}
	catch (const Exceptie&) {
		assert(true);
	}
	//sterg daca lista are un singur element
	setTest.sterge(1);
	assert(setTest.getDim() == 0);
	setTest.adauga(1);
	setTest.adauga(2); 
	setTest.adauga(3);
	//sterg element de pe ultima pozitie;
	setTest.sterge(1);
	setTest.sterge(3);
	assert(setTest.getDim() == 1);
	setTest.sterge(2);
	assert(setTest.getDim() == 0);

	setTest.adauga(4);
	setTest.adauga(5);
	setTest.adauga(6);
	//sterg un element care nu se afla pe prima sau ultima pozitie
	setTest.sterge(5);
	assert(setTest.getDim() == 2);
	setTest.sterge(4);
	setTest.sterge(6);
	assert(setTest.getDim() == 0);
	
}

void testGoleste()
{
	Set<int>setTest;
	assert(setTest.vida() == true);
	//am golit un set vid
	setTest.goleste();
	setTest.adauga(1);
	setTest.adauga(2);
	setTest.adauga(3);
	setTest.adauga(4);
	setTest.adauga(5);
	assert(setTest.vida() == false);
	assert(setTest.getDim() == 5);
	setTest.goleste();
	assert(setTest.getDim() == 0);
	assert(setTest.vida() == true);
}

void testIterator()
{
	Set <int>setTest;
	IteratorSet<int> itTest1(setTest);
	assert(!itTest1.valid());
	setTest.adauga(1);
	IteratorSet<int> itTest2(setTest);
	assert(itTest2.valid());
	int it = itTest2.element();
	assert(it == 1);
	itTest2.element() = 2;
	int it2 = itTest2.element();
	assert(it2 == 2);
	itTest2.urmator();
	assert(!itTest2.valid());
	itTest2.anterior();
	assert(itTest2.valid());

}

void testParcurgere()
{
	Set<int>setTest;
	setTest.adauga(1);
	setTest.adauga(2);
	setTest.adauga(3);
	IteratorSet<int> it =  setTest.primElem();
	int val = it.element();
	assert(val== 3);
	for (IteratorSet<int> it = setTest.primElem(); it != setTest.ultimElem(); it.urmator())
	{
		assert(it.valid());
	}
	IteratorSet<int>it2 =  setTest.cauta(1);
	assert(it2.element() == 1);
	
}
