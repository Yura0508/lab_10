// lab_10_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

struct Product {
    string name;
    string storeName;
    double price;
    int quantity;
    string unit;

    void input() {
        cout << "Назва товару: ";
        cin >> name;
        cout << "Назва магазину: ";
        cin >> storeName;
        cout << "Вартість одиниці товару (грн): ";
        cin >> price;
        cout << "Кількість товару: ";
        cin >> quantity;
        cout << "Одиниця вимірювання: ";
        cin >> unit;
    }

    void print() const {
        cout << "| " << setw(15) << name
            << "   | " << setw(15) << storeName
            << "  | " << setw(13) << price
            << " | " << setw(10) << quantity
            << " | " << setw(20) << unit << " |" << endl;
    }
};

void addProduct(Product*& products, int& count, int& capacity) {
    
    if (count >= capacity) {
        capacity += 1;
        Product* newProducts = new Product[capacity];
        for (int i = 0; i < count; i++) {
            newProducts[i] = products[i];
        }
        delete[] products;
        products = newProducts;
    }

    cout << "Додавання товару:" << endl;
    products[count].input();
    count++;
}

void Remove(Product*& products, int& count) {
    string name;
    cout << "Введіть назву товару для видалення: ";
    cin >> name;
    int K = 0; // кількість елементів, які потрібно залишити
    for (int i = 0; i < count; i++) // скануємо масив і обчислюємо кількість елементів для видалення
        if (products[i].name != name) // кількість товару має бути більше нуля
            K++; // кількість елементів для збереження

    Product* temp = new Product[K]; // тимчасовий масив для збережених елементів
    int j = 0; // індекс у тимчасовому масиві
    for (int i = 0; i < count; i++) { // скануємо масив і копіюємо елементи
        if (products[i].name != name) // якщо товар має кількість більше нуля
            temp[j++] = products[i];
    }
    delete[] products; // знищуємо старий масив
    products = temp; // оновлюємо вказівник на новий масив
    count = K; // оновлюємо кількість елементів
}

void editProduct(Product* products, int count) {
    string name, storeName;
    cout << "Введіть назву товару для редагування: ";
    cin >> name;
    cout << "Введіть назву магазину для редагування: ";
    cin >> storeName;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (products[i].name == name && products[i].storeName == storeName) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        cout << "Редагування товару:" << endl;
        products[index].input();
    }
    else {
        cout << "Товар не знайдено." << endl;
    }
}

void printAll(const Product* products, int count) {
    cout << "============================================================================================" << endl;
    cout << "| Назва товару      | Назва магазину   | Вартість (грн) | Кількість | Одиниця вимірювання  |" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < count; i++) {
        products[i].print();
    }
    cout << "============================================================================================" << endl;
}

void printByName(const Product* products, int count) {
    string name;
    cout << "Введіть назву товару для виведення: ";
    cin >> name;

    bool found = false;
    cout << "============================================================================================" << endl;
    for (int i = 0; i < count; i++) {
        if (products[i].name == name) {
            products[i].print();
            found = true;
        }
    }
    cout << "============================================================================================" << endl;
    if (!found) {
        cout << "Товар не знайдено." << endl;
    }
}

void printByStore(const Product* products, int count) {
    string store;
    cout << "Введіть назву магазину для виведення товарів: ";
    cin >> store;
    cout << "============================================================================================" << endl;
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (products[i].storeName == store) {
            products[i].print();
            found = true;
        }
    }
    cout << "============================================================================================" << endl;
    if (!found) {
        cout << "Товари з таким магазином не знайдено." << endl;
    }
}

void sortByName(Product* products, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (products[j].name > products[j + 1].name) {
                Product temp = products[j];     
                products[j] = products[j + 1]; 
                products[j + 1] = temp; ;
            }
        }
    }
    cout << "Товари відсортовано за назвою." << endl;
}

void sortByStore(Product* products, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (products[j].storeName > products[j + 1].storeName) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp; ;
            }
        }
    }
    cout << "Товари відсортовано за назвою магазину." << endl;
}

