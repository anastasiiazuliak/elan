#include "elan/storage/ClientStorage.h"
#include "elan/storage/Id/ID.h"

#include <iostream>
#include <fstream>
#include <algorithm>

constexpr const char *FILE_NAME = "../data/clients_file.bin";
constexpr const char *ID_FILE = "../data/clients_id.bin";

namespace storage
{
    void ClientStorage::Add(domain::Client &client)
    {
        id::ID gen(ID_FILE);
        client.SetId(gen.Get());

        std::ofstream file(FILE_NAME, std::ios::binary | std::ios::app);

        if (!file.is_open())
            return;

        file.write(reinterpret_cast<const char *>(&client), sizeof(domain::Client));
    }

    std::optional<domain::Client> ClientStorage::GetById(int id)
    {
        std::ifstream file(FILE_NAME, std::ios::binary);

        domain::Client client;

        while (file.read(reinterpret_cast<char *>(&client), sizeof(domain::Client)))
        {
            if (client.GetId() == id)
                return client;
        }

        return std::nullopt;
    }

    std::vector<domain::Client> ClientStorage::GetAll()
    {
        std::vector<domain::Client> clients;
        std::ifstream file(FILE_NAME, std::ios::binary);
        domain::Client client;

        while (file.read(reinterpret_cast<char *>(&client), sizeof(domain::Client)))
        {
            clients.push_back(client);
        }

        return clients;
    }

    bool ClientStorage::Update(const domain::Client &client)
    {
        std::vector<domain::Client> clients = GetAll();

        bool found = false;

        for (domain::Client &c : clients)
        {
            if (c.GetId() == client.GetId())
            {
                c = client;
                found = true;
                break;
            }
        }

        if (!found)
            return false;

        std::ofstream file(FILE_NAME, std::ios::binary | std::ios::trunc);

        for (domain::Client &c : clients)
            file.write(reinterpret_cast<char *>(&c), sizeof(domain::Client));

        return true;
    }

    bool ClientStorage::Delete(int id)
    {

        auto clients = GetAll();
        auto oldSize = clients.size();

        clients.erase(std::remove_if (clients.begin(), clients.end(), [id](auto &c)
                {
                    return c.GetId() == id;
                }
            ),
            clients.end());

        if (oldSize == clients.size())
            return false;

        std::ofstream file(FILE_NAME, std::ios::binary | std::ios::trunc);

        for (auto &c : clients) file.write(reinterpret_cast<char *>(&c), sizeof(domain::Client));

        return true;
    }
}
