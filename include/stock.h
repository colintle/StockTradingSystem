#ifndef STOCK_TRADING_SYSTEM_STOCK_H
#define STOCK_TRADING_SYSTEM_STOCK_H

#include <string>

namespace StockTradingSystem
{
    class Stock
    {
        public:
            Stock(double price, const std::string& name);
            void setPrice(double price);
            void setName (const std::string& name);
            double getPrice() const;
            std::string getName() const;
        private:
            double price_;
            std::string name_;
    };
}

#endif