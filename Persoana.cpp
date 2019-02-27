#include "Persoana.h"
#include <cassert>

void testPersoana()
{
	Persoana p("Ion", "Dan", 2345, 4);
	assert(p.getNume() == "Ion");
	assert(p.getPrenume() == "Dan");
	assert(p.getCnp() == 2345);
	assert(p.getNrCarti() == 4);

}
