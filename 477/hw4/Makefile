SRC = main.cpp \
		Scene.cpp \
			Mesh.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS = -std=c++11 -O3 -lGL -lGLU -lglut -lGLEW -lm

.cpp.o:
	g++ -c $< $(CFLAGS)

all: test

test: $(OBJ)
	g++ $(OBJ) -o hw4 $(CFLAGS)

clean:
	rm -f *.o hw4 *.ppm *.png
