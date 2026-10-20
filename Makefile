CC: gcc
FLAG: -std=c23 -Wall


debug:
	$(CC) $(FLAG) main.c -o ./main
build:
	$(CC) $(FLAG) -Wall -Werror -DLY_BUILD_MODE main.c -o ./main

.PHONY:
	debug
