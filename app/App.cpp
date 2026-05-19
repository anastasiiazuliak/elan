#include "App.h"
#include <iostream>

storage::Storage<domain::Subscription> App::subscriptions(
    "../data/subscriptions.bin",
    "../data/subscriptions_id.bin");

storage::Storage<domain::Client> App::clients(
    "../data/clients.bin",
    "../data/clients_id.bin");

storage::Storage<domain::Style> App::styles(
    "../data/styles.bin",
    "../data/styles_id.bin");

storage::Storage<domain::Location> App::locations(
    "../data/locations.bin",
    "../data/locations_id.bin");

storage::Storage<domain::Group> App::groups(
    "../data/groups.bin",
    "../data/groups_id.bin");

storage::Storage<domain::Employee> App::employees(
    "../data/employees.bin",
    "../data/employees_id.bin");

storage::Storage<domain::Coach> App::coaches(
    "../data/coaches.bin",
    "../data/coaches_id.bin");

storage::Storage<domain::Admin> App::admin(
        "../data/admin.bin",
        "../data/admin_id.bin");

void App::addTestData()
{
    //Адмін
    domain::Admin a("Анастасія", "Зуляк", "Любомирівна", common::Date(28, 11, 2008), "0955681473", "2008", "anastasiiazuliak");

    admin.Add(a);

    // Абонементи
    domain::Subscription sub1("Дорослі", common::Category::Age_16_plus, 28, 12);
    domain::Subscription sub2("Підлітки", common::Category::Age_14_plus, 28, 12);
    domain::Subscription sub3("Діти", common::Category::Age_6_plus, 28, 12);

    subscriptions.Add(sub1);
    subscriptions.Add(sub2);
    subscriptions.Add(sub3);

    // клієети
    domain::Client c1("Karina", "Havriluik", "Ihorvna", common::Date(2010, 4, 10), "0956182688", 1, "200828", "karina_client");
    domain::Client c2("Stanislav", "Moscalu", "Michailovych", common::Date(2012, 6, 18), "380671223344", 2, "200828", "stas_client");
    domain::Client c3("Andrii", "Hodan", "Olehrovych", common::Date(2014, 3, 25), "380931122233", 3, "200828", "andrii_client");

    clients.Add(c1);
    clients.Add(c2);
    clients.Add(c3);

    // стилі
    domain::Style s1("Contemporary", "Expressive modern dance focused on emotions and movements");
    domain::Style s2("Hip-Hop", "Dynamic street dance style with energetic choreography");
    domain::Style s3("Ballet", "Classical dance style focused on technique and flexibility");
    domain::Style s4("Pilates", "Core strength and posture improvement exercises");
    domain::Style s5("Yoga", "Flexibility, balance and breathing exercises");
    domain::Style s6("Zumba", "Dance-based cardio fitness workout");
    domain::Style s7("Stretching", "Exercises for improving flexibility and mobility");
    domain::Style s8("Fitness Mix", "Combination of cardio and strength fitness training");

    styles.Add(s1);
    styles.Add(s2);
    styles.Add(s3);
    styles.Add(s4);
    styles.Add(s5);
    styles.Add(s6);
    styles.Add(s7);
    styles.Add(s8);

    // зали
    domain::Hall h1(24);
    domain::Hall h2(20);
    domain::Hall h3(14);
    domain::Hall h4(10);
    domain::Hall h5(5);
    domain::Hall h6(8);
    domain::Hall h7(7);
    domain::Hall h8(9);
    domain::Hall h9(11);
    domain::Hall h10(16);

    // зали
    domain::Location l1("Heroiv Maidanu");

    l1.AddHall(h1);
    l1.AddHall(h2);
    l1.AddHall(h3);
    l1.AddHall(h4);

    domain::Location l2("Kaspruca 2");

    l2.AddHall(h5);
    l2.AddHall(h6);
    l2.AddHall(h7);

    domain::Location l3("Polytech");

    l3.AddHall(h8);
    l3.AddHall(h9);
    l3.AddHall(h10);

    locations.Add(l1);
    locations.Add(l2);
    locations.Add(l3);

    // Тренери
    domain::Coach coach1(
        "Alina",
        "Petrenko",
        "Olehivna",
        common::Date(1998, 5, 12),
        "380991112233",
        "Contemporary and fitness trainer with 5 years of experience",
        "alina123",
        "alina_coach");

    domain::Coach coach2(
        "Maksym",
        "Bondarenko",
        "Serhiiovych",
        common::Date(1995, 9, 21),
        "380671234567",
        "Hip-Hop trainer and choreographer",
        "maks123",
        "maks_coach");

    domain::Coach coach3(
        "Sofiia",
        "Koval",
        "Ivanivna",
        common::Date(1993, 2, 3),
        "380931119988",
        "Professional ballet and stretching instructor",
        "sofia123",
        "sofia_coach");

    coach1.AddStyle(s1);
    coach1.AddStyle(s3);
    coach1.AddStyle(s5);

    coach2.AddStyle(s2);
    coach2.AddStyle(s6);
    coach2.AddStyle(s8);

    coach3.AddStyle(s8);
    coach3.AddStyle(s1);
    coach3.AddStyle(s4);

    coaches.Add(coach1);
    coaches.Add(coach2);
    coaches.Add(coach3);

    // Групи
    domain::Group g1(1, s1, domain::SkillLevel::Beginner);
    domain::Group g2(2, s2, domain::SkillLevel::Intermediate);
    domain::Group g3(3, s3, domain::SkillLevel::Advanced);
    domain::Group g4(1, s4, domain::SkillLevel::Beginner);
    domain::Group g5(2, s5, domain::SkillLevel::Intermediate);
    domain::Group g6(3, s6, domain::SkillLevel::Advanced);

    groups.Add(g1);
    groups.Add(g2);
    groups.Add(g3);
    groups.Add(g4);
    groups.Add(g5);
    groups.Add(g6);

    // Працівники
    domain::Employee e1(
        "Olena",
        "Marchuk",
        "Vasylivna",
        common::Date(1999, 7, 14),
        "380501112233",
        1,
        "olena.elan@gmail.com",
        "olena123",
        "olena_employee");

    domain::Employee e2(
        "Dmytro",
        "Kovalchuk",
        "Petrovych",
        common::Date(1997, 11, 2),
        "380671234890",
        2,
        "dmytro.elan@gmail.com",
        "dmytro123",
        "dmytro_employee");

    domain::Employee e3(
        "Iryna",
        "Shevchenko",
        "Mykolaivna",
        common::Date(2001, 1, 25),
        "380931117744",
        3,
        "iryna.elan@gmail.com",
        "iryna123",
        "iryna_employee");

    employees.Add(e1);
    employees.Add(e2);
    employees.Add(e3);
}

