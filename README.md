# Flight Ticket Management System

## Overview

The Flight Ticket Management System is a C++ program that manages flight ticket information using a hash table implementation. It supports importing and exporting flight tickets, adding new tickets, deleting tickets, searching for specific tickets, and viewing tickets sorted by date or destination.

## Directory Structure

```
.
├── flightticket.cpp      # Implementation for the Flight_Ticket class
├── flightticket.h        # Header file for the Flight_Ticket class
├── flighthashtable.cpp   # Implementation for the FlightHASHTABLE class
├── flighthashtable.h     # Header file for the FlightHASHTABLE class
├── mylist.cpp            # Implementation for a doubly linked list template
├── mylist.h              # Header file for the doubly linked list template
├── main.cpp              # Main driver file for the program
├── Makefile              # Makefile for compiling the program
├── README.md             # Documentation file
```

## Features

- **Import Tickets**: Import flight tickets from a CSV file.
- **Export Tickets**: Export flight tickets to a CSV file.
- **Count Collisions**: Display the number of collisions in the hash table.
- **Add Ticket**: Add a new flight ticket to the system.
- **Delete Ticket**: Delete a specific flight ticket by its key.
- **Find Ticket**: Search for a flight ticket by its key.
- **View Tickets by Date**: Display all tickets on a specific date.
- **Print in Ascending Order**: Print tickets in ascending order of the destination.

## Dependencies

- C++ Standard Library

## Compilation and Execution

### Compilation

The program can be compiled using the provided `Makefile`. Run the following command:

```bash
make
```

This will generate an executable file named `ftm.out`.

### Execution

Run the program using:

```bash
./ftm.out
```

## Commands

The program accepts the following commands:

| Command            | Description                                                  |
| ------------------ | ------------------------------------------------------------ |
| `import <path>`    | Import flight tickets from a CSV file.                       |
| `export <path>`    | Export flight tickets to a CSV file.                         |
| `count_collisions` | Print the number of hash table collisions.                   |
| `add`              | Add a new flight ticket.                                     |
| `delete <key>`     | Delete a flight ticket by key (company name, flight number). |
| `find <key>`       | Find a flight ticket by key (company name, flight number).   |
| `allinday <date>`  | Display all flight tickets for a specific date.              |
| `printASC <key>`   | Print flight tickets in ascending order of the destination.  |
| `help`             | Display the list of commands.                                |
| `exit`             | Exit the program.                                            |

## Input Validation

The program includes extensive input validation for:

- **Company Name**: Ensures valid text input.
- **Flight Number**: Must be a valid integer.
- **Country of Origin/Destination**: Ensures valid country names.
- **Stopover**: Validates the stopover input.
- **Price**: Ensures the price is numeric.
- **Time**: Validates time format (`HH:MM`).
- **Date**: Validates date format (`DD-MMM`).

## Hashing Mechanism

The program uses a cycle-shift hash function with a division compression function. This ensures an even distribution of keys across the hash table.

## Data Structures

### `Flight_Ticket`

Represents a flight ticket with the following attributes:

- Company Name
- Flight Number
- Country of Origin
- Country of Destination
- Stopover
- Price
- Time of Departure
- Time of Arrival
- Date

### `FlightHASHTABLE`

Implements the hash table using an array of doubly linked lists (`MyList`). Each list stores `HashNode` objects, which contain flight tickets and their corresponding keys.

### `MyList`

A doubly linked list template used to manage collisions in the hash table.

## Example Usage

### Adding a Ticket

1. Enter `add`.
2. Provide details such as company name, flight number, origin, destination, etc.

### Importing Tickets

1. Prepare a CSV file with the following format:
   ```csv
   CompanyName,FlightNumber,Origin,Destination,Stopover,Price,DepartureTime,ArrivalTime,Date
   ```
2. Enter `import <path>` to load tickets into the system.

### Finding a Ticket

1. Enter `find <CompanyName>,<FlightNumber>` to retrieve ticket details.

---
