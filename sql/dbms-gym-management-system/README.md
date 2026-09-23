# Gym Membership & Booking System

| **Course** | Database Management Systems (DBMS) |
| **Language** | MySQL |
| **Type** | Database project |

A relational database for a commercial gym: membership plans, member enrollment, trainers, a weekly class schedule, class bookings and a payment ledger. The script builds the whole schema, fills it with realistic sample data, and then runs a series of reporting queries over it.

## Features
- **Six linked tables:** Membership_Plans, Members, Trainers, Classes, Bookings and Payments, joined through foreign keys with `ON DELETE CASCADE` and `ON DELETE SET NULL` rules
- **Integrity rules:** auto-increment primary keys on every table, a `UNIQUE` constraint on member email, and a `CHECK (amount > 0)` rule on the payment ledger
- **Realistic sample data:** 30 membership plans, 30 trainers, 31 members, 31 scheduled classes, 30 bookings and 30 payments
- **Sixteen reporting queries:** inner and left joins, `GROUP BY` with `HAVING`, independent and correlated subqueries, `EXISTS` / `NOT EXISTS` checks, a four-table nested join, and a `DATE_ADD` based membership expiry report
- **Normalized design:** the schema is verified up to Third Normal Form (3NF), with the reasoning documented

## Files
- `gym_management_system.sql`: the complete MySQL script (schema, sample data and all queries)
- `Gym_Management_Documentation.docx`: project documentation with the entity relation diagram, table descriptions, test cases and normalization analysis

