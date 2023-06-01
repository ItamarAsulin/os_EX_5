CC = g++
CFLAGS = -std=c++11 -Wall -g

OBJ = ThreadSafeQueue.o ActiveObject.o main.o

all: st_pipeline

st_pipeline: $(OBJ)
	$(CC) $(CFLAGS) -o st_pipeline $(OBJ)

ThreadSafeQueue.o: ThreadSafeQueue.cpp ThreadSafeQueue.hpp
	$(CC) $(CFLAGS) -c ThreadSafeQueue.cpp

ActiveObject.o: ActiveObject.cpp ActiveObject.hpp ThreadSafeQueue.hpp
	$(CC) $(CFLAGS) -c ActiveObject.cpp

main.o: main.cpp ActiveObject.hpp ThreadSafeQueue.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f st_pipeline $(OBJ)
