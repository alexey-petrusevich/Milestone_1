run: compile test_all

compile:
	cmake build/CmakeLists.txt
	cd build/ && make
test_all:
	./bin/test_serialization
	./bin/test_sorer
clean:
	rm -rf bin/
	rm -rf build/CMakeFiles/
	rm build/cmake_install.cmake
	rm build/CMakeCache.txt
	rm build/Makefile