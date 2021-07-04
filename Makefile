all: bin/Client/client bin/Server/server

INCLUDES = $$(pkg-config --cflags sfml-network) $$(pkg-config --cflags glew) $$(pkg-config --cflags glfw3)
LIBS = $$(pkg-config --libs sfml-network) $$(pkg-config --libs glew) $$(pkg-config --libs glfw3)

# Variables
CFLAGS = -c -std=c++17 -O0 ${INCLUDES} -fdiagnostics-color=always -g -m64 -Wall -Werror
LFLAGS = -pthread ${LIBS}
CXX = clang++

# Linking Targets
bin/Client/client: obj/Client/clientMain.o obj/Client/window.o obj/Client/inputmanager.o obj/Client/player.o obj/Client/chunk.o obj/Client/shader.o obj/Client/utils.o obj/Client/chunkshader.o obj/Client/game.o obj/Client/camera.o obj/Client/world.o obj/Client/cubemap.o obj/Client/cube.o obj/Client/cubemapshader.o obj/Client/cubemaptexture.o obj/Client/particlehandler.o obj/Client/particle.o obj/Client/particlequad.o obj/Client/particleshader.o obj/Client/pausemenu.o obj/Client/guifont.o obj/Client/guifontshader.o obj/Client/guihandler.o obj/Client/guirenderer.o obj/Client/guishader.o obj/Client/guibutton.o obj/Client/guiimage.o obj/Client/checkbox.o obj/Client/image.o obj/Client/transform.o obj/Client/model.o obj/Client/modelshader.o obj/Client/entityhandler.o obj/Client/entity.o obj/Client/objloader.o obj/Client/frustum.o obj/Client/blockoutlineshader.o obj/Client/blockoutline.o obj/Client/outlinerenderer.o obj/Client/guitextmesh.o obj/Client/textureArray.o obj/Client/program.o obj/Client/network.o
	@${CXX} ${LFLAGS} $(wildcard obj/Client/*.o) -o bin/Client/client

bin/Server/server: obj/Server/serverMain.o
	@${CXX} ${LFLAGS} $(wildcard obj/Server/*.o) -o bin/Server/server

# Compiling Server Targets
obj/Server/serverMain.o: src/Server/main.cpp
	@echo "Building serverMain.o"
	@${CXX} ${CFLAGS} src/Server/main.cpp -o obj/Server/serverMain.o


# Compiling Client Targets
obj/Client/clientMain.o: src/Client/main.cpp
	@echo "Building clientMain.o":
	@${CXX} ${CFLAGS} src/Client/main.cpp -o obj/Client/clientMain.o
obj/Client/window.o: src/Client/Engine/Input/Window.cpp
	@echo "Building window.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Input/Window.cpp -o obj/Client/window.o
obj/Client/program.o: src/Client/Program.cpp
	@echo "Building program.o"
	@${CXX} ${CFLAGS} src/Client/Program.cpp -o obj/Client/program.o
obj/Client/blockoutline.o: src/Client/BlockOutline.cpp
	@echo "Building blockoutline.o"
	@${CXX} ${CFLAGS} src/Client/BlockOutline.cpp -o obj/Client/blockoutline.o
obj/Client/outlinerenderer.o: src/Client/Engine/Utils/OutlineRenderer.cpp
	@echo "Building outlinerenderer.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/OutlineRenderer.cpp -o obj/Client/outlinerenderer.o
obj/Client/blockoutlineshader.o: src/Client/Engine/Utils/BlockOutlineShader.cpp
	@echo "Building blockoutlineshader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/BlockOutlineShader.cpp -o obj/Client/blockoutlineshader.o
obj/Client/textureArray.o: src/Client/Engine/Utils/TextureArray.cpp
	@echo "Building textureArray.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/TextureArray.cpp -o obj/Client/textureArray.o
obj/Client/frustum.o: src/Client/Engine/Libs/Frustum.cpp
	@echo "Building frustum.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Libs/Frustum.cpp -o obj/Client/frustum.o
obj/Client/inputmanager.o: src/Client/Engine/Input/InputManager.cpp
	@echo "Building inputmanager.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Input/InputManager.cpp -o obj/Client/inputmanager.o
obj/Client/model.o: src/Client/Engine/Utils/Model.cpp
	@echo "Building model.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Model.cpp -o obj/Client/model.o
obj/Client/modelshader.o: src/Client/Engine/Utils/ModelShader.cpp
	@echo "Building modelshader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/ModelShader.cpp -o obj/Client/modelshader.o
obj/Client/transform.o: src/Client/Engine/Utils/Transform.cpp
	@echo "Building transform.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Transform.cpp -o obj/Client/transform.o
obj/Client/entity.o: src/Client/Entity.cpp
	@echo "Building entity.o"
	@${CXX} ${CFLAGS} src/Client/Entity.cpp -o obj/Client/entity.o
obj/Client/entityhandler.o: src/Client/EntityHandler.cpp
	@echo "Building entityhandler.o"
	@${CXX} ${CFLAGS} src/Client/EntityHandler.cpp -o obj/Client/entityhandler.o
obj/Client/player.o: src/Client/Player.cpp
	@echo "Building player.o"
	@${CXX} ${CFLAGS} src/Client/Player.cpp -o obj/Client/player.o
obj/Client/chunk.o: src/Client/Engine/World/Chunk.cpp
	@echo "Building chunk.o"
	@${CXX} ${CFLAGS} src/Client/Engine/World/Chunk.cpp -o obj/Client/chunk.o
obj/Client/shader.o: src/Client/Engine/Utils/Shader.cpp
	@echo "Building shader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Shader.cpp -o obj/Client/shader.o
obj/Client/utils.o: src/Client/Engine/Utils/Utils.cpp
	@echo "Building utils.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Utils.cpp -o obj/Client/utils.o
obj/Client/chunkshader.o: src/Client/Engine/Utils/ChunkShader.cpp
	@echo "Building chunkshader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/ChunkShader.cpp -o obj/Client/chunkshader.o
obj/Client/game.o: src/Client/Game.cpp
	@echo "Building game.o"
	@${CXX} ${CFLAGS} src/Client/Game.cpp -o obj/Client/game.o
obj/Client/camera.o: src/Client/Engine/Utils/Camera.cpp
	@echo "Building camera.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Camera.cpp -o obj/Client/camera.o
obj/Client/network.o: src/Client/NetworkManager.cpp
	@echo "Building network.o"
	@${CXX} ${CFLAGS} src/Client/NetworkManager.cpp -o obj/Client/network.o
obj/Client/world.o: src/Client/Engine/World/World.cpp
	@echo "Building world.o"
	@${CXX} ${CFLAGS} src/Client/Engine/World/World.cpp -o obj/Client/world.o
obj/Client/cubemap.o: src/Client/Engine/Utils/CubeMap.cpp
	@echo "Building cubemap.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/CubeMap.cpp -o obj/Client/cubemap.o
obj/Client/cube.o: src/Client/Engine/Utils/Cube.cpp
	@echo "Building cube.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Cube.cpp -o obj/Client/cube.o
obj/Client/cubemapshader.o: src/Client/Engine/Utils/CubeMapShader.cpp
	@echo "Building cubemapshader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/CubeMapShader.cpp -o obj/Client/cubemapshader.o
obj/Client/cubemaptexture.o: src/Client/Engine/Utils/CubeMapTexture.cpp
	@echo "Building cubemaptexture.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/CubeMapTexture.cpp -o obj/Client/cubemaptexture.o
obj/Client/particlehandler.o: src/Client/Engine/Utils/ParticleHandler.cpp
	@echo "Building particlehandler.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/ParticleHandler.cpp -o obj/Client/particlehandler.o
obj/Client/particle.o: src/Client/Engine/Utils/Particle.cpp
	@echo "Building particle.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Particle.cpp -o obj/Client/particle.o
obj/Client/particlequad.o: src/Client/Engine/Utils/ParticleQuad.cpp
	@echo "Building particlequad.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/ParticleQuad.cpp -o obj/Client/particlequad.o
obj/Client/particleshader.o: src/Client/Engine/Utils/ParticleShader.cpp
	@echo "Building particleshader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/ParticleShader.cpp -o obj/Client/particleshader.o
obj/Client/guibutton.o: src/Client/Engine/GUI/GUIButton.cpp
	@echo "Building guibutton.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUIButton.cpp -o obj/Client/guibutton.o
obj/Client/guifont.o: src/Client/Engine/GUI/GUIFont.cpp
	@echo "Building guifont.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUIFont.cpp -o obj/Client/guifont.o
obj/Client/guifontshader.o: src/Client/Engine/GUI/GUIFontShader.cpp
	@echo "Building guifontshader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUIFontShader.cpp -o obj/Client/guifontshader.o
obj/Client/guihandler.o: src/Client/Engine/GUI/GUIHandler.cpp
	@echo "Building guihandler.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUIHandler.cpp -o obj/Client/guihandler.o
obj/Client/guirenderer.o: src/Client/Engine/GUI/GUIRenderer.cpp
	@echo "Building guirenderer.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUIRenderer.cpp -o obj/Client/guirenderer.o
obj/Client/guishader.o: src/Client/Engine/GUI/GUIShader.cpp
	@echo "Building guishader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUIShader.cpp -o obj/Client/guishader.o
obj/Client/pausemenu.o: src/Client/PauseMenu.cpp
	@echo "Building pausemenu.o"
	@${CXX} ${CFLAGS} src/Client/PauseMenu.cpp -o obj/Client/pausemenu.o
obj/Client/guiimage.o: src/Client/Engine/GUI/GUIImage.cpp
	@echo "Building guiimage.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUIImage.cpp -o obj/Client/guiimage.o
obj/Client/checkbox.o: src/Client/Engine/GUI/GUICheckbox.cpp
	@echo "Building checkbox.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUICheckbox.cpp -o obj/Client/checkbox.o
obj/Client/image.o: src/Client/Engine/Utils/Image.cpp
	@echo "Building image.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Utils/Image.cpp -o obj/Client/image.o
obj/Client/objloader.o: src/Client/Engine/Libs/OBJLoader.cpp
	@echo "Building objloader.o"
	@${CXX} ${CFLAGS} src/Client/Engine/Libs/OBJLoader.cpp -o obj/Client/objloader.o
obj/Client/guitextmesh.o: src/Client/Engine/GUI/GUITextMesh.cpp
	@echo "Building guitextmesh.o"
	@${CXX} ${CFLAGS} src/Client/Engine/GUI/GUITextMesh.cpp -o obj/Client/guitextmesh.o

clean:
	@echo "Cleaning Files"
	@rm -rf bin/Client/client
	@rm -rf bin/Server/server
	@rm -rf obj/Client/*.o
	@rm -rf obj/Server/*.o