// Physics-engine.cpp : définit le point d'entrée pour l'application console.


#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <ctime>
#include <string>
#include <vector>

#include "Quantum.h"
#include "GxWorld.h"
#include "GxParticle.h"
#include "MyGxUpdater.h"

using namespace std;
using namespace Quantum;


GxWorld gxWorld;
QmWorld pxWorld;

glm::vec3* mousePointer;

int scene = 0;

// ********************** GLUT 
// Variables globales

int SCREEN_X = 800;
int SCREEN_Y = 800;
int VIEWPORT_X = 5; int VIEWPORT_Y = 5; int VIEWPORT_Z = 200;

GLuint DrawListSphere;

int buttons = 0;
float camRotate = 90.f;
float camDist = 30.f;
float camHeight = 0.f;
float mx = 0.f;
float my = 0.f;
int seedSize = 25;

// Variables du calcul de framerate 
int timeold = 0;
int frame = 0;
float accTime = 0.0;
float timebase = 0;
float timeBaseFrame = 0;
float timeFrame = 0;
bool paused = false;
bool independant = false;

GLfloat light_pos[] = { 0.0, 6.0, 1.0, 1.0 };
vector<glm::vec3> seedVel;
vector<glm::vec3> seedPos;
vector<glm::vec3> seedCol;
vector<float> seedRadius;


// ********************************************

glm::vec3 randomColor()
{
	float red = (rand() % 100) / 100.f;
	float green = (rand() % 100) / 100.f;
	float blue = (rand() % 100) / 100.f;
	return glm::vec3(red, green, blue);

}

glm::vec3 randomVector(float min, float max)
{
	float x = min + (max - min)*((rand() % 100) / 100.f);
	float y = min + (max - min)*((rand() % 100) / 100.f);
	float z = min + (max - min)*((rand() % 100) / 100.f);
	return glm::vec3(x, y, z);

}

void createSeeds(){
	for (int i = 0; i < seedSize; i++){
		float radius = 0.1f + 0.2f*((rand() % 100) / 100.f);
		seedVel.push_back(randomVector(-1, 1));
		seedCol.push_back(randomColor());
		seedPos.push_back(randomVector(-1, 1));
		seedRadius.push_back(radius);
	}
}

void createParticlesWithSeed()
{
	for (int i = 0; i < seedSize; i++){
		GxParticle* g = new GxParticle(seedCol[i], seedRadius[i]);
		QmParticle* p = new QmParticle(glm::vec3(0), seedVel[i], seedPos[i], seedRadius[i]);
		p->gxUpdater = new MyGxUpdater(g);
		gxWorld.addParticle(g);
		pxWorld.addParticle(p);
	}
}

void createParticle()
{
	float radius = 0.1f + 0.2f*((rand() % 100) / 100.f);
	GxParticle* g = new GxParticle(randomColor(), radius);
	QmParticle* p = new QmParticle(randomVector(-1, 1), randomVector(-1, 1), randomVector(-1, 1), radius);
	p->gxUpdater = new MyGxUpdater(g);
	gxWorld.addParticle(g);
	pxWorld.addParticle(p);
}

void createParticleVoidRand()
{
	float radius = 2.0f*(0.1f + 0.2f*((rand() % 100) / 100.f));
	GxParticle* g = new GxParticle(randomColor(), radius);
	QmParticle* p = new QmParticle(randomVector(-1, 1), randomVector(-3, 3), randomVector(-4, 4), radius, static_cast <float> (rand()) / static_cast <float> (RAND_MAX), radius/3.0f);
	p->gxUpdater = new MyGxUpdater(g);
	gxWorld.addParticle(g);
	pxWorld.addParticle(p);
}

void createParticleDrag()
{
	float radius = 0.1f + 0.2f*((rand() % 100) / 100.f);
	GxParticle* g = new GxParticle(randomColor(), radius);
	QmParticle* p = new QmParticle(randomVector(-1, 1), randomVector(-1, 1), randomVector(-1, 1), radius);
	p->gxUpdater = new MyGxUpdater(g);
	gxWorld.addParticle(g);
	pxWorld.addParticle(p);
	pxWorld.addForceRegistry(new ForceRegistry(p, new Drag()));
	
}

