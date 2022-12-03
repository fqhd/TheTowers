import os

def getIncludeDirs(ourDir):
    files = os.listdir(ourDir)
    includeDirs = set()
    for f in files:
        if(os.path.isdir(os.path.join(ourDir, f))):
            includeDirs = includeDirs.union(getIncludeDirs(ourDir + '/' + f))
        else:
            if(f[-4:] == '.hpp'):
                includeDirs.add(ourDir)
    return includeDirs

def getSourceFiles(ourDir):
    files = os.listdir(ourDir)
    sourceFiles = []
    for f in files:
        if(os.path.isdir(os.path.join(ourDir, f))):
            sourceFiles = sourceFiles + getSourceFiles(ourDir + '/' + f)
        else:
            if(f[-4:] == '.cpp'):
                sourceFiles.append(ourDir + '/' + f)
    return sourceFiles

def createBuildScript(clientSources, serverSources, includeDirs):
    file = open('CMakeLists.txt', 'w')
    file.write('cmake_minimum_required(VERSION 3.15.0)\n')
    file.write('project(TheTowers VERSION 1.0.0)\n')
    file.write('set(CMAKE_CXX_STANDARD 20)\n')
    file.write('set(CMAKE_CXX_STANDARD_REQUIRED ON)\n')
    file.write('add_subdirectory(deps/asio-cmake)\n')
    file.write('add_subdirectory(deps/glad-cmake)\n')
    file.write('add_subdirectory(deps/glfw)\n')
    file.write('add_subdirectory(deps/glm)\n')
    file.write('add_subdirectory(deps/stb-cmake)\n')

    file.write('add_executable(client')
    for f in clientSources:
        file.write(' ' + f)
    file.write(')\n')

    file.write('add_executable(server')
    for f in serverSources:
        file.write(' ' + f)
    file.write(')\n')

    for d in includeDirs:
        file.write('target_include_directories(client PUBLIC ' + d + ')\n')

    file.write('target_link_libraries(client PUBLIC asio-cmake)\n')
    file.write('target_link_libraries(client PUBLIC glad-cmake)\n')
    file.write('target_link_libraries(client PUBLIC stb-cmake)\n')
    file.write('target_link_libraries(client PUBLIC glfw)\n')
    file.write('target_link_libraries(client PUBLIC glm)\n')
    file.write('target_link_libraries(server PUBLIC asio-cmake)\n')

    file.close()

def main():
    clientSources = getSourceFiles('./src/Client')
    serverSources = getSourceFiles('./src/Server')
    includeDirs = getIncludeDirs('./src')
    createBuildScript(clientSources, serverSources, includeDirs)

main()