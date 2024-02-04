TARGET := ardusdl
VPATH = ../Asokoban
CPPFLAGS :=  -ggdb -D_REENTRANT -I/usr/include/SDL2
LDLIBS := -lSDL2
SOURCES := $(wildcard $(VPATH)/*.cpp *.cpp)
OBJECTS := $(SOURCES:%.cpp=%.o)
INCLUDES := levels.h sprites.h defines.h font.h font4x6.h

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LDLIBS)

$(OBJECTS) : $(SOURCES) $(INCLUDES)

.PHONY: clean
clean:
	@$(RM) $(TARGET)
	@$(RM) $(OBJECTS)
