#pragma once
#include "ForceGenerator.h"
namespace Quantum {

	class GravityVoid : public ForceGenerator
	{
	public:
		GravityVoid();
		GravityVoid(QmParticle* oP);
		~GravityVoid();
		void update(QmParticle* p);
		QmParticle* otherParticle;
	};
}

