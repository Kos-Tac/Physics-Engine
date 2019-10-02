#pragma once
#include "Body.h"
#include <glm\glm.hpp>
#include "QmParticle.h"


namespace Quantum {
	class Contact
	{
	public:
		Contact();
		Contact(Body* p1, Body* p2);
		~Contact();
		Body* body1;
		Body* body2;
		glm::vec3 point;
		glm::vec3 normal;
		float depth;
	};
}
