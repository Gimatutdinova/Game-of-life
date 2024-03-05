gcc = gcc  
flags = -Werror -Wall -Wextra -std=c11
files = *.c
out_file = game_of_life

ifeq ($(shell uname -s), Linux)
	flags += -std=gnu99
endif

all: game_of_life

game_of_life:
	$(gcc) $(flags) $(files) -o $(out_file) -lncurses
	
clean:
	-rm $(out_file)

rebuild:
	make clean
	make all