CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS = -lrt -lm -lasound -ljack -pthread -lsndfile 
LIB_FLAGS = lib/libportaudio.a


all : TerminalTuner run

TerminalTuner: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^ $(LIB_FLAGS)

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

run : 
	./TerminalTuner