void App::EmployeesMenu()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========== EMPLOYEES MENU ==========\n";
        std::cout << "1. Show all employees\n";
        std::cout << "2. Find employee by ID\n";
        std::cout << "3. Add employee\n";
        std::cout << "4. Delete employee\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            auto all = employees.GetAll();

            if (all.empty())
            {
                std::cout << "No employees found\n";
                break;
            }

            for (auto &e : all)
            {
                e.PrintEmployee();
                std::cout << "-------------------\n";
            }

            break;
        }

        case 2:
        {
            int id;
            std::cout << "Enter employee ID: ";
            std::cin >> id;

            auto emp = employees.GetById(id);

            if (!emp)
            {
                std::cout << "Employee not found\n";
                break;
            }

            emp->PrintEmployee();
            break;
        }

        case 3:
        {
            char firstName[50], lastName[50], patronymic[50];
            int day = 0;
            int month = 0;
            int year = 0;
            char phone[20], email[50], username[50], password[50];
            int locationId;

            std::cout << "First name: ";
            std::cin >> firstName;

            std::cout << "Last name: ";
            std::cin >> lastName;

            std::cout << "Patronymic: ";
            std::cin >> patronymic;

            std::cout << "Birth day: ";
            std::cin >> day;
            std::cout << "month: ";
            std::cin >> month;
            std::cout << "year: ";
            std::cin >> year;

            std::cout << "Phone: ";
            std::cin >> phone;

            std::cout << "Email: ";
            std::cin >> email;

            std::cout << "Username: ";
            std::cin >> username;

            std::cout << "Password: ";
            std::cin >> password;

            std::cout << "Location ID: ";
            std::cin >> locationId;

            domain::Employee emp(
                firstName,
                lastName,
                patronymic,
                common::Date{day, month, year},
                phone,
                locationId,
                email,
                password,
                username);

            employees.Add(emp);

            std::cout << "Employee added!\n";
            break;
        }

        case 4:
        {
            int id;
            std::cout << "Enter employee ID to delete: ";
            std::cin >> id;

            if (employees.Delete(id))
                std::cout << "Deleted successfully\n";
            else
                std::cout << "Employee not found\n";

            break;
        }

        case 0:
            std::cout << "Back...\n";
            break;

        default:
            std::cout << "Invalid option\n";
        }
    }
}

