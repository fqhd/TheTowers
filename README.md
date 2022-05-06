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
- GCC
- python
---
### Instructions
1. Make sure you installed the latest version of python and GCC.
1. clone the repository `git clone https://github.com/fqhd/TheTowers.git`
1. cd into the project `cd TheTowers`
1. run `python create_build_files.py` to create the build.ninja build file. If that doesn't work, try `python3 create_build_files.py`
1. run `./buildsystem/x/ninja`. Make sure to replace the x with your current operating system. This can be either windows, macos or linux(All lowercase).
1. run `./client` to run the client
1. If you would like to host a server, run `./server`

---
## In Progress
- Add clouds underneath the world to mkae it look like the map is floating
- Chat
- Sever game loop
- Add player inventory state
- Add instanced block models rendering(for block drops)
