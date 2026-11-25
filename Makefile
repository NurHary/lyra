CC:= gcc
DFLAG:= -std=c99 -Wall -Werror
BFLAG:= -std=c99 -DLYC_BUILD_MODE -DNDEBUG

debug:
	$(CC) $(DFLAG) main.c -o ./main
build:
	$(CC) $(BFLAG) main.c -o ./main

.PHONY: debug build
