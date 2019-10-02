#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <vector>
#include "QmParticle.h"
#include "HalfSpace.h"
#include "ForceRegistry.h"
#include "Contact.h"


namespace Quantum {

	class QmWorld {
	public:
		QmWorld();
		~QmWorld();
		void integrate(float);
		void addParticle(Body*);
		void addHalfSpace(HalfSpace*);
		void addForceRegistry(ForceRegistry* fg);
		std::vector<QmParticle*> getParticles();
		std::vector<HalfSpace*> getHalfSpaces();
		std::vector<Body*> getBodies();
		std::vector<ForceRegistry*> getForces();
		bool getGravity();
		void update(float dt);
		float tick();
		void integrateTick(float dt);
		void applyGravity();
		void destroy(QmParticle* p, int index);
		void updateForces();
		void toggleGravity();
		void toggleCollisions();
		std::vector<Contact*> broadPhase();
		std::vector<Contact*> narrowPhase(std::vector<Contact*> contacts);
		void resolve(std::vector<Contact*> contacts);
		void clear();
		float time = 0.0f;
		float ticktime = 0.0f;
		float delta = 0.016f;
	private:
		bool gravity;
		bool collisions;
		//float time;
		float tick(float t);
		std::vector<QmParticle*> particles;
		std::vector<Body*> bodies;
		std::vector<HalfSpace*> halfSpaces;
		std::vector<ForceRegistry*> forceRegistries;

	};

}

#endif