LDFLAGS = -lm
FLAGS = -w -fpermissive -Wnarrowing -D LINUX
CC = g++ -MMD -g

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

all: S2RYOBJ2 DRAINOBJ2 cstuff link
	./drain && ./move.sh

$(DRAINDIR)/%.o: $(DRAINDIR)/%.cpp
	$(CC) $(FLAGS) -IDrain/S2RYBRUH/ -c $< -o $@

DRAINOBJ2: $(DRAINSRC:.cpp=.o)

$(S2RYDIR)/%.o: $(S2RYDIR)/%.cpp
	$(CC) $(FLAGS) -c $< -o $@

cstuff: $(S2RYDIR)/kiss_fft.c $(S2RYDIR)/kiss_fftr.c
	gcc -MMD -c -IDrain/S2RYBRUH $(S2RYDIR)/kiss_fft.c -o $(S2RYDIR)/kiss_fft.o
	gcc -MMD -c -IDrain/S2RYBRUH $(S2RYDIR)/kiss_fftr.c -o $(S2RYDIR)/kiss_fftr.o

S2RYOBJ2: $(S2RYSRC:.cpp=.o)

link:
	$(CC) Drain/Drain/*.o Drain/S2RYBRUH/*.o -o drain $(LDFLAGS)

.PHONY: clean
clean:
	del $(CUROD)

.PHONY: cleanall
cleanall:
	del $(CUROS)

#-include $(DRAINSRC:.c=.d)
