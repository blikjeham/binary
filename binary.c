/* binary.c
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "binary.h"

extern struct field field[XMAX][YMAX];

int get_left(void)
{
    int count=0;
    int x,y;
    for (y=0; y<YMAX; y++) {
	for (x=0; x<XMAX; x++) {
	    if (field[x][y].value == -1)
		count++;
	}
    }
    return count;
}

int is_solved(void)
{
    int x,y;
    for (y=0; y<YMAX; y++) {
	for (x=0; x<XMAX; x++) {
	    if (field[x][y].value == -1)
		return 0;
	}
    }
    return 1;
}

