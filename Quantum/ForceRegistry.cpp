#include "stdafx.h"
#include "ForceRegistry.h"

using namespace Quantum;

ForceRegistry::ForceRegistry(QmParticle* qmP, ForceGenerator* forceGen)
{
	p = qmP;
	fg = forceGen;
}


ForceRegistry::~ForceRegistry()
{
}
