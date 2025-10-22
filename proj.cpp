#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// -------------------- Class Definitions --------------------

class MenuItem {
public:
    string name;
    float price;
    string category;

    MenuItem(string n, float p, string c) {
        name = n;
        price = p;
        category = c;
    }

    void display() {
        cout << left << setw(20) << name 
             << setw(10) << category 
             << setw(6) << price << endl;
    }
};

class Order {
public:
    vector<MenuItem> items;
    vector<int> quantities;
    
    void addItem(MenuItem item, int qty) {
        items.push_back(item);
        quantities.push_back(qty);
    }

    float calculateTotal() {
        float total = 0;
        for(size_t i = 0; i < items.size(); i++) {
            total += items[i].price * quantities[i];
        }
        return total;
    }

    void showOrder() {
    cout << "\n================= Your Bill ================\n";
    cout << left << setw(20) << "Item"
         << setw(10) << "Qty"
         << setw(10) << "Price"
         << setw(10) << "Total" << endl;
    cout << "---------------------------------------------\n";

    float total = 0;
    for(size_t i = 0; i < items.size(); i++) {
        float itemTotal = items[i].price * quantities[i];
        total += itemTotal;
        cout << left << setw(20) << items[i].name
             << setw(10) << quantities[i]
             << setw(10) << items[i].price
             << setw(10) << itemTotal << endl;
    }

    cout << "---------------------------------------------\n";
    cout << left << setw(30) << "Grand Total:" << total << endl;
    cout << "=============================================\n";
}


    // Save order data to Excel (CSV)
    void saveOrderToExcel() {
        ofstream file("orders.csv", ios::app);
        file << "Item,Quantity,TotalPrice\n";
        for(size_t i = 0; i < items.size(); i++) {
            file << items[i].name << "," 
                 << quantities[i] << "," 
                 << items[i].price * quantities[i] << "\n";
        }
        file << "Total,," << calculateTotal() << "\n\n";
        file.close();
        cout << "Order saved to orders.csv\n";
    }
};

class Inventory {
public:
    vector<string> ingredients;
    vector<int> quantity;

    void addIngredient(string name, int qty) {
        ingredients.push_back(name);
        quantity.push_back(qty);
    }

    void showInventory() {
        cout << "----- Inventory -----\n";
        for(size_t i = 0; i < ingredients.size(); i++) {
            cout << ingredients[i] << " : " << quantity[i] << endl;
        }
    }

    // Save inventory to Excel (CSV)
    void saveInventoryToExcel() {
        ofstream file("inventory.csv");
        file << "Ingredient,Quantity\n";
        for(size_t i = 0; i < ingredients.size(); i++) {
            file << ingredients[i] << "," << quantity[i] << "\n";
        }
        file.close();
        cout << "Inventory saved to inventory.csv\n";
    }
};

// -------------------- Function Declarations --------------------

void showMenu(vector<MenuItem>& menu);
void customerModule(vector<MenuItem>& menu);
void adminModule(vector<MenuItem>& menu, Inventory& inventory);
void saveMenuToExcel(vector<MenuItem>& menu);

// -------------------- Main Program --------------------

int main() {
    vector<MenuItem> menu;
    Inventory inventory;

    // Sample menu items
    menu.push_back(MenuItem("Tea", 20, "Beverage"));
    menu.push_back(MenuItem("Coffee", 35, "Beverage"));
    menu.push_back(MenuItem("Sandwich", 50, "Snack"));

    // Sample inventory
    inventory.addIngredient("Tea Leaves", 100);
    inventory.addIngredient("Coffee Powder", 100);
    inventory.addIngredient("Bread", 50);

    int choice;
    do {
        cout << "\n----- Chai & Code Cafe -----\n";
        cout << "1. Customer Module\n";
        cout << "2. Admin Module\n";
        cout << "3. Export Menu to Excel\n";
        cout << "4. Export Inventory to Excel\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                customerModule(menu);
                break;
            case 2:
                adminModule(menu, inventory);
                break;
            case 3:
                saveMenuToExcel(menu);
                break;
            case 4:
                inventory.saveInventoryToExcel();
                break;
            case 5:
                cout << "Thank you! Visit Again.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while(choice != 5);

    return 0;
}

// -------------------- Function Definitions --------------------

void showMenu(vector<MenuItem>& menu) {
    cout << "\n----------- Menu -----------\n";
    cout << left << setw(5) << "No."
         << setw(20) << "Item"
         << setw(15) << "Category"
         << setw(10) << "Price" << endl;
    cout << "---------------------------------------------\n";

    for (size_t i = 0; i < menu.size(); i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << menu[i].name
             << setw(15) << menu[i].category
             << setw(10) << menu[i].price << endl;
    }

    cout << "---------------------------------------------\n";
}

void customerModule(vector<MenuItem>& menu) {
    Order order;
    int choice, qty;

    do {
        showMenu(menu);
        cout << "Enter item number to order (0 to finish): ";
        cin >> choice;

        if(choice > 0 && choice <= (int)menu.size()) {
            cout << "Enter quantity: ";
            cin >> qty;
            order.addItem(menu[choice-1], qty);
        } else if(choice != 0) {
            cout << "Invalid item number.\n";
        }
    } while(choice != 0);

    order.showOrder();
    order.saveOrderToExcel();  // Save order to file
}

void adminModule(vector<MenuItem>& menu, Inventory& inventory) {
    int choice;
    do {
        cout << "\n----- Admin Module -----\n";
        cout << "1. Add Menu Item\n";
        cout << "2. Show Inventory\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                string name, category;
                float price;
                cout << "Enter item name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter price: ";
                cin >> price;
                menu.push_back(MenuItem(name, price, category));
                cout << "Menu item added successfully!\n";
                break;
            }
            case 2:
                inventory.showInventory();
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 3);
}

void saveMenuToExcel(vector<MenuItem>& menu) {
    ofstream file("menu.csv");
    file << "Item,Category,Price\n";
    for(auto& item : menu) {
        file << item.name << "," << item.category << "," << item.price << "\n";
    }
    file.close();
    cout << "Menu saved to menu.csv\n";
}
