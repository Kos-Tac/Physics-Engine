#pragma once
#include <glm\glm.hpp>
#include <string>

namespace Quantum {
	class Body
	{
	public:
		Body(){};
		~Body(){};
		virtual glm::vec3 getPos() = 0;
		virtual glm::vec3 getNormal() = 0;
		virtual float getOffset() = 0;
		virtual float getRadius() = 0;
		virtual glm::vec3 getVel() = 0;
		virtual float getInvMass() = 0;
		virtual void setPos(glm::vec3 p) = 0;
		virtual void setVelocity(glm::vec3 v) = 0;
	};
}
