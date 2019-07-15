# Granular-Material-Simulation
A simulation environment in C++ and SFML, with the goal of implementing collision detection optimization through quadtrees and spatial hashing, as well as accurate dynamics

## Dependencies 
[SFML](https://www.sfml-dev.org/)- This is will need to be installed and can be installed with ```sudo apt-get install libsfml-dev ```

[Rapidjson](http://rapidjson.org/)- Header Json Writer and Parsing Library

[Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page)- Header Math Library

## Current Feature Set
- Ability to simulate particle collision and interaction using two force contact models (Soft Sphere DEM).
- Simulation Data storage in json format, particle positions, velocities, and accelerations per sub-frame are all stored.
- Configurable simulation settings, including ram flush periodicity as well as particle count and window resolution.
- Ability to trim data-sets outputted by the generator and render particles in real time
## Planned Feature Set
- Much more heightened configurability
- Collision Detection optimization through either quadtree or spatial hashing methods (configurable choice)
- Improved physics models, with options for several different contact modes as well as rendering options

## Dream Feature Set
(Only to be implemented if my attention is not drawn away to other projects and interests)
- User Interface and Monitoring for Data Generation, Data Analysis, and Simulation Playback
