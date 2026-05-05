#include "elan/storage/Storage.h"

namespace service
{
    class AuthService
    {
    public:
        AuthService(storage::Storage<domain::Person> &persons);

        domain::Person *Login(const char *username, const char *password);
    };
}