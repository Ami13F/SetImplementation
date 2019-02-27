#pragma once
#include <string>
using std::string;
#define NIL -1
#define CAP_INIT 100


template<typename TElement>
class IteratorSet;


//o functie care verifica egalitatea a doua elemente
template<typename TElement>
using cmp_fct = bool(*)(const TElement& t1, const TElement& t2);

template<typename TElement>
bool fct_egal(const TElement& t1, const TElement& t2) {
	return t1 == t2;
}

class Exceptie {
	string msg;
public:
	Exceptie(const string& msg) :msg{ msg } {};

	const string& getMsg() const {
		return msg;
	}
};


template<typename TElement>
class Set {
private:

	//un vector care memoreaza adresele nodului anterior
	int* prec;
	//un vector care memoreaza adresele urmatorului nod
	int* urm;
	//un vector care memoreaza valorile nodurilor
	TElement* elem;
	//pozitia primului nod din lista si respectiv pozitia primei locatii libere
	int prim, primLiber;
	//dimensiunea logica
	int dim;
	//capacitate totala tablou
	int cp;

	//functie de comparare intre doua elemente de tip T
	cmp_fct<TElement> egal;

	//alocam memorie pentru un nod
	//returneaza pozitia nodului alocat
	int alocaNod();

	//dealocam memoria pentru un nod
	//param:  nod : int
	void dealocaNod(int nod);

	//creeaza nod 
	//primeste o valoare de tip TElement si returneaza pozitia in lista a nodului nou creeat;
	//param: value: T
	int creeazaNod(const TElement& value);


public:
	//constructor implicit
	Set(); 
	//constructor cu functie de comparare
	//primeste parametru o functie care compara doua obiecte de tip T
	Set(cmp_fct<TElement> fct_param);



	//adauga un nod 
	void adauga(const TElement& el);

	//sterge un element din multime
	void sterge(const TElement& el);

	//dimensiunea multimii(nr de elemente pe care le contine)
	const int & getDim()const ;

	//sterge toate elementele din multime
	void goleste();

	bool vida();

	IteratorSet<TElement> cauta(const TElement& el);

	//returneaza un iterator catre primul element din multime
	IteratorSet<TElement> primElem();

	//returneaza un iterator catre ultimul element din multime
	IteratorSet<TElement> ultimElem();

	friend class IteratorSet<TElement>;

	//destructor
	~Set();

};

template<typename TElement>
int Set<TElement>::alocaNod()
{
	int nod = primLiber;
	primLiber = urm[primLiber];

	return nod;
}

template<typename TElement>
void Set<TElement>::dealocaNod(int nod)
{
	prec[nod] = NIL;
	urm[nod] = primLiber;
	prec[primLiber] = nod;
	primLiber = nod;
}


template<typename TElement>
int Set<TElement>::creeazaNod(const TElement & value)
{
	int nod = alocaNod();
	urm[nod] = NIL;
	prec[nod] = NIL;
	elem[nod] = value;
	return nod;
}


template<typename TElement>
Set<TElement>::Set() : prec{ nullptr }, urm{ nullptr }, elem{ nullptr },
			prim{ NIL }, primLiber{ NIL }, dim{ 0 }, cp{ CAP_INIT }, egal{ fct_egal } {
	prec = new int[cp];
	urm = new int[cp];
	elem = new TElement[cp];
	for (int i = 0; i < cp; i++) {
		prec[i] = i - 1;
		urm[i] = i + 1;
	}
	urm[cp-1] = NIL;
	primLiber = 0;

}

template<typename TElement>
Set<TElement>::Set(cmp_fct<TElement> fct_param): prec{ nullptr }, urm{ nullptr }, elem{ nullptr },
									prim{ NIL }, primLiber{ NIL }, dim{ 0 }, cp{ CAP_INIT }, egal{ fct_param } {
	prec = new int[cp];
	urm = new int[cp];    //alocam memorie pentru noduri
	elem = new TElement[cp];
	for (int i = 0; i < cp; i++) {
		prec[i] = i - 1;   //setam legaturile intre noduri
		urm[i] = i + 1;
	}
	urm[cp - 1] = NIL;     
	primLiber = 0;   // initializam pozitia primului spatiu liber
}