void App::CoachesMenu()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========== COACHES MENU ==========\n";
        std::cout << "1. Show all coaches\n";
        std::cout << "2. Find coach by ID\n";
        std::cout << "3. Add coach\n";
        std::cout << "4. Delete coach\n";
        std::cout << "5. Add style to coach\n";
        std::cout << "6. Remove style from coach\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        service::CoachService service;

        switch (choice)
        {
        case 1:
        {
            auto all = coaches.GetAll();

            if (all.empty())
            {
                std::cout << "No coaches found\n";
                break;
            }

            for (auto &c : all)
            {
                c.PrintCoach();
                std::cout << "-------------------\n";
            }

            break;
        }

        case 2:
        {
            int id;
            std::cout << "Enter coach ID: ";
            std::cin >> id;

            auto coach = coaches.GetById(id);

            if (!coach)
            {
                std::cout << "Coach not found\n";
                break;
            }

            coach->PrintCoach();
            break;
        }

        case 3:
        {
            char firstName[50], lastName[50], patronymic[50];
            int day = 0;
            int month = 0;
            int year = 0;
            char phone[20], description[100];
            char username[50], password[50];

            std::cout << "First name: ";
            std::cin >> firstName;

            std::cout << "Last name: ";
            std::cin >> lastName;

            std::cout << "Patronymic: ";
            std::cin >> patronymic;

            std::cout << "Birth day: ";
            std::cin >> day;
            std::cout << "month: ";
            std::cin >> month;
            std::cout << "year: ";
            std::cin >> year;

            std::cout << "Phone: ";
            std::cin >> phone;

            std::cout << "Description: ";
            std::cin >> description;

            std::cout << "Username: ";
            std::cin >> username;

            std::cout << "Password: ";
            std::cin >> password;

            domain::Coach coach(
                firstName,
                lastName,
                patronymic,
                common::Date{day, month, year},
                phone,
                description,
                password,
                username);

            coaches.Add(coach);

            std::cout << "Coach added!\n";
            break;
        }

        case 4:
        {
            int id;
            std::cout << "Enter coach ID to delete: ";
            std::cin >> id;

            if (coaches.Delete(id))
                std::cout << "Deleted successfully\n";
            else
                std::cout << "Coach not found\n";

            break;
        }

        case 5:
        {
            int coachId, styleId;

            std::cout << "Coach ID: ";
            std::cin >> coachId;

            std::cout << "Style ID: ";
            std::cin >> styleId;

            service.AddStyleToCoach(coachId, styleId);

            std::cout << "Style added to coach\n";
            break;
        }

        case 6:
        {
            int coachId, styleId;

            std::cout << "Coach ID: ";
            std::cin >> coachId;

            std::cout << "Style ID: ";
            std::cin >> styleId;

            service.RemoveStyleFromCoach(coachId, styleId);

            std::cout << "Style removed\n";
            break;
        }

        case 0:
            std::cout << "Back...\n";
            break;

        default:
            std::cout << "Invalid option\n";
        }
    }
}

