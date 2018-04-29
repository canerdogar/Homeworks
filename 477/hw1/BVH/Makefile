SRC = main.cpp \
	Image.cpp \
		Sphere.cpp \
			Scene.cpp \
				Camera.cpp \
					Triangle.cpp \
						Material.cpp \
							BVHNode.cpp
OBJ = $(SRC:.cpp=.o)
CFLAGS = -std=c++11 -O3

.cpp.o:
	g++ -c $< $(CFLAGS)

all: test

test: $(OBJ)
	g++ $(OBJ) -o raytracer $(CFLAGS)

clean:
	rm -f *.o raytracer *.ppm *.png
