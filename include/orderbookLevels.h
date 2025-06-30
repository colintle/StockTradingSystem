#ifndef STOCK_TRADING_ORDERBOOK_LEVELS_H
#define STOCK_TRADING_ORDERBOOK_LEVELS_H

#include "level.h"

namespace StockTradingSystem
{
    class OrderBookLevels
    {
        public:
            OrderBookLevels(const Levels& bid, const Levels& asks);
            const Levels& getBids() const;
            const Levels& getAsks() const;
        private:
            Levels bids_;
            Levels asks_;
    };
}

#endif