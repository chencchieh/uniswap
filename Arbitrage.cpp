#include "liquidity_pool.h"

class Arbitrage {
public:
    Arbitrage(LiquidityPool& poolA, LiquidityPool& poolB) : poolA(poolA), poolB(poolB) {
        poolACurrentPrice = poolA.getPrice(TOKEN_A);
        poolBCurrentPrice = poolB.getPrice(TOKEN_A);
    }

    double executeArbitrage() const {
        double profit;
        double sellTokenA;
        double buyBackTokenA;
        if (poolACurrentPrice / poolBCurrentPrice > 1.006) {
            poolA.swap(TOKEN_A, TOKEN_A_AMOUNT);
            sellTokenA = TOKEN_A_AMOUNT * poolACurrentPrice;
            buyBackTokenA = TOKEN_A_AMOUNT * poolBCurrentPrice;
            poolB.swap(TOKEN_B, buyBackTokenA);
        }
        else {
            poolB.swap(TOKEN_A, TOKEN_A_AMOUNT);
            sellTokenA = TOKEN_A_AMOUNT * poolBCurrentPrice;
            buyBackTokenA = TOKEN_A_AMOUNT * poolACurrentPrice;
            poolA.swap(TOKEN_B, buyBackTokenA);
        }

        profit = (1 - FEES) * (sellTokenA - buyBackTokenA);

        return profit;
    }

private:
    LiquidityPool& poolA;
    LiquidityPool& poolB;
    double poolACurrentPrice;
    double poolBCurrentPrice;
    const std::string TOKEN_A = "ETH";
    const std::string TOKEN_B = "DAI";
    const double TOKEN_A_AMOUNT = 2.0;
    const double FEES = 0.003;
};