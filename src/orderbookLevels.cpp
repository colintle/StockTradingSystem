#include "orderbookLevels.h"

namespace StockTradingSystem
{
    OrderBookLevels::OrderBookLevels(const Levels& bids, const Levels& asks):
    bids_{bids},
    asks_{asks}{}

    const Levels& OrderBookLevels::getBids() const
    {
        return bids_;
    }

    const Levels& OrderBookLevels::getAsks() const
    {
        return asks_;
    }
}