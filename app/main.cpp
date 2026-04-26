#include <iostream>

#include "elan/storage/Storage.h"

#include "elan/domain/Client.h"
#include "elan/domain/User.h"

int main()
{
    //-----------------------------------
    // CLIENT TESTS
    //-----------------------------------

    storage::Storage<domain::Client> clients(
        "../data/clients.bin",
        "../data/clients_id.bin"
    );

    common::Date d1{2005,1,10};
    common::Date d2{2006,5,20};
    common::Date d3{2007,8,15};

    domain::Client c1(
        "Ivan",
        "Petrenko",
        "Ivanovych",
        d1,
        "111111111111",
        1
    );

    domain::Client c2(
        "Oleh",
        "Ivanenko",
        "Petrovych",
        d2,
        "222222222222",
        2
    );

    domain::Client c3(
        "Andrii",
        "Shevchenko",
        "Mykolayovych",
        d3,
        "333333333333",
        3
    );

    clients.Add(c1);
    clients.Add(c2);
    clients.Add(c3);

    std::cout
        << "\n=== CLIENTS CREATED ===\n";

    auto allClients = clients.GetAll();

    for(auto& c : allClients)
    {
        std::cout
            << "Client ID: "
            << c.GetId()
            << "\n";
    }

    //-----------------------------------
    // DELETE SECOND CLIENT
    //-----------------------------------

    clients.Delete(2);

    std::cout
        << "\n=== AFTER DELETE CLIENT 2 ===\n";

    for(auto& c : clients.GetAll())
    {
        std::cout
            << "Client ID: "
            << c.GetId()
            << "\n";
    }

    //-----------------------------------
    // GET BY ID
    //-----------------------------------

    auto foundClient =
        clients.GetById(1);

    std::cout
      << "\nClient #1 "
      << (foundClient
            ? "FOUND"
            : "NOT FOUND")
      << "\n";


    //-----------------------------------
    // USER TESTS
    //-----------------------------------

    storage::Storage<domain::User> users(
        "../data/users.bin",
        "../data/users_id.bin"
    );

    // якщо є конструктор User(...)
    domain::User u1, u2;

    users.Add(u1);
    users.Add(u2);

    std::cout
        << "\n=== USERS CREATED ===\n";

    for(auto& u : users.GetAll())
    {
        std::cout
            << "User ID: "
            << u.GetId()
            << "\n";
    }

    //-----------------------------------
    // DELETE USER 1
    //-----------------------------------

    users.Delete(1);

    std::cout
        << "\n=== USERS AFTER DELETE ===\n";

    for(auto& u : users.GetAll())
    {
        std::cout
            << "User ID: "
            << u.GetId()
            << "\n";
    }

    //-----------------------------------
    // USER GET TEST
    //-----------------------------------

    auto foundUser=
        users.GetById(2);

    std::cout
        << "\nUser #2 "
        << (foundUser
              ? "FOUND"
              : "NOT FOUND")
        << "\n";


    std::cout
        << "\nALL TESTS DONE\n";

    return 0;
}