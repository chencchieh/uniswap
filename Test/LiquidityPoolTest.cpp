#include "gtest/gtest.h"
#include "../uniswap/LiquidityPool.cpp"

// Test fixture for the LiquidityPool class
class LiquidityPoolTest : public ::testing::Test {
protected:
    LiquidityPoolTest() : pool_(100.0, 1000.0) {}

    LiquidityPool pool_;
};

// Test the getPrice() method for ETH
TEST_F(LiquidityPoolTest, GetPriceETH) {
    EXPECT_NEAR(pool_.getPrice("ETH"), 10.0, 0.001);
}

// Test the getPrice() method for DAI
TEST_F(LiquidityPoolTest, GetPriceDAI) {
    EXPECT_NEAR(pool_.getPrice("DAI"), 0.1, 0.001);
}

// Test adding liquidity
TEST_F(LiquidityPoolTest, AddLiquidity) {
    pool_.addLiquidity(10.0, 100.0);
    EXPECT_NEAR(pool_.getLiquidity("ETH"), 110.0, 0.001);
    EXPECT_NEAR(pool_.getLiquidity("DAI"), 1100.0, 0.001);
}

// Test removing liquidity
TEST_F(LiquidityPoolTest, RemoveLiquidity) {
    pool_.removeLiquidity(10.0, 100.0);
    EXPECT_NEAR(pool_.getLiquidity("ETH"), 90.0, 0.001);
    EXPECT_NEAR(pool_.getLiquidity("DAI"), 900.0, 0.001);
}

// Test removing more liquidity than provided
TEST_F(LiquidityPoolTest, RemoveLiquidityExceedsProvided) {
    EXPECT_THROW(pool_.removeLiquidity(110.0, 1100.0), std::logic_error);
}

// Test adding liquidity when one or both reserves are zero
TEST_F(LiquidityPoolTest, AddLiquidityZeroReserves) {
    LiquidityPool zero_pool(0.0, 0.0);
    zero_pool.addLiquidity(10.0, 100.0);
    EXPECT_NEAR(zero_pool.getLiquidity("ETH"), 10.0, 0.001);
    EXPECT_NEAR(zero_pool.getLiquidity("DAI"), 100.0, 0.001);
}

// Test removing liquidity when one or both reserves become zero
TEST_F(LiquidityPoolTest, RemoveLiquidityZeroReserves) {
    LiquidityPool zero_pool(10.0, 100.0);
    zero_pool.removeLiquidity(10.0, 100.0);
    EXPECT_NEAR(zero_pool.getLiquidity("ETH"), 0.0, 0.001);
    EXPECT_NEAR(zero_pool.getLiquidity("DAI"), 0.0, 0.001);
}

// Test getPrice() with an invalid token
TEST_F(LiquidityPoolTest, InvalidToken) {
    EXPECT_THROW(pool_.getPrice("invalid"), std::invalid_argument);
}

TEST_F(LiquidityPoolTest, SwapETHToken) {
    pool_.swap("ETH", 3.0);

    EXPECT_NEAR(pool_.getLiquidity("ETH"), 103.009, 0.001);
    EXPECT_NEAR(pool_.getLiquidity("DAI"), 970, 0.001);
}

TEST_F(LiquidityPoolTest, SwapDAIToken) {
    pool_.swap("DAI", 150.0);

    EXPECT_NEAR(pool_.getLiquidity("ETH"), 85.045, 0.001);
    EXPECT_NEAR(pool_.getLiquidity("DAI"), 1150, 0.001);
}

TEST_F(LiquidityPoolTest, InvalidSwap) {
    EXPECT_THROW(pool_.swap("USDT", 10.0), std::invalid_argument);
}