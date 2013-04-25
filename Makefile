objects = world.o object.o drawing.o basic_object.o ship.o level.o
libs = -L/home/alecb/Downloads/Box2D_v2.2.1/Build/gmake/bin/Debug/ -lBox2D -lSDL -lGL -lGLU -lgtest -llua5.1
includes = -I/home/alecb/Downloads/Box2D_v2.2.1

main: main.o world.h level.h $(objects)
	clang++ -g main.o $(objects) $(libs) -o main

main.o: main.cc
	clang++ -g -c $(includes)  main.cc

object.o: object.cc object.h help.h
	clang++ -g -c $(includes) object.cc

world.o: world.cc world.h help.h
	clang++ -g -c $(includes) world.cc

drawing.o: drawing.cc drawing.h
	clang++ -g -c $(includes) drawing.cc

basic_object.o: basic_object.cc basic_object.h object.h
	clang++ -g -c $(includes) basic_object.cc

ship.o: ship.cc ship.h drawing.h
	clang++ -g -c $(includes) ship.cc

level.o: level.cc level.h basic_object.h ship.h
	clang++ -g -c $(includes) level.cc


tests: world_test

run_tests: tests
	./world_test

world_test.o: world_test.cc world.h object.h
	clang++ -c $(includes) world_test.cc

world_test: world_test.o world.o object.o
	clang++ -g world_test.o $(objects) $(libs) -o world_test


.PHONY: clean
clean:
	rm -rf main object_test world_test *.o
