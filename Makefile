CPP = g++
RUN = Lab1
FLAGS = -Werror -Wpedantic -Wall
OBJS = main.o bmpFuncs.o

all: $(RUN)

$(RUN): $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CPP) -c $<

clean:
	rm *.o $(RUN)

cleanall:
	rm *.o *.cpp $(RUN)
