#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

string toLower(string s) {
	for (int i = 0; i < (int)s.size(); i++)
		s[i] = tolower(s[i]);
	return s;
}

enum Color { RED, BLACK };

class MenuItem 
{
public:
	string    itemName;      
	string    displayName;   
	int       itemPrice;
	Color     color;
	MenuItem* left;
	MenuItem* right;
	MenuItem* parent;

	MenuItem(string n, int p)
		: displayName(n),
		itemName(toLower(n)), 
		itemPrice(p), color(RED),
		left(nullptr), right(nullptr), parent(nullptr) {
	}
};


class MenuSystem
{
private:
	MenuItem* root;
	MenuItem* NIL;


	void leftRotate(MenuItem* x)
	{
		MenuItem* y = x->right;


		x->right = y->left;
		if (y->left != NIL)
			y->left->parent = x;


		y->parent = x->parent;
		if (x->parent == nullptr)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rightRotate(MenuItem* x) {
		MenuItem* y = x->left;

		x->left = y->right;
		if (y->right != NIL)
			y->right->parent = x;

		y->parent = x->parent;
		if (x->parent == nullptr)
			root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;

		y->right = x;
		x->parent = y;
	}

	void insertFixUp(MenuItem* z)
	{
		while (z->parent && z->parent->color == RED) {

			if (z->parent == z->parent->parent->left) {

				MenuItem* y = z->parent->parent->right;

				if (y->color == RED) {

					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right) {

						z = z->parent;
						leftRotate(z);
					}

					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			}
			else
			{

				MenuItem* y = z->parent->parent->left;

				if (y->color == RED) {

					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {

						z = z->parent;
						rightRotate(z);
					}

					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}


	void transplant(MenuItem* u, MenuItem* v)
	{
		if (u->parent == nullptr)
			root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	MenuItem* minimum(MenuItem* node)
	{
		while (node->left != NIL)
			node = node->left;
		return node;
	}

	void deleteFixUp(MenuItem* x)
	{
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				MenuItem* w = x->parent->right;

				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}

				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}

					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				MenuItem* w = x->parent->left;

				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

	void inOrder(MenuItem* node) 
	{
		if (node == NIL) return;
		inOrder(node->left);
		cout << "  " << node->displayName       // original naam dikhao
			<< "  -->  Rs. " << node->itemPrice
			<< "   [" << (node->color == RED ? "RED" : "BLACK") << "]\n";
		inOrder(node->right);
	}

	void preOrder(MenuItem* node)
	{
		if (node == NIL) return;
		cout << "  " << node->displayName
			<< "  [" << (node->color == RED ? "R" : "B") << "]\n";
		preOrder(node->left);
		preOrder(node->right);
	}

	void postOrder(MenuItem* node) 
	{
		if (node == NIL) return;
		postOrder(node->left);
		postOrder(node->right);
		cout << "  " << node->displayName
			<< "  [" << (node->color == RED ? "R" : "B") << "]\n";
	}

	MenuItem* searchNode(MenuItem* node, string target) 
	{
		if (node == NIL) return NIL;
		if (node->itemName == target) return node; 
		if (target < node->itemName)
			return searchNode(node->left, target);
		else
			return searchNode(node->right, target);
	}

	void printTree(MenuItem* node, string indent, bool isRight) 
	{
		if (node == NIL) return;
		cout << indent;
		if (isRight) {
			cout << "R----";
			indent += "     ";
		}
		else {
			cout << "L----";
			indent += "|    ";
		}
		string clr = (node->color == RED) ? "(R)" : "(B)";
		cout << node->displayName << "  Rs." << node->itemPrice << clr << "\n";
		printTree(node->left, indent, false);
		printTree(node->right, indent, true);
	}

public:

	MenuSystem()
	{
		NIL = new MenuItem("", 0);
		NIL->color = BLACK;
		NIL->left = NIL->right = NIL->parent = NIL;
		root = NIL;
		cout << "  [RBT] Red-Black Tree initialised. Root = NIL (empty).\n";
	}

	void addItem(string name, int price) 
	{
		cout << "\n  [RBT INSERT] Adding \"" << name << "\" Rs." << price << " ...\n";

		if (searchNode(root, toLower(name)) != NIL) 
		{
			cout << "  \"" << name << "\" already exists in the menu.\n";
			return;
		}

		MenuItem* z = new MenuItem(name, price);  
		z->left = z->right = NIL;

		MenuItem* y = nullptr;
		MenuItem* x = root;

		while (x != NIL) 
		{
			y = x;
			if (z->itemName < x->itemName)   
				x = x->left;
			else
				x = x->right;
		}

		z->parent = y;
		if (y == nullptr)
			root = z;
		else if (z->itemName < y->itemName)
			y->left = z;
		else
			y->right = z;
		cout << "   [RBT INSERT] Setting colour RED..\n";
		cout << "  [RBT INSERT] Checking for RBT violations...\n";

		insertFixUp(z);

		cout << "  [RBT INSERT] \"" << name << "\" successfully inserted. Tree is balanced.\n";
	}

	void deleteItem(string name)
	{
		string key = toLower(name);  
		cout << "\n  [RBT DELETE] Searching for \"" << name << "\" ...\n";
		MenuItem* z = searchNode(root, key);

		if (z == NIL) 
		{   
			cout << "  [RBT DELETE] \"" << name << "\" NOT FOUND in menu.\n";
			return;
		}
		cout << "  [RBT DELETE] Found \"" << z->displayName << "\". Removing...\n";

		MenuItem* y = z;
		MenuItem* x;
		Color     yOriginalColor = y->color;

		if (z->left == NIL) {
			cout << "  [RBT DELETE] Case A: No left child. Replace with right child.\n";
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == NIL) {
			cout << "  [RBT DELETE] Case B: No right child. Replace with left child.\n";
			x = z->left;
			transplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			yOriginalColor = y->color;
			x = y->right;
			cout << "  [RBT DELETE] Case C: Two children. In-order successor = \""
				<< y->displayName << "\".\n";

			if (y->parent == z) {
				x->parent = y;
			}
			else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		string removedName = z->displayName;
		delete z;

		if (yOriginalColor == BLACK)
		{
			cout << "  [RBT DELETE] Removed node was BLACK. Running deleteFixUp...\n";
			deleteFixUp(x);
		}

		cout << "  [RBT DELETE] \"" << removedName << "\" removed. Tree is balanced.\n";
	}

	bool isItemAvailable(string name)
	{
		return searchNode(root, toLower(name)) != NIL;
	}

	void searchItem(string name) 
	{
		cout << "\n  [RBT SEARCH] Looking for \"" << name << "\" ...\n";
		MenuItem* found = searchNode(root, toLower(name));
		if (found != NIL)
			cout << "  [RBT SEARCH] FOUND --> \"" << found->displayName
			<< "\"  Rs." << found->itemPrice
			<< "  [" << (found->color == RED ? "RED" : "BLACK") << " node]\n";
		else
			cout << "  [RBT SEARCH] \"" << name << "\" is NOT on the menu.\n";
	}
	int getItemPrice(string name) 
	{
		MenuItem* found = searchNode(root, toLower(name));
		return (found != NIL) ? found->itemPrice : 0;
	}

	string getDisplayName(string name)
	{
		MenuItem* found = searchNode(root, toLower(name));
		return (found != NIL) ? found->displayName : name;
	}

	void showMenu()
	{
		cout << "\n  ========== MENU (InOrder / Alphabetical) ==========\n";
		cout << "  [InOrder = Left subtree -> Root -> Right subtree]\n";
		cout << "  Items are sorted because BST: left < root < right\n";
		cout << "  ----------------------------------------------------\n";
		inOrder(root);
		cout << "  ====================================================\n";
	}

	void showPreOrder()
	{
		cout << "\n  --- PreOrder Traversal (Root -> Left -> Right) ---\n";
		cout << "  [The ROOT of each subtree appears before its children]\n";
		preOrder(root);
	}

	void showPostOrder() 
	{
		cout << "\n  --- PostOrder Traversal (Left -> Right -> Root) ---\n";
		cout << "  [Children appear before their parent]\n";
		postOrder(root);
	}

	void visualizeTree()
	{
		cout << "\n  ======= RED-BLACK TREE STRUCTURE =======\n";
		cout << "  (R) = RED node    (B) = BLACK node\n";
		cout << "  L---- = Left child    R---- = Right child\n";
		cout << "  -----------------------------------------\n";
		if (root == NIL)
		{
			cout << "  (Tree is empty)\n";
		}
		else {
			string clr = (root->color == RED) ? "(R)" : "(B)";
			cout << "  Root---" << root->displayName
				<< "  Rs." << root->itemPrice << clr << "\n";
			printTree(root->left, "         ", false);
			printTree(root->right, "         ", true);
		}
		cout << "  =========================================\n";
	}
};


struct Order
{
	int    orderId;
	string customerName;
	string itemName;
	int    itemPrice;

	Order(int id = 0, string c = "", string i = "", int p = 0)
		: orderId(id), customerName(c), itemName(i), itemPrice(p) {
	}
};

struct QueueNode 
{
	Order      order;
	QueueNode* next;
	QueueNode(Order o) : order(o), next(nullptr) {}
};

class OrderQueue
{
	QueueNode* front;
	QueueNode* rear;
	int        size;
public:
	OrderQueue() : front(nullptr), rear(nullptr), size(0) {}

	void enqueue(Order o) 
	{
		cout << "\n  [QUEUE ENQUEUE] Adding Order #" << o.orderId
			<< " for " << o.customerName << " ...\n";
		QueueNode* n = new QueueNode(o);
		if (!rear)
		{
			front = rear = n;
		}
		else 
		{
			rear->next = n;
			rear = n;
		}
		size++;
		cout << "  [QUEUE] Order #" << o.orderId
			<< " placed at rear. Queue size = " << size << ".\n";
	}

	bool dequeue(Order& o) 
	{
		if (!front) 
		{
			cout << "  [QUEUE] Queue is empty. No order to serve.\n";
			return false;
		}
		QueueNode* temp = front;
		o = front->order;
		front = front->next;
		if (!front) rear = nullptr;
		delete temp;
		size--;
		cout << "  [QUEUE DEQUEUE] Order #" << o.orderId
			<< " removed from front. Queue size = " << size << ".\n";
		return true;
	}

	void display() 
	{
		if (!front) 
		{
			cout << "  [QUEUE] No active orders in queue.\n";
			return;
		}
		QueueNode* temp = front;
		cout << "\n  ===== ACTIVE ORDERS in QUEUE (" << size << " pending) =====\n";
		cout << "  [FRONT = next to be served | REAR = most recently placed]\n";
		cout << "  ----------------------------------------------------------\n";
		int pos = 1;
		while (temp)
		{
			cout << "  [" << pos++ << "] Order #" << temp->order.orderId
				<< "  |  Customer: " << temp->order.customerName
				<< "  |  Item: " << temp->order.itemName
				<< "  |  Rs." << temp->order.itemPrice << "\n";
			temp = temp->next;
		}
		cout << "  ==========================================================\n";
	}

	bool isEmpty() { return front == nullptr; }

	bool removeById(int id)
	{
		QueueNode* prev = nullptr;
		QueueNode* cur = front;
		while (cur) {
			if (cur->order.orderId == id) {
				if (prev) prev->next = cur->next;
				else front = cur->next;
				if (cur == rear) rear = prev;
				delete cur;
				size--;
				return true;
			}
			prev = cur;
			cur = cur->next;
		}
		return false;
	}
};

struct StackNode 
{
	Order      order;
	StackNode* next;
	StackNode(Order o) : order(o), next(nullptr) {}
};

class CancelStack
{
	StackNode* topNode;
	int size;
public:
	CancelStack() : topNode(nullptr), size(0) {}

	void push(Order o) 
	{
		StackNode* n = new StackNode(o);
		n->next = topNode;
		topNode = n;
		size++;
		cout << "  [STACK PUSH] Order #" << o.orderId
			<< " pushed onto cancel stack. Stack size = " << size << ".\n";
	}

	bool pop(Order& o) 
	{
		if (!topNode) 
		{
			cout << "  [STACK] Stack is empty. Nothing to cancel.\n";
			return false;
		}
		StackNode* temp = topNode;
		o = topNode->order;
		topNode = topNode->next;
		delete temp;
		size--;
		cout << "  [STACK POP] Order #" << o.orderId
			<< " popped from stack. Stack size = " << size << ".\n";
		return true;
	}

	bool isEmpty() { return topNode == nullptr; }

	bool removeById(int id)
	{
		StackNode* prev = nullptr;
		StackNode* cur = topNode;
		while (cur) {
			if (cur->order.orderId == id) {
				if (prev) prev->next = cur->next;
				else topNode = cur->next;
				delete cur;
				size--;
				return true;
			}
			prev = cur;
			cur = cur->next;
		}
		return false;
	}
};

struct DeliveryNode 
{
	Order order;
	DeliveryNode* next;
	DeliveryNode(Order o) : order(o), next(nullptr) {}
};

class DeliveryHistory
{
	DeliveryNode* head;
	DeliveryNode* tail;
	int count;
public:
	DeliveryHistory() : head(nullptr), tail(nullptr), count(0) {}

	void add(Order o) 
	{
		DeliveryNode* n = new DeliveryNode(o);
		if (!head)
		{
			head = tail = n;
		}
		else 
		{
			tail->next = n;
			tail = n;
		}
		count++;
		cout << "Order #" << o.orderId
			<< " appended to delivery history. Total = " << count << ".\n";
	}

	void show()
	{
		if (!head) 
		{
			cout << "No deliveries recorded yet.\n";
			return;
		}
		DeliveryNode* temp = head;
		cout << "\n  ===== DELIVERY HISTORY (Linked List) (" << count << " orders) =====\n";
		cout << "  [Traversing from HEAD (oldest) to TAIL (most recent)]\n";
		cout << "  -------------------------------------------------------\n";
		int i = 1;
		while (temp) 
		{
			cout << "  " << i++ << ". Order #" << temp->order.orderId
				<< "  |  " << temp->order.customerName
				<< "  |  " << temp->order.itemName
				<< "  |  Rs." << temp->order.itemPrice << "\n";
			temp = temp->next;
		}
		cout << "  =========================================================\n";
	}

	int getCount() { return count; }
};

int main()
{
	MenuSystem menu;
	OrderQueue orderQueue;
	DeliveryHistory history;
	CancelStack cancelStack;

	cout << "\n Pre-loading default menu items into RBT \n";
	menu.addItem("Biryani", 300);
	menu.addItem("Burger", 250);
	menu.addItem("Fries", 150);
	menu.addItem("Pasta", 350);
	menu.addItem("Pizza", 800);
	menu.addItem("Shawarma", 200);
	menu.addItem("Zinger", 450);
	cout << "\n Menu ready! RBT is balanced.\n";

	int    orderId = 1;
	int    choice;
	string cname, itemName;

	while (true)
	{
		cout << "\n  ============================================================\n";
		cout << "          ONLINE FOOD ORDERING SYSTEM\n";
		cout << "  ============================================================\n";
		cout << "   1.  Show Menu  \n";
		cout << "   2.  Search Item \n";
		cout << "   3.  Place Order \n";
		cout << "   4.  Serve Next Order \n";
		cout << "   5.  Cancel Last Order \n";
		cout << "   6.  View Active Orders \n";
		cout << "   7.  Delivery History \n";
		cout << "   8.  Add New Menu Item\n";
		cout << "   9.  Remove Menu Item \n";
		cout << "   10. All 3 RBT Traversals\n";
		cout << "   11. Visualize RBT Tree \n";
		cout << "   12. Exit\n";
		cout << "  ------------------------------------------------------------\n";
		cout << "   Enter your choice: ";

		if (!(cin >> choice)) 
		{
			cin.clear();            
			string garbage;
			getline(cin, garbage);  
			cout << "  [!] Invalid input. Please enter a number (1-12).\n";
			continue;              
		}
		cin.ignore();
	

		switch (choice)
		{
		case 1:
			menu.showMenu();
			break;

		case 2:
			cout << "\n  Enter item name to search: ";
			getline(cin, itemName);
			menu.searchItem(itemName);   
			break;

		case 3:
		{
			cout << "\n  Enter customer name: ";
			getline(cin, cname);
			if (cname.empty()) {
				cout << "  [!] Name cannot be empty.\n";
				break;
			}
			menu.showMenu();


			int attempts = 0;
			bool validItem = false;
			while (!validItem) {
				cout << "  Enter item to order: ";
				getline(cin, itemName);
				if (menu.isItemAvailable(itemName)) 
				{  
					validItem = true;
				}
				else {
					attempts++;
					cout << "  [!] \"" << itemName << "\" not found. Please choose from the menu.\n";
					if (attempts >= 5) {
						cout << "  [!] Too many invalid attempts. Returning to main menu.\n";
						break;
					}
				}
			}
			if (!validItem) break;

			int price = menu.getItemPrice(itemName);
			string displayItem = menu.getDisplayName(itemName); // original naam
			Order o(orderId++, cname, displayItem, price);
			orderQueue.enqueue(o);
			cancelStack.push(o);
			break;
		}

		case 4: {
			cout << "\n  [ACTION] Serving next order from queue (FIFO)...\n";
			Order o;
			if (orderQueue.dequeue(o)) 
			{
				cout << "  [SERVED] Order #" << o.orderId
					<< "  Customer: " << o.customerName
					<< "  Item: " << o.itemName
					<< "  Rs." << o.itemPrice << "\n";
				history.add(o);
				cancelStack.removeById(o.orderId);
			}
			break;
		}

		case 5: {
			cout << "\n  [ACTION] Cancelling most recent order (LIFO)...\n";
			Order o;
			if (cancelStack.pop(o)) {
				cout << "  [CANCELLED] Order #" << o.orderId
					<< "  Customer: " << o.customerName
					<< "  Item: " << o.itemName << "\n";
				orderQueue.removeById(o.orderId);
			}
			break;
		}

		case 6:
			orderQueue.display();
			break;

		case 7:
			history.show();
			break;

		case 8: {
			cout << "\n  Enter new item name : ";
			getline(cin, itemName);
			if (itemName.empty()) {
				cout << "  [!] Name cannot be empty.\n";
				break;
			}
			int newPrice;
			cout << "  Enter price (Rs.)   : ";
			// ── Price input bhi safe kiya ─────────────────────────
			if (!(cin >> newPrice)) {
				cin.clear();
				string garbage;
				getline(cin, garbage);
				cout << "  [!] Invalid price. Please enter a number.\n";
				break;
			}
			cin.ignore();
			if (newPrice <= 0) {
				cout << "  [!] Invalid price. Must be greater than 0.\n";
				break;
			}
			menu.addItem(itemName, newPrice);
			break;
		}

		case 9:
			cout << "\n  Enter item name to remove: ";
			getline(cin, itemName);
			menu.deleteItem(itemName);   // andar toLower() ho ga
			break;

		case 10:
			cout << "\n  [TRAVERSALS] Showing all three RBT traversals:\n";
			menu.showMenu();
			menu.showPreOrder();
			menu.showPostOrder();
			break;

		case 11:
			menu.visualizeTree();
			break;

		case 12:
			cout << "\n  Thank you for using the Online Food Ordering System!\n";
			cout << "  [Summary]\n";
			cout << "    Total deliveries completed : " << history.getCount() << "\n";
			cout << "    Goodbye!\n\n";
			system("pause");
			return 0;

		default:
			cout << "Invalid choice. Please enter a number between 1 and 12.\n";
		}
	}
}