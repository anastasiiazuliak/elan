# Domain Analysis

Elan supports the day-to-day work of a dance and fitness studio. It organizes classes by group, dance style, skill level, and age category. A group is assigned a coach, and its weekly sessions are scheduled in halls at studio locations.

## Studio workflows

1. The system administrator sets up locations and halls, registers staff and coaches, and creates styles, groups, and subscription plans. The administrator assigns plans to groups and adds sessions to the weekly schedule.
2. An employee registers a client and assigns a membership for a group and one of its available subscription plans. The client’s age category must match the group’s category. A client can join several groups and can have one active membership per group.
3. The coach uses **My Groups** to see assigned groups, their scheduled sessions, and their enrolled clients. The client uses the dashboard to see their groups and upcoming sessions.
4. An employee or system administrator records attendance from the dashboard. Using a visit on an active membership decrements the remaining count and increments the completed count.

## Implementation

Elan is a second-year college coursework project. The C++17 backend uses Crow to serve JSON endpoints and a browser interface built with HTML, CSS, and JavaScript. The application runs on localhost and persists records in binary files. The browser stores the signed-in user’s ID and role and uses that role to choose which controls to show.

See the [README](../README.md) for the Windows build and demo accounts, and the [entity reference](entities.md) for the data model.