#ifndef STOCK_TRADING_ORDER_H
#define STOCK_TRADING_ORDER_H

#include "trader.h"
#include <ctime>

namespace StockTradingSystem
{
    enum OrderType {BUY, SELL};

    class Order
    {
        public:
            Order(Trader& trader, double price, int quantity, OrderType ordertype);
            Trader getTrader() const;
            double getPrice() const;
            int getQuantity() const;
            std::time_t getTimestamp() const;
            OrderType getOrdertype() const;
        private:
            Trader trader_;
            double price_;
            int quantity_;
            std::time_t timestamp_;
            OrderType ordertype_;
    };
}

#endif