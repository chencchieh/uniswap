#ifndef ARBITRAGE_H
#define ARBITRAGE_H

#include "liquidity_pool.h"
#include <string>

class Arbitrage {
public:
    Arbitrage(LiquidityPool& poolA, LiquidityPool& poolB);
    double executeArbitrage() const;

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

#endif // ARBITRAGE_H