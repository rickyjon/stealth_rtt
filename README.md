Todo:
	rename some stuff

	test if it builds on windows (don't bother testing OSX)


Compiling:

	git submodule update --init --recursive
	cd godot-cpp
	scons platform=windows/linux/osx headers_dir=../godot_headers generate_bindings=yes
	cd ..
	scons platform=windows/linux/osx

Modifying:

	if you declare a function in the header file, make sure to decalre it as well in the body of the .cpp file as well, even if it's empty (wip) or a virutal function.