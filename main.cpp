
#include "order.h"

void showMenu() {
    cout << "--- ORDER MANAGEMENT SYSTEM ---" << endl;
    cout << "1. Add Product" << endl;
    cout << "2. Remove Product" << endl;
    cout << "3. Show Order" << endl;
    cout << "4. Save to File" << endl;
    cout << "5. Load from File" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}

int main() {
    OnlineOrder myOrder(1, "2026-04-16");
    int choice;
    string name;
    double price;
    int qty;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter name, price, and quantity: ";
            cin >> name >> price >> qty;
            myOrder.addProduct(name, price, qty);
            break;
        case 2:
            cout << "Enter product name to remove: ";
            cin >> name;
            if (myOrder.removeProduct(name)) cout << "Done!\n";
            else cout << "Not found.\n";
            break;
        case 3:
            myOrder.displayOrder();
            break;
        case 4:
            myOrder.saveToFile("my_order.json");
            cout << "Saved successfully.\n";
            break;
        case 5:
            myOrder.loadFromFile("my_order.json");
            cout << "Loaded successfully.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}