void App::GroupsMenu()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========== GROUPS MENU ==========\n";
        std::cout << "1. Show all groups\n";
        std::cout << "2. Find group by ID\n";
        std::cout << "3. Add group\n";
        std::cout << "4. Delete group\n";
        std::cout << "5. Add client to group\n";
        std::cout << "6. Remove client from group\n";
        std::cout << "7. Show groups by coach ID\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        service::GroupService service;

        switch (choice)
        {
        case 1:
        {
            auto all = groups.GetAll();

            if (all.empty())
            {
                std::cout << "No groups found\n";
                break;
            }

            for (auto &g : all)
            {
                g.PrintGroup();
                std::cout << "-------------------\n";
            }

            break;
        }

        case 2:
        {
            int id;
            std::cout << "Enter group ID: ";
            std::cin >> id;

            auto group = groups.GetById(id);

            if (!group)
            {
                std::cout << "Group not found\n";
                break;
            }

            group->PrintGroup();
            break;
        }

        case 3:
        {
            int coachId;
            int skillLevelInt;
            int styleId;

            std::cout << "Coach ID: ";
            std::cin >> coachId;

            std::cout << "Style ID: ";
            std::cin >> styleId;

            std::cout << "Skill level (0 Beginner, 1 Intermediate, 2 Advanced): ";
            std::cin >> skillLevelInt;

            domain::Style style = styles.GetById(styleId).value();

            domain::Group group(
                coachId,
                style,
                static_cast<domain::SkillLevel>(skillLevelInt));

            groups.Add(group);

            std::cout << "Group added!\n";
            break;
        }

        case 4:
        {
            int id;
            std::cout << "Enter group ID: ";
            std::cin >> id;

            if (groups.Delete(id))
                std::cout << "Deleted successfully\n";
            else
                std::cout << "Group not found\n";

            break;
        }

        case 5:
        {
            int groupId, clientId;

            std::cout << "Group ID: ";
            std::cin >> groupId;

            std::cout << "Client ID: ";
            std::cin >> clientId;

            service.AddClientToGroup(groupId, clientId);

            std::cout << "Client added to group\n";
            break;
        }

        case 6:
        {
            int groupId, clientId;

            std::cout << "Group ID: ";
            std::cin >> groupId;

            std::cout << "Client ID: ";
            std::cin >> clientId;

            service.RemoveClientFromGroup(groupId, clientId);

            std::cout << "Client removed\n";
            break;
        }

        case 7:
        {
            int coachId;

            std::cout << "Coach ID: ";
            std::cin >> coachId;

            auto coachGroups = service.GetGroupsByCoachId(coachId);

            for (auto &g : coachGroups)
            {
                g.PrintGroup();
                std::cout << "-------------------\n";
            }

            break;
        }

        case 0:
            std::cout << "Back...\n";
            break;

        default:
            std::cout << "Invalid option\n";
        }
    }
}

void App::LocationHallsMenu()
{
    int choice;

    while (true)
    {
        std::cout << "\n===== HALLS MENU =====\n";
        std::cout << "1. Add hall\n";
        std::cout << "2. Remove hall\n";
        std::cout << "3. Show halls\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        if (choice == 0)
            return;

        int locationId;
        std::cout << "Location ID: ";
        std::cin >> locationId;

        auto locOpt = locations.GetById(locationId);
        if (!locOpt)
        {
            std::cout << "Location not found\n";
            continue;
        }

        auto loc = *locOpt;

        service::LocationService service;

        switch (choice)
        {
        case 1:
        {
            int capacity;
            std::cout << "Capacity: ";
            std::cin >> capacity;

            domain::Hall hall(capacity);

            service.AddHall(locationId, hall);

            std::cout << "Hall added\n";
            break;
        }

        case 2:
        {
            int hallId;
            std::cout << "Hall ID: ";
            std::cin >> hallId;

            service.RemoveHall(locationId, hallId);

            std::cout << "Removed\n";
            break;
        }

        case 3:
        {
            loc.PrintLocationHalls();
            break;
        }
        }
    }
}