template<typename TElement>
void Set<TElement>::adauga(const TElement & el)
{
	//daca e plin arunc exceptie
	if (dim == cp) {
		throw Exceptie("Multimea e plina");
	}
	int nod = creeazaNod(el);

	//cazul in care multime vida
	if (prim == NIL) {
		prim = nod;
	}
	else {
		int i = prim;
		//cat timp nu am ajuns la final sau nu am gasit elementul 
		while (i != NIL && !egal(elem[i], elem[nod])) {
			i = urm[i];
		}
		if (i == NIL) {
			urm[nod] = prim;
			prec[prim] = nod;
			prim = nod;
		}
		else {
			dealocaNod(nod);
			throw Exceptie("Elementul exista!");
		}
	}
	dim++;
}

template<typename TElement>
void Set<TElement>::sterge(const TElement & el)
{
	//multimea e vida
	if (prim == NIL) {
		throw Exceptie("Multimea e vida!");
	}
	int i = prim;
	while (i != NIL && !egal(el, elem[i])) {
		i = urm[i];
	}
	if (i == NIL) {
		throw Exceptie("Elementul nu exista!");
	}
	//elementul e pe prima pozitie
	if (i == prim) {
		int var = prim;
		prim = urm[prim];
		dealocaNod(var);
		//daca nu are un singur element marcam legatura cu nodul anterior ca fiind NIL
		if (prim != NIL) prec[prim] = NIL;
	}
	//daca e pe ultima pozitie
	else if (urm[i]==NIL) {
		urm[prec[i]] = urm[i];
		dealocaNod(i);
	}
	//se afla pe pozitia i in lista
	else {
		prec[urm[i]] = prec[i];
		urm[prec[i]] = urm[i];
		dealocaNod(i);
	}
	dim--;
}

template<typename TElement>
const int & Set<TElement>::getDim()const{
	return dim;
}

template<typename TElement>
void Set<TElement>::goleste(){
	//daca e vida deja
	if (prim == NIL) {
		return;
	}
	int i = prim;
	while (i != NIL) {
		sterge(elem[i]);
		i = prim;
	}
}

template<typename TElement>
bool Set<TElement>::vida()
{
	if (dim == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<typename TElement>
IteratorSet<TElement> Set<TElement>::cauta(const TElement& el)
{
	int i = prim;
	while (!egal(el, elem[i]) && i != NIL) {
		i = urm[i];
	}
	return IteratorSet<TElement>(*this, i);
}

template<typename TElement>
IteratorSet<TElement> Set<TElement>::primElem()
{
	IteratorSet<TElement> it(*this);
	return it;

}

template<typename TElement>
IteratorSet<TElement> Set<TElement>::ultimElem()
{
	IteratorSet<TElement> it(*this,NIL);
	return it;                                                                                                                                                                       
}

template<typename TElement>
Set<TElement>::~Set()
{
	//dealocam
	delete[] prec;
	delete[] urm;
	delete[] elem;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*****************					      ITERATOR                             *************************
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename TElement>
class IteratorSet {
	int curent;
	Set<TElement>& set;

public:
	IteratorSet(Set<TElement>& set);
	IteratorSet(Set<TElement>& set,int poz);

	TElement& element();

	void urmator();

	void anterior();

	bool valid();

	bool operator==(const IteratorSet& other){
		return this->curent == other.curent;
	}
	bool operator!=(const IteratorSet& other) {
		return this->curent != other.curent;
	}
};


template<typename TElement>
IteratorSet<TElement>::IteratorSet(Set<TElement>& set) :set{ set }
{
	curent = set.prim;
}

template<typename TElement>
IteratorSet<TElement>::IteratorSet(Set<TElement>& set, int poz):set{set},curent{poz}{
}

template<typename TElement>
TElement & IteratorSet<TElement>::element()
{	
	return set.elem[curent];
}

template<typename TElement>
void IteratorSet<TElement>::urmator()
{
	if(valid())
	curent = set.urm[curent];
}

template<typename TElement>
void IteratorSet<TElement>::anterior()
{

	if(set.prec[curent]!=NIL)
	curent = set.prec[curent];
}

template<typename TElement>
bool IteratorSet<TElement>::valid()
{
	return curent != NIL;
}

void testConstructor();
void testAdauga();
void testSterge();
void testGoleste();
void testIterator();
void testParcurgere();