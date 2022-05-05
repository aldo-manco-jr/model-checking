#include <stdio.h>

__CPROVER_bitvector[1] nonDeterministicNumber();

__CPROVER_bitvector[1] nondet_1;
__CPROVER_bitvector[1] nondet_2;
__CPROVER_bitvector[1] nondet_3;
__CPROVER_bitvector[1] nondet_4;
__CPROVER_bitvector[1] nondet_5 = nonDeterministicNumber();
__CPROVER_bitvector[1] nondet_6 = nonDeterministicNumber();
__CPROVER_bitvector[1] nondet_7 = nonDeterministicNumber();

int main() {

    nondet_2 = nondet_1;

    unsigned __CPROVER_bitvector[4] num, fact=1;

    printf("\n Factorial of ");
    scanf("%i", &num);

    if(nondet_2){

        for(int i=1; i<=3; i++)
            fact=fact*i;

        printf("\n %u", fact);
    }

    assert(!nondet_2);

    return 0;
}