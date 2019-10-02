#pragma once
#include "ForceGenerator.h"
namespace Quantum {

	class Magnetism : public ForceGenerator
	{
	public:
		Magnetism();
		Magnetism(QmParticle* oP);
		~Magnetism();
		void update(QmParticle* p);
		QmParticle* otherParticle;
	};

}
