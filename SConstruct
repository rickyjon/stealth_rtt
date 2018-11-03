#!python
import os

target = ARGUMENTS.get("target", "debug")
platform = ARGUMENTS.get("platform", "windows")
bits = ARGUMENTS.get("bits", 64)

final_lib_path = 'bin/'

# This makes sure to keep the session environment variables on windows,
# that way you can run scons in a vs 2017 prompt and it will find all the required tools
env = Environment()
if platform == "windows":
    env = Environment(ENV = os.environ)

def add_sources(sources, directory):
    for file in os.listdir(directory):
        if file.endswith('.cpp'):
            sources.append(directory + '/' + file)

#env["CXX"] = "clang++"
if platform == "osx":
    env.Append(CCFLAGS = ['-g','-O3', '-arch', 'x86_64', '-std=c++14'])
    env.Append(LINKFLAGS = ['-arch', 'x86_64'])
    env.Append(LIBS=["godot-cpp" + "." + platform + "." + str(bits)])


    final_lib_path = final_lib_path + 'osx/'

elif platform == "linux":
    env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14'])
    #env.Append(CCFLAGS = ['-fPIC', '-g','-O3', '-std=c++14', '-Wno-writable-strings'])
   # env.Append(LINKFLAGS = ['-Wl,-R,\'$$ORIGIN\''])
    env.Append(LIBS=["godot-cpp" + "." + platform + "." + "release." + str(bits)])


    final_lib_path = final_lib_path + 'x11/'

elif platform == "windows":
    if target == "debug":
        env.Append(CCFLAGS = ['-EHsc', '-D_DEBUG', '-MDd'])
    else:
        env.Append(CCFLAGS = ['-O2', '-EHsc', '-DNDEBUG', '-MD'])

    env.Append(LIBS=["godot-cpp" + "." + platform + "." + str(bits)])

    final_lib_path = final_lib_path + 'win' + str(bits) + '/'

env.Append(CPPPATH=['.', 'src/', "godot_headers/", 'godot-cpp/include/', 'godot-cpp/include/core/'])
env.Append(LIBPATH="godot-cpp/bin")

sources = []
add_sources(sources, "src")
#add_sources(sources, "unit")
#add_sources(sources, "mousemovement")

library = env.SharedLibrary(target=final_lib_path + 'libcommon', source=sources)
#library = env.SharedLibrary(target=final_lib_path + 'libplayer', source=sources)
Default(library)
