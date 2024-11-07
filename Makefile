CXX = g++
RUN = Lab1
FLAGS = -Werror -Wpedantic -Wall
SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)

all: $(RUN)

$(RUN): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) -c $< $(FLAGS)

clean:
	rm -f $(OBJS) $(RUN)

cleanall:
	rm -f $(OBJS) $(RUN)
