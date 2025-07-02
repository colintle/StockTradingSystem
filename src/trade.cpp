#include "trade.h"

namespace StockTradingSystem
{
    Trade::Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade):
    bidTrade_{bidTrade},
    askTrade_{askTrade}{}

    const TradeInfo& Trade::getBidTrade() const
    {
        return bidTrade_;
    }

    const TradeInfo& Trade::getAskTrade() const
    {
        return askTrade_;
    }
}