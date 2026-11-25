CC: gcc
FLAG: -std=c99 -Wall


debug:
	$(CC) $(FLAG) main.c -o ./main
build:
	$(CC) $(FLAG) -Wall -Werror -DLY_BUILD_MODE -DNDEBUG main.c -o ./main

.PHONY:
	debug
