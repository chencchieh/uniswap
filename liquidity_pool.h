#ifndef LIQUIDITY_POOL_H
#define LIQUIDITY_POOL_H

#include <vector>
#include <map>
#include <string>
#include <stdexcept>

class LiquidityPool {
public:
    LiquidityPool(double reserveA, double reserveB);

    double getPrice(std::string token) const;
    void addLiquidity(double amountA, double amountB);
    void removeLiquidity(double amountA, double amountB);
    double getLiquidity(std::string token) const;
    void swap(std::string token, double amount);

private:
    std::map<std::string, double> reserves_;
    const std::string TOKEN_A = "ETH";
    const std::string TOKEN_B = "DAI";
    const double FEES = 0.003;
};

#endif // LIQUIDITY_POOL_H