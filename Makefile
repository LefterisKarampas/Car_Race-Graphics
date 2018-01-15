all:
	mkdir -p ./build
	g++ ./src/visuals.cpp ./src/main.cpp ./src/Model.cpp ./src/custom_vertexes.cpp \
	./src/bridge.cpp ./src/vehicle.cpp -o ./build/race \
	./src/Crash.cpp ./src/Map.cpp ./src/Score.cpp ./src/traffic_light.cpp \
	./src/CarModel.cpp -lglut -lGL -lGLU

clean:
	rm -rf ./build/*