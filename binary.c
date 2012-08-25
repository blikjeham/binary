/* binary.c
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "binary.h"

extern struct field field[XMAX][YMAX];

void init_link(struct field *f)
{
    f->link.x = -1;
    f->link.y = -1;
}

void init_field(int x, int y, int value)
{
    field[x][y].value = value;
    field[x][y].initial = (value == -1 ? 0 : 1);
    field[x][y].link.x = -1;
    field[x][y].link.y = -1;
}

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
