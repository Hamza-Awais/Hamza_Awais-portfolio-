# Smart Cafeteria Management System

**Course:** Software Engineering (Final Project)
**Name:** Hamza Awais
**Reg No:** L1F24BSCS0229
**Section:** D-15
**Semester:** 4th

---

## Overview

Smart Cafeteria Management System is a responsive web application designed to make ordering food at a campus cafeteria fast, transparent, and easy to manage. It has two separate portals:

- **Student / Staff Portal:** sign in, browse the live menu, add items to a cart, pay with a campus wallet, and track order status.
- **Cafeteria Manager (Admin) Portal:** view sales and order analytics, manage menu items and stock, and run the kitchen order queue.

This repository contains the **project documentation and UI prototype designs**.

## Motivation

Traditional cafeteria ordering means long queues, cash payments, and no visibility into order progress. This system lets students order ahead and skip the line, gives the kitchen a live queue, shows stock levels in real time, and supports cashless payment.

## Key Features

**Student / Staff**
- Login with Campus ID
- Live, searchable menu with category and dietary filters
- Real-time stock status (In Stock, Only a Few Left, Sold Out)
- Cart with adjustable quantities and a transparent price summary
- Campus wallet payment
- Order confirmation with a unique order ID
- Live order tracker: Placed, Preparing, Ready

**Manager**
- Separate admin login
- Dashboard with daily orders, revenue, and average preparation time
- Top-selling items chart and low-stock alerts
- Add, edit, and remove menu items; set price and availability
- Kitchen queue board (New, Preparing, Ready)

## UI Prototype Screens

1. Login / Sign-up
2. Browse Menu
3. Cart & Checkout
4. Order Confirmation
5. Manager Dashboard
6. Manage Menu
7. Kitchen Order Queue

## System Design Summary

- **Architecture:** client-server (responsive single-page frontend, RESTful backend API, relational database)
- **Roles:** Student / Staff (ordering portal) and Cafeteria Manager (admin portal)
- **Database tables:** `users`, `menu_items`, `orders`, `order_items`
- **Order lifecycle:** Placed, Preparing, Ready, Picked Up



## Documentation

The full report (introduction, system analysis, functional and non-functional requirements, system design, and UI screens) is in:

`docs/Software_Engineering_Final_Project.docx`

## Author

Hamza Awais 