void createParticle2()
{
	float radius = 0.1f + 0.2f*((rand() % 100) / 100.f);
	GxParticle* g = new GxParticle(randomColor(), radius);
	QmParticle* p = new QmParticle(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), randomVector(-1, 1), radius);
	p->gxUpdater = new MyGxUpdater(g);
	gxWorld.addParticle(g);
	pxWorld.addParticle(p);
}

void createParticle3()
{
	
	for (int i = 0; i < 2; i++){
		float radius = 0.1f + 0.2f*((rand() % 100) / 100.f);
		GxParticle* g = new GxParticle(glm::vec3(1.0f, 0, 0), radius);
		QmParticle* p = new QmParticle(glm::vec3(0), glm::vec3(0), randomVector(-3, 3), radius, 1.5f * static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
		p->gxUpdater = new MyGxUpdater(g);
		gxWorld.addParticle(g);
		pxWorld.addParticle(p);
	}
	float radius = 0.1f + 0.2f*((rand() % 100) / 100.f);
	GxParticle* g = new GxParticle(glm::vec3(0, 0, 1.0f), radius);
	QmParticle* p = new QmParticle(glm::vec3(0), glm::vec3(0), randomVector(-3, 3), radius, -(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
	p->gxUpdater = new MyGxUpdater(g);
	gxWorld.addParticle(g);
	pxWorld.addParticle(p);
}

void createParticleVoid()
{
	float radius = 2.0f;
	GxParticle* g = new GxParticle(glm::vec3(1, 1, 0), radius);
	QmParticle* p = new QmParticle(glm::vec3(0), glm::vec3(0), glm::vec3(0), radius, static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 0.001f);//7.4912018 * pow(10, -23));
	p->gxUpdater = new MyGxUpdater(g);
	gxWorld.addParticle(g);
	pxWorld.addParticle(p);

	float radius2 = 0.5f;
	GxParticle* g2 = new GxParticle(glm::vec3(0.1843137254901961, 0.5490196078431373, 0.9058823529411765), radius2);
	QmParticle* p2 = new QmParticle(glm::vec3(0), glm::vec3(0,11.0f,0), glm::vec3(8.0f, 0, 0), radius2, static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 0.08f);//2.4916388 * pow(10, -14));
	p2->gxUpdater = new MyGxUpdater(g2);
	gxWorld.addParticle(g2);
	pxWorld.addParticle(p2);

	float radius3 = 0.1f;
	GxParticle* g3 = new GxParticle(glm::vec3(0.5, 0.5, 0.5), radius3);
	QmParticle* p3 = new QmParticle(glm::vec3(0), glm::vec3(0, 11.0f, 0), glm::vec3(8.5f, 0, 0), radius3, static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 0.8f);//2.4916388 * pow(10, -14));
	p3->gxUpdater = new MyGxUpdater(g3);
	gxWorld.addParticle(g3);
	pxWorld.addParticle(p3);
}

void createParticleDestruction()
{
	float radius = 2.001f;
	GxParticle* g = new GxParticle(glm::vec3(1, 0, 0.125f), radius);
	QmParticle* p = new QmParticle(glm::vec3(0), glm::vec3(0), glm::vec3(0, 0, -15.0f), glm::vec3(1, 0, 0.125f), radius, static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 0.08f);//7.4912018 * pow(10, -23));
	p->gxUpdater = new MyGxUpdater(g);
	gxWorld.addParticle(g);
	pxWorld.addParticle(p);

	float radius2 = 0.30f;
	GxParticle* g2 = new GxParticle(glm::vec3(0.1843137254901961, 0.5490196078431373, 0.9058823529411765), radius2);
	QmParticle* p2 = new QmParticle(glm::vec3(0), glm::vec3(0, 0, -15.0f), glm::vec3(0, 0, 10.0f), glm::vec3(0.1843137254901961, 0.5490196078431373, 0.9058823529411765), radius2, static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 0.02f);//2.4916388 * pow(10, -14));
	p2->gxUpdater = new MyGxUpdater(g2);
	gxWorld.addParticle(g2);
	pxWorld.addParticle(p2);

}


void createHalfSpaces(){
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(1, 0, 0),  3.0f)); //face droite
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(-1, 0, 0), 3.0f)); //face gauche
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(0, 1, 0), 3.0f)); //face haut
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(0, -1, 0), 3.0f)); //face bas
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(0, 0, 1), 3.0f)); //face devant
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(0, 0, -1), 3.0f)); //face profonde
}

void createHalfSpaces2(){
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(-1, -1, 0), 3.0f)); //face droite
	pxWorld.addHalfSpace(new HalfSpace(glm::vec3(1, -1, 0), 3.0f)); //face gauche
}

void initScene0()
{
	printf("Scene 0: Scene with drag.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	for (int i = 0; i < 100; i++)
		createParticleDrag();
}

void initScene1()
{
	printf("Scene 1: Random particles.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	for (int i = 0; i < 100; i++)
		createParticle();
}

void initScene2()
{
	printf("Scene 2.\n");
	printf("Scene with Springs.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	for (int i = 0; i < 10; i++){
			createParticle2();
	}
		
	std::vector<QmParticle*> particleSpring;
	for each (QmParticle* p in pxWorld.getBodies()){
		particleSpring.push_back(p);
	}
	particleSpring[0]->setInvMass(-1.0f);
	for (int i = 0; i < 9; i++){
		pxWorld.addForceRegistry(new ForceRegistry(particleSpring[i], new Spring(particleSpring[i + 1])));
	}
	for (int i = 9; i > 0; i--){
		pxWorld.addForceRegistry(new ForceRegistry(particleSpring[i], new Spring(particleSpring[i -1])));
	}

	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[3], new Spring(particleSpring[1])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[1], new Spring(particleSpring[3])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[4], new Spring(particleSpring[1])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[1], new Spring(particleSpring[4])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[4], new Spring(particleSpring[2])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[2], new Spring(particleSpring[4])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[2], new Spring(particleSpring[5])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[5], new Spring(particleSpring[2])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[3], new Spring(particleSpring[5])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[5], new Spring(particleSpring[3])));


	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[6], new Spring(particleSpring[9])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[9], new Spring(particleSpring[6])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[7], new Spring(particleSpring[9])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[9], new Spring(particleSpring[7])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[6], new Spring(particleSpring[8])));
	pxWorld.addForceRegistry(new ForceRegistry(particleSpring[8], new Spring(particleSpring[6])));
}

