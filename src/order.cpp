#include "order.h"

namespace StockTradingSystem
{
    Order::Order(Trader& trader, Price price, Quantity quantity, Side side, OrderType orderType):
    trader_{trader},
    price_{price},
    quantity_{quantity},
    orderType_{orderType},
    timestamp_(std::time(nullptr)),
    side_{side}
    {}

    Trader Order::getTrader() const
    {
        return trader_;
    }

    Price Order::getPrice() const
    {
        return price_;
    }

    Quantity Order::getQuantity() const
    {
        return quantity_;
    }

    OrderType Order::getOrderType() const
    {
        return orderType_;
    }

    std::time_t Order::getTimestamp() const
    {
        return timestamp_;
    }

    Side Order::getSide() const
    {
        return side_;
    }
}