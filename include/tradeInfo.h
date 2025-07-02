#ifndef STOCK_TRADING_TRADE_INFO_H
#define STOCK_TRADING_TRADE_INFO_H

#include "usings.h"

namespace StockTradingSystem
{
    struct TradeInfo
    {
        OrderId orderId_;
        Price price_;
        Quantity quantity_;
    };
}

#endif