void SaveToFile(Product* products, const int count, const char* filename) {
    ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
    fout.write((char*)&count, sizeof(count)); // записали кількість елементів
    for (int i = 0; i < count; i++)
        fout.write((char*)&products[i], sizeof(Product)); // записали елементи масиву
    fout.close(); // закрили файл
}

void LoadFromFile(Product*& products, int& count, const char* filename) {
    delete[] products;
    ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
    fin.read((char*)&count, sizeof(count)); // прочитали кількість елементів
    products = new Product[count]; // створили динамічний масив
    for (int i = 0; i < count; i++)
        fin.read((char*)&products[i], sizeof(Product)); // прочитали елементи масиву
    fin.close(); // закрили файл
}



int* IndexSort(Product* products, const int count) {
    int sortOption;
    cout << "Виберіть варіант сортування:" << endl;
    cout << "1. За назвою товару" << endl;
    cout << "2. За назвою магазину" << endl;
    cin >> sortOption; // Input sorting option
    
    int* indices = new int[count];
    for (int i = 0; i < count; i++) {
        indices[i] = i;
    }

    for (int i = 1; i < count; i++) {
        int value = indices[i];
        int j;
        if (sortOption == 1) {
            for (j = i - 1; j >= 0 && products[indices[j]].name > products[value].name; j--) {
                indices[j + 1] = indices[j];
            }
        }
        else if (sortOption == 2) {
            for (j = i - 1; j >= 0 && products[indices[j]].storeName > products[value].storeName; j--) {
                indices[j + 1] = indices[j];
            }
        }
        indices[j + 1] = value;
    }
    return indices;
}

void PrintSorted(Product* products, int* indices, const int count) {
    cout << "============================================================================================" << endl;
    cout << "| Назва товару      | Назва магазину   | Вартість (грн) | Кількість | Одиниця вимірювання  |" << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < count; i++) {
        products[indices[i]].print();
    }
    cout << "============================================================================================" << endl;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int capacity = 2;
    int count = 0;
    Product* products = new Product[capacity];

    char filename[100];
    int menuItem;
    do {
        cout << "Виберіть дію:" << endl;
        cout << " [1] - додати товар" << endl;
        cout << " [2] - видалити товар" << endl;
        cout << " [3] - редагувати товар" << endl;
        cout << " [4] - вивести всі товари" << endl;
        cout << " [5] - вивести товар за назвою" << endl;
        cout << " [6] - вивести товари за магазином" << endl;
        cout << " [7] - зберегти дані в файл" << endl;
        cout << " [8] - завантажити дані з файлу" << endl;
        cout << " [9] - сортування" << endl;
        cout << " [0] - вихід" << endl;
        cout << "Введіть значення: ";
        cin >> menuItem;
        
        
       
        switch (menuItem) {
        case 1:
            addProduct(products, count, capacity);
            break;
        case 2:
            Remove(products, count);
            break;
        case 3:
            editProduct(products, count);
            break;
        case 4:
            printAll(products, count);
            break;
        case 5:
            printByName(products, count);
            break;
        case 6:
            printByStore(products, count);
            break;
        case 7:
            cin.get(); // очищуємо буфер клавіатури
            cin.sync();
            cout << "Введіть ім'я файлу: ";
            cin.getline(filename, 99);
            SaveToFile(products, count, filename);
            break;
        case 8:
            cin.get(); // очищуємо буфер клавіатури
            cin.sync();
            cout << "Введіть ім'я файлу: ";
            cin.getline(filename, 99);
            LoadFromFile(products, count, filename);
            break;
        case 9:
            
            PrintSorted(products, IndexSort(products, count), count);
            break;
        case 0:
            cout << "Завершення програми." << endl;
            break;
        default:
            cout << "Неправильний вибір! Спробуйте ще раз." << endl;
            break;
        }
    } while (menuItem != 0);
    return 0;
}
