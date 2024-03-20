#include "Storage.h"
#include <iostream>
#include <fstream>
#include <sstream>

Storage::Storage()
{
    // TO DO
    // Push the control people
};

Storage* Storage::getInstance()
{
    if (storage == nullptr)
    {
        storage = new Storage();
    }
    return storage;
}

//getter ceny z mapy
float Storage::getPrice(const std::string& name) const 
{
    for (const auto& fruit : fruits) 
    {
        if (fruit.first.getName() == name) 
        {
            return fruit.first.getPrice();
        }
    }
    return -1;
}

//getter ilości owocu z mapy
int Storage::getAmount(const std::string& name) const 
{
    int totalAmount = 0;
    for (const auto& pair : fruits) 
    {
        if (pair.first.getName() == name) 
        {
            totalAmount += pair.second;
        }
    }

    if (totalAmount > 0) 
    {
        return totalAmount;
    }
    else 
    {
        return 0;
    }
}

//getter całego obiektu z mapy
Fruit Storage::getFruit(const std::string& name) const 
{
    for (const auto& fruit : fruits) 
    {
        if (fruit.first.getName() == name) 
        {
            return fruit.first;
        }
    }

    return Fruit("", 0.0f);
}

//sprawdzenie, czy owoc jest w mapie
bool Storage::isInStorage(const std::string& name) const 
{
    for (const auto& item : fruits) 
    {
        if (item.first.getName() == name) 
        {
            return true;
        }
    }
    return false;
}

//wczytywanie danych z pliku i zapis do mapy
void Storage::readStorage() 
{
    std::fstream file("storage.txt", std::ios::in);

    if (!file.is_open())
    {
        std::cerr << "Nie można otworzyć pliku." << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string name, bufor;
        float price;
        int amount;

        getline(ss, name, ',');
        ss.ignore();
        getline(ss, bufor, ',');
        price = stof(bufor);
        ss.ignore();
        getline(ss, bufor, ';');
        amount = stoi(bufor);

        this->fruits[Fruit(name, price)] = amount;
    }

    file.close();
}

//wyświetlenie danych z mapy
void Storage::showStorage() 
{
    for (const auto& fruit : fruits)
    {
        std::cout << "Nazwa: " << fruit.first.getName() << ", Cena: " << fruit.first.getPrice()<< ", Ilosc: " << fruit.second << std::endl;
    }
}

    //dodanie owoca do pliku storage.txt i do mapy
void Storage::addFruit(std::string name, float price, int amount) 
{
    std::ofstream file("storage.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
        return;
    }

    for (const auto& fruit : fruits)
    {
        if (fruit.first.getName() == name)
        {
            std::cerr << "Podany owoc istnieje" << std::endl;
            return;
        }
    }

    std::stringstream fruitstream;
    fruitstream << name << ", " << price << ", " << amount << ";";

    file << fruitstream.str() << std::endl;
    this->fruits[Fruit(name, price)] = amount;

    file.close();
}

    //usuniecie owoca z pliku i mapy
void Storage::deleteFruit(const std::string& name) 
 {
    bool fruitExists = false;
    for (const auto& fruit : fruits)
    {
        if (fruit.first.getName() == name)
        {
            fruitExists = true;
            break;
        }
    }

    if (!fruitExists)
    {
        std::cerr << "Owoc o nazwie " << name << " nie istnieje." << std::endl;
        return;
    }

    for (auto fruit = fruits.begin(); fruit != fruits.end();)
    {
        if (fruit->first.getName() == name)
        {
            fruit = fruits.erase(fruit);
        }
        else
        {
            fruit++;
        }
    }

    std::ifstream file("storage.txt");
    std::stringstream buffor;
    std::string line;
    while (getline(file, line))
    {
        if (line.find(name + ",") == std::string::npos)
        {
            buffor << line << '\n';
        }
    }
    file.close();

    std::ofstream fileOut("storage.txt", std::ios::trunc);
    fileOut << buffor.str();
    fileOut.close();
}

    //aktualizacja danych danego owoca w pliku i w mapie
void Storage::updateFruit(const std::string& name, float newPrice, int newAmount) 
{
    bool fruitExists = false;
    for (const auto& fruit : fruits)
    {
        if (fruit.first.getName() == name)
        {
            fruitExists = true;
            break;
        }
    }

    if (!fruitExists)
    {
        std::cerr << "Owoc o nazwie " << name << " nie istnieje." << std::endl;
        return;
    }
    //usuniecie z mapy
    for (auto fruit = fruits.begin(); fruit != fruits.end();) 
    {
        if (fruit->first.getName() == name) 
        {
            fruit = fruits.erase(fruit);
        }
        else 
        {
            fruit++;
        }
    }

    // Dodanie zaktualizowanego owocu do mapy
    fruits[Fruit(name, newPrice)] = newAmount;

    // Aktualizacja pliku
    std::ifstream file("storage.txt");
    std::stringstream buffer;
    std::string line;
    while (getline(file, line)) 
    {
        if (line.find(name + ",") != std::string::npos) 
        {
            buffer << name << ", " << newPrice << ", " << newAmount << ";\n";
        }
        else
        {
            // Kopiowanie pozostałych linii
            buffer << line << '\n';
        }
    }
    file.close();

    // Zapisanie zmodyfikowanej zawartości z powrotem do pliku
    std::ofstream fileOut("storage.txt", std::ios::trunc);
    fileOut << buffer.str();
    fileOut.close();
}