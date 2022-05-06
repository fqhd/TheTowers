import os

# Functions
def getUserOS():
    userOS = input("What is your operating system?(linux/windows/macos): ")
    if(userOS != 'windows' and userOS != 'macos' and usrOS != 'linux'):
        print(userOS)
        print('Incorrect OS entered')
        exit()
    return userOS

def getClientSourceDirs():
    sourceDirs = []
    sourceDirs.append('./src/Client/Engine')
    sourceDirs.append('./src/Client/Game')
    sourceDirs.append('./src/Client/glad')
    sourceDirs.append('./src/Client/GUI')
    sourceDirs.append('./src/Client/Input')
    sourceDirs.append('./src/Client/Math')
    sourceDirs.append('./src/Client')
    return sourceDirs

def getServerSourceDirs():
    sourceDirs = []
    sourceDirs.append('./src/Server')
    return sourceDirs

def getCFlags(sourceDirs):
    cFlags = 'cflags = -std=c++17 -O0 -fdiagnostics-color=always -g -m64 -I./deps/include'
    for d in sourceDirs:
        cFlags += ' -I' + d
    return cFlags

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

def createBuildScript(lFlags, cFlags, clientSourceDirs, serverSourceDirs):
    file = open('build.ninja', 'w')
    file.write(cFlags + '\n')
    file.write(lFlags + '\n')
    file.write('rule cxx\n')
    file.write('  command = g++ -c $in -o $out $cflags\n')
    file.write('rule lnk\n')
    file.write('  command = g++ -o $out $in $lflags\n')

    clientODirs = []
    serverODirs = []

    for d in clientSourceDirs:
        files = os.listdir(d)
        for f in files:
            if(f[-4:] == '.cpp'):
                currODir = 'obj/' + d[2:] + '/' + f[:-4] + '.o'
                clientODirs.append(currODir)
                file.write('build ' + currODir + ': cxx ' + os.path.join(d, f) + '\n')

    for d in serverSourceDirs:
        files = os.listdir(d)
        for f in files:
            if(f[-4:] == '.cpp'):
                currODir = 'obj/' + d[2:] + '/' + f[:-4] + '.o'
                serverODirs.append(currODir)
                file.write('build ' + currODir + ': cxx ' + os.path.join(d, f) + '\n')
    
    file.write('build client: lnk')
    for o in clientODirs:
        file.write(' ' + o)
    file.write('\n')
    
    file.write('build server: lnk')
    for o in serverODirs:
        file.write(' ' + o)
    file.write('\n')

    file.close()

def main():
    userOS = getUserOS()
    clientSourceDirs = getClientSourceDirs()
    serverSourceDirs = getServerSourceDirs()
    cFlags = getCFlags(clientSourceDirs)
    lFlags = getLFlags(userOS)
    createBuildScript(lFlags, cFlags, clientSourceDirs, serverSourceDirs)

main()