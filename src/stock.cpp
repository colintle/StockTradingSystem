#include "stock.h"

namespace StockTradingSystem
{
    Stock::Stock(double price, const std::string& name):
    price_{price},
    name_{name}{}

    void Stock::setPrice(double price)
    {
        price_ = price;
    }

    void Stock::setName(const std::string& name)
    {
        name_ = name;
    }

    double Stock::getPrice() const
    {
        return price_;
    }

    std::string Stock::getName() const 
    {
        return name_;
    }
}
