objects = main.o world.o object.o
libs = -L/home/alec/Downloads/Box2D_v2.2.1/Build/gmake/bin/Debug/ -lBox2D -lSDL -lGL -lGLU -lgtest
includes = -I/home/alec/Downloads/Box2D_v2.2.1 -I/home/alec/Downloads/gtest-1.6.0/include

main: $(objects)
	clang++ -g $(objects) $(libs) -o main

main.o: main.cc
	clang++ -c $(includes)  main.cc

object.o: object.cc object.h help.h
	clang++ -c $(includes) object.cc

object_test.o: object_test.cc object.h
	clang++ -c $(includes) object_test.cc

object_test: object_test.o object.o
	clang++ -g object_test.o object.o $(libs) -o object_test

world_test.o: world_test.cc world.h object.h
	clang++ -c $(includes) world_test.cc

world_test: world_test.o world.o object.o
	clang++ -g world_test.o world.o object.o $(libs) -o world_test

world.o: world.cc world.h help.h
	clang++ -c $(includes) world.cc

.PHONY: clean
clean:
	rm -rf main object_test world_test *.o
