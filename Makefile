CC = g++ -std=c++17

# INCLUDES = -I/usr/local/Cellar/sfml/2.5.1_1/include/

CFLAGS = -g

LDFLAGS = -L/usr/local/Cellar/sfml/2.5.1_1/lib/

SERVEROBJS = main.o game.o object.o player.o planet.o gravity_objects.o laser.o arrow.o server.o threadsafe_queue.o

CLIENTOBJS = client_main.o game.o object.o player.o planet.o gravity_objects.o laser.o arrow.o client.o threadsafe_queue.o

server: $(SERVEROBJS)
	$(CC) $(SERVEROBJS) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o main

client: $(CLIENTOBJS)
	$(CC) $(CLIENTOBJS) $(LDFLAGS) -lsfml-graphics -lsfml-window -lsfml-system -o main


main.o: main.cpp game.h
	$(CC) $(CFLAGS) -c main.cpp game.h

client_main.o: client_game/client_main.cpp client_game/client_game.h
	$(CC) $(CFLAGS) -c client_game/client_main.cpp client_game/client_game.h

object.o: object.cpp object.h
	$(CC) $(CFLAGS) -c object.cpp object.h

game.o: game.cpp game.h player.h object.h arrow.h
	$(CC) $(CFLAGS) -c game.cpp game.h player.h object.h arrow.h

player.o: player.cpp player.h laser.h
	$(CC) $(CFLAGS) -c player.cpp player.h laser.h

planet.o: planet.cpp planet.h laser.h
	$(CC) $(CLFLAGS) -c planet.cpp planet.h object.h gravity_objects.h laser.h

gravity_objects.o: gravity_objects.cpp gravity_objects.h object.h planet.h
	$(CC) $(CFLAGS) -c gravity_objects.cpp gravity_objects.h object.h planet.h

laser.o: laser.cpp laser.h
	$(CC) $(CFLAGS) -c laser.cpp laser.h

arrow.o: arrow.cpp arrow.h
	$(CC) $(CFLAGS) -c arrow.cpp arrow.h

client.o: networking/client.cpp networking/client.h networking/message.h networking/threadsafe_queue.h
	$(CC) $(CFLAGS) -c networking/client.cpp networking/client.h networking/message.h networking/threadsafe_queue.h

server.o: networking/server.cpp networking/server.h networking/message.h networking/threadsafe_queue.h
	$(CC) $(CFLAGS) -c networking/server.cpp networking/server.h networking/message.h networking/threadsafe_queue.h

threadsafe_queue.o: networking/threadsafe_queue.cpp networking/threadsafe_queue.h networking/message.h
	$(CC) $(CFLAGS) -c networking/threadsafe_queue.cpp networking/threadsafe_queue.h networking/message.h

client_game.o: client_game/client_game.cpp client_game/client_game.h game.h networking/client.h
	$(CC) $(CFLAGS) -c client_game/client_game.cpp client_game/client_game.h game.h networking/client.h


clean:
	rm -f $(OBJS) *~