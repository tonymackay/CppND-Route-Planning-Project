# Route Planning Project
This repo is a fork of the Udacity C++ Nanodegree route planning project with changes made to meet the project specification.

## Building this project on Ubuntu 18.04
In order to build this project, the following dependancies must be installed:

- CMake 3.11.3 or newer
- IO2D

### Installing Dependancies
This project requires a newer version of CMake than what's installed by APT. [Click here for installation instructions](https://graspingtech.com/upgrade-cmake/).

Once you have installed CMake, you install IO2D by running the commands:

```
sudo apt install libcairo2-dev libgraphicsmagick1-dev libpng-dev
git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
cd P0267_RefImpl
mkdir Debug && cd Debug
cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
cmake --build .
sudo make install 
```

## Building the Route Planning Project
The project is now ready to be built by running the commands:

```
git clone git@github.com:tonymackay/CppND-Route-Planning-Project.git --recurse-submodules
cd CppND-Route-Planning-Project
mkdir build && cd build
cmake ..
make
```

## Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing
The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```
