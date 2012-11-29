#ifndef BINARY_H
#define BINARY_H

#define XMAX 12
#define YMAX 12

#define hori(a) (a == 1 || a == -1 ? 1 : 0)

struct link {
    int x;
    int y;
};

struct field {
    short int value;
    short int initial;
    struct link link;
};

void init_link(struct field *);
void init_field(int , int , int );
int get_left(void);
int is_solved(void);
void set_value(struct field *, int );
#define set_link(a,b,link) (link->x = a; link->y = b)
#define get_link(link) (link.x != -1 || link.y != -1 ? 1 : 0)

#endif /* BINARY_H */
