CC = g++ -std=c++11

INCLUDES = -I/usr/local/Cellar/sfml/2.5.1_1/include/

CFLAGS = -g $(INCLUDES)

LDFLAGS = -L/usr/local/Cellar/sfml/2.5.1_1/lib/

OBJS = main.o game.o object.o player.o planet.o gravity_objects.o


main: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp object.h

game.o: game.cpp game.h player.h object.h
	$(CC) $(CFLAGS) -c game.cpp game.h player.h object.h

player.o: player.cpp player.h
	$(CC) $(CFLAGS) -c player.cpp player.h

planet.o: planet.cpp planet.h
	$(CC) $(CLFLAGS) -c planet.cpp planet.h object.h gravity_objects.h

gravity_objects.o: gravity_objects.cpp gravity_objects.h object.h planet.h
	$(CC) $(CFLAGS) -c gravity_objects.cpp gravity_objects.h object.h planet.h


clean:
	rm -f $(OBJS) *~