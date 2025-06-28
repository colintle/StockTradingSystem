#include "orderBook.h"

namespace StockTradingSystem
{
    OrderBook::OrderBook(OrderMatchingStrategy* strategy): strategy_{strategy}{}

    void OrderBook::addOrder(Order order)
    {
        book_.push_back(order);
    }

    void OrderBook::matchOrders()
    {
        std::vector<Order> buyOrders;
        std::vector<Order> sellOrders;

        for (const Order& order : book_){
            if (order.getOrdertype() == OrderType::BUY){
                buyOrders.push_back(order);
            }
            else{
                sellOrders.push_back(order);
            }
        }
    }

    void OrderBook::printOrderBook() const
    {

    }

    void OrderBook::setStrategy(OrderMatchingStrategy* strategy)
    {
        strategy_ = strategy;
    }
}