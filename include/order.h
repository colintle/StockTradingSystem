#ifndef STOCK_TRADING_ORDER_H
#define STOCK_TRADING_ORDER_H

#include "side.h"
#include "usings.h"
#include "orderType.h"
#include "constants.h"
#include <stdexcept>
#include <format>
#include <memory>
#include <list>

namespace StockTradingSystem
{
    class Order
    {
        public:
            Order(Price price, Quantity quantity, Side side, OrderType orderType, OrderId orderId);
            Order(Quantity quantity, Side side, OrderId orderId);
            Price getPrice() const;
            Side getSide() const;
            OrderType getOrderType() const;
            OrderId getOrderId() const;
            Quantity getInitialQuantity() const;
            Quantity getRemainingQuantity() const;
            Quantity getFilledQuantity() const;
            bool isFilled() const;
            void fill(Quantity quantity);
            void toGoodTillCancel(Price price);
        private:
            Price price_;
            Side side_;
            OrderType orderType_;
            OrderId orderId_;
            Quantity initialQuantity_;
            Quantity remainingQuantity_;
    };

    using OrderPointer = std::shared_ptr<Order>;
    using OrderPointers = std::list<OrderPointer>;
}

#endif