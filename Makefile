all:
	mkdir -p ./build
	g++ ./src/visuals.cpp ./src/main.cpp ./src/custom_vertexes.cpp ./src/bridge.cpp ./src/vehicle.cpp ./src/test_car.cpp -o ./build/race -lglut -lGL -lGLU

clean:
	rm -rf ./build/*