void App::LocationScheduleMenu()
{
    int locationId;
    std::cout << "Location ID: ";
    std::cin >> locationId;

    auto locOpt = locations.GetById(locationId);
    if (!locOpt)
    {
        std::cout << "Not found\n";
        return;
    }

    auto loc = *locOpt;

    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n===== SCHEDULE MENU =====\n";
        std::cout << "1. Show schedule\n";
        std::cout << "2. Add schedule\n";
        std::cout << "3. Remove schedule\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        service::LocationService service;

        switch (choice)
        {
        case 1:
            loc.PrintLocationSchedule();
            break;

        case 2:
        {
            domain::Schedule s;

            std::cout << "Hall ID: ";
            std::cin >> s.hallId;

            std::cout << "Group ID: ";
            std::cin >> s.groupId;

            int d, t;
            std::cout << "Day (0-5): ";
            std::cin >> d;
            std::cout << "Time (0-12): ";
            std::cin >> t;

            s.day = static_cast<domain::Day>(d);
            s.time = static_cast<domain::Time>(t);

            service.AddSchedule(locationId, s);

            std::cout << "Added\n";
            break;
        }

        case 3:
        {
            domain::Schedule s;

            std::cout << "Hall ID: ";
            std::cin >> s.hallId;

            int d, t;
            std::cout << "Day: ";
            std::cin >> d;
            std::cout << "Time: ";
            std::cin >> t;

            s.day = static_cast<domain::Day>(d);
            s.time = static_cast<domain::Time>(t);

            service.RemoveSchedule(locationId, s);

            std::cout << "Removed\n";
            break;
        }
        }
    }
}

void App::LocationsMenu()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========== LOCATIONS MENU ==========\n";
        std::cout << "1. Show all locations\n";
        std::cout << "2. Find location by ID\n";
        std::cout << "3. Add location\n";
        std::cout << "4. Delete location\n";
        std::cout << "5. Manage halls\n";
        std::cout << "6. Manage schedule\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            auto all = locations.GetAll();

            for (auto &l : all)
            {
                l.PrintLocation();
                std::cout << "-------------------\n";
            }
            break;
        }

        case 2:
        {
            int id;
            std::cout << "Enter location ID: ";
            std::cin >> id;

            auto loc = locations.GetById(id);

            if (!loc)
            {
                std::cout << "Not found\n";
                break;
            }

            loc->PrintLocation();
            break;
        }

        case 3:
        {
            char address[100];

            std::cout << "Address: ";
            std::cin >> address;

            domain::Location loc(address);
            locations.Add(loc);

            std::cout << "Added!\n";
            break;
        }

        case 4:
        {
            int locationId;

            std::cout << "Location ID: ";
            std::cin >> locationId;

            locations.Delete(locationId);

            std::cout << "Deleted!\n";
            break;
        }

        case 5:
            LocationHallsMenu();
            break;

        case 6:
            LocationScheduleMenu();
            break;

        case 0:
            break;

        default:
            std::cout << "Invalid\n";
        }
    }
}

void App::StylesMenu()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========== STYLES MENU ==========\n";
        std::cout << "1. Show all styles\n";
        std::cout << "2. Find style by ID\n";
        std::cout << "3. Add style\n";
        std::cout << "4. Delete style\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            auto all = styles.GetAll();

            if (all.empty())
            {
                std::cout << "No styles found\n";
                break;
            }

            for (auto &s : all)
            {
                s.PrintStyle();
                std::cout << "-------------------\n";
            }

            break;
        }

        case 2:
        {
            int id;
            std::cout << "Enter style ID: ";
            std::cin >> id;

            auto s = styles.GetById(id);

            if (!s)
            {
                std::cout << "Style not found\n";
                break;
            }

            s->PrintStyle();
            break;
        }

        case 3:
        {
            char name[50], desc[100];

            std::cout << "Name: ";
            std::cin >> name;

            std::cout << "Description: ";
            std::cin >> desc;

            domain::Style style(name, desc);
            styles.Add(style);

            std::cout << "Style added!\n";
            break;
        }

        case 4:
        {
            int id;
            std::cout << "Enter style ID: ";
            std::cin >> id;

            if (styles.Delete(id))
                std::cout << "Deleted successfully\n";
            else
                std::cout << "Style not found\n";

            break;
        }

        case 0:
            std::cout << "Back...\n";
            break;

        default:
            std::cout << "Invalid option\n";
        }
    }
}

