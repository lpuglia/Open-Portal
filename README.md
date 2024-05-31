## Open Portal

This is the "Open Portal Engine", A Portal-like game engine written in classic OpenGL interface.
Feel free to fork the repository to improve it.

See the video:

[![Preview](https://img.youtube.com/vi/tqqeUCzWcdQ/0.jpg)](http://www.youtube.com/watch?v=tqqeUCzWcdQ)


## Dependencies

* Opengl and glut should be installed manually on your system, it should be pretty straight forward using package manager of your OS;
* FreeImage is also easy to intall from package manager;
* CML library is a header-only library for math operation handling, it is a submodule of the repository, if CML folder is empty do:
```
    git submodule init
    git submodule update
```

## Build Instructions

Create the `build` directory and enter it:

```
mkdir build
cd build
```

from build directory call, `cmake` and `make`

```
cmake ..
make
```

it should be enough to create the executable
