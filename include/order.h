#ifndef STOCK_TRADING_ORDER_H
#define STOCK_TRADING_ORDER_H

#include "trader.h"
#include "side.h"
#include "usings.h"
#include "orderType.h"
#include <ctime>
#include <iostream>
#include <format>

namespace StockTradingSystem
{
    class Order
    {
        public:
            Order(Trader& trader, Price price, Quantity quantity, Side side, OrderType orderType);
            Trader getTrader() const;
            Price getPrice() const;
            Quantity getQuantity() const;
            OrderType getOrderType() const;
            std::time_t getTimestamp() const;
            Side getSide() const; 
        private:
            Trader trader_;
            Price price_;
            Quantity quantity_;
            OrderType orderType_;
            std::time_t timestamp_;
            Side side_;
    };
}

#endif