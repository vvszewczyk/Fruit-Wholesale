# Fruit Wholesale

**A console-based application for managing fruit orders, deliveries, and user roles**  
This project was developed during classes at AGH. It handles important processes like storing fruit data, placing orders, processing payments, managing deliveries, and more.

## UML Diagrams

Designed in **Visual Paradigm**.

1. **Use Case Diagram** – Shows how customers, employees, and suppliers interact with the system.  
2. **Class Diagram** – Gives an overview of the classes (like Fruit, Order, Payment, etc.) and their relationships.  
3. **Sequence Diagram** – Depicts the order of method calls, for example when placing or processing an order.  
4. **State Machine Diagram** – Illustrates the possible states of an order (created, paid, delivered, returned, etc.).  
5. **Activity Diagram** – Shows the flow of operations, such as how a user’s request travels through the system.  
6. **Component Diagram** – Visualizes the system’s structure in terms of software components.  
7. **Deployment Diagram** – Represents how the system might be physically deployed on hardware or servers.

## Use Case Diagram
![ucd](media/ucd.png)<br>
*Use Case Diagram*<br>

## Class Diagram
![cd](media/cd.png)<br>
*Class Diagram*<br>

## Sequence Diagrams

![s1](media/s1.png)<br>
*Price list update Sequence Diagram*<br>

![s2](media/s2.png)<br>
*Stock update Sequence Diagram*<br>

![s3](media/s3.png)<br>
*Logging to system Sequence Diagram*<br>

![s4](media/s4.png)<br>
*Receiving a delivery of fruit Sequence Diagram*<br>

![s5](media/s5.png)<br>
*Order fulfillment  Sequence Diagram*<br>

![s6](media/s6.png)<br>
*Consideration of return Sequence Diagram*<br>

![s7](media/s7.png)<br>
*Placing an order Sequence Diagram*<br>

![s8](media/s8.png)<br>
*Creating an account Sequence Diagram*<br>

![s9](media/s9.png)<br>
*Payment for order Sequence Diagram*<br>

![s10](media/s10.png)<br>
*Submitting a return Sequence Diagram*<br>

![sm1](media/sm1.png)<br>
*Supplier State Machine Diagram*<br>

![sm2](media/sm2.png)<br>
*Update order status State Machine Diagram*<br>

## Activity Diagrams

![a1](media/a1.png)<br>
*Price list update Activity Diagram*<br>

![a2](media/a2.png)<br>
*Submitting a return Activity Diagram*<br>

![a3](media/a3.png)<br>
*Update stock Activity Diagram*<br>

![a4](media/a4.png)<br>
*Logging to system Activity Diagram*<br>

![a5](media/a5.png)<br>
*Acceptance of fruit delivery Activity Diagram*<br>

![a6](media/a6.png)<br>
*Order fulfillment Activity Diagram*<br>

![a7](media/a7.png)<br>
*Consideration of return Activity Diagram*<br>

![a8](media/a8.png)<br>
*Placing an order Activity Diagram*<br>

![a9](media/a9.png)<br>
*Creating an account Activity Diagram*<br>

![a19](media/a10.png)<br>
*Payment for order Activity Diagram*<br>

## Component Diagram
![c1](media/c1.png)<br>
*Payment for order Activity Diagram*<br>

## Deployment Diagram
![c1](media/d1.png)<br>
*Payment for order Activity Diagram*<br>

## Key Features

1. **Multiple User Roles**  
   - **Customer** – Can create an account, place orders, choose payment methods (bank transfer, card), and request returns.  
   - **Employee** – Can process or cancel orders, manage fruit data, and handle deliveries.  
   - **Supplier** – Can register new deliveries and view delivery history.

2. **Data Persistence**  
   - **Database** – Stores user credentials (customers, employees, suppliers) in a text file.  
   - **Storage** – Maintains a list of fruits, their prices, and available quantities.  
   - **Orders** – Placed orders are logged with a unique ID, status (e.g., “Zrealizowane,” “Zwrot,” “Anulowane”), and the items purchased.

3. **Order Processing**  
   - **Order Creation** – Customers choose fruits and quantities; the system updates the storage.  
   - **Payment** – Via bank transfer or card (simulated).  
   - **Order Status Updates** – Employees confirm completion (“Zrealizowane”) or mark returns (“Zwrot”).  

4. **Delivery Management**  
   - **Supplier** registers new deliveries (fruit name, price, quantity).  
   - **Employee** finalizes the delivery, merges it into current storage, and updates any differing fruit prices.

5. **Console Interface**  
   - Simple text-based menus for each role.  
   - Easy prompts to guide the user through login, order creation, storage updates, etc.

## Code Overview

- **main.cpp**  
  - Sets up the application by loading the database (users) and storage (fruits).  
  - Presents the main menu for selecting which user role to log in as (customer, employee, or supplier).  

- **Database**  
  - Singleton class for handling user credentials.  
  - Methods to verify if a user exists, log them in, and read or append user data in `database.txt`.

- **Storage**  
  - Singleton class that reads fruit data from `storage.txt`.  
  - Maintains a map of Fruit objects (price, name) and their quantities.  
  - Methods to add, delete, or update fruit information, reflecting changes both in memory and in the file.

- **Order**  
  - Represents a customer’s order.  
  - Tracks a list of fruits, their quantities, total cost, and status (e.g., “Zrealizowane,” “Zwrot,” etc.).  
  - Stores and reads orders from `orders.txt`.

- **Payment**  
  - Handles payment logic (bank transfer or card).  
  - In this demo, payments are simulated with basic checks (e.g., matching codes or card length).

- **Person**, **Customer**, **Employee**, **Supplier**  
  - Inherit basic login/password from `Person`.  
  - Additional methods:
    - **Customer** can place/cancel orders.  
    - **Employee** can process orders, returns, deliveries, and manage the storage.  
    - **Supplier** can register new deliveries and show delivery history.

- **Delivery**  
  - Maintains a map of (Fruit → quantity) for incoming stock.  
  - Used when suppliers register deliveries and employees finalize them.

## Requirements
- Visual Studio (Project files are included in the repository, so just open the .sln or .vcxproj file).
- Visual Paradigm (at least 17.2 version) if you want to open .vpp project file.
- After cloning the repository, simply build and run from Visual Studio.
