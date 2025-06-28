#ifndef STOCK_TRADING_ORDER_MATCHING_STRATEGY
#define STOCK_TRADING_ORDER_MATCHING_STRATEGY

#include "order.h"
#include <vector>

namespace StockTradingSystem
{
    class OrderMatchingStrategy
    {
        public:
            virtual void matchOrders(std::vector<Order>& buy_orders, std::vector<Order>& sell_orders) = 0;
            virtual ~OrderMatchingStrategy();
    };

    class PriceTimeMatchingStrategy : public OrderMatchingStrategy
    {
        public:
            void matchOrders(std::vector<Order>& buy_orders, std::vector<Order>& sell_orders) override;
    };
}
#endif
