# Build Instructions

## Dependencies
- glfw
- sfml
- glew
- clang
- pkg-config
- ninja

### Mac OS X
- Add -framework OpenGL to the lflags in build.ninja
- To install the depdencies type the following commands into a terminal:
  - brew install clang
  - brew install sfml
  - brew install glfw
  - brew install glm
  - brew install glew
  - brew install pkg-config
  - brew install ninja
- In a new terminal, cd into the Client directory(in the BuildBattle project) and run "ninja". Then run "./out" to run the project

### Linux
- Install the depdencies, then cd into the Client directory of the BuildBattle project and run "ninja". Then run "./out" to run the project

### Windows
- Create a new project linking the lib files for all the listed dependencies. Make sure all the header files are in a deps folder. deps folder needs to be structured like this:
  - deps:
    - GLFW/*glfw headers*
    - GLM/*glm headers*
    - GL/*glew headers*
    - SFML/*sfml headers*
- After that, you should be able to build and run the project without any difficulties
