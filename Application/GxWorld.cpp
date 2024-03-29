#include "stdafx.h"
#include <iostream>
#include "GxWorld.h"

GxWorld::GxWorld()
{
	std::cout << "Starting GLUT Graphics engine." << std::endl;
}

GxWorld::~GxWorld()
{

}

void GxWorld::addParticle(GxParticle* p)
{
	particles.push_back(p);
}

std::list<GxParticle*> GxWorld::getParticles()
{
	return particles;
}

void GxWorld::setParticles(std::list<GxParticle*> particles)
{
	this->particles = particles;
}

void GxWorld::clear()
{
	for each (GxParticle* p in particles)
	{
		delete p;
	}
	particles.clear();
}
