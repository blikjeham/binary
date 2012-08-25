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

struct field field[XMAX][YMAX];
int solved;

int readfield(char *filename)
{
    FILE *fd;
    int x,y;
    char number;
    
    if (!(fd = fopen(filename, "r")))
	return 1;

    printf("Reading file\n");
    
    for (y=0; y<YMAX; y++) {
	for (x=0; x<XMAX; x++) {
	    number = fgetc(fd);
	    switch(number) {
	    case '0':
		field[x][y].value = 0;
		field[x][y].initial = 1;
		break;
	    case '1':
		field[x][y].value = 1;
		field[x][y].initial = 1;
		break;
	    default:
		field[x][y].value = -1;
		field[x][y].initial = 0;
		break;
	    }
	}
    }

    fclose(fd);
    return 0;
}

static void printfield(void)
{
    int x,y;
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
	printf("left = %d\tdir = %d\n", left, dir);
	
	check_twin(dir);
	printfield();
	check_split(dir);
	printfield();
	solved = is_solved();
    }
    return 0;
}