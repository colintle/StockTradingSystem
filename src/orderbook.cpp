#include "orderbook.h"

namespace StockTradingSystem
{
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