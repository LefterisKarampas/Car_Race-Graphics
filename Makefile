OBJS = build/visuals.o\
       build/Model.o\
       build/custom_vertexes.o\
       build/bridge.o\
       build/vehicle.o\
       build/Crash.o\
       build/Map.o\
       build/Score.o\
       build/traffic_light.o\
       build/CarModel.o
	
BIN = build/race
CXXFLAGS += -march=native -O2 -pedantic-errors -pipe -std=c++14
ifneq (,$(findstring clang++,$(CXX)))
	CXXFLAGS += -g -stdlib=libc++ -Weverything
	LDFLAGS += -stdlib=libc++
	LDLIBS += -lc++abi
else
	CXXFLAGS += -flto -g3
endif
LDLIBS = -lglut -lGL -lGLU

.PHONY = all clean
all : $(BIN)
clean :
	$(RM) -r $(BIN) build/*

build/main.o : src/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/visuals.o : src/visuals.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Model.o : src/Model.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/custom_vertexes.o : src/custom_vertexes.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/bridge.o : src/bridge.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/vehicle.o : src/vehicle.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Crash.o : src/Crash.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Map.o : src/Map.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/Score.o : src/Score.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/traffic_light.o : src/traffic_light.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/CarModel.o : src/CarModel.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN) : $(OBJS) build/main.o
	mkdir -p ./build && $(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)