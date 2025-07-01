#ifndef STOCK_TRADING_ORDERBOOK_H
#define STOCK_TRADING_ORDERBOOK_H

#include "order.h"
#include "orderMatchStrategy.h"
#include <vector>
#include <iostream>

namespace StockTradingSystem
{
    class OrderBook
    {
        public:
            OrderBook(OrderMatchingStrategy* strategy);
            void addOrder(Order order);
            void matchOrders();
            void printOrderBook() const;
            void setStrategy(OrderMatchingStrategy* strategy);
        private:
            std::vector<Order> book_;
            OrderMatchingStrategy* strategy_;
    };
}

#endif