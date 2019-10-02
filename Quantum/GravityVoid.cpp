#include "stdafx.h"
#include "GravityVoid.h"
#include <math.h>

using namespace Quantum;

GravityVoid::GravityVoid()
{
}


GravityVoid::GravityVoid(QmParticle* oP)
{
	otherParticle = oP;
}

GravityVoid::~GravityVoid()
{
}


void GravityVoid::update(QmParticle* p){
	glm::vec3 d = p->getPos() - otherParticle->getPos();
	glm::vec3 p1 = p->getPos();
	glm::vec3 p2 = otherParticle->getPos();
	glm::vec3 direction = glm::normalize(p2 - p1);
	float distance = glm::distance(p1, p2) *glm::distance(p1, p2);
	glm::vec3 attraction = float((6.674 * 0.01*((1 / p->getInvMass()) * (1 / otherParticle->getInvMass()))) / distance) * direction;
	if (p->getInvMass() != 0.001f)
		p->addForce(attraction);
		
}