#ifndef STOCK_TRADING_CONSTANTS_H
#define STOCK_TRADING_CONSTANTS_H

#include <limits>
#include "usings.h"

namespace StockTradingSystem
{
    struct Constants
    {
        static const Price InvalidPrice = std::numeric_limits<Price>::quiet_NaN();
    };
}

#endif