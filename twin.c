#include "twin.h"

extern struct field field[XMAX][YMAX];

static int in_twin_grid(int x, int y, int dir)
{
    switch (dir) {
    case 1:
	if ((x >= 0) && (x+1 < XMAX))
	    return 1;
	break;
    case -1:
	if ((x < XMAX) && (x-1 >= 0))
	    return 1;
	break;
    case 12:
	if ((y >= 0) && (y+1 < YMAX))
	    return 1;
	break;
    case -12:
	if ((y < YMAX) && (y-1 >= 0))
	    return 1;
	break;
    }
    return 0;
}

static int in_split_grid(int x, int y, int dir)
{
    switch (dir) {
    case 1:
	if ((x >= 0) && (x+2 < XMAX))
	    return 1;
	break;
    case -1:
	if ((x < XMAX) && (x-2 >= 0))
	    return 1;
	break;
    case 12:
	if ((y >= 0) && (y+2 < YMAX))
	    return 1;
	break;
    case -12:
	if ((y < YMAX) && (y-2 >= 0))
	    return 1;
	break;
    }
    return 0;
}

static int is_twin(int x, int y, int dir)
{
    if (!in_twin_grid(x, y, dir))
	return 0;

    if (field[x][y].value == -1)
	return 0;
    
    switch (dir) {
    case 1:
	if (field[x][y].value == field[x+1][y].value)
	    return 1;
	break;
    case -1:
	if (field[x][y].value == field[x-1][y].value)
	    return 1;
	break;
    case 12:
	if (field[x][y].value == field[x][y+1].value)
	    return 1;
	break;
    case -12:
	if (field[x][y].value == field[x][y-1].value)
	    return 1;
	break;
    }
    return 0;
}

static int is_split(int x, int y, int dir)
{
    if (!in_split_grid(x, y, dir))
	return 0;
    if (field[x][y].value == -1)
	return 0;
    
    switch (dir) {
    case 1:
	if (field[x][y].value == field[x+2][y].value)
	    return 1;
	break;
    case -1:
	if (field[x][y].value == field[x-2][y].value)
	    return 1;
	break;
    case 12:
	if (field[x][y].value == field[x][y+2].value)
	    return 1;
	break;
    case -12:
	if (field[x][y].value == field[x][y-2].value)
	    return 1;
	break;
    }
    return 0;
}

static void bind_twin(int x, int y, int dir)
{
    switch (dir) {
    case 1:
	if (((x < XMAX) && (x > 0)) && (field[x-1][y].value == -1))
	    field[x-1][y].value = !(field[x][y].value);
	break;
    case -1:
	if (((x >= 0) && (x < XMAX-1)) && (field[x+1][y].value == -1))
	    field[x+1][y].value = !(field[x][y].value);
	break;
    case 12:
	if ((y > 0) && (field[x][y-1].value == -1))
	    field[x][y-1].value = !(field[x][y].value);
	break;
    case -12:
	if ((y < YMAX-1) && (field[x][y+1].value == -1))
	    field[x][y+1].value = !(field[x][y].value);
	break;
    }
}

static void split_twin(int x, int y, int dir)
{
    switch(dir) {
    case 1:
	field[x+1][y].value = !(field[x][y].value);
	break;
    case -1:
	field[x-1][y].value = !(field[x][y].value);
	break;
    case 12:
	field[x][y+1].value = !(field[x][y].value);
	break;
    case -12:
	field[x][y-1].value = !(field[x][y].value);
	break;
    }
}

int check_twin(int dir)
{
    int x,y;

    for (y=0; y<YMAX; y++) {
	for (x=0; x<XMAX; x++) {
	    if (is_twin(x, y, dir))
		bind_twin(x, y, dir);
	}
    }
    return 0;
}

int check_split(int dir)
{
    int x,y;
    for (y=0; y<YMAX; y++) {
	for (x=0; x<XMAX; x++) {
	    if (is_split(x, y, dir))
		split_twin(x, y, dir);
	}
    }
    return 0;
}
