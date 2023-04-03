#include <vector>
#include <map>
#include <string>
#include <stdexcept>

class LiquidityPool {
public:
    LiquidityPool(double reserveA, double reserveB) {
        reserves_[TOKEN_A] = reserveA;
        reserves_[TOKEN_B] = reserveB;
    }

    double getPrice(std::string token) const {
        if (token != TOKEN_A && token != TOKEN_B) {
            throw std::invalid_argument("Invalid token");
        }

        double reserveA = reserves_.at(TOKEN_A);
        double reserveB = reserves_.at(TOKEN_B);

        if (reserveA == 0 || reserveB == 0) {
            throw std::logic_error("Cannot calculate price, one or both reserves are zero");
        }

        if (token == TOKEN_A) {
            return reserveB / reserveA;
        }
        else {
            return reserveA / reserveB;
        }
    }

    void addLiquidity(double amountA, double amountB) {
        double reserveA = reserves_[TOKEN_A];
        double reserveB = reserves_[TOKEN_B];

        if (reserveA == 0 || reserveB == 0) {
            // Special case for adding liquidity when one or both reserves are zero
            reserves_[TOKEN_A] = amountA;
            reserves_[TOKEN_B] = amountB;
        }
        else {
            reserves_[TOKEN_A] = reserveA + amountA;
            reserves_[TOKEN_B] = reserveB + amountB;
        }
    }

    void removeLiquidity(double amountA, double amountB) {
        double reserveA = reserves_[TOKEN_A];
        double reserveB = reserves_[TOKEN_B];

        if (amountA > reserveA || amountB > reserveB) {
            throw std::logic_error("Insufficient liquidity");
        }

        double new_reserveA = reserveA - amountA;
        double new_reserveB = reserveB - amountB;

        if (new_reserveA == 0 || new_reserveB == 0) {
            // Special case for removing liquidity when one or both reserves become zero
            reserves_[TOKEN_A] = 0;
            reserves_[TOKEN_B] = 0;
        }
        else {
            reserves_[TOKEN_A] = new_reserveA;
            reserves_[TOKEN_B] = new_reserveB;
        }
    }

    double getLiquidity(std::string token) const {
        if (token != TOKEN_A && token != TOKEN_B) {
            throw std::invalid_argument("Invalid token");
        }

        return reserves_.at(token);
    }

    void swap(std::string token, double amount) {
        if (token != TOKEN_A && token != TOKEN_B) {
            throw std::invalid_argument("Invalid token");
        }

        double reserveA = reserves_[TOKEN_A];
        double reserveB = reserves_[TOKEN_B];

        double currentPrice = getPrice(TOKEN_A);

        if (token == TOKEN_A) {
            //Swap from ETH to DAI
            reserves_[TOKEN_A] = reserveA + (1 + FEES) * amount;
            reserves_[TOKEN_B] = reserveB - amount * currentPrice;
        }
        else {
            //Swap from DAI to ETH
            reserves_[TOKEN_A] = reserveA - (1 - FEES) * amount / currentPrice;
            reserves_[TOKEN_B] = reserveB + amount;
        }
    }

private:
    std::map<std::string, double> reserves_;
    const std::string TOKEN_A = "ETH";
    const std::string TOKEN_B = "DAI";
    const double FEES = 0.003;
};