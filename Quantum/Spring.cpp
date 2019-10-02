#include "stdafx.h"
#include "Spring.h"

using namespace Quantum;


Spring::Spring()
{

}

Spring::~Spring()
{

}

Spring::Spring(QmParticle* oP)
{
	otherParticle = oP;
}

void Spring::update(QmParticle* p){
	if (p->getInvMass() != 0){
		glm::vec3 d = p->getPos() - otherParticle->getPos();
		float coeff = -(glm::length(d)-0.2) * 5;
		p->addForce(glm::normalize(d)*coeff);
		//Damping
		p->addForce(10.0f*(d/2.0f / glm::length(d)));
	}
}
