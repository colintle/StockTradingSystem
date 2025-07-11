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

    Order::Order(Quantity quantity, Side side, OrderId orderId):
    Order(Constants::InvalidPrice, quantity, side, OrderType::Market, orderId)
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

    bool Order::isFilled() const
    {
        return getRemainingQuantity() == 0;
    }

    void Order::fill(Quantity quantity)
    {
        if (quantity > getRemainingQuantity())
        {
            throw std::logic_error(std::format("ORder {} cannot be filled for more than its remaining quantity.", getOrderId()));
        }

        remainingQuantity_ -= quantity;
    }

    void Order::toGoodTillCancel(Price price) 
    {
        if (getOrderType() != OrderType::Market)
        {
            throw std::logic_error(std::format("Order ({}) cannot have its price adjusted, only market orders can.", getOrderId()));

            price_ = price;
            orderType_ = OrderType::GoodTillCancel;
        }
    }
}