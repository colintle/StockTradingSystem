#ifndef STOCK_TRADING_ORDERBOOK_H
#define STOCK_TRADING_ORDERBOOK_H

#include "order.h"
#include "orderModify.h"
#include "orderbookLevels.h"
#include "trade.h"

#include <map>
#include <numeric>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace StockTradingSystem
{
    class Orderbook
    {
        public:

            Orderbook();
            // copy constuctor
            Orderbook(const Orderbook&) = delete;
            // copy assignment
            void operator=(const Orderbook&) = delete;
            // move constructor
            Orderbook(Orderbook&&) = delete;
            // move assignment
            void operator=(Orderbook&&) = delete;
            // deconstructor 
            ~Orderbook();

            Trades addOrder(OrderPointer order);
            void cancelOrder(OrderId orderId);
            Trades modifyOrder(OrderModify order);
            std::size_t size() const;
            OrderBookLevels getOrderInfos() const;
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

            void cancelOrderInternal(OrderId orderId);
            void cancelOrders(OrderIds orderIds);

            mutable std::mutex ordersMutex_;
            std::thread ordersPruneThread_;
            std::condition_variable shutdownConditionVariable_;
            std::atomic<bool> shutdown_{false};
            void pruneGoodForDayOrders();
    };
}

#endif