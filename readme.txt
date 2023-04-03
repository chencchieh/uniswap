This Project is consist of Two main cpp files: LiquidityPool.cpp and Arbitrage.cpp

LiquidityPool.cpp :

1. getPrice(string token) which return the price of that token in this liquidity pool.
2. addLiquidity(double amountA, double amountB) which add the liquidity for both relevant coins into this liquidity pool. (amountB / amountA must be same as the price)
3. removeLiquidity(double amountA, double amountB) which remove the liquidity for both relevant coins from this liquidity pool. (amountB / amount A must be same as the price)
4. getLiquidity(string token) which return the liquidity of that token from this liquidity pool.
5. swap(string token, double amount) which swap the token by amount to another token. At the same time, updating the liquidity pool reserves. Eg. token is ETH and amount is 2.0, swap from 2 ETH to 2 * currentPrice DAI.

Arbitrage.cpp :

1. executeArbitrage() which return the profit of that arbitrage in terms of DAI by swapping either of the liquidity pools and updating both liquidity pools.