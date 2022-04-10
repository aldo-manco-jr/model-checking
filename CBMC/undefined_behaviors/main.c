#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void setVariableOverriden(int *variableToWrite);

void checkUndefinedBehaviors(int *x, int *y, int *z);

int main() {

    __CPROVER_field_decl_local("updating_memory", (_Bool) 0);
    __CPROVER_field_decl_global("updating_memory", (_Bool) 0);

    __CPROVER_field_decl_local("undefined_behaviors", (_Bool) 0);
    __CPROVER_field_decl_global("undefined_behaviors", (_Bool) 0);

    int x = 3;
    int y;
    int z;

    y = (setVariableOverriden(&y), checkUndefinedBehaviors(&x, &y, &z), x);
    z = (setVariableOverriden(&z), checkUndefinedBehaviors(&x, &y, &z), y);
    (x = (setVariableOverriden(&x), x + 1),
            x = (setVariableOverriden(&x), x + 1),
            checkUndefinedBehaviors(&x, &y, &z));

    return 0;
}

void setVariableOverriden(int *variableToWrite) {

    (__CPROVER_get_field(variableToWrite, "updating_memory") == 1
     && __CPROVER_set_field(variableToWrite, "undefined_behaviors", 1)
    );

    (__CPROVER_get_field(variableToWrite, "updating_memory") == 0
     && __CPROVER_set_field(variableToWrite, "updating_memory", 1)
    );
}

void checkUndefinedBehaviors(int *x, int *y, int *z) {

    assert(__CPROVER_get_field(x, "undefined_behaviors") == 0
           && __CPROVER_get_field(y, "undefined_behaviors") == 0
           && __CPROVER_get_field(z, "undefined_behaviors") == 0);

    __CPROVER_set_field(x, "updating_memory", 0);
    __CPROVER_set_field(y, "updating_memory", 0);
    __CPROVER_set_field(z, "updating_memory", 0);

    __CPROVER_set_field(x, "undefined_behaviors", 0);
    __CPROVER_set_field(y, "undefined_behaviors", 0);
    __CPROVER_set_field(z, "undefined_behaviors", 0);
}