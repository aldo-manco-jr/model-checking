#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

__CPROVER_bitvector[10] generateNonDeterministicFloatNumbers();
__CPROVER_bitvector[2] generateNonDeterministicNumbers();

int main(int argc, char *argv[]) {

    puts("--- LOGARITHMIC MANCO MODEL FOR MONEY MANAGEMENT ---\n");

    float positiveTransactions = 1, totalTransactions = 1, amountGained = 1, amountLost = 1, depthMantissa = 5, stopLossPips, centroid = 50000, equity = 50000, zetaValue = 0.8, lowerOmegaValue = 0.8, upperOmegaValue = 0.8, lambdaValue = 0.3, optimalRiskDivisor = 0;

    float repulsor = zetaValue * centroid;
    float attractor = 2 * zetaValue * centroid;
    float startingPrice = lowerOmegaValue * centroid;
    float endingPrice = upperOmegaValue * attractor;

    __CPROVER_bitvector[10] arrayStopLossTrades[9]={0};
    __CPROVER_bitvector[2] arrayWinLoss[9]={0};

    for (unsigned __CPROVER_bitvector[4] i = 0; i < 8; ++i) {

        if (arrayWinLoss[i] == 0) {
            arrayWinLoss[i] = generateNonDeterministicNumbers();
            __VERIFIER_assume(arrayWinLoss[i]==-1 || arrayWinLoss[i]==1);
        }

        if (arrayStopLossTrades[i] == 0) {
            arrayStopLossTrades[i] = generateNonDeterministicFloatNumbers();
            __VERIFIER_assume(arrayStopLossTrades[i]>=20 && arrayStopLossTrades[i]<=900);

            float probabilityWin = positiveTransactions / totalTransactions;

            //float takeProfitPips = ((takeProfit*10000)-(openingPrice*10000)+0.00005)>=0 ? (takeProfit*10000)-(openingPrice*10000)+0.00005 : ((takeProfit*10000)-(openingPrice*10000)+0.00005)*-1;
            //float stopLossPips = ((openingPrice*10000)-(stopLoss*10000)+0.00005)>=0 ? (openingPrice*10000)-(stopLoss*10000)+0.00005 : ((openingPrice*10000)-(stopLoss*10000)+0.00005)*-1;
            float ratioWinLoss = amountGained / amountLost;

            // kelly criterion
            float aggressiveRisk = ((probabilityWin * ratioWinLoss) - (1 - probabilityWin)) / (ratioWinLoss);
            float conservativeRisk = aggressiveRisk * 0.5;
            float customRisk = aggressiveRisk * optimalRiskDivisor;

            float startingLevelRiskConservative = conservativeRisk * startingPrice;
            float startingLevelOffsetConservative = (attractor - startingPrice) * conservativeRisk;
            float offsetConservative = startingLevelRiskConservative - startingLevelOffsetConservative;

            float startingLevelRiskAggressive = aggressiveRisk * startingPrice;
            float startingLevelOffsetAggressive = (attractor - startingPrice) * aggressiveRisk;
            float offsetAggressive = startingLevelRiskAggressive - startingLevelOffsetAggressive;

            float startingLevelRiskCustom = customRisk * startingPrice;
            float startingLevelOffsetCustom = (attractor - startingPrice) * customRisk;
            float offsetCustom = startingLevelRiskCustom - startingLevelOffsetCustom;

            float maximumLossAmountConservative =
                    (conservativeRisk * (attractor - (lambdaValue * equity) - ((1 - lambdaValue) * centroid))) +
                    offsetConservative;
            float maximumLossAmountAggressive =
                    (aggressiveRisk * (attractor - (lambdaValue * equity) - ((1 - lambdaValue) * centroid))) + offsetAggressive;
            float maximumLossAmountCustom =
                    (customRisk * (attractor - (lambdaValue * equity) - ((1 - lambdaValue) * centroid))) + offsetCustom;

            float epsilon = 1 / pow(10, 3);

            // manco logarithmic model of money management
            float lotsConservative =
                    ((conservativeRisk * (attractor - (lambdaValue * equity) - ((1 - lambdaValue) * centroid))) +
                     offsetConservative) / (100000 * epsilon * stopLossPips);
            float lotsAggressive = ((aggressiveRisk * (attractor - (lambdaValue * equity) - ((1 - lambdaValue) * centroid))) +
                                     offsetAggressive) / (100000 * epsilon * stopLossPips);
            float lotsCustom =
                    ((customRisk * (attractor - (lambdaValue * equity) - ((1 - lambdaValue) * centroid))) + offsetCustom) /
                    (100000 * epsilon * stopLossPips);

            float lotsConservativeRounded = (lotsConservative * 100) / 100;
            float lotsAggressiveRounded = (lotsAggressive * 100) / 100;
            float lotsCustomRounded = (lotsCustom * 100) / 100;

            if(arrayWinLoss[i]==1){
                positiveTransactions++;
                amountGained+=arrayStopLossTrades[i];
            } else if(arrayWinLoss[i]==-1){
                amountLost+=arrayStopLossTrades[i];
            }

            totalTransactions++;

            equity = equity+(100000*lotsConservative*arrayStopLossTrades[i])*arrayWinLoss[i];
            assert(equity>=startingPrice);
        }
    }

    return 0;
}