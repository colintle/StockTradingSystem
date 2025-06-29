#ifndef STOCK_TRADING_ORDER_H
#define STOCK_TRADING_ORDER_H

#include "trader.h"
#include "side.h"
#include <ctime>
#include <iostream>
#include <format>

namespace StockTradingSystem
{
    class Order
    {
        public:
            Order(Trader& trader, double price, int quantity, Side side);
            Trader getTrader() const;
            double getPrice() const;
            int getQuantity() const;
            std::time_t getTimestamp() const;
            Side getSide() const;
            bool reduceQuantity(int quantity);
        private:
            Trader trader_;
            double price_;
            int quantity_;
            std::time_t timestamp_;
            Side side_;
    };
}

#endif