#ifndef STOCK_TRADING_LEVEL_INFO_H
#define STOCK_TRADING_LEVEL_INFO_H

#include "usings.h"

namespace StockTradingSystem
{
    // Each level represents the quantity of shares or contracts available for purchase or sale at that particular price.
    struct Level
    {
        Price price_;
        Quantity quantity;
    };

    using Levels = std::vector<Level>;
}

#endif