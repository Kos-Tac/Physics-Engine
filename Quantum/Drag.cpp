#include "stdafx.h"
#include "Drag.h"

using namespace Quantum;

Drag::Drag()
{
}


Drag::~Drag()
{
}

void Drag::update(QmParticle* p){
	float coeff = -(1.0f * glm::length(p->getVel()) + 1.0f * glm::length(p->getVel()) * glm::length(p->getVel()));
	p->addForce(glm::normalize(p->getVel()) * coeff);
}