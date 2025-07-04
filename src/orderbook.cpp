#include "orderbook.h"

namespace StockTradingSystem
{
    Trades Orderbook::addOrder(OrderPointer order)
    {
        if (orders_.contains(order->getOrderId()))
        {
            return {};
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

    void Orderbook::cancelOrder(OrderId orderId)
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
                bid->Fill(quantity);
                ask->Fill(quantity);

                if (bid->IsFilled())
                {
                    bids.pop_front();
                    orders_.erase(bid->getOrderId());
                }

                if (ask->IsFilled())
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

        return trades;
    }
}