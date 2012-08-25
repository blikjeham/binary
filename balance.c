#include "balance.h"

extern struct field field[XMAX][YMAX];

static void resetline(struct line *line)
{
    line->zero = 0;
    line->one = 0;
    line->empty = -1;
    line->num = 0;
}

static void countline(int i, int dir, struct line *line)
{
    int j;
    switch (dir) {
    case 1:
    case -1:
	for (j=0; j<XMAX; j++) {
	    switch (field[j][i].value) {
	    case 0:
		line->zero++;
		line->num++;
		break;
	    case 1:
		line->one++;
		line->num++;
		break;
	    case -1:
		line->empty = j;
		break;
	    }
	}
	break;
    case 12:
    case -12:
	for (j=0; j<YMAX; j++) {
	    switch (field[i][j].value) {
	    case 0:
		line->zero++;
		line->num++;
		break;
	    case 1:
		line->one++;
		line->num++;
		break;
	    case -1:
		line->empty = j;
		break;
	    }
	}
	break;
    }
}

void check_balance(int dir)
{
    int i;
    struct line line;

    switch (dir) {
    case 1:
    case -1:
	for (i=0; i<YMAX; i++) {
	    resetline(&line);
	    countline(i, dir, &line);
	    if (line.num != XMAX) {
		if ((line.zero == XMAX/2) && (line.empty > -1))
		    field[line.empty][i].value = 1;
		if ((line.one == XMAX/2) && (line.empty > -1))
		    field[line.empty][i].value = 0;
	    }
	}
	break;
    case 12:
    case -12:
	for (i=0; i<XMAX; i++) {
	    resetline(&line);
	    countline(i, dir, &line);
	    if (line.num != YMAX) {
		if ((line.zero == YMAX/2) && (line.empty > -1))
		    field[i][line.empty].value = 1;
		if ((line.one == YMAX/2) && (line.empty > -1))
		    field[i][line.empty].value = 0;
	    }
	}
	break;
    }
}
