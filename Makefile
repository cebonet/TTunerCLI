CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS = -lsndfile

all : TerminalTuner run

TerminalTuner: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

run : 
	./TerminalTuner
