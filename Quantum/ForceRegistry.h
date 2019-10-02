#pragma once
#include "ForceGenerator.h"
#include "QmParticle.h"

namespace Quantum{
	class ForceRegistry
	{
	public:
		ForceRegistry(QmParticle* qmP, ForceGenerator* forceGen);
		~ForceRegistry();
		QmParticle* p;
		ForceGenerator* fg;
	};
}


