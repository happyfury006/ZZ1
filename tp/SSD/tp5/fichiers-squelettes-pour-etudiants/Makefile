CFILES = $(wildcard *.c)
HFILES = $(wildcard *.h)
OFILES = $(patsubst %.c,%.o,$(CFILES))
COMPILER_FLAGS = -Wall
LD_FLAGS =

all: main

%.o: %.c $(HFILES)
	gcc $(COMPILER_FLAGS) -c $<

main: $(OFILES) $(HFILES)
	gcc $(LD_FLAGS) -o main $(OFILES)

clean:
	-rm *.o main
