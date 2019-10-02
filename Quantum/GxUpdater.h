#ifndef GXUPDATER_H
#define GXUPDATER_H

#include <glm/glm.hpp>

namespace Quantum {

	class GxUpdater {
	public:
		GxUpdater() {};
		~GxUpdater() {};
		virtual void setGxObject(void* gxObj){ gxObject = gxObj; };
		virtual void update(glm::vec3) = 0;
		virtual void* getGxObj(){ return gxObject; };

	protected:
		void* gxObject;
	};

}

#endif