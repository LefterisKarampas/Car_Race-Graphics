all:
	g++ ./src/visuals.cpp ./src/main.cpp ./src/Model.cpp ./src/custom_vertexes.cpp -o ./build/race -lglut -lGL -lGLU

clean:
	rm -rf ./build/*