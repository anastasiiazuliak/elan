# Elan Dance & Fitness Studio

I built Elan as my second-year college coursework project in C++. It uses the Crow C++ web framework to serve a browser interface and a JSON API for managing a dance and fitness studio.

The studio can maintain clients, coaches, staff, dance styles, groups, locations, halls, weekly schedules, and class passes. Memberships link clients to groups and track the visits covered by a pass.

## Roles and demo sign-in

| Role | Username | What the web interface supports |
| --- | --- | --- |
| System administrator | `demo-admin` | Manage studio catalogs, staff, groups, and schedules, and record attendance. |
| Employee (location administrator) | `demo-employee` | Register clients, assign group memberships, and record attendance from the dashboard. |
| Coach | `demo-coach` | View assigned groups, their schedules, and enrolled clients. |
| Client | `demo-client` | View the personal dashboard and schedule, and browse studio listings. |

The password for all four accounts is **`ElanDemo2026`**. These credentials are for the local demo.

## Build and run on Windows

Use CMake 3.16 or later, Visual Studio with the **Desktop development with C++** workload, and a bootstrapped vcpkg installation. Install Crow and run the following from the project root in PowerShell. This example assumes vcpkg is in a local `vcpkg/` folder. Adjust the vcpkg paths if you installed it elsewhere.

```powershell
.\vcpkg\vcpkg.exe install crow:x64-windows
cmake -S . -B build "-DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -A x64
cmake --build build --config Release
.\build\Release\ELAN.exe --seed-demo
.\build\Release\ELAN.exe
```

Open [Elan](http://127.0.0.1:18080/) and sign in with one of the demo accounts. Run `--seed-demo` once on a fresh checkout, with the server stopped. It creates one account per role and requires a `data/` directory with no `.bin` files. Start the server without arguments on subsequent runs.

Elan stores records and ID counters in local binary files under `data/`. The demo starts with empty studio catalogs. The demo employee has no assigned location until one is created and assigned. The browser interface is in Ukrainian.

## Project layout

| Path | Contents |
| --- | --- |
| `app/` | Server entry point and demo account setup |
| `core/include/elan/` | Public headers for the API, domain model, services, DTOs, and storage |
| `core/src/` | Implementations for those components |
| `frontend/` | HTML, CSS, browser JavaScript, and assets |
| `data/` | Local binary storage created at runtime |
| `docs/` | Domain and data model documentation |

- [Domain analysis](docs/domain-analysis.md)
- [Entities](docs/entities.md)
- [Relationships](docs/relationships.md)