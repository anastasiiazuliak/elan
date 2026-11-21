# Entities

## Person
```json
{
    "Id": "int",
    "FirstName": "string",
    "LastName": "string",
    "Patronymic": "string",
    "BirthDate": "datetime",
    "Phone": "string",
    "Username": "string",
    "Password": "hash",
    "Role": "Role"
}
```

Person є базовою сутністю системи. Вона містить персональні дані користувача, а також інформацію для авторизації: логін (Username), пароль (Password) та роль (Role). Від цієї сутності успадковуються клієнти, працівники та тренери.

---

## Client
```json
{
    "Id": "int",
    "SubscriptionId": "int",
    "SubscriptionStartDate": "datetime",
    "SubscriptionEndDate": "datetime",
    "RemainingWorkouts": "int",
    "CompletedWorkouts": "int",
    "Category": "Category"
}
```

Client успадковує Person та представляє клієнта студії. Для клієнта зберігається інформація про активний абонемент, термін його дії, кількість доступних та використаних занять, а також категорія клієнта.

---

## Employee
```json
{
    "Id": "int",
    "LocationId": "int",
    "Email": "string"
}
```

Employee успадковує Person та представляє працівника студії. Основними атрибутами є локація роботи та службова електронна адреса.

---

## Coach
```json
{
    "Id": "int",
    "Styles": "int[]",
    "Description": "string"
}
```

Coach успадковує Person та представляє тренера студії. Для кожного тренера зберігається перелік стилів, які він викладає, а також його опис.

---

## Group
```json
{
    "Id": "int",
    "Name": "string",
    "CoachId": "int",
    "StyleId": "int",
    "SkillLevel": "SkillLevel",
    "Clients": "Client[]"
}
```

Group містить інформацію про навчальну групу. Кожна група має назву, тренера, стиль танцю, рівень підготовки та список клієнтів, які її відвідують.

### SkillLevel
```text
Beginner
Intermediate
Advanced
```

---

## Location
```json
{
    "Id": "int",
    "Address": "string",
    "Halls": "Hall[]",
    "Schedule": "Schedule[]"
}
```

Location описує одну з локацій студії. Вона містить адресу, список залів та розклад занять.

---

## Hall
```json
{
    "Id": "int",
    "Name": "string",
    "Type": "HallType",
    "Capacity": "int"
}
```

Hall представляє фізичний зал для проведення занять. Для кожного залу зберігається назва, тип та максимальна кількість відвідувачів.

### HallType
```text
Large
Medium
Individual
```

---

## Schedule
```json
{
    "GroupId": "int",
    "HallId": "int",
    "Day": "Day",
    "Time": "Time",
    "IsOccupied": "bool"
}
```

Schedule використовується для формування розкладу занять. Він пов'язує групу та зал у певний день і час.

### Day
```text
Monday
Tuesday
Wednesday
Thursday
Friday
Saturday
```

### Time
```text
08:00
09:00
10:00
11:00
12:00
13:00
14:00
15:00
16:00
17:00
18:00
19:00
20:00
```

---

## Style
```json
{
    "Id": "int",
    "Name": "string",
    "Description": "string"
}
```

Style описує танцювальний або спортивний напрямок студії. Містить назву стилю та його опис.

---

## Subscription
```json
{
    "Id": "int",
    "Name": "string",
    "Category": "Category",
    "Duration": "int",
    "NumberOfWorkouts": "int",
    "GroupId": "int"
}
```

Subscription описує абонементи студії. Для кожного абонемента зберігається назва, категорія клієнтів, тривалість дії, кількість занять та група, до якої він прив'язаний.

---

## Role
```text
Admin
Client
Employee
Coach
```