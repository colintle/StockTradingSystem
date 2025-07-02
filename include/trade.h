#ifndef STOCK_TRADING_TRADE_H
#define STOCK_TRADING_TRADE_H

#include "tradeInfo.h"

namespace StockTradingSystem
{
    class Trade
    {
        public:
            Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade);
            const TradeInfo& getBidTrade() const;
            const TradeInfo& getAskTrade() const;
        private:
            TradeInfo bidTrade_;
            TradeInfo askTrade_;
    };

    using Trades = std::vector<Trade>;
}

#endif