void initScene3()
{
	printf("Scene 3: Magnetism.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	if (pxWorld.getGravity())
		pxWorld.toggleGravity();
	for (int i = 0; i < 10; i++)
		createParticle3();


	std::vector<QmParticle*> particlesMagn;
	for each (QmParticle* p in pxWorld.getBodies()){
		particlesMagn.push_back(p);
	}
	for (int j = 0; j < particlesMagn.size(); j++){
		for (int m = 0; m < particlesMagn.size(); m++){
			if (m != j)
				pxWorld.addForceRegistry(new ForceRegistry(particlesMagn[j], new Magnetism(particlesMagn[m])));
		}
	}
}

void initScene4()
{
	printf("Scene 4 : cube with collisions.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	for (int i = 0; i < 30; i++)
		createParticle();
	createHalfSpaces();
}

void initScene5()
{
	printf("Scene 5: spaces.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	for (int i = 0; i < 30; i++)
		createParticle();
	createHalfSpaces2();
}

void initScene6()
{
	printf("Scene 6: cube with seed.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	createParticlesWithSeed();
	createHalfSpaces();
}

void initScene7()
{
	printf("Scene 7: Attractions in void.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	if (pxWorld.getGravity())
		pxWorld.toggleGravity();

	createParticleVoid();


	std::vector<QmParticle*> particlesVoid;
	for each (QmParticle* p in pxWorld.getBodies()){
		particlesVoid.push_back(p);
	}
	for (int j = 0; j < particlesVoid.size(); j++){
		for (int m = 0; m < particlesVoid.size(); m++){
			if (m != j)
				pxWorld.addForceRegistry(new ForceRegistry(particlesVoid[j], new GravityVoid(particlesVoid[m])));
		}
	}
}

void initScene8()
{
	printf("Scene 8: Attractions in void with random particles.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	if (pxWorld.getGravity())
		pxWorld.toggleGravity();

	for (int i = 0; i < 30; i++)
		createParticleVoidRand();


	std::vector<QmParticle*> particlesVoid;
	for each (QmParticle* p in pxWorld.getBodies()){
		particlesVoid.push_back(p);
	}
	for (int j = 0; j < particlesVoid.size(); j++){
		for (int m = 0; m < particlesVoid.size(); m++){
			if (m != j)
				pxWorld.addForceRegistry(new ForceRegistry(particlesVoid[j], new GravityVoid(particlesVoid[m])));
		}
	}
}

void initScene9()
{
	printf("Scene 9: Destruction.\n");
	printf("Type space to pause.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	if (pxWorld.getGravity())
		pxWorld.toggleGravity();

	createParticleDestruction();


}

// ***************************** GLUT methods

void resetView()
{
	camRotate = 90.f;
	camDist = 30.f;
	camHeight = 0.f;
	mx = 0.f;
	my = 0.f;
	if (mousePointer) {
		delete mousePointer;
		mousePointer = NULL;
	}
}

void createDisplayListSphere()
{
	DrawListSphere = glGenLists(1);
	glNewList(DrawListSphere, GL_COMPILE);
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, 1, 12, 8);
	glEndList();
}

void initLight()
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	GLfloat ambient_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuse_light[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
}

void calculateFPS(float dt)
{
	accTime += dt;

	if (accTime > 0.5)
	{
		char t[200];
		sprintf_s(t, "Quantum Physics Engine: Scene %d, %.2f FPS", scene, frame / accTime);
		glutSetWindowTitle(t);
		accTime = 0.0;
		frame = 0;
	}
}

void idleFunc()
{
	glutPostRedisplay();
}




/*************************************************************************/




void drawFunc()
{

	int timer = glutGet(GLUT_ELAPSED_TIME);
	timeFrame = glutGet(GLUT_ELAPSED_TIME);
	float dt = (float)(timer - timeold) / 1000.f;
	timeold = timer;

	calculateFPS(dt);
	if (!paused) {
		if (!independant)
			pxWorld.integrate(dt);
		else
			pxWorld.integrateTick(dt);
	}
	

	//******* DESTRUCTION REBUILD OF GX PARTICLES **********//

	//TODO CORRECT THIS THING ...

	if (pxWorld.getBodies().size() != gxWorld.getParticles().size()){

		gxWorld.clear();
		for each(QmParticle* p in pxWorld.getBodies()){
			//delete p->gxUpdater->getGxObj();
			float rad = p->getRadius();
			glm::vec3 col = p->getColor();
			printf("%f \n", rad);	
			GxParticle* g = new GxParticle(col, rad);
			if (p->isDestructible()){
				p->gxUpdater = new MyGxUpdater(g);
				gxWorld.addParticle(g);
			}
			else{
				//delete p->gxUpdater->getGxObj();
				delete p->gxUpdater;
				gxWorld.addParticle(g);
			}
		}
		//system("pause");
	}

	//******************************************************//

	timeBaseFrame = timeFrame;
	frame++;
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camDist * cos(camRotate), camHeight, camDist * sin(camRotate), 0, camHeight, 0, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	for each (GxParticle* p in gxWorld.getParticles())
	{
		glPushMatrix();
		glm::vec3 color = p->getColor();
		glColor3f(color.x, color.y, color.z);
		glTranslatef(p->getPos().x, p->getPos().y, p->getPos().z);
		glScaled(p->getRadius(), p->getRadius(), p->getRadius());
		glCallList(DrawListSphere);
		glPopMatrix();
	}
	if (mousePointer) {
		glPushMatrix();
		glColor3f(1.f, 1.f, 1.f);
		glTranslatef(mousePointer->x, mousePointer->y, mousePointer->z);
		glScaled(0.1f, 0.1f, 0.1f);
		glCallList(DrawListSphere);
		glPopMatrix();
	}
	if (scene == 2){
		glm::vec3 s1;
		glm::vec3 s2;
		std::vector<GxParticle*> vecTest;
		for each (GxParticle* p in gxWorld.getParticles())
		{
			vecTest.push_back(p);
		}
		for (int i = 0; i < vecTest.size() - 1; i++){
			s1 = vecTest[i]->getPos();
			s2 = vecTest[i+1]->getPos();
			glBegin(GL_LINES);
				glVertex3f(s1.x, s1.y, s1.z);
				glVertex3f(s2.x, s2.y, s2.z);
			glEnd();
		}
		glBegin(GL_LINES);
			glVertex3f(vecTest[1]->getPos().x, vecTest[1]->getPos().y, vecTest[1]->getPos().z);
			glVertex3f(vecTest[3]->getPos().x, vecTest[3]->getPos().y, vecTest[3]->getPos().z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(vecTest[1]->getPos().x, vecTest[1]->getPos().y, vecTest[1]->getPos().z);
			glVertex3f(vecTest[4]->getPos().x, vecTest[4]->getPos().y, vecTest[4]->getPos().z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(vecTest[2]->getPos().x, vecTest[2]->getPos().y, vecTest[2]->getPos().z);
			glVertex3f(vecTest[4]->getPos().x, vecTest[4]->getPos().y, vecTest[4]->getPos().z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(vecTest[2]->getPos().x, vecTest[2]->getPos().y, vecTest[2]->getPos().z);
			glVertex3f(vecTest[5]->getPos().x, vecTest[5]->getPos().y, vecTest[5]->getPos().z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(vecTest[3]->getPos().x, vecTest[3]->getPos().y, vecTest[3]->getPos().z);
			glVertex3f(vecTest[5]->getPos().x, vecTest[5]->getPos().y, vecTest[5]->getPos().z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(vecTest[6]->getPos().x, vecTest[6]->getPos().y, vecTest[6]->getPos().z);
			glVertex3f(vecTest[9]->getPos().x, vecTest[9]->getPos().y, vecTest[9]->getPos().z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(vecTest[6]->getPos().x, vecTest[6]->getPos().y, vecTest[6]->getPos().z);
			glVertex3f(vecTest[8]->getPos().x, vecTest[8]->getPos().y, vecTest[8]->getPos().z);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(vecTest[7]->getPos().x, vecTest[7]->getPos().y, vecTest[7]->getPos().z);
			glVertex3f(vecTest[9]->getPos().x, vecTest[9]->getPos().y, vecTest[9]->getPos().z);
		glEnd();

	}

	if (scene == 4 || scene==6){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		//glColor3f(0.5, 0.5, 0.0);
		glVertex3f(-3.0, 3.0, 3.0);
		glVertex3f(3.0, 3.0, 3.0);
		glVertex3f(3.0, -3.0, 3.0);
		glVertex3f(-3.0, -3.0, 3.0);
		glEnd();

		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		//glColor3f(1.0, 0.0, 0.0);
		glVertex3f(3.0, 3.0, 3.0);
		glVertex3f(3.0, 3.0, -3.0);
		glVertex3f(3.0, -3.0, -3.0);
		glVertex3f(3.0, -3.0, 3.0);
		glEnd();

		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, -1.0);
		//glColor3f(0.0, 1.0, 0.0);
		glVertex3f(3.0, 3.0, -3.0);
		glVertex3f(3.0, -3.0, -3.0);
		glVertex3f(-3.0, -3.0, -3.0);
		glVertex3f(-3.0, 3.0, -3.0);
		glEnd();

		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		//glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-3.0, 3.0, -3.0);
		glVertex3f(-3.0, 3.0, 3.0);
		glVertex3f(-3.0, -3.0, 3.0);
		glVertex3f(-3.0, -3.0, -3.0);
		glEnd();

		glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		//glColor3f(0.0, 0.5, 0.5);
		glVertex3f(-3.0, 3.0, -3.0);
		glVertex3f(3.0, 3.0, -3.0);
		glVertex3f(3.0, 3.0, 3.0);
		glVertex3f(-3.0, 3.0, 3.0);
		glEnd();

		glBegin(GL_QUADS);
		glNormal3f(0.0, -1.0, 0.0);
		//glColor3f(0.5, 0.0, 0.5);
		glVertex3f(-3.0, -3.0, -3.0);
		glVertex3f(3.0, -3.0, -3.0);
		glVertex3f(3.0, -3.0, 3.0);
		glVertex3f(-3.0, -3.0, 3.0);
		glEnd();
	}

	if (scene == 5){
		

		
	}
	glutSwapBuffers();
}


void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) buttons = 1;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) buttons = 2;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) buttons = 3;
	if (button == 3) camDist /= 1.07f;
	if (button == 4) camDist *= 1.07f;
	if (state == GLUT_UP) buttons = 0;

	mx = (float)x;
	my = (float)y;
}

void motionFunc(int x, int y)
{
	if (buttons == 1)
	{
		camRotate += (x - mx) / 100.f;
		camHeight += (y - my) * camDist / 1000.f;
	}
	if (buttons == 3)
	{
		if (mousePointer)
		*mousePointer += glm::vec3(x - mx, my - y, 0.f) / 15.f;
	}

	mx = (float)x;
	my = (float)y;
}

void clearWorld()
{
	gxWorld.clear();
	pxWorld.clear();

}

void toggleScene(int s)
{
	clearWorld();
	scene = s;
	resetView();

	switch (scene)
	{
	case 0: initScene0(); break;
	case 1: initScene1(); break;
	case 2: initScene2(); break;
	case 3: initScene3(); break;
	case 4: initScene4(); break;
	case 5: initScene5(); break;
	case 6: initScene6(); break;
	case 7: initScene7(); break;
	case 8: initScene8(); break;
	case 9: initScene9(); break;
	}
}


void keyFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': case 'Q': case 27:
		clearWorld();
		glDeleteLists(DrawListSphere, 1);
		exit(0);
		break;
	case '0':
		toggleScene(0);
		break;
	case '1':
		toggleScene(1);
		break;
	case '2':
		toggleScene(2);
		break;
	case '3':
		toggleScene(3);
		break;
	case '4':
		toggleScene(4);
		break;
	case '5':
		toggleScene(5);
		break;
	case '6':
		toggleScene(6);
		break;
	case '7':
		toggleScene(7);
		break;
	case '8':
		toggleScene(8);
		break;
	case '9':
		toggleScene(9);
		break;
	case 'g':
		pxWorld.toggleGravity();
		break;
	case 'c':
		pxWorld.toggleCollisions();
		break;
	case 'i':
		independant = !independant;
		break;
	case 'f':
		if (scene == 0)
			createParticleDrag();
		if (scene==1)
			createParticle();
		if (scene==2)
			createParticle2();
		if (scene == 3){
			createParticle3();
			pxWorld.getForces().clear();
			initScene3();
		}
		if (scene == 4){
			createParticle();
		}
		if (scene == 7 || scene ==8){
			createParticleVoidRand();
			pxWorld.getForces().clear();
			initScene8();
		}
		break;
	case ' ': 
		paused = !paused; 
		break;
	default:
		break;
	}
}

void initGraphics(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow("Quantum Demo");

	glutIdleFunc(idleFunc);
	glutDisplayFunc(drawFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutKeyboardFunc(keyFunc);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_PROGRAM_POINT_SIZE);
	//glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = SCREEN_X / (float)SCREEN_Y;
	gluPerspective(45.0, aspect, 1.0, VIEWPORT_Z);
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	createDisplayListSphere();
	initLight();
}

// ************************** end GLUT methods

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	createSeeds();
	initGraphics(argc, argv);

	toggleScene(1);

	glutMainLoop();
	return 0;
}




