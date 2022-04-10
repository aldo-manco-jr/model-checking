#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define CARDINALITY_ROUND 5
#define CARDINALITY_THREAD 2

int threadsProgramCounter[CARDINALITY_THREAD] = {0, 0};

int canSwitchContext(int, int);

int generateNonDeterministicIndexStatement(int, int);

int chooseThread(int);

int main() {

    bool arrayActivationStateThreads[CARDINALITY_THREAD] = {true, false};
    int lineStatementContextSwitch = generateNonDeterministicIndexStatement();

    for (int round = 0; round < CARDINALITY_ROUND; round++) {
        for (int i = 0; i < CARDINALITY_THREAD; ++i) {
            if (arrayActivationStateThreads[i]) {
                lineStatementContextSwitch = generateNonDeterministicIndexStatement(34, 9);
            }
        }
    }
    return 0;
}

void canSwitchContext(int threadChosen, int lineToCheck, int nextContextSwitch){
    if(lineToCheck<threadsProgramCounter[threadChosen] || lineToCheck>=nextContextSwitch){
        goto threadsProgramCounter[threadChosen]+1;
    }
}

int generateNonDeterministicIndexStatement(int lineStart, int cardinalityStatement) {
    srand(time(NULL));
    return (rand() % cardinalityStatement) + lineStart;
}

int chooseThread(int threadChosen, int lineStatementNextContextSwitch, int lineStart, int cardinalityStatement) {

    int c = 0;
    double d = 0;

    switch (threadChosen) {
        case 1:
            canSwitchContext(threadChosen, 51, 54);
            c++;
            c++;
            c++;
            c++;
            c++;
            c++;
            c++;
            c++;
            c++;
            c++;
            return c;
        case 2:
            d += 0.3;
            d += 0.3;
            d += 0.3;
            d += 0.3;
            d += 0.3;
            d += 0.3;
            d += 0.3;
            d += 0.3;
            d += 0.3;
            d += 0.3;
            return d;
    }


}