TARGET := ardusdl
VPATH = ../Asokoban
CPPFLAGS :=  -ggdb -D_REENTRANT -I/usr/include/SDL2
LDLIBS := -lSDL2
SOURCES := $(wildcard $(VPATH)/*.cpp *.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) -ggdb -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	@$(RM) $(TARGET)
	@$(RM) $(OBJECTS)
