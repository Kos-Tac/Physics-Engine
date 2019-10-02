#include "stdafx.h"
#include "QmParticle.h"
#include "Spring.h"
#include "Drag.h"

using namespace Quantum;

QmParticle::QmParticle() : acceleration(0, 0, 0), velocity(0, 0, 0), position(0, 0, 0)
{
}

QmParticle::QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos) : QmParticle()
{
	acceleration = acc;
	velocity = vel;
	position = pos;
	invMass = 0.5f;
	damping = 1.f;
	destructible = false;
}

QmParticle::QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, float rad) : QmParticle()
{
	acceleration = acc;
	velocity = vel;
	position = pos;
	invMass = 0.5f;
	damping = 1.f;
	radius = rad;
	destructible = false;
}

QmParticle::QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, float rad, float magnetism) : QmParticle()
{
	acceleration = acc;
	velocity = vel;
	position = pos;
	invMass = 0.5f;
	damping = 1.f;
	radius = rad;
	magneticCharge = magnetism;
	destructible = false;
}

QmParticle::QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, float rad, float magnetism, float invM) : QmParticle()
{
	acceleration = acc;
	velocity = vel;
	position = pos;
	invMass = invM;
	damping = 1.f;
	radius = rad;
	magneticCharge = magnetism;
	destructible = false;
}

QmParticle::QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, glm::vec3 col, float rad, float invM, bool toDestroy) : QmParticle()
{
	acceleration = acc;
	velocity = vel;
	position = pos;
	invMass = invM;
	damping = 1.f;
	radius = rad;
	destructible = toDestroy;
	color = col;
}

QmParticle::~QmParticle()
{

}

void QmParticle::integrate(float t)
{
	//acceleration *= invMass;
	position = position + t*velocity; // + 1/2 * acceleration * t * t
	velocity = velocity*damping + t*acceleration; // (damping^t)

	if (gxUpdater != NULL)
		gxUpdater->update(position);
	//acceleration = glm::vec3(0);
}

void QmParticle::addForce(glm::vec3 f)
{
	acceleration += f;
}

bool QmParticle::checkContact(QmParticle* other){
	/*
	glm::vec3 delta = position - other->getPos();
	float distanceSqrt = delta.x*delta.x + delta.y*delta.y + delta.z*delta.z;
	distanceSqrt *= distanceSqrt;
	float rSqrt = radius - other->getRadius();
	rSqrt *= rSqrt;
	*/
	float distanceSqrt = glm::distance(position, other->getPos());
	float rSqrt = radius + other->getRadius();
	return (distanceSqrt < rSqrt);
}

bool QmParticle::checkContactHalfSpace(HalfSpace* hF){
	float dist = glm::dot(position, hF->getNormal()) - hF->getOffset() + radius;
	return (dist > 0);
}

glm::vec3 QmParticle::getAcc()
{
	return acceleration;
}

glm::vec3 QmParticle::getVel()
{
	return velocity;
}

glm::vec3 QmParticle::getPos()
{
	return position;
}

glm::vec3 QmParticle::getForceAccumulator()
{
	return forceAccumulator;
}

float QmParticle::getInvMass()
{
	return invMass;
}


void QmParticle::setInvMass(float m){
	invMass = m;
}

void QmParticle::setPos(glm::vec3 p){
	position = p;
}

void QmParticle::setVelocity(glm::vec3 v){
	velocity = v;
}


void QmParticle::resetVel(){
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}


void QmParticle::resetAcc(){
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	forceAccumulator = glm::vec3(0.0f, 0.0f, 0.0f);
}

float QmParticle::getMagnCharge(){
	return magneticCharge;
}

void QmParticle::setMagnCharge(float m){
	magneticCharge = m;
}

float QmParticle::getRestitution(){
	return restitution;
}

float QmParticle::getRadius(){
	return radius;
}

glm::vec3 QmParticle::getNormal(){
	return glm::vec3(0);
}

float QmParticle::getOffset(){
	return 0;
}

bool QmParticle::isDestructible(){
	return destructible;
}

glm::vec3 QmParticle::getColor(){
	return color;
}