#ifndef BINARY_H
#define BINARY_H

#define XMAX 12
#define YMAX 12

struct field {
    int value;
    int initial;
};

int get_left(void);
int is_solved(void);

#endif /* BINARY_H */
