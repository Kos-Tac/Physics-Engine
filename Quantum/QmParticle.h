#ifndef PARTICLE_H
#define PARTICLE_H
#pragma once
#include <glm/glm.hpp>
#include "GxUpdater.h"
#include "Body.h"
#include "HalfSpace.h"

namespace Quantum {

	class QmParticle : public Body {
	public:
		QmParticle();
		QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos);
		QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, float rad);
		QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, float rad, float magnetism);
		QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, float rad, float magnetism, float invM);
		QmParticle(glm::vec3 acc, glm::vec3 vel, glm::vec3 pos, glm::vec3 col, float rad, float invM, bool toDestroy);
		~QmParticle();
		GxUpdater* gxUpdater;

		virtual void integrate(float);
		
		glm::vec3 getAcc();
		glm::vec3 getVel();
		glm::vec3 getPos();
		glm::vec3 getForceAccumulator();
		glm::vec3 getColor();
		float getInvMass();
		float getMagnCharge();
		float getRestitution();
		float getRadius();
		float getOffset();
		void setInvMass(float m);
		void setMagnCharge(float m);
		void setPos(glm::vec3 p);
		void setVelocity(glm::vec3 v);
		void resetVel();
		void resetAcc();
		bool checkContact(QmParticle* other);
		bool checkContactHalfSpace(HalfSpace* hF);
		glm::vec3 getNormal();
		void addForce(glm::vec3 f);
		void clear();
		bool isDestructible();

	private:
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 acceleration;
		glm::vec3 forceAccumulator;
		glm::vec3 color;
		float invMass;
		float magneticCharge;
		float restitution;
		float radius;
		float damping;
		bool destructible;
	};

}

#endif