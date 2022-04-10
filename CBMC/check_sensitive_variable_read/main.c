#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>


int getVariable(int x);

void setVariable(int x, int value);


int main() {

    __CPROVER_field_decl_local("read", (_Bool) 0);
    __CPROVER_field_decl_global("read", (_Bool) 0);

    __CPROVER_field_decl_local("written", (_Bool) 0);
    __CPROVER_field_decl_global("written", (_Bool) 0);

    int x;
    setVariable(x, 3);

    int y;
    setVariable(y, getVariable(x));
}

int getVariable(int variable) {
    __CPROVER_set_field(&variable, "read", (_Bool) 1);
    return variable;
}

void setVariable(int variable, int value) {
    variable = value;
    __CPROVER_set_field(&variable, "written", (_Bool) 1);
}