#include <iostream>
#include "elan/storage/ClientStorage.h"


int main()
{
    storage::ClientStorage storage;

    // 1. Створюємо 3 клієнти
    domain::Client c1("Ivan", "Petrenko", "O.", {2000,1,1}, "111", 1);
    domain::Client c2("Petro", "Ivanenko", "O.", {2001,2,2}, "222", 2);
    domain::Client c3("Anna", "Shevchenko", "O.", {2002,3,3}, "333", 3);

    // 2. Додаємо
    storage.Add(c1);
    storage.Add(c2);
    storage.Add(c3);

    std::cout << "Added 3 clients\n";

    // 3. Перевіряємо всі
    auto all = storage.GetAll();
    std::cout << "All clients: " << all.size() << "\n";

    // 4. Видаляємо другого (припустимо id = 2)
    bool deleted = storage.Delete(2);

    std::cout << "Deleted id 2: " << (deleted ? "yes" : "no") << "\n";

    // 5. Перевіряємо знову
    all = storage.GetAll();
    std::cout << "After delete: " << all.size() << "\n";

    // 6. Перевірка GetById
    auto client = storage.GetById(1);

    if (client)
        std::cout << "Found client with id 1\n";
    else
        std::cout << "Not found\n";

    return 0;

    std::cout<<"hello world";
    return 0;
}