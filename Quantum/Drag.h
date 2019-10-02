#pragma once
#include "ForceGenerator.h"

namespace Quantum {
	class Drag : public Quantum::ForceGenerator
	{
	public:
		Drag();
		~Drag();
		virtual void update(QmParticle* p);
	};
}
