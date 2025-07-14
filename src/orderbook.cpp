#include "orderbook.h"

namespace StockTradingSystem
{
    Orderbook::Orderbook(): ordersPruneThread_{[this] {pruneGoodForDayOrders();}}{}

    Orderbook::~Orderbook(){}

    Trades Orderbook::addOrder(OrderPointer order)
    {
        if (orders_.contains(order->getOrderId()))
        {
            return {};
        }

        if (order->getOrderType() == OrderType::Market)
        {
            if (order->getSide() == Side::BUY && !asks_.empty())
            {
                const auto& [worstAsk, _] = *asks_.rbegin();
                order->toGoodTillCancel(worstAsk);
            }
            else if (order->getSide() == Side::SELL && !bids_.empty())
            {
                const auto& [worstBuy, _] = *bids_.rbegin();
                order->toGoodTillCancel(worstBuy);
            }
            else
            {
                return {};
            }
        }

        OrderPointers::iterator iterator;
        if (order->getSide() == Side::BUY)
        {   
            OrderPointers& orders= bids_[order->getPrice()];
            orders.push_back(order);
            iterator = std::next(orders.begin(), orders.size() - 1);
        }
        else
        {
            OrderPointers& orders = asks_[order->getPrice()];
            orders.push_back(order);
            iterator = std::next(orders.begin(), orders.size() - 1);
        }

        orders_.insert({order->getOrderId(), OrderEntry{order, iterator}});
        return matchOrders();

    }

    void Orderbook::cancelOrderInternal(OrderId orderId)
    {
        if (!orders_.contains(orderId))
        {
            return;
        }

        const auto& [order, orderIterator] = orders_.at(orderId);
        orders_.erase(orderId);

        if (order->getSide() == Side::SELL)
        {
            Price price =  order->getPrice();
            OrderPointers& orders = asks_.at(price);
            orders.erase(orderIterator);
            if (orders.empty())
            {
                asks_.erase(price);
            }
        }
        else
        {
            Price price =  order->getPrice();
            OrderPointers& orders = bids_.at(price);
            orders.erase(orderIterator);
            if (orders.empty())
            {
                bids_.erase(price);
            }
        }
    }

    Trades Orderbook::modifyOrder(OrderModify order)
    {
        if (!orders_.contains(order.getOrderId()))
        {
            return {};
        }

        const auto& [existingOrder, _] = orders_.at(order.getOrderId());
        cancelOrder(order.getOrderId());
        return addOrder(order.ToOrderPointer(existingOrder->getOrderType()));
    }

    bool Orderbook::canMatch(Side side, Price price) const
    {
        if (side == Side::BUY)
        {
            if (asks_.empty())
            {
                return false;
            }

            const auto& [bestAsk, _] = *asks_.begin();
            return price >= bestAsk;
        }
        else
        {
            if (bids_.empty())
            {
                return false;
            }

            const auto& [bestBid, _] = *bids_.begin();
            return price <= bestBid;
        }
    }

    Trades Orderbook::matchOrders()
    {
        Trades trades;
        trades.reserve(orders_.size());

        while (true)
        {
            if (bids_.empty() || asks_.empty())
            {
                break;
            }

            auto& [bidPrice, bids] = *bids_.begin();
            auto& [askPrice, asks] = *asks_.begin();

            if (bidPrice < askPrice)
            {
                break;
            }

            while (bids.size() && asks.size())
            {
                auto& bid = bids.front();
                auto& ask = asks.front();

                Quantity quantity = std::min(bid->getRemainingQuantity(), ask->getRemainingQuantity());
                bid->fill(quantity);
                ask->fill(quantity);

                if (bid->isFilled())
                {
                    bids.pop_front();
                    orders_.erase(bid->getOrderId());
                }

                if (ask->isFilled())
                {
                    asks.pop_front();
                    orders_.erase(ask->getOrderId());
                }

                if (bids.empty())
                {
                    bids_.erase(bidPrice);
                }

                if (asks.empty())
                {
                    asks_.erase(askPrice);
                }

                trades.push_back(Trade{TradeInfo{bid->getOrderId(), bid->getPrice(), quantity}, TradeInfo{ask->getOrderId(), ask->getPrice(), quantity}});
            }
        }

        if (!bids_.empty())
        {
            auto& [_, bids] = *bids_.begin();
            auto& order = bids.front();
            if (order->getOrderType() == OrderType::FillAndKill)
            {
                cancelOrder(order->getOrderId());
            }
        }

        if (!asks_.empty())
        {
            auto& [_, asks] = *asks_.begin();
            auto& order = asks.front();
            if (order->getOrderType() == OrderType::FillAndKill)
            {
                cancelOrder(order->getOrderId());
            }
        }

        return trades;
    }

    std::size_t Orderbook::size() const
    {
        return orders_.size();
    }

    OrderBookLevels Orderbook::getOrderInfos() const
    {
        Levels bids, asks;
        bids.reserve(orders_.size());
        asks.reserve(orders_.size());

        auto createLevelInfos = [](Price price, const OrderPointers& orders)
        {
            return Level{price, std::accumulate(orders.begin(), orders.end(), (Quantity) 0,
            [](Quantity runningSum, const OrderPointer& order)
            {
                return runningSum + order->getRemainingQuantity();
            }
            )};
        };

        for (const auto& [price, orders] : bids_)
        {
            bids.push_back(createLevelInfos(price, orders));
        }

        for (const auto& [price, orders] : asks_)
        {
            asks.push_back(createLevelInfos(price, orders));
        }

        return OrderBookLevels{bids, asks};
    }

    void Orderbook::cancelOrder(OrderId orderId)
    {
        std::scoped_lock ordersLock{ ordersMutex_ };
        cancelOrderInternal(orderId);
    }

    void Orderbook::cancelOrders(OrderIds orderIds)
    {
        std::scoped_lock ordersLock{ ordersMutex_};

        for (const auto& orderId : orderIds)
        {
            cancelOrderInternal(orderId);
        }

    }

    void Orderbook::pruneGoodForDayOrders()
    {

    }
}