#ifndef UNIQUE_H
#define UNIQUE_H

#include "binary.h"

/* field for checking uniqueness */
struct u_field {
    short int value;
    short int comp;
};

void check_unique(int , int , int );

#endif /* UNIQUE_H */
