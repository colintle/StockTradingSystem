#include "order.h"

namespace StockTradingSystem
{
    Order::Order(Price price, Quantity quantity, Side side, OrderType orderType, OrderId orderId):
    price_{price},
    side_{side},
    orderType_{orderType},
    orderId_{orderId},
    initialQuantity_{quantity},
    remainingQuantity_{quantity}
    {}

    Price Order::getPrice() const
    {
        return price_;
    }

    Quantity Order::getInitialQuantity() const
    {
        return initialQuantity_;
    }

    Quantity Order::getRemainingQuantity() const
    {
        return remainingQuantity_;
    }

    OrderType Order::getOrderType() const
    {
        return orderType_;
    }

    OrderId Order::getOrderId() const
    {
        return orderId_;
    }

    Side Order::getSide() const
    {
        return side_;
    }

    Quantity Order::getFilledQuantity() const
    {
        return getInitialQuantity() - getRemainingQuantity();
    }

    bool Order::IsFilled() const
    {
        return getRemainingQuantity() == 0;
    }

    void Order::Fill(Quantity quantity)
    {
        if (quantity > getRemainingQuantity())
        {
            throw std::logic_error(std::format("ORder {} cannot be filled for more than its remaining quantity.", getOrderId()));
        }

        remainingQuantity_ -= quantity;
    }
}