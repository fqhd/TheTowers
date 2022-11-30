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
- GLFW
- ASIO
- GLAD
- GLM
- STB
---
### Instructions
1. Make sure you installed a recent version of cmake.
1. Clone the repository `git clone --recursive https://github.com/fqhd/TheTowers.git`
1. Cd into the project `cd TheTowers`
1. Create build directory `mkdir build`
1. CD into build directory `cd build`
1. Create cmake cache `cmake ..`
1. Build the project `cmake --build .`
1. Run the client: `./client`
1. Optionally, if you'd like to host a server, run `./server`
---
## In Progress
- Add clouds underneath the world to mkae it look like the map is floating
- Chat
- Sever game loop
- Add player inventory state
- Add instanced block models rendering(for block drops)
