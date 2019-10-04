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
	
	float sprElong = 1.0f;
	float k = 25.0f;
	glm::vec3 spring = p->getPos() - otherParticle->getPos();
	float sLen = glm::length(spring);
	float displacement = sLen - sprElong;
	glm::vec3 springNorm = glm::normalize(spring);
	
	if (p->getInvMass() > 0)
		p->addForce(- springNorm * displacement * k);
	if (otherParticle->getInvMass() > 0)
		otherParticle->addForce(springNorm * displacement * k);
		

	//Damping
	float kd = 15.0f;
	glm::vec3 deltaVel = otherParticle->getVel() - p->getVel();
	float damp = glm::dot(springNorm, deltaVel) * kd;
	glm::vec3 dampForce = springNorm * damp;

	if (p->getInvMass() > 0)
		p->addForce(dampForce);
	if (otherParticle->getInvMass() > 0)
		otherParticle->addForce(-dampForce);
	
	/*
	Old force computing
	glm::vec3 d = p->getPos() - otherParticle->getPos();
	float coeff = -(glm::abs(glm::length(d)-0.5f)) * 10.0f;
	p->addForce(glm::normalize(d)*coeff);
	otherParticle->addForce(glm::normalize(d)*(-coeff));
		
	//Damping
	if (glm::abs(glm::length(d)-0.5f)>0.05)
		p->addForce(-0.5f*(d));
		*/
}
