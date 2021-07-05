INCLUDES = $$(pkg-config --cflags sfml-network) $$(pkg-config --cflags glew) $$(pkg-config --cflags glfw3)
LIBS = $$(pkg-config --libs sfml-network) $$(pkg-config --libs glew) $$(pkg-config --libs glfw3)

CFLAGS = -c -std=c++17 -O0 ${INCLUDES} -fdiagnostics-color=always -g -m64 -Wall -Werror
LFLAGS = -pthread ${LIBS}
CXX = clang++

WORLD_SOURCES = $(wildcard src/Client/Engine/World/*.cpp)
UTILS_SOURCES = $(wildcard src/Client/Engine/Utils/*.cpp)
GUI_SOURCES = $(wildcard src/Client/Engine/GUI/*.cpp)
INPUT_SOURCES = $(wildcard src/Client/Engine/Input/*.cpp)
LIB_SOURCES = $(wildcard src/Client/Engine/Libs/*.cpp)
CLIENT_SOURCES = $(wildcard src/Client/*.cpp)
SERVER_SOURCES = $(wildcard src/Server/*.cpp)

CLIENT_OBJS = $(patsubst %.cpp, %.o, ${WORLD_SOURCES} ${UTILS_SOURCES} ${GUI_SOURCES} ${INPUT_SOURCES} ${LIB_SOURCES} ${CLIENT_SOURCES})
SERVER_OBJS = $(patsubst %.cpp, %.o, ${SERVER_SOURCES})

all: bin/Client/client bin/Server/server

# Linking Targets
bin/Client/client: ${CLIENT_OBJS}
	${CXX} ${LFLAGS} $^ -o bin/Client/client

bin/Server/server: ${SERVER_OBJS}
	mkdir bin/Server
	${CXX} ${LFLAGS} $^ -o bin/Server/server


%.o: %.cpp
	${CXX} ${CFLAGS} -c $^ -o $@

clean:
	find . -name "*.o" -delete
	rm -rf bin/Client/client
	rm -rf bin/Server/server
