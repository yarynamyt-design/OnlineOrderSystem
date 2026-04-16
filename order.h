#pragma once
#include "product.h"

enum class OrderStatus { Pending, Processing, Completed, Cancelled };

class OnlineOrder {
private:
    vector<Product> items;
    string orderDate;
    OrderStatus status;
    int orderID;

public:
    OnlineOrder(int id, string date);
    void addProduct(const string& name, double price, int qty);
    bool removeProduct(const string& name);
    void updateQuantity(const string& name, int newQty);
    void setStatus(OrderStatus newStatus);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    void displayOrder() const;
    double calculateTotal() const;
    string getStatusString() const;
};