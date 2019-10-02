#include "stdafx.h"
#include "HalfSpace.h"

using namespace Quantum;

HalfSpace::HalfSpace()
{
}

HalfSpace::HalfSpace(glm::vec3 norm, float offs) : HalfSpace(){
	normal = norm;
	offset = offs;
}


HalfSpace::~HalfSpace(){

}

glm::vec3 HalfSpace::getNormal(){
	return normal;
}

float HalfSpace::getOffset(){
	return offset;
}

float HalfSpace::getInvMass(){
	return -1.0f;
}

float HalfSpace::getRadius(){
	return 0;
}
glm::vec3 HalfSpace::getPos(){
	return glm::vec3(0);
}
glm::vec3 HalfSpace::getVel(){
	return glm::vec3(0);
}
void HalfSpace::setPos(glm::vec3 p){
	
}
void HalfSpace::setVelocity(glm::vec3 v){

}