#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int setVariable(int *variableToWrite, int *variableToRead);

int setVariableExpression(int *variableToWrite, int *variableToRead);

int main() {

    __CPROVER_field_decl_local("is_dependent", (_Bool) 0);
    __CPROVER_field_decl_global("is_dependent", (_Bool) 0);

    int x = 3;
    int y;
    int z;

    __CPROVER_set_field(&x, "is_dependent", 1);

    y = (setVariableExpression(&y, &x), x);
    z = (setVariableExpression(&z, &y), y);

    assert(!__CPROVER_get_field(&y, "is_dependent") && !__CPROVER_get_field(&z, "is_dependent"));

    return 0;
}

int setVariableExpression(int *variableToWrite, int *variableToRead) {

    (__CPROVER_get_field(variableToRead, "is_dependent") == 1
               && __CPROVER_set_field(variableToWrite, "is_dependent", 1)
    );
}