
# Setup / General Info
- Used C++ and Qt
- It requires Qt 5
- It is a Qt Creator project.\
Set the appropriate kit inside Qt Creator (Qt 5)
- It uses MariaDB
- Set the database parameters (username, password, etc.) in *config.cpp*
- Create an empty database
`CREATE DATABASE blueCar;`
- Then run all
*sql.txt*
It generates and populates the tables and views
# Run
To run:
```
chmod +x runBlueCar.sh
./runBlueCar.sh
```
*error.log* → debug info and errors
# External Modules
Submodules used by the application that have not been developed by me:
- rbk\
https://github.com/dublinbranch/rbk\
General utility functions.\
E.g., used to run queries on the database\
- variadictable.h\
https://github.com/friedmud/variadic_table/blob/master/include/VariadicTable.h\
To print ASCII tables
# Definitions
## blueCar
Name of the application requested
## Admin
Role of the boss who manages the cars and the users
## User / Normal User
Role of a person who rents a car
## Pickup Point (PUP)
A point where a user can pick up (and then return) a car who has rented
# Car Location
Assumption: each location (circle) has exactly 1 PUP.\
So, when a car is free, its location is the circle where the PUP is located (column car.locationId in the database), while when a car is rented, the location is unknown (car.locationId = NULL)
# Hash Function
The program can use 2 hash functions (according to *simulateHash* in *config.cpp*):
- Simulated hash function
For testing and debugging, the function is (not a hash one):\
`<string> → HASH_OF_<string>`
- RealSha3_512

Important note:\
I used RealSha3_512 for ease of implementation and because the application is not real.
In a real application, it would be necessary to use strong functions like bcrypt or PBKDF2
https://stackoverflow.com/questions/16877976/is-the-c-hash-function-reasonably-safe-for-passwords

