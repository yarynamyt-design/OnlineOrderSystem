#include "order.h"
OnlineOrder::OnlineOrder(int id, string date)
    : orderID(id), orderDate(date), status(OrderStatus::Pending) {
}

void OnlineOrder::addProduct(const string& name, double price, int qty) {
    items.push_back({ name, price, qty });
}

bool OnlineOrder::removeProduct(const string& name) {
    auto it = remove_if(items.begin(), items.end(),
        [&name](const Product& p) { return p.name == name; });

    if (it != items.end()) {
        items.erase(it, items.end());
        return true;
    }
    return false;
}

void OnlineOrder::updateQuantity(const string& name, int newQty) {
    for (auto& item : items) {
        if (item.name == name) {
            item.quantity = newQty;
            return;
        }
    }
}

void OnlineOrder::saveToFile(const string& filename) {
    json j;
    j["orderID"] = orderID;
    j["orderDate"] = orderDate;
    j["status"] = static_cast<int>(status);
    j["items"] = json::array();
    for (const auto& item : items) j["items"].push_back(item.to_json());

    std::ofstream outFile(filename);
    if (outFile) outFile << j.dump(4);
}

void OnlineOrder::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) return;

    json j;
    inFile >> j;
    orderID = j["orderID"];
    orderDate = j["orderDate"];
    status = static_cast<OrderStatus>(j["status"].get<int>());
    items.clear();
    for (const auto& itemJson : j["items"]) items.push_back(Product::from_json(itemJson));
}

void OnlineOrder::displayOrder() const {
    cout << "ORDER #" << orderID << " [" << orderDate << "]" << endl;
    for (const auto& item : items) {
        cout << "- " << left << setw(12) << item.name
            << " | $" << setw(6) << item.price
            << " | x" << item.quantity << endl;
    }
    cout << "-------------------------------" << endl;
    cout << "TOTAL: $" << fixed << setprecision(2) << calculateTotal() << endl;
    cout << "===============================\n" << endl;
}

double OnlineOrder::calculateTotal() const {
    double total = 0;
    for (const auto& item : items) total += item.price * item.quantity;
    return total;
}

string OnlineOrder::getStatusString() const {
    switch (status) {
    case OrderStatus::Pending: return "Pending";
    case OrderStatus::Processing: return "Processing";
    case OrderStatus::Completed: return "Completed";
    case OrderStatus::Cancelled: return "Cancelled";
    default: return "Unknown";
    }
}