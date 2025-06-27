#ifndef STOCK_TRADING_TRADER_H
#define STOCK_TRADING_TRADER_H

#include <string>

namespace StockTradingSystem
{
    class Trader
    {
        public:
            Trader(const std::string&);
            std::string getName() const;
        private:
            std::string name_;
    };
}
#endif