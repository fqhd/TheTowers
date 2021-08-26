# The Towers
---

![Markdown Logo](https://i.imgur.com/lDl7Pab.png)
![Markdown Logo](https://img.shields.io/badge/build-stable-brightgreen)
![Markdown Logo](https://img.shields.io/badge/version-1.1.0-blue)

## Build Instructions
---
### Dependencies
- sfml
- epoxy
- clang
- pkg-config
- ninja
---
### Mac OS X
1. `brew install clang sfml libepoxy pkg-config ninja` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. Add -framework OpenGL to the lflags in build.ninja
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under ./client
- The server binary file should be under ./server
---
### Linux

#### Arch
1. `sudo pacman -S clang sfml libepoxy pkg-config ninja` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under ./client
- The server binary file should be under ./server

#### Debian
1. `sudo apt install clang libsfml-dev libepoxy-dev pkg-config ninja-build` (This will install the dependencies)
1. Clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. CD into the project and run `ninja` , this will build the project
- The client binary file should be under ./client
- The server binary file should be under ./server

---
### Windows
- Create a new project linking the lib files for all the listed dependencies. Make sure all the header files are in a deps folder. Deps folder needs to be structured like this:
  - deps:
    - GL/
    - SFML/
- After that, you should be able to build and run the project without any difficulties
---
## In Progress
- Add clouds underneath the world to mkae it look like the map is floating
- Use hashmap for clients on server code
- Chat
- Packet Authentification
- Server client-instruction processing
- Add server `loadWorldFromFile()` function
- Server `saveWorldToFile()` function
- Add proper settings menu to pause menu
- Add player inventory state
- Fix particle handler
- Add instanced block models rendering(for block drops)
- Improve random clientID
