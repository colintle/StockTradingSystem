#ifndef STOCK_TRADING_ORDER_MODIFY_H
#define STOCK_TRADING_ORDER_MODIFY_H

#include "order.h"

namespace StockTradingSystem
{
    class OrderModify
    {
        public:
            OrderModify(OrderId orderId, Price price, Side side, Quantity quantity);
            OrderId getOrderId() const;
            Price getPrice() const;
            Side getSide() const;
            Quantity getQuantity() const;
            OrderPointer ToOrderPointer(OrderType type) const;
        private:
            OrderId orderId_;
            Price price_;
            Side side_;
            Quantity quantity_;
    };
}

#endif