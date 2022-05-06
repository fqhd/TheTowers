import os

# Functions
def getLFlags(userOS):
    lFlags = 'lflags = '
    if(userOS == 'macos'):
        files = os.listdir('./deps/macos')
        lFlags += '-L./deps/macos'
        for f in files:
            lFlags += ' -l' + f[3:-6]
        lFlags += ' -framework OpenGL'
    elif(userOS == 'linux'):
        # Not supported currently
        pass
    elif(userOS == 'windows'):
        # Not supported currently
        pass
    return lFlags

def getUserOS():
    userOS = input("What is your operating system?(linux/windows/macos): ")
    if(userOS != 'windows' and userOS != 'macos' and usrOS != 'linux'):
        print(userOS)
        print('Incorrect OS entered')
        exit()
    return userOS

def getSourceDirs():
    sourceDirs = []
    sourceDirs.append('./src/Client/Engine')
    sourceDirs.append('./src/Client/Game')
    sourceDirs.append('./src/Client/glad')
    sourceDirs.append('./src/Client/GUI')
    sourceDirs.append('./src/Client/Input')
    sourceDirs.append('./src/Client/Math')
    return sourceDirs

def getCFlags(sourceDirs):
    cFlags = 'cflags = -std=c++17 -O0 -fdiagnostics-color=always -g -m64 -I./deps/include'
    for dir in sourceDirs:
        cFlags += ' -I' + dir
    return cFlags

def main():
    userOS = getUserOS()
    sourceDirs = getSourceDirs()
    cFlags = getCFlags(sourceDirs)
    lFlags = getLFlags(userOS)
    print(cFlags)

main()