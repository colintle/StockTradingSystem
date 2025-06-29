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

        strategy_->matchOrders(buyOrders, sellOrders);
        book_.clear();
        book_.insert(book_.end(), buyOrders.begin(), buyOrders.end());
        book_.insert(book_.end(), sellOrders.begin(), sellOrders.end());
    }

    void OrderBook::printOrderBook() const
    {
        std::cout << "Order Book content...\n";
        std::cout << "ID\tPrice\tQuantity\tOrderType\n";
        for (const Order& order : book_)
        {
            std::string orderTypeName = order.getOrdertype() == OrderType::BUY ? "Buy" : "Sell";
            std::string output = std::format("{}\t{}\t{}\t{}\n", 
                order.getTrader().getName(),
                order.getPrice(),
                order.getQuantity(),
                orderTypeName);
            std::cout << output;
        }
        std::cout << "\n";

    }

    void OrderBook::setStrategy(OrderMatchingStrategy* strategy)
    {
        strategy_ = strategy;
    }
}