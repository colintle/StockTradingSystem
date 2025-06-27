#include <iostream>
#include <format>
#include "stock.h"
#include "trader.h"
#include "order.h"

int main()
{
    StockTradingSystem::Stock stock {145, "aapl"};
    StockTradingSystem::Trader trader{"Colin"};
    StockTradingSystem::Order order {trader, 100.1, 2, StockTradingSystem::BUY};

    std::string line = std::format(
        "Stock: {}  Trader: {}  Price: {:.2f}  Qty: {}\n",
        stock.getName(),
        trader.getName(),
        order.getPrice(),
        order.getQuantity()
    );
    std::cout << line;
}