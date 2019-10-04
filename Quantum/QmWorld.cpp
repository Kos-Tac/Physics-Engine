#include "stdafx.h"
#include <iostream>
#include "QmWorld.h"
#include <typeinfo>

using namespace Quantum;

QmWorld::QmWorld()
{
	std::cout << "Starting Quantum Physics engine." << std::endl;
	time = 0.f;
}

QmWorld::~QmWorld()
{

}




void QmWorld::integrate(float t)
{
	time += t;
	if (collisions){
		//std::vector<Contact*> contacts = broadPhase();

		resolve(narrowPhase(broadPhase()));
	}
	updateForces();
	for each (QmParticle* p in bodies)//in particles
	if (p->getInvMass() != -1.0f)
		p->integrate(t);
}

void QmWorld::updateForces(){

	for each (QmParticle* p in bodies){//in particles
		p->resetAcc();
	}
	if (gravity)
		applyGravity();

	for each (ForceRegistry* f in forceRegistries){
		f->fg->update(f->p);
	}
}

void QmWorld::applyGravity(){
	for each (QmParticle* p in bodies){//in particles
		if (p->getInvMass() != -1.0f){
			p->addForce(glm::vec3(0.0f, -9.81f * p->getInvMass(), 0.0f));
		}
	}
}

void QmWorld::destroy(QmParticle* p, int index){
	glm::vec3 pPos = p->getPos();
	float pRadius = p->getRadius();
	float pInvMass = p->getInvMass();
	if ((pRadius / 2.0f) <= 0.25f){
		QmParticle* p1 = new QmParticle(glm::vec3(0), glm::vec3(0), pPos - glm::vec3(pRadius / 2, 0, 0), glm::vec3(1, 0, 0.125f), pRadius / 2, pInvMass / 2, false);
		QmParticle* p2 = new QmParticle(glm::vec3(0), glm::vec3(0), pPos + glm::vec3(pRadius / 2, 0, 0), glm::vec3(1, 0, 0.125f), pRadius / 2, pInvMass / 2, false);
		bodies.push_back(p1);
		bodies.push_back(p2);
	}
	else{
		QmParticle* p1 = new QmParticle(glm::vec3(0), glm::vec3(0), pPos - glm::vec3(pRadius / 2, 0, 0), glm::vec3(1, 0, 0.125f), pRadius / 2, pInvMass / 2, true);
		QmParticle* p2 = new QmParticle(glm::vec3(0), glm::vec3(0), pPos + glm::vec3(pRadius / 2, 0, 0), glm::vec3(1, 0, 0.125f), pRadius / 2, pInvMass / 2, true);
		bodies.push_back(p1);
		bodies.push_back(p2);
	}
	//delete p->gxUpdater->getGxObj();
	
	/*delete p->gxUpdater;
	bodies.erase(bodies.begin() + index);
	delete p;*/
	
}


void QmWorld::addParticle(Body* p)
{
	//particles.push_back(p);
	bodies.push_back(p);
}

void QmWorld::addHalfSpace(HalfSpace* h)
{
	//particles.push_back(p);
	halfSpaces.push_back(h);
}

void QmWorld::addForceRegistry(ForceRegistry* fg)
{
	forceRegistries.push_back(fg);
}



std::vector<QmParticle*> QmWorld::getParticles()
{
	return particles;
}

std::vector<Body*> QmWorld::getBodies()
{
	return bodies;
}

std::vector<HalfSpace*> QmWorld::getHalfSpaces()
{
	return halfSpaces;
}

std::vector<ForceRegistry*> QmWorld::getForces()
{
	return forceRegistries;
}

bool QmWorld::getGravity(){
	return gravity;
}

bool QmWorld::getCollisions(){
	return collisions;
}

void QmWorld::toggleGravity(){
	gravity = !gravity;
}

void QmWorld::toggleCollisions(){
	collisions = !collisions;
}

std::vector<Contact*> QmWorld::broadPhase(){
	std::vector<Contact*> contacts;
	std::vector<QmParticle*> tempParticles;
	for each(QmParticle* p in bodies){
		tempParticles.push_back(p);
	}
	for (int i = 0; i < tempParticles.size(); i++){
		for each(HalfSpace* h in halfSpaces){
			if (tempParticles[i]->checkContactHalfSpace(h)){
				contacts.push_back(new Contact(tempParticles[i], h));
				//printf("ok");
			}
		}
		for (int j = i + 1; j < tempParticles.size(); j++){
			if (tempParticles[i]->checkContact(tempParticles[j])){
				contacts.push_back(new Contact(tempParticles[i], tempParticles[j]));		
			}
		}		
	}
	tempParticles.clear();
	return contacts;
}

std::vector<Contact*> QmWorld::narrowPhase(std::vector<Contact*> contacts){
	for each (Contact* c in contacts){
		if (c->body2->getInvMass() != -1.0f){
			glm::vec3 pos1 = c->body1->getPos();
			glm::vec3 pos2 = c->body2->getPos();
			c->normal = glm::normalize(pos1 - pos2);
			c->depth = c->body1->getRadius() + c->body2->getRadius() - glm::distance(pos1, pos2);
			c->point = glm::vec3((pos1.x + pos2.x) / 2, (pos1.y + pos2.y) / 2, (pos1.z + pos2.z) / 2);
		}

		else{
			c->normal = c->body2->getNormal();
			c->depth = glm::dot(c->body1->getPos(), c->body2->getNormal()) - c->body2->getOffset() + c->body1->getRadius();
		}
	}
	return contacts;
}

void QmWorld::resolve(std::vector<Contact*> contacts){
	for each (Contact* c in contacts){
		if (c->body2->getInvMass() != -1.0f){
			c->body1->setPos(c->body1->getPos() + c->normal*((c->depth) / 2));
			c->body2->setPos(c->body2->getPos() + -c->normal*((c->depth) / 2));
			glm::vec3 vel1 = c->body1->getVel();
			glm::vec3 vel2 = c->body2->getVel();
			glm::vec3 norm = glm::normalize(-c->normal);
			glm::vec3 velNorm1 = norm * glm::dot(vel1, norm);
			glm::vec3 velNorm2 = -norm * glm::dot(vel2, -norm);
			glm::vec3 velUp1 = vel1 - velNorm1;
			glm::vec3 velUp2 = vel2 - velNorm2;
			float mass1 = 1 / c->body1->getInvMass();
			float mass2 = 1 / c->body2->getInvMass();
			c->body1->setVelocity(0.90f*((velNorm1 * (mass1 - mass2) + 2 * mass2*velNorm2) / (mass1 + mass2) + velUp1));
			c->body2->setVelocity(0.90f*((velNorm2 * (mass2 - mass1) + 2 * mass1*velNorm1) / (mass1 + mass2) + velUp2));
			//c->body1->setVelocity(glm::vec3(0.01));
			//c->body2->setVelocity(glm::vec3(0.01));
		}
		else{
			c->body1->setPos(c->body1->getPos() - c->normal*c->depth);
			glm::vec3 vel1 = c->body1->getVel();

			/*glm::vec3 norm = glm::normalize(c->normal);
			glm::vec3 velNorm1 = 0.80f * -norm * glm::dot(vel1, norm);
			glm::vec3 velUp1 = 0.80f * vel1 - velNorm1;
			c->body1->setVelocity(velNorm1);
			*/
			

			glm::vec3 newVel = 0.80f * glm::reflect(vel1, glm::normalize(c->normal));
			c->body1->setVelocity(newVel);
		}
	}

	std::vector<QmParticle*> toDestroy;
	for each (Contact* c in contacts){
		Body* b1 = c->body1;
		Body* b2 = c->body1;
		if (QmParticle* part1 = dynamic_cast<QmParticle*>(b1)) {
			if (part1->isDestructible()){
				if (!(std::find(toDestroy.begin(), toDestroy.end(), part1) != toDestroy.end())) {
					//TODO : Finish this...
				}
			}
		}
	}

	/*
	std::vector<QmParticle*> tempParticles;
	for each(QmParticle* p in bodies){
		tempParticles.push_back(p);
	}
	for (int i = 0; i < tempParticles.size(); i++){
		if (tempParticles[i]->isDestructible()){
			if (tempParticles[i]->isDestructible()){
				destroy(tempParticles[i], i);
				tempParticles.erase(tempParticles.begin() + i);
			}
			if (tempParticles[j]->isDestructible()){
				destroy(tempParticles[j], j);
				tempParticles.erase(tempParticles.begin() + j);
			}
		}
	}
	*/
	
}

void QmWorld::clear()
{

	for each (QmParticle* p in bodies)//in particles
	{
		delete p->gxUpdater;
		delete p;
	}
	for each (HalfSpace* h in halfSpaces)//in particles
	{
		delete h;
	}
	//particles.clear();
	bodies.clear();
	halfSpaces.clear();
	for each (ForceRegistry* fg in forceRegistries)
	{
		delete fg;
	}
	forceRegistries.clear();
}



/****************** ~~~~~ Integration with ticks  ~~~~~*********************/

float QmWorld::tick(){
	if (collisions)
		resolve(narrowPhase(broadPhase()));
	updateForces();
	for each (QmParticle* p in bodies)
	{
		p->integrate(delta);
	}
	ticktime += delta;
	return time - ticktime;
}

void QmWorld::update(float dt){
	for each (QmParticle* p in bodies)
	{
		p->gxUpdater->update(p->getPos() + dt * p->getVel());
	}
}

void QmWorld::integrateTick(float t){
	time += t;
	float dt = time - ticktime;
	while (dt >= delta){
		dt = tick();
	}
	update(dt);
}

/*****************************************************************/
