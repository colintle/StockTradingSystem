#include "trader.h"

namespace StockTradingSystem
{
    Trader::Trader(const std::string& name):
    name_{name}
    {}

    std::string Trader::getName() const
    {
        return name_;
    }
}