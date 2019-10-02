#pragma once
#include "QmParticle.h"

namespace Quantum {
	class ForceGenerator
	{
	public:
		ForceGenerator(){};
		~ForceGenerator(){};
		virtual void update(QmParticle* p) = 0;
	};
}

