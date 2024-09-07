#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class Item {
public:
    string name;
    int rate;
    int quantity;

    Item(string name, int rate, int quantity)
        : name(name), rate(rate), quantity(quantity) {}
};

class Bill {
private:
    vector<Item> items;

public:
    void addItem(const string& itemName, int rate, int quantity) {
        items.emplace_back(itemName, rate, quantity);
    }

    bool getItemDetails(const string& itemName, int& rate, int& quantity) {
        for (auto& item : items) {
            if (item.name == itemName) {
                rate = item.rate;
                quantity = item.quantity;
                return true;
            }
        }
        return false;
    }

    bool updateItemQuantity(const string& itemName, int quantity) {
        for (auto& item : items) {
            if (item.name == itemName) {
                if (item.quantity >= quantity) {
                    item.quantity -= quantity;
                    return true;
                }
                return false; // Not enough quantity
            }
        }
        return false; // Item not found
    }

    void printItems() {
        for (const auto& item : items) {
            cout << item.name << " | Rate: " << item.rate << " | Quantity: " << item.quantity << endl;
        }
    }
};

void addItems(Bill& bill) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add" << endl;
        cout << "\t2. Close" << endl;
        cout << "\t3. Enter Choice" << endl;
        cin >> choice;
        if (choice == 1) {
            string itemName;
            int rate, quantity;
            cout << "\tEnter Item Name: ";
            cin >> itemName;
            cout << "\tEnter Item Rate: ";
            cin >> rate;
            cout << "\tEnter Item Quantity: ";
            cin >> quantity;
            bill.addItem(itemName, rate, quantity);
            cout << "Item Added Successfully" << endl;
            Sleep(3000);
        }
        else if (choice == 2) {
            close = true;
            cout << "\tBack to main menu!" << endl;
        }
    }
}

void printBill(Bill& bill) {
    system("cls");
    int totalAmount = 0;
    bool close = false;
    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Print Bill" << endl;
        cout << "\t2. Close System" << endl;
        cout << "\t3. Enter the Choice" << endl;
        cin >> choice;
        if (choice == 1) {
            string itemName;
            int quantity;
            cout << "Enter Item Name: ";
            cin >> itemName;
            cout << "\tEnter the Quantity: ";
            cin >> quantity;

            int rate, availableQuantity;
            if (bill.getItemDetails(itemName, rate, availableQuantity)) {
                if (quantity <= availableQuantity) {
                    int amount = rate * quantity;
                    cout << "\tItems | Rate | Quantity | Amount" << endl;
                    cout << "\t" << itemName << "\t" << rate << "\t" << quantity << "\t" << amount << endl;
                    totalAmount += amount;
                    if (!bill.updateItemQuantity(itemName, quantity)) {
                        cout << "\tNot enough quantity available." << endl;
                    }
                    cout << "\tUpdated Quantity: " << availableQuantity - quantity << " | Rate: " << rate << endl << endl;
                }
                else {
                    cout << "\tSorry, " << itemName << " is out of stock." << endl;
                }
            }
            else {
                cout << "\tItem not available!" << endl;
            }
            Sleep(3000);
        }
        else if (choice == 2) {
            close = true;
            cout << "\tCounting Total Bill" << endl;
        }
    }
    system("cls");
    cout << endl << endl;
    cout << "\tTotal Bill ------------- : " << totalAmount << endl;
    cout << "\tThanks for Shopping" << endl;
}

int main() {
    Bill bill;
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t*********************" << endl;
        cout << "\t\t1. Add Items." << endl;
        cout << "\t\t2. Print Bill" << endl;
        cout << "\t\t3. Exit" << endl;
        cout << "\t\tEnter your Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            addItems(bill);
        }
        else if (val == 2) {
            system("cls");
            printBill(bill);
        }
        else if (val == 3) {
            exit = true;
            cout << "\tGood Luck" << endl;
            Sleep(3000);
        }
    }

    return 0;
}
