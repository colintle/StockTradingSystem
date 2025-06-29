#include "order.h"

namespace StockTradingSystem
{
    Order::Order(Trader& trader, double price, int quantity, Side side):
    trader_{trader},
    price_{price},
    quantity_{quantity},
    timestamp_(std::time(nullptr)),
    side_{side}
    {}

    Trader Order::getTrader() const
    {
        return trader_;
    }

    double Order::getPrice() const
    {
        return price_;
    }

    int Order::getQuantity() const
    {
        return quantity_;
    }

    std::time_t Order::getTimestamp() const
    {
        return timestamp_;
    }

    Side Order::getSide() const
    {
        return side_;
    }

    bool Order::reduceQuantity(int quantity)
    {
        if (quantity > 0 && quantity <= quantity_)
        {
            quantity_ -= quantity;
            return true;
        }
        return false;
    }
}