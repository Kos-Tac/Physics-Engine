#include "stdafx.h"
#include "Magnetism.h"

using namespace Quantum;

Magnetism::Magnetism()
{
}


Magnetism::~Magnetism()
{
}

Magnetism::Magnetism(QmParticle* oP)
{
	otherParticle = oP;
}

void Magnetism::update(QmParticle* p){
	glm::vec3 d = p->getPos() - otherParticle->getPos();
	
	float norm = glm::length(d);
	float coeff = 7.0*(p->getMagnCharge() * otherParticle->getMagnCharge());
	if (norm>0.1)
		p->addForce(glm::normalize(d)*coeff/norm/norm);
}