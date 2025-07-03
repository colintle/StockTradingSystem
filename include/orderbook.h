#ifndef STOCK_TRADING_ORDERBOOK_H
#define STOCK_TRADING_ORDERBOOK_H

#include "order.h"
#include "orderModify.h"
#include "trade.h"
#include <map>
#include <unordered_map>

namespace StockTradingSystem
{
    class Orderbook
    {
        public:
            Trades addOrder(OrderPointer order);
            void cancelOrder(OrderId orderId);
            Trades modifyOrder(OrderModify order);
        private:
            struct OrderEntry
            {
                OrderPointer order_{nullptr};
                OrderPointers::iterator location_;
            };
            // lowest ask is first (best buy order)
            std::map<Price, OrderPointers, std::less<Price>> asks_;
            // highest bid is first (best sell order)
            std::map<Price, OrderPointers, std::greater<Price>> bids_;
            std::unordered_map<OrderId, OrderEntry> orders_;
            bool canMatch(Side side, Price price) const;
            Trades matchOrders();
    };
}

#endif