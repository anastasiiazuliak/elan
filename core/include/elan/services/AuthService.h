#include "elan/storage/Storage.h"

namespace service
{
    class AuthService
    {
        storage::Storage<domain::Person> &persons;

    public:
        AuthService(storage::Storage<domain::Person> &persons);

        domain::Person *Login(const char *username, const char *password);
    };
}