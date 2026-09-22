# Smart Restaurant Management System (ByteBites)

| **Course** | Data Structures (DS) |
| **Language** | C++ |
| **Type** | Console application |

An online food ordering system built entirely from scratch with native C++ pointers and dynamic memory. The food menu is stored in a self-balancing Red-Black Tree, active orders wait in a linked Queue, cancellations undo through a linked Stack, and completed deliveries are archived in a Singly Linked List.

## Features
- **Menu in a Red-Black Tree:** insert, delete and search menu items in O(log n); the tree rebalances itself with rotations and recolouring
- **Case-insensitive input:** keys are stored lowercase while the original capitalisation is kept for display, so `pizza`, `Pizza` and `PIZZA` all match
- **Place Order:** validates the customer name and the item (max 5 attempts), then enqueues the order and pushes it on the cancel stack
- **Serve Next Order:** dequeues the oldest order (FIFO) and appends it to the delivery history
- **Cancel Last Order:** pops the most recent order (LIFO) and removes it from the active queue
- **View Active Orders:** lists every order still waiting, front to rear
- **Delivery History:** traverses the linked list of served orders from oldest to newest
- **Three traversals:** InOrder (alphabetical menu), PreOrder and PostOrder
- **Visualize Tree:** prints an ASCII diagram of the Red-Black Tree with node colours
- **Safe input:** non-numeric choices and prices are rejected without crashing or looping forever

## How it works
- **Red-Black Tree** keeps the menu sorted and balanced; a shared BLACK `NIL` sentinel simplifies all boundary checks.
- **Queue (FIFO)** guarantees the first customer placed is the first served; both enqueue and dequeue are O(1) using front and rear pointers.
- **Stack (LIFO)** makes the most recently placed order the first cancellable, like an undo button; push and pop are O(1).
- **Singly Linked List** appends each served order at the tail in O(1) and traverses head-to-tail in O(n) for the history.
- Serving an order also removes it from the cancel stack, and cancelling removes it from the queue, so the two structures never disagree.

## Files
- `smart_restaurant_management_system.cpp`: the source code
- `Smart_Restaurant_Management_System_Documentation.docx`: full project documentation

