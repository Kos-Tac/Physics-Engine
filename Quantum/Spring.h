#pragma once
#include "ForceGenerator.h"

namespace Quantum {
	class Spring : public ForceGenerator
	{
	public:
		Spring();
		Spring(QmParticle* oP);
		~Spring();
		void update(QmParticle* p);
		QmParticle* otherParticle;
	};
}
