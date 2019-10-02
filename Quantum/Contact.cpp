#include "stdafx.h"
#include "Contact.h"

using namespace Quantum;

Contact::Contact()
{
}

Contact::Contact(Body* p1, Body* p2){
	body1 = p1;
	body2 = p2;
}


Contact::~Contact()
{
}
