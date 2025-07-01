#include "orderModify.h"

namespace StockTradingSystem
{
    OrderModify::OrderModify(OrderId orderId, Price price, Side side, Quantity quantity):
    orderId_{orderId},
    price_{price},
    side_{side},
    quantity_{quantity}
    {}

    OrderId OrderModify::getOrderId() const
    {
        return orderId_;
    }

    Price OrderModify::getPrice() const
    {
        return price_;
    }

    Side OrderModify::getSide() const
    {
        return side_;
    }

    Quantity OrderModify::getQuantity() const
    {
        return quantity_;
    }

    OrderPointer OrderModify::ToOrderPointer(OrderType type) const
    {
        return std::make_shared<Order>(getPrice(), getQuantity(), getSide(), type, getOrderId());
    }
}