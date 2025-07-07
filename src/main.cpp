#include <iostream>
#include <format>
#include "orderbook.h"

using namespace StockTradingSystem;


int main()
{
    Orderbook orderbook;
    const OrderId orderId = 1;
    orderbook.addOrder(std::make_shared<Order>(100, 10, Side::BUY, OrderType::GoodTillCancel, orderId));
    std::cout << orderbook.size() << std::endl;
    orderbook.cancelOrder(orderId);
    std::cout << orderbook.size() << std::endl;
    return 0;
}