#include "../uniswap/Arbitrage.cpp"
#include <gtest/gtest.h>

// Test that arbitrage returns a positive value when there is an opportunity for profit
TEST(ArbitrageTest, TestExecuteArbitragePositiveProfit) {
    LiquidityPool poolA(1000, 2000);
    LiquidityPool poolB(2000, 1000);
    Arbitrage arbitrage(poolA, poolB);

    double profit = arbitrage.executeArbitrage();

    ASSERT_GT(profit, 0);
}

// Test that arbitrage returns zero when there is no opportunity for profit
TEST(ArbitrageTest, TestExecuteArbitrageNoProfit) {
    LiquidityPool poolA(1000, 1000);
    LiquidityPool poolB(1000, 1000);
    Arbitrage arbitrage(poolA, poolB);

    double profit = arbitrage.executeArbitrage();

    ASSERT_EQ(profit, 0);
}