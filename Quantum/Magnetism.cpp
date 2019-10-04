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
	float coeff = 9.0*(p->getMagnCharge() * otherParticle->getMagnCharge());
	if (norm > p->getRadius() + otherParticle->getRadius() && p->getInvMass() > 0)
		p->addForce(glm::normalize(d)*coeff/(norm*norm));
}