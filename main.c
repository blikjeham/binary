/*
 * main.c
 *
 * Main file for binary puzzle solver.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "binary.h"
#include "twin.h"
#include "balance.h"
#include "unique.h"

struct field field[XMAX][YMAX];
int solved;

int readfield(char *filename)
{
    FILE *fd;
    int x,y;
    char number;
    int value;
	
    if (!(fd = fopen(filename, "r")))
	return 1;

    for (y=0; y<YMAX; y++) {
	for (x=0; x<XMAX; x++) {
	    number = fgetc(fd);
	    switch (number) {
	    case '0': value = 0; break;
	    case '1': value = 1; break;
	    case '.': value = -1; break;
	    default:
		x--;
		if (x<0) {
		    x = XMAX-1;
		    y--;
		    if (y<0) y = 0;
		}
		break;
	    }
	    init_field(x, y, value);
	}
    }

    fclose(fd);
    return 0;
}

static void printfield(void)
{
    int x,y;
    for (x=0; x<XMAX; x++) {
	printf("--");
    }
    printf("\n");
    for (y=0; y<YMAX; y++) {
	for (x=0; x<XMAX; x++) {
	    if ((field[x][y].value == 1) || (field[x][y].value == 0))
		printf("%d", field[x][y].value);
	    else
		printf(" ");

	    if (field[x][y].initial)
		printf(".");
	    else
		printf(" ");
	}
	printf("|\n");
    }
    for (x=0; x<XMAX; x++) {
	printf("--");
    }
    printf("\n");

}

static int switch_dir(int dir)
{
    switch(dir) {
    case 1:
	return -1;
    case -1:
	return 12;
    case 12:
	return -12;
    case -12:
	return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int dir = 1;
    int left = 0;
    solved = 0;
    if (readfield("binary.field"))
	exit(1);
    printfield();
    while (!solved) {
	left = get_left();
	dir = switch_dir(dir);
	printf("left = %d\n", left);
	printf("check_twin(%d)\n", dir);
	check_twin(dir);
	printfield();
	printf("check_split(%d)\n", dir);
	check_split(dir);
	printfield();
	printf("check_balance(%d)\n", dir);
	if (hori(dir)) {
	    check_balance(dir, YMAX);
	    check_unique(dir, YMAX, XMAX);
	} else {
	    check_balance(dir, XMAX);
	    check_unique(dir, XMAX, YMAX);
	}
	printfield();
	solved = is_solved();
    }
    return 0;
}
