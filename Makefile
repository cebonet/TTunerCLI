CPP_FILES := $(filter-out src/wavReader.cpp , $(wildcard src/*.cpp))
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS = -g -lrt -lm -lasound -ljack -pthread 
LD_TEST_FLAGS = -g -lrt -lm -lasound -ljack -pthread -lsndfile 
LIB_FLAGS = lib/libportaudio.a

CPP_TEST_FILES := $(filter-out src/TerminalTuner.cpp src/recordaudio.cpp, $(wildcard */*.cpp))
OBJ_TEST_FILES := $(addprefix obj/,$(notdir $(CPP_TEST_FILES:.cpp=.o)))

CPP_DSP_FILES := $(wildcard src/DSPFilters/*.cpp)
OBJ_DSP_FILES := $(addprefix obj/,$(notdir $(CPP_DSP_FILES:.cpp=.o)))

all : TerminalTuner 

testProject: test runTest

DSPFilters: $(OBJ_DSP_FILES)
	g++  -o $@ $^ 

TerminalTuner: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^ $(LIB_FLAGS)

test: $(OBJ_TEST_FILES) 
	g++ $(LD_TEST_FLAGS) -o $@ $^ 

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<


obj/%.o: tests/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

run : 
	./TerminalTuner

runTest :
	./test -s
