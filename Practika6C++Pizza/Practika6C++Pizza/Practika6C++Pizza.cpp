#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

class Order {
private:
    string customerName;
    time_t orderTime;
    vector<string> pizzas;

public:
    void takeOrder(string name) {
        customerName = name;
        orderTime = time(NULL); // Получение текущего времени
    }

    void addPizza(string pizza) {
        pizzas.push_back(pizza);
    }

    void displayOrder() {
        char timeStr[26];
        time_t orderTimeT = orderTime;
        if (ctime_s(timeStr, sizeof(timeStr), &orderTimeT) == 0) {
            cout << "Заказ от " << customerName << " был оформлен в " << timeStr << endl;
            cout << "Заказанные пиццы:" << endl;
            for (const auto& pizza : pizzas) {
                cout << "- " << pizza << endl;
            }
        }
        else {
            cout << "Ошибка при преобразовании времени в строку." << endl;
        }
    }
};

// Класс для представления меню
class Menu {
private:
    vector<string> items;

public:
    void createItem(string item) {
        items.push_back(item);
        cout << "Новый элемент меню: " << item << " добавлен." << endl;
    }

    void readMenu() {
        cout << "Меню:" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i] << endl;
        }
    }

    void updateItem(int index, string newItem) {
        if (index >= 0 && index < items.size()) {
            items[index] = newItem;
            cout << "Элемент меню обновлен." << endl;
        }
        else {
            cout << "Неверный индекс." << endl;
        }
    }

    void deleteItem(int index) {
        if (index >= 0 && index < items.size()) {
            items.erase(items.begin() + index);
            cout << "Элемент меню удален." << endl;
        }
        else {
            cout << "Неверный индекс." << endl;
        }
    }

    string getItem(int index) {
        if (index >= 0 && index < items.size()) {
            return items[index];
        }
        else {
            return "";
        }
    }

    int getSize() {
        return items.size();
    }
};

// Класс для представления пиццерии
class Pizzeria {
private:
    Order currentOrder;
    Menu menu;

public:
    void takeOrder() {
        string customerName;
        cout << "Введите имя заказчика: ";
        getline(cin, customerName);
        currentOrder.takeOrder(customerName);
    }

    void displayOrder() { 
        currentOrder.displayOrder();
    }

    void greetCustomer() {
        cout << "Добро пожаловать в нашу пиццерию!" << endl;
    }

    void thankCustomer() {
        cout << "Спасибо за ваш заказ!" << endl;
    }

    void manageMenu() {
        int choice;
        string item;
        int index;

        do {
            cout << "\nУправление меню:" << endl;
            cout << "1. Создать элемент меню" << endl;
            cout << "2. Просмотреть меню" << endl;
            cout << "3. Обновить элемент меню" << endl;
            cout << "4. Удалить элемент меню" << endl;
            cout << "5. Оформить заказ" << endl;
            cout << "0. Выход" << endl;
            cout << "Введите выбор: ";
            cin >> choice;
            cin.ignore(); // Очистка буфера

            switch (choice) {
            case 1:
                cout << "Введите новый элемент меню: ";
                getline(cin, item);
                menu.createItem(item);
                break;
            case 2:
                menu.readMenu();
                break;
            case 3:
                cout << "Введите индекс элемента меню для обновления: ";
                cin >> index;
                cin.ignore(); // Очистка буфера
                cout << "Введите новое название элемента меню: ";
                getline(cin, item);
                menu.updateItem(index - 1, item);
                break;
            case 4:
                cout << "Введите индекс элемента меню для удаления: ";
                cin >> index;
                menu.deleteItem(index - 1);
                break;
            case 5:
                placeOrder();
                break;
            case 0:
                cout << "Выход из управления меню." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
            }
        } while (choice != 0);
    }

    void placeOrder() {
        string pizza;
        int choice;

        do {
            cout << "\nОформление заказа:" << endl;
            menu.readMenu();
            cout << "0. Завершить заказ" << endl;
            cout << "Введите номер пиццы для добавления в заказ: ";
            cin >> choice;
            cin.ignore();

            if (choice == 0) {
                break;
            }
            else if (choice > 0 && choice <= menu.getSize()) {
                pizza = menu.getItem(choice - 1);
                currentOrder.addPizza(pizza);
                cout << "Пицца '" << pizza << "' добавлена в заказ." << endl;
            }
            else {
                cout << "Неверный номер пиццы. Попробуйте снова." << endl;
            }
        } while (true);

        displayOrder();
    }
};

int main() {
    Pizzeria pizzeria;
    pizzeria.greetCustomer();
    pizzeria.takeOrder();
    pizzeria.manageMenu();
    pizzeria.thankCustomer();
    return 0;
}