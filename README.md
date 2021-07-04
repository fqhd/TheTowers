# The Towers
---

![Markdown Logo](https://i.imgur.com/PHS68Jv.png)  
![Markdown Logo](https://i.imgur.com/O5hvb38.png)  
![Markdown Logo](https://img.shields.io/badge/build-stable-brightgreen)
![Markdown Logo](https://img.shields.io/badge/version-1.1.0-blue)

## Build Instructions
---
### Dependencies
- glfw
- sfml
- glew
- clang
- pkg-config
- ninja
---
### Mac OS X
1. `brew install clang sfml glfw glm glew pkg-config ninja` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. Add -framework OpenGL to the lflags in build.ninja
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under bin/Client/client
- The server binary file should be under bin/Server/server
---
### Linux

#### Arch
1. `sudo pacman -S clang sfml glfw glm glew pkg-config ninja` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under bin/Client/client
- The server binary file should be under bin/Server/server

#### Debian
1. `sudo apt install clang libsfml-dev libglfw-dev libglm-dev libglew-dev pkg-config ninja-build` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under bin/Client/client
- The server binary file should be under bin/Server/server

---
### Windows
- Create a new project linking the lib files for all the listed dependencies. Make sure all the header files are in a deps folder. deps folder needs to be structured like this:
  - deps:
    - GLFW
    - GLM
    - GL
    - SFML
- After that, you should be able to build and run the project without any difficulties
---
## In Progress
- Add server world class
- Server `sendWorldToClient(clientID)`
- Client `NetworkManager::downloadWorld()`
- Add world compression to server and world decompression function to network manager in client
- Remove fog and change cubemap to something more adecuate
- Add clouds underneath the world to mkae it look like the map is floating
- Add server `loadWorldFromFile()` function
- Add HUD and GUI to gameplay
- Add proper settings menu to pause menu
- Add player inventory state
- Fix particle handler
- Transition to make instead of ninja as the buildsystem
- Fix particle handler
- Add instanced block models rendering(for block drops)
- Server instruction processing on separate thread