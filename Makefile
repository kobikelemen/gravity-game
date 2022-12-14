CC = g++ -std=c++17

# INCLUDES = -I/usr/local/Cellar/sfml/2.5.1_1/include/

CFLAGS = -g

LDFLAGS = -L/usr/local/Cellar/sfml/2.5.1_1/lib/

SERVEROBJS = main.o game.o object.o player.o planet.o gravity_objects.o laser.o arrow.o server.o message.o animation.o

CLIENTOBJS = client_main.o game.o object.o player.o planet.o gravity_objects.o laser.o arrow.o client.o message.o server.o client_game.o animation.o

all: server client

server: $(SERVEROBJS)
	$(CC) $(SERVEROBJS) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o server

client: $(CLIENTOBJS)
	$(CC) $(CLIENTOBJS) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o client


main.o: main.cpp game.h
	$(CC) $(CFLAGS) -c main.cpp game.h

client_main.o: client_game/client_main.cpp client_game/client_game.h
	$(CC) $(CFLAGS) -c client_game/client_main.cpp

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp object.h

game.o: game.cpp game.h player.h object.h arrow.h animation.h
	$(CC) $(CFLAGS) -c game.cpp

player.o: player.cpp player.h laser.h
	$(CC) $(CFLAGS) -c player.cpp

planet.o: planet.cpp planet.h laser.h
	$(CC) $(CLFLAGS) -c planet.cpp

gravity_objects.o: gravity_objects.cpp gravity_objects.h object.h planet.h
	$(CC) $(CFLAGS) -c gravity_objects.cpp

laser.o: laser.cpp laser.h
	$(CC) $(CFLAGS) -c laser.cpp

arrow.o: arrow.cpp arrow.h
	$(CC) $(CFLAGS) -c arrow.cpp

client.o: networking/client.cpp networking/client.h networking/message.h networking/threadsafe_queue.h
	$(CC) $(CFLAGS) -c networking/client.cpp

server.o: networking/server.cpp networking/server.h networking/message.h networking/threadsafe_queue.h
	$(CC) $(CFLAGS) -c networking/server.cpp

client_game.o: client_game/client_game.cpp client_game/client_game.h game.h networking/client.h networking/server.h animation.h
	$(CC) $(CFLAGS) -c client_game/client_game.cpp
	
message.o: networking/message.cpp networking/message.h move.h
	$(CC) $(CFLAGS) -c networking/message.cpp

animation.o: animation.cpp animation.h
	$(CC) $(CFLAGS) -c animation.cpp

clean:
	rm -f $(SERVEROBJS) $(CLIENTOBJS) *~