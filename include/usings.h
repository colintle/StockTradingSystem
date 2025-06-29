#ifndef STOCK_TRADING_USINGS_H
#define STOCK_TRADING_USINGS_H

#include <vector>
#include <cstdint>

namespace StockTradingSystem
{
    // + or -
    using Price = std::int32_t;
    // +
    using Quantity = std::uint32_t;
    using OrderId = std::uint64_t;
    using OrderId = std::vector<OrderId>;
}

#endif