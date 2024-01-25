TARGET := drawing
VPATH = Asokoban:Desktop
CPPFLAGS := -std=c++14 -D_REENTRANT -I/usr/include/SDL2 
LDLIBS := -lSDL2 

all: $(TARGET)

clean:
	@$(RM) $(TARGET)
