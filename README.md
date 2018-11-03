Todo:
	rename some stuff

	test if it builds on windows (don't bother testing OSX)


Compiling:

	git submodule update --init --recursive
	cd godot-cpp
	scons platform=windows/linux/osx headers_dir=../godot_headers generate_bindings=yes
	cd ..
	scons platform=windows/linux/osx