void App::SubscriptionsMenu()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========== SUBSCRIPTIONS MENU ==========\n";
        std::cout << "1. Show all subscriptions\n";
        std::cout << "2. Find subscription by ID\n";
        std::cout << "3. Add subscription\n";
        std::cout << "4. Delete subscription\n";
        std::cout << "0. Back\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            auto all = subscriptions.GetAll();

            if (all.empty())
            {
                std::cout << "No subscriptions found\n";
                break;
            }

            for (auto &s : all)
            {
                s.PrintSubscription();
                std::cout << "-------------------\n";
            }

            break;
        }

        case 2:
        {
            int id;
            std::cout << "Enter subscription ID: ";
            std::cin >> id;

            auto sub = subscriptions.GetById(id);

            if (!sub)
            {
                std::cout << "Subscription not found\n";
                break;
            }

            sub->PrintSubscription();
            break;
        }

        case 3:
        {
            char name[50];
            int category, duration, workouts;

            std::cout << "Name: ";
            std::cin >> name;

            std::cout << "Category (0-6): ";
            std::cin >> category;

            std::cout << "Duration (months): ";
            std::cin >> duration;

            std::cout << "Number of workouts: ";
            std::cin >> workouts;

            domain::Subscription sub(
                name,
                static_cast<common::Category>(category),
                duration,
                workouts);

            subscriptions.Add(sub);

            std::cout << "Subscription added!\n";
            break;
        }

        case 4:
        {
            int id;
            std::cout << "Enter subscription ID: ";
            std::cin >> id;

            if (subscriptions.Delete(id))
                std::cout << "Deleted successfully\n";
            else
                std::cout << "Subscription not found\n";

            break;
        }

        case 0:
            std::cout << "Back...\n";
            break;

        default:
            std::cout << "Invalid option\n";
        }
    }
}

void App::ShowMainMenu()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========== ELAN ==========\n";
        std::cout << "1. Employees\n";
        std::cout << "2. Coaches\n";
        std::cout << "3. Groups\n";
        std::cout << "4. Locations\n";
        std::cout << "5. Subscriptions\n";
        std::cout << "6. Styles\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose option: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            EmployeesMenu();
            break;

        case 2:
            CoachesMenu();
            break;

        case 3:
            GroupsMenu();
            break;

        case 4:
            LocationsMenu();
            break;

        case 5:
            SubscriptionsMenu();
            break;

        case 6:
            StylesMenu();
            break;

        case 0:
            std::cout << "Bye!\n";
            break;

        default:
            std::cout << "Invalid option\n";
        }
    }
}

void App::LoginMenu()
{
    char username[50];
    char password[50];

    std::cout << "\n========== LOGIN ==========\n";

    std::cout << "Username: ";
    std::cin >> username;

    std::cout << "Password: ";
    std::cin >> password;

    auto user = service::AuthService::Login(username, password);

    if (!user)
    {
        std::cout << "\nInvalid username or password\n";
        return;
    }

    std::cout << "\nLogin successful!\n";

/*
    switch (user->GetRole())
    {
    case domain::Role::Admin:
        std::cout << "Logged as ADMIN\n";
        ShowMainMenu();
        break;

    case domain::Role::Coach:
        std::cout << "Logged as COACH\n";
        CoachesMenu();
        break;

    case domain::Role::Employee:
        std::cout << "Logged as EMPLOYEE\n";
        EmployeesMenu();
        break;

    case domain::Role::Client:
        std::cout << "Logged as CLIENT\n";
        ClientsMenu();
        break;
    

    default:
        std::cout << "Unknown role\n";
        break;
    }*/

    ShowMainMenu();
}