all:
	g++ ./src/visuals.cpp ./src/main.cpp ./src/Model.cpp -o ./build/race -lglut -lGL -lGLU