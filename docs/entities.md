# Entities

The following fields describe the C++ domain model. JSON response fields are defined separately by the API controllers and DTOs.

| Entity | Stored fields and purpose |
| --- | --- |
| `Person` | Base class for accounts. Holds ID, first name, last name, patronymic, birth date, phone, username, password hash, and role. Login reports the role associated with the account store. |
| `Admin` | System administrator account. |
| `Client` | Client account with an age category derived from the date of birth. |
| `Employee` | Studio employee account with an assigned location ID. The demo uses `0` for an unassigned location. |
| `Coach` | Coach account with a description and up to 10 style IDs. |
| `Style` | Dance or fitness style with an ID, name, and description. |
| `Group` | Named group with an ID, coach ID, style ID, skill level, age category, and up to 10 allowed subscription plan IDs. |
| `Location` | Studio location with an ID, address, up to 5 halls, and weekly schedule slots. |
| `Hall` | Room within a location with a local ID, name, capacity, and a type derived from capacity. |
| `Schedule` | Weekly slot in a location, identified by hall, weekday, and hour. Holds a group ID and an occupancy flag. |
| `Subscription` | Reusable plan with an ID, name, duration in days, number of visits, and price. |
| `Membership` | Enrollment record with its own ID and references to a client, group, and subscription plan. Stores start and end dates, remaining visits, and completed visits. |

## Enumerations and schedule

| Value | Options |
| --- | --- |
| Role | System administrator (`Admin`, 0), client (`Client`, 1), employee (`Employee`, 2), coach (`Coach`, 3) |
| Skill level | Beginner, Intermediate, Advanced |
| Age category | 3–5, 5+, 6+, 7+, 10–12, 14+, 16+ |
| Hall type | Large, Medium, Individual |
| Schedule slots | Monday through Saturday, hourly from 08:00 through 20:00 |

See [Relationships](relationships.md) for how these entities are connected.