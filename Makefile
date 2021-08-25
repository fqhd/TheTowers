INCLUDES = $$(pkg-config --cflags sfml-all) $$(pkg-config --cflags epoxy)
LIBS = $$(pkg-config --libs sfml-all) $$(pkg-config --libs epoxy)

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

all: client server

# Linking Targets
client: ${CLIENT_OBJS}
	${CXX} ${LFLAGS} $^ -o client

server: ${SERVER_OBJS}
	${CXX} ${LFLAGS} $^ -o server


%.o: %.cpp
	${CXX} ${CFLAGS} -c $^ -o $@

clean:
	find . -name "*.o" -delete
	rm -rf client
	rm -rf server
