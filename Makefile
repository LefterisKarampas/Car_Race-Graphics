OBJS = build/visuals.o\
       build/Model.o\
       build/custom_vertexes.o\
       build/bridge.o\
       build/vehicle.o\
       build/Crash.o\
       build/Map.o\
       build/Score.o\
       build/traffic_light.o\
       build/CarModel.o\
       build/functions.o\
	
BIN = build/race
LDLIBS = -lglut -lGL -lGLU

.PHONY = all clean
all : $(BIN)
clean :
	$(RM) -r $(BIN) build/*

build/main.o : src/main.cpp
	$(CXX) -c $< -o $@

build/visuals.o : src/visuals.cpp
	$(CXX) -c $< -o $@

build/Model.o : src/Model.cpp
	$(CXX) -c $< -o $@

build/custom_vertexes.o : src/custom_vertexes.cpp
	$(CXX) -c $< -o $@

build/bridge.o : src/bridge.cpp
	$(CXX) -c $< -o $@

build/vehicle.o : src/vehicle.cpp
	$(CXX) -c $< -o $@

build/Crash.o : src/Crash.cpp
	$(CXX) -c $< -o $@

build/Map.o : src/Map.cpp
	$(CXX) -c $< -o $@

build/Score.o : src/Score.cpp
	$(CXX) -c $< -o $@

build/traffic_light.o : src/traffic_light.cpp
	$(CXX) -c $< -o $@

build/CarModel.o : src/CarModel.cpp
	$(CXX) -c $< -o $@

build/functions.o : src/functions.cpp
	$(CXX) -c $< -o $@

$(BIN) : $(OBJS) build/main.o
	mkdir -p ./build && $(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)