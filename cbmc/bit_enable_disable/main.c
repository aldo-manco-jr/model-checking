#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int setVariableExpression(int *variableToWrite, int *variableToRead);

int main() {

    __CPROVER_field_decl_local("is_dependent", (_Bool) 0);
    __CPROVER_field_decl_global("is_dependent", (_Bool) 0);

    __CPROVER_bitvector[1] a;
    __CPROVER_bitvector[1] b;
    __CPROVER_bitvector[1] c=0;
    /*__CPROVER_bitvector[1]
    __CPROVER_bitvector[1] e;
    __CPROVER_bitvector[1] f;
    __CPROVER_bitvector[1] g;
    __CPROVER_bitvector[1] h;
    __CPROVER_bitvector[1] i;
    __CPROVER_bitvector[1] j;
    __CPROVER_bitvector[1] k;
    __CPROVER_bitvector[1] l;
    __CPROVER_bitvector[1] m;
    __CPROVER_bitvector[1] n;
    __CPROVER_bitvector[1] o;
    __CPROVER_bitvector[1] p;*/

    int x = 3;
    int y;
    int z;

    __CPROVER_set_field(&x, "is_dependent", 1);

    y = (setVariableExpression(&y, &x), x);
    z = (setVariableExpression(&z, &y), y);

    //assert(!__CPROVER_get_field(&y, "is_dependent") && !__CPROVER_get_field(&z, "is_dependent"));
    __CPROVER_assert((a||b)||c, "unsat");

    return 0;
}

int setVariableExpression(int *variableToWrite, int *variableToRead) {

    (__CPROVER_get_field(variableToRead, "is_dependent") == 1
     && __CPROVER_set_field(variableToWrite, "is_dependent", 1)
    );
}