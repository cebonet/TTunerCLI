CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS = -lrt -lm -lasound -ljack -pthread -lsndfile 
LIB_FLAGS = lib/libportaudio.a

CPP_TEST_FILES := $(wildcard tests/*.cpp)
OBJ_TEST_FILES := $(addprefix obj/,$(notdir $(CPP_TEST_FILES:.cpp=.o)))

all : TerminalTuner run

testProject: TerminalTuner test runTest

test: $(OBJ_TEST_FILES) 
	g++ $(LD_FLAGS) -o $@ $^ $(LIB_FLAGS)


TerminalTuner: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^ $(LIB_FLAGS)


obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<


obj/%.o: tests/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

run : 
	./TerminalTuner

runTest :
	./test
