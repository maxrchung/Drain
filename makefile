FLAGS = -lm -w -fpermissive -Wnarrowing 
CC = g++ -g

STORY = main

S2RYDIR = Drain/S2RYBRUH
DRAINDIR = Drain/Drain

CUROS = $(wildcard $(S2RYDIR)/*.o)
CUROD = $(wildcard Drain/Drain/*.o)

DRAINSRC := $(wildcard Drain/Drain/*.cpp)
DRAINH   := $(wildcard Drain/Drain/*.hpp)

S2RYSRC := $(wildcard Drain/S2RYBRUH/*.cpp)
S2RYH   := $(wildcard Drain/S2RYBRUH/*.hpp)

OUT = drain

all: clean S2RYOBJ2 DRAINOBJ2 link
	./drain

$(DRAINDIR)/%.o: $(DRAINDIR)/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

DRAINOBJ2: $(DRAINSRC:.cpp=.o)

$(S2RYDIR)/%.o: $(S2RYDIR)/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

S2RYOBJ2: $(S2RYSRC:.cpp=.o)
	gcc -c Drain/S2RYBRUH/kiss_fft.c -o Drain/S2RYBRUH/kiss_fft.o
	gcc -c Drain/S2RYBRUH/kiss_fftr.c -o Drain/S2RYBRUH/kiss_fftr.o

link:
	$(CC) Drain/Drain/*.o Drain/S2RYBRUH/*.o -o drain

clean:
	del $(CUROD)

cleanall:
	del $(CUROS)

hardlink:
	ln Drain/Drain/*.hpp Drain/S2RYBRUH/*.hpp
