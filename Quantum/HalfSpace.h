#pragma once
#include <glm\glm.hpp>
#include "Body.h"

namespace Quantum {

	class HalfSpace : public Body
	{
	public:
		HalfSpace();
		HalfSpace(glm::vec3 norm, float offs);
		~HalfSpace();
		glm::vec3 getNormal();
		glm::vec3 getPos();
		float getOffset();
		float getInvMass();
		float getRadius();
		glm::vec3 getVel();
		void setPos(glm::vec3 p);
		void setVelocity(glm::vec3 v);
	private:
		glm::vec3 normal;
		float offset;
	};


}
