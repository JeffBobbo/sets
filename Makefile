EXEC:=test

MAIN = main.o

# general compiler settings
CPPFLAGS=
CXXFLAGS=-Wall -Wextra -Werror -ggdb
LDFLAGS=

#default target is debug Linux
all: linux

win: CXX=x86_64-w64-mingw32-c++
win: LDFLAGS+=-static-libgcc -static-libstdc++ -static
win: EXEC:=$(EXEC).exe
win: comp

droid: LDFLAGS+=-lgnustl_shared
droid: linux

linux: EXEC:=$(EXEC).out
linux: comp

comp: $(MAIN)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(MAIN) -o $(EXEC) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(warning Cleaning...)
	@$(RM) $(MAIN)

.PHONY: all clean

