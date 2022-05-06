import os

def getLFlags():
    lFlags = 'lflags = '
    if(userOS == 'macos'):
        files = os.listdir('./deps/macos')
        lFlags += '-L./deps/macos'
        for f in files:
            lFlags += ' -l' + f[3:-6]
        lFlags += ' -framework OpenGL'
    elif(userOS == 'linux'):
        pass
    elif(userOS == 'windows'):
        pass
    return lFlags

userOS = input("What is your operating system?(linux/windows/macos): ")

if(userOS != 'windows' and userOS != 'macos' and usrOS != 'linux'):
    print(userOS)
    print('Incorrect OS entered')
    exit()

print(getLFlags())
