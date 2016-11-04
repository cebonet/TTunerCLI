CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS = -lrt -lm -lasound -ljack -pthread -lsndfile 
LIB_FLAGS = lib/libportaudio.a

CPP_TEST_FILES := $(filter-out src/TerminalTuner.cpp src/recordaudio.cpp, $(wildcard */*.cpp))
OBJ_TEST_FILES := $(addprefix obj/,$(notdir $(CPP_TEST_FILES:.cpp=.o)))

all : TerminalTuner run

testProject: test runTest

TerminalTuner: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^ $(LIB_FLAGS)

test: $(OBJ_TEST_FILES) 
	g++ $(LD_FLAGS) -o $@ $^ 

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<


obj/%.o: tests/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

run : 
	./TerminalTuner

runTest :
	./test -s
