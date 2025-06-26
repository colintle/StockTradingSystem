#ifndef STOCK_TRADING_TRADER_H
#define STOCK_TRADING_TRADER_H

#include <string>

namespace StockTradingSystem
{
    class Trader
    {
        public:
            Trader(const std::string&);
        private:
            std::string name_;
    };
}
#endif