# Airline Reservation System

| **Course** | Programming Fundamentals (PF) |
| **Language** | C++ |
| **University** | University of Central Punjab (UCP) |
| **Type** | Console application (colored UI, Windows) |

A menu-based airline reservation system with a colored console interface. The cursor is placed with the Windows console API to draw a boxed main menu, a seat layout grid, and colored status messages. Passenger, flight and seat records are kept in dynamic arrays and saved to files, so bookings are still there the next time the program runs.

## Features
- **View Available Flights:** shows 3 flights (PK501, PK502, PK503) with origin, destination, date, time and seats left; a flight with no seat left is shown as `FULL`
- **Display Seat Layout:** a 6x6 grid (rows 1-6, columns A-F) for any flight; booked seats are marked `X` in a different color
- **Book a Seat:** enter passenger name, choose a flight, then a row and column; input is validated and an already-booked seat cannot be booked again
- **Cancel a Reservation:** the passenger list is shown with numbers; pick a number to cancel, which frees the seat and lowers the booked count
- **View Passenger List:** lists every current booking (name, flight, seat)
- **Save Data to File:** writes the name, flight and seat records to `namefile`, `flightnofile` and `seatfile`
- **View Booking Log:** shows the full history of every booking and cancellation with date and time
- Colored output and cursor placement give the whole program a clean, boxed layout

## How it works
- Each flight has 6 x 6 = **36 seats**. Seats left = 36 - seats booked.
- Bookings are stored in three parallel dynamic arrays (name, flight, seat). Adding a booking grows the arrays by one; cancelling removes the entry from all three and shifts the rest down.
- On start-up the program reads the saved files and **rebuilds the seat grids and booked counts**, so the seat layout matches the saved bookings.
- Every booking and cancellation is appended to the `bookinglog` file, which the View Booking Log option reads back.

## Menu
```
1. View Available Flights
2. Display Seat Layout
3. Book a Seat
4. Cancel a Reservation
5. View Passenger List
6. Save Data to File
7. View Booking Log
8. Exit
```

## How to compile and run
This project uses the Windows console API (`windows.h`), so it must be built on Windows with MSVC (Visual Studio) or MinGW.

- **Visual Studio:** open the project and press `Ctrl + F5` (Run Without Debugging).
- **MinGW (g++):**
  ```
  g++ airline_reservation_system.cpp -o airline
  airline.exe
  ```

> Keep the data files (`namefile`, `flightnofile`, `seatfile`) in the same folder as the program so saved bookings can be loaded. The `bookinglog` file is created automatically the first time you book or cancel.

## Files
- `airline_reservation_system.cpp`: the source code
- `namefile`: saved passenger names (first line = count)
- `flightnofile`: saved flight number for each booking (first line = count)
- `seatfile`: saved seat label for each booking (first line = count)
- `passengers.txt`: passenger count data file kept with the project
- `bookinglog`: created at run time; holds the booking / cancellation history
- `Airline_Reservation_System_Documentation.md`: full project documentation

