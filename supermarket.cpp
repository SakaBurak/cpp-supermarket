#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include<vector>

using namespace std;

// Structure to store item details
struct SupermarketItem {
    string QR;
    string name;
    double price;
};

// Structure for shopping list
struct ShoppingListItem {
    string QR;
    int quantity;
};

int main() {
    vector<SupermarketItem> inventory;
    vector<ShoppingListItem> shoppingList;

    // Input phase for inventory setup
    cout << "Enter product QR, name, and price (enter 'END' to finish):\n";
    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        if (line == "END") break;

        size_t firstSpace = line.find(' ');
        string QR = line.substr(0, firstSpace);
        
        size_t dollarSign = line.find('$');
        string name = line.substr(firstSpace + 1, dollarSign - firstSpace - 1);

        string priceStr = line.substr(dollarSign + 1);
        double price = atof(priceStr.c_str());

        inventory.push_back({QR, name, price});
    }

    // Input phase for shopping list
    cout << "Enter shopping list item QR and quantity (enter 'END' to finish):\n";
    while (true) {
        cout << "> ";
        string QR;
        int quantity;
        cin >> QR;
        if (QR == "END") break;
        cin >> quantity;
        shoppingList.push_back({QR, quantity});
    }

    // Processing shopping list and calculating costs
    double totalCost = 0.0;
    const double VAT_RATE = 0.18;

    cout << fixed << setprecision(2);
    cout << "\nItem          Quantity    Total Cost\n";
    cout << "------------------------------------\n";

    for (const auto& listItem : shoppingList) {
        bool itemFound = false;
        for (const auto& item : inventory) {
            if (item.QR == listItem.QR) {
                itemFound = true;
                double itemTotalCost = item.price * listItem.quantity;
                totalCost += itemTotalCost;
                cout << setw(5) << left << item.name << setw(3) << right << listItem.quantity << setw(31 - item.name.length()) << right << itemTotalCost << endl;
                break;
            }
        }
        if (!itemFound) {
            cout << "Item with QR code " << listItem.QR << " not found in inventory." << endl;
        }
    }

    double VAT = totalCost * VAT_RATE;
    double totalWithVAT = totalCost + VAT;

    cout << "\n VAT(18%):" << setw(27) << right << VAT << endl;
    cout << " Total:" << setw(30) << right << totalWithVAT << endl;

    return 0;
}

