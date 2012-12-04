#include <stdio.h>
#include <stdlib.h>
#include "unique.h"

extern struct field field[XMAX][YMAX];

static void printline(int max, struct u_field *line)
{
    int i;

    for (i=0; i<max; i++) {
	printf("%2d ", line[i].value);
    }
    printf("\n");
}

static void makeline(int dir, int linenum, int max, struct u_field *line)
{
    int i;

    for (i=0; i<max; i++) {
	if (hori(dir)) 
	    line[i].value = field[linenum][i].value;
	else
	    line[i].value = field[i][linenum].value;
    }
}

static void restoreline(int dir, int linenum, int max, struct u_field *line)
{
    int i;

    for (i=0; i<max; i++) {
	if (hori(dir))
	    field[linenum][i].value = line[i].value;
	else
	    field[i][linenum].value = line[i].value;
    }
}

static int countempty(int max, struct u_field *line)
{
    int i;
    int empty = 0;

    for (i=0; i<max; i++) {
	if (line[i].value == -1)
	    empty++;
    }
    return empty;
}

static int countcomp(int max, struct u_field *line)
{
    int i;
    int count = 0;

    for (i=0; i<max; i++) {
	if (line[i].comp != -1)
	    count++;
    }
    return count;
}

static void fillcomp(int max, struct u_field *line)
{
    int i;
    for (i=0; i<max; i++) {
	if (line[i].comp != -1)
	    line[i].value = line[i].comp;
    }
}

static int makediff(int max, struct u_field *complete, struct u_field *compare)
{
    int i;

    /* find difference */
    for (i=0; i<max; i++) {
	if ((compare[i].value != -1) && (compare[i].value != complete[i].value))
	    return 0;
    }

    /* fill in the blanks */
    for (i=0; i<max; i++) {
	if (compare[i].value == -1) {
	    compare[i].comp = complete[i].value;
	}
    }
    return 1;
}

static int countnums(int max, int num, struct u_field *line)
{
    int i;
    int count = 0;
    for (i=0; i<max; i++) {
	if (line[i].comp == num)
	    count++;
    }
    return count;
}

static void flipone(int max, struct u_field *line)
{
    int i;

    if (countnums(max, 1, line) == 1) {
	for (i=0; i<max; i++) {
	    if (line[i].comp == 1) {
		line[i].value = 0;
		line[i].comp = -1;
	    }
	}
    }
    if (countnums(max, 0, line) == 1) {
	for (i=0; i<max; i++) {
	    if (line[i].comp == 0) {
		line[i].value = 1;
		line[i].comp = -1;
	    }
	}
    }
}

static int diffline(int max, struct u_field *one, struct u_field *two)
{
    int i;
    int emptyone;
    int emptytwo;
    struct u_field *complete;
    struct u_field *compare;
	
    /* We need at least one filled line */
    emptyone = countempty(max, one);
    emptytwo = countempty(max, two);
    if ((emptyone > 0) && (emptytwo > 0))
	return 0;

    /* For now, only accept one line that is missing three */
    if ((emptyone > 3) || (emptytwo > 3)) {
	printf("not enough data\n");
	return 0;
    }

    if (emptyone > 0) {
	complete = two;
	compare = one;
    } else {
	complete = one;
	compare = two;
    }

    if (!makediff(max, complete, compare))
	return 0;
    
    flipone(max, compare);
    return 1;
}

void check_unique(int dir, int max, int lines)
{
    int i,j;
    int changed = 0;
    struct u_field u_field[lines][max];

    for (i=0; i<lines; i++)
	makeline(dir, i, max, u_field[i]);

    for (i=0; i<lines; i++) {
	for (j=i; j<lines; j++) {
	    changed += diffline(max, u_field[i], u_field[j]);
	}
    }
    if (changed) {
	for (i=0; i<lines; i++)
	    restoreline(dir, i, max, u_field[i]);
    }
}
