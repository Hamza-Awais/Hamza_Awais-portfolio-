# Airline Reservation System — Project Documentation

**Course:** Programming Fundamentals (PF)
**Language:** C++ (Windows console application)
**University:** University of Central Punjab (UCP)
**Author:** Hamza Awais

---

## 1. Introduction
The Airline Reservation System is a console-based program that lets a user manage
flight seat bookings. It has a colored, boxed user interface built with the Windows
console API. The program can show available flights, display a seat layout, book a
seat, cancel a reservation, list passengers, save all records to files, and show a
complete booking log.

The project was written using Programming Fundamentals concepts only: functions,
arrays (1-D and 2-D), dynamic memory (`new` / `delete`), pointers, file handling,
loops, conditionals and switch statements. No advanced libraries or frameworks are used.

## 2. Objectives
- Manage bookings for three flights (PK501, PK502, PK503), each with 36 seats (6 rows x 6 columns).
- Keep passenger, flight and seat records in dynamic arrays that grow and shrink at run time.
- Save and reload records so data persists between runs.
- Validate every user input so wrong input does not crash the program.
- Keep a permanent log of all bookings and cancellations.
- Present everything in a clean colored console layout.

## 3. System Design

### 3.1 Data structures
| Data | Type | Purpose |
| --- | --- | --- |
| `PK501`, `PK502`, `PK503` | `char[6][6]` | Seat layout of each flight; `' '` = free, `'X'` = booked |
| `seat[3]` | `int[3]` | Number of seats booked on each flight |
| `namelist` | `char**` | Dynamic array of passenger names |
| `userflightlist` | `char**` | Dynamic array of flight names (one per booking) |
| `userseatlist` | `char**` | Dynamic array of seat labels such as `2C` (one per booking) |
| `size`, `flightsize`, `seatsize` | `int` | Counts of entries in the three dynamic arrays |

The three dynamic arrays are **parallel**: entry `i` in each array describes the same
booking (name `i` booked flight `i` at seat `i`).

### 3.2 Files used
| File | Written by | Contents |
| --- | --- | --- |
| `namefile` | Save Data | first line = count, then one passenger name per line |
| `flightnofile` | Save Data | first line = count, then one flight number per line |
| `seatfile` | Save Data | first line = count, then one seat label per line |
| `bookinglog` | Booking / Cancel | one line per action: `ACTION \| name \| flight \| seat \| date time` |
| `passengers.txt` | (data file kept with project) | passenger count data |

### 3.3 Main menu
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

## 4. Function Reference
| Function | Role |
| --- | --- |
| `working()` | Main driver: loads data, rebuilds seats, runs the menu loop |
| `Goto(x, y)` | Moves the console cursor to a position |
| `txtcolor(c)` | Sets the console text color |
| `box(w, h)` | Draws a bordered box for the menu |
| `viewFlights(...)` | Prints the flight table and seats left (`FULL` when none left) |
| `displaySeatLayout(...)` | Draws the 6x6 seat grid for a chosen flight |
| `bookSeat(...)` | Reads name, flight, row, column; books a free seat |
| `cancelReservation(...)` | Lists bookings; frees the chosen seat and removes the record |
| `viewPassengerList(...)` | Prints all current bookings |
| `saveData(...)` | Writes the three record files |
| `viewLog()` | Reads and prints `bookinglog` |
| `getusernameList / regrow / getsinglename / copyarray` | Dynamic name-array growth |
| `getuserflight / flightregrow` | Dynamic flight-array growth |
| `getusreseat / seatregrow` | Dynamic seat-array growth |
| `gettingdatafromfile(...)` | Loads the three record files at start-up |
| `restoreSeats(...)` | Rebuilds seat grids and counts from loaded bookings |
| `markSeat(...)` | Marks a seat `X` (book) or `' '` (free) and updates the count |
| `removeEntry(...)` | Deletes one entry from a dynamic array and shifts the rest |
| `writeLog(...)` | Appends one action line to `bookinglog` |
| `cleanup(...)` | Frees all dynamic memory before exit |

## 5. Key Algorithms

### 5.1 Booking a seat
1. Read and validate the passenger name.
2. Read the flight choice (1-3), repeating until valid.
3. Read row (1-6) and column (1-6), repeating until valid.
4. If the seat already holds `'X'`, reject and ask again.
5. Otherwise mark the seat `'X'`, increase that flight's booked count, add entries to
   the flight and seat arrays, and append a `BOOKED` line to the log.

### 5.2 Cancelling a reservation
1. If there are no bookings, show a message and return.
2. Otherwise print the bookings with numbers.
3. Read a booking number (0 goes back).
4. Free that seat in the grid, lower the flight's count, write a `CANCELLED` log line,
   then remove the entry from all three parallel arrays.

### 5.3 Restoring seats on load
After reading the saved files, `restoreSeats` walks every saved booking and calls
`markSeat(..., 'X', +1)` so the seat grid and the `FULL` / seats-left display match
the saved data.

### 5.4 Dynamic array growth
`regrow`, `flightregrow` and `seatregrow` allocate a new array one slot larger, copy
the old pointers across, `delete[]` the old array, and store the new entry at the last
slot. This keeps memory use exact (no fixed maximum).

## 6. Input Validation
- Flight choice, row and column must be numbers within range; invalid input is caught
  with `cin.fail()`, cleared, and re-asked.
- An already-booked seat cannot be booked again.
- Cancel accepts only a valid booking number (or 0 to go back).

## 7. Limitations / Future Work
- Seats per flight are fixed at 36 (6x6).
- Names longer than 19 characters are truncated by the input buffer.
- The flight schedule (origin, destination, date, time) is fixed in the source.
