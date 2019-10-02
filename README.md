# Physics-Engine
This is a school project which aim was to create a physics engine manipulating particles, and applying various forces to them. It also features a rendering part.

# Running the engine
You can run the engine by going to the Release Directory and launching Application.exe.

# Instructions
When lauching the executable file, you will see a scene open.
You can interact with the engine in various ways, the first being changing scenes. 
For every scene, you can activate/deactivate some behaviors with the following keys :
- g : enables/disables gravity
- c : enables/disables collisions
- f : spawns additional particles in the scene
- space : pauses/resumes the simulation
- q : quits the program

Each scene shows a unique display of forces. To change/reset a scene, press these keys on the numPad:
- 1 : Launch scene, simply spawns particles with random velocities
- 0 : Spawns particles submitted to a drag force
- 2 : Spawns particles linked by springs, featuring spring force
- 3 : Spawns particles submitted to magnetism
- 4 : Spawns particles in a cube. Demonstrates collisions.
- 5 : Spawns particles above two intersecting planes. Demonstrates collisions.
- 6 : Spawns particles with a random seed in a cube. You can activate or deactivation the integration of forces with ticks by pressing i. If enabled, the simulation becomes deterministic, and the particles will always behave the same way.
- 7 : Spawns particles with gravitational forces, modelising a sun and a planet. 
- 8 : Spawns random particles with gravitational forces
- 9 : Spawns a particle aimed with an initial velocity at a bigger one. Scene used for a basic destruction of particles. At this time, destruction and fracture into multiple particles is not functional.