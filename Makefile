CC = g++ -std=c++11

INCLUDES = -I/usr/local/Cellar/sfml/2.5.1_1/include/

CFLAGS = -g $(INCLUDES)

LDFLAGS = -L/usr/local/Cellar/sfml/2.5.1_1/lib/

OBJS = main.o game.o object.o player.o


main: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

game.o: game.cpp 
	$(CC) $(CFLAGS) -c game.cpp

object.o: object.cpp
	$(CC) $(CFLAGS) -c object.cpp

player.o: player.cpp
	$(CC) $(CFLAGS) -c player.cpp

clean:
	rm -f $(OBJS) *~