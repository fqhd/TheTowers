# The Towers
---

![Markdown Logo](https://i.imgur.com/Z93zZlr.png)
![Markdown Logo](https://i.imgur.com/o7fQ2NW.png)
![Markdown Logo](https://img.shields.io/badge/build-stable-brightgreen)
![Markdown Logo](https://img.shields.io/badge/version-1.1.0-blue)
![Markdown Logo](https://tokei.rs/b1/github/fqhd/TheTowers)

## Build Instructions
---
### Dependencies
- sfml
- glew
- glfw
- clang
- pkg-config
- ninja
---
### Mac OS X
1. Before you begin, make sure you have both homebrew, and the apple command line tools installed
1. `brew install sfml glew pkg-config ninja glfw` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. Add -framework OpenGL to the lflags in build.ninja
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under ./client
- The server binary file should be under ./server
---
### Linux

#### Arch
1. `sudo pacman -S clang sfml glew pkg-config glfw ninja` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under ./client
- The server binary file should be under ./server
#### Debian
1. `sudo apt install clang libsfml-dev libglfw3-dev libglew-dev pkg-config ninja-build` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under ./client
- The server binary file should be under ./server
---
### Windows
- Create a new project linking the lib files for all the listed dependencies. Make sure all the header files are in a deps folder. Deps folder needs to be structured like this:
  - deps:
    - GLFW/
    - GL/
    - SFML/
- After that, you should be able to build and run the project without any difficulties
---
## In Progress
- Add clouds underneath the world to mkae it look like the map is floating
- Chat
- Sever game loop
- Add proper settings menu to pause menu
- Add player inventory state
- Add instanced block models rendering(for block drops)
- Legacy Block outline
- Multithreaded Chunk Mesh Generation
