CXX = g++
RUN = Lab1
FLAGS = -Werror -Wpedantic -Wall
OBJSDIR = objs
SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:src/%.cpp=$(OBJSDIR)/%.o)

all: $(RUN)

$(RUN): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(OBJSDIR)/%.o: src/%.cpp | $(OBJSDIR)
	$(CXX) -c $< $(FLAGS) -o $@

$(OBJSDIR):
	mkdir $(OBJSDIR)

clean:
	rm -rf $(OBJSDIR) $(RUN) 90.bmp 90blurred.bmp 270.bmp 270blurred.bmp

cleanall:
	rm $(OBJSDIR) $(RUN)
