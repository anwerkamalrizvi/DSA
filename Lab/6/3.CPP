#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

class MenuItem {
public:
  string itemName;
  int quantity;
  double pricePerUnit;

  MenuItem() {
    itemName = "";
    quantity = 0;
    pricePerUnit = 0.0;
  }

  MenuItem(string name, int qty, double price) {
    itemName = name;
    quantity = qty;
    pricePerUnit = price;
  }

  double getTotalPrice() { return quantity * pricePerUnit; }
};

class Order {
public:
  int orderId;
  string customerName;
  string tableNumber;
  MenuItem items[10];
  int itemCount;
  double totalAmount;
  string timestamp;
  string status;

  Order() {
    orderId = 0;
    customerName = "";
    tableNumber = "";
    itemCount = 0;
    totalAmount = 0.0;
    status = "PENDING";
    timestamp = getCurrentTime();
  }

  Order(int id, string name, string table) {
    orderId = id;
    customerName = name;
    tableNumber = table;
    itemCount = 0;
    totalAmount = 0.0;
    status = "PENDING";
    timestamp = getCurrentTime();
  }

  void addItem(string name, int qty, double price) {
    if (itemCount < 10) {
      items[itemCount] = MenuItem(name, qty, price);
      totalAmount += items[itemCount].getTotalPrice();
      itemCount++;
    }
  }

  string getCurrentTime() {
    time_t now = time(0);
    char buffer[20];
    strftime(buffer, 20, "%H:%M:%S", localtime(&now));
    return string(buffer);
  }

  void display() {
    cout << "Order NO " << orderId << " - " << status << endl;
    cout << "Customer: " << customerName << " (" << tableNumber << ")" << endl;
    cout << "Time: " << timestamp << endl;
    for (int i = 0; i < itemCount; i++) {
      cout << " " << items[i].quantity << "x " << items[i].itemName << " - Rs."
           << fixed << setprecision(2) << items[i].getTotalPrice() << endl;
    }
    cout << "Total Amount: Rs." << totalAmount << endl;
  }
};

class QueueNode {
public:
  Order data;
  QueueNode *next;

  QueueNode(Order ord) {
    data = ord;
    next = nullptr;
  }
};

class OrderQueue {
private:
  QueueNode *front;
  QueueNode *rear;
  int currentSize;
  int maxCapacity;
  int warningThreshold;

public:
  OrderQueue(int capacity = 50) {
    front = NULL;
    rear = NULL;
    currentSize = 0;
    maxCapacity = capacity;
    warningThreshold = (int)(capacity * 0.8);
  }

  bool isEmpty() { return front == NULL; }

  bool isFull() { return currentSize >= maxCapacity; }

  bool isNearFull() { return currentSize >= warningThreshold; }

  int getSize() { return currentSize; }

  bool enqueue(Order ord) {
    if (isFull()) {
      cout << "\nERROR: Queue is full! Cannot accept more orders." << endl;
      cout << "Current capacity: " << currentSize << "/" << maxCapacity << endl;
      cout << "Please process pending orders first.\n" << endl;
      return false;
    }

    QueueNode *newNode = new QueueNode(ord);

    if (isEmpty()) {
      front = rear = newNode;
    } else {
      rear->next = newNode;
      rear = newNode;
    }

    currentSize++;

    cout << "Order NO " << ord.orderId << " added hogea--> queue mey." << endl;

    if (isNearFull()) {
      int percentage = (currentSize * 100) / maxCapacity;
      cout << "WARNING: Queue is " << percentage << "%\full (" << currentSize
           << "/" << maxCapacity << " orders)\n"
           << endl;
    }

    return true;
  }

  Order dequeue() {
    if (isEmpty()) {
      cout << "\nERROR: Queue is empty! No orders to process.\n" << endl;
      Order emptyOrder;
      emptyOrder.orderId = -1;
      return emptyOrder;
    }

    QueueNode *temp = front;
    Order processedOrder = temp->data;
    front = front->next;

    if (front == NULL) {
      rear = NULL;
    }

    delete temp;
    currentSize--;

    cout << "Order #" << processedOrder.orderId << " removed from queue."
         << endl;
    cout << "Remaining orders in queue: " << currentSize << "\n" << endl;

    return processedOrder;
  }

  Order peek() {
    if (isEmpty()) {
      cout << "Queue is empty." << endl;
      Order emptyOrder;
      return emptyOrder;
    }
    return front->data;
  }

  void displayAllOrders() {
    if (isEmpty()) {
      cout << "\nNo pending orders in queue.\n" << endl;
      return;
    }

    cout << "PENDING ORDERS QUEUE" << endl;
    cout << "Total orders in queue: " << currentSize << "/" << maxCapacity
         << endl;

    QueueNode *current = front;
    int position = 1;

    while (current != NULL) {
      cout << "\n[Position " << position << " in queue]";
      current->data.display();
      current = current->next;
      position++;
    }
  }

  void expandCapacity(int additionalCapacity) {
    maxCapacity += additionalCapacity;
    warningThreshold = (int)(maxCapacity * 0.8);
    cout << "Queue capacity expanded to " << maxCapacity << " orders.\n"
         << endl;
  }

  ~OrderQueue() {
    while (!isEmpty()) {
      dequeue();
    }
  }
};

class CompletedOrderStack {
private:
  Order orders[100];
  int top;

public:
  CompletedOrderStack() { top = -1; }

  bool isEmpty() { return top == -1; }

  bool isFull() { return top >= 99; }

  void push(Order ord) {
    if (isFull()) {
      cout << "ERROR: Completed orders stack is full!" << endl;
      return;
    }
    ord.status = "COMPLETED";
    orders[++top] = ord;
    cout << "Order #" << ord.orderId << " marked as completed.\n" << endl;
  }

  Order pop() {
    if (isEmpty()) {
      Order empty;
      return empty;
    }
    return orders[top--];
  }

  void displayAll() {
    if (isEmpty()) {
      cout << "\nNo completed orders yet.\n" << endl;
      return;
    }
    cout << "COMPLETED ORDERS (Most Recent First)" << endl;
    for (int i = top; i >= 0; i--) {
      orders[i].display();
    }
  }

  void displayInOrder() {
    if (isEmpty()) {
      cout << "\nNo completed orders yet.\n" << endl;
      return;
    }
    cout << "COMPLETED ORDERS (Chronological)" << endl;
    cout << "Total completed: " << (top + 1) << " orders\n" << endl;

    for (int i = 0; i <= top; i++) {
      orders[i].display();
    }
  }
};

class RestaurantSystem {
private:
  OrderQueue pendingOrders;
  CompletedOrderStack completedOrders;
  int orderIdCounter;

public:
  RestaurantSystem() { orderIdCounter = 1001; }

  void placeNewOrder(string customerName, string tableNumber) {
    Order newOrder(orderIdCounter++, customerName, tableNumber);
    return;
  }

  void addItemsToOrder(Order &order, string items[][3], int itemCount) {
    for (int i = 0; i < itemCount; i++) {
      string name = items[i][0];
      int qty = stoi(items[i][1]);
      double price = stod(items[i][2]);
      order.addItem(name, qty, price);
    }
    pendingOrders.enqueue(order);
  }

  void processNextOrder() {
    cout << "\nProcessing next order from queue..." << endl;
    Order processedOrder = pendingOrders.dequeue();

    if (processedOrder.orderId != -1) {
      processedOrder.status = "PROCESSING";
      cout << "Kitchen preparing:";
      processedOrder.display();
      completedOrders.push(processedOrder);
    }
  }
  void viewPendingOrders() { pendingOrders.displayAllOrders(); }
  void viewCompletedOrders() { completedOrders.displayInOrder(); }
  void displaySystemStatus() {
  cout << "RESTAURANT SYSTEM STATUS" << "Pending Orders: " << pendingOrders.getSize() <<"\nSystem Status: " << (pendingOrders.isEmpty() ? "IDLE" : "BUSY")
    << "\nNext Order ID: " << orderIdCounter << endl;
  }
};

int main() {
  cout << "Restaurant Order Management System" << endl;
  OrderQueue pendingQueue;
  CompletedOrderStack completedStack;

  cout << "Creating new order for Ahmed Khan at Table 5..." << endl;
  Order order1(1001, "Ahmed Khan", "Table 5");
  order1.addItem("Chicken Biryani", 2, 450);
  order1.addItem("Cold Drink", 2, 80);
  order1.addItem("Raita", 1, 60);
  pendingQueue.enqueue(order1);

  cout << "\nCreating new order for Sara Ali at Table 3..." << endl;
  Order order2(1002, "Sara Ali", "Table 3");
  order2.addItem("Karahi", 1, 850);
  order2.addItem("Naan", 4, 30);
  pendingQueue.enqueue(order2);

  cout << "\nCreating new order for Hassan Raza at Table 7..." << endl;
  Order order3(1003, "Hassan Raza", "Table 7");
  order3.addItem("Pizza", 1, 950);
  order3.addItem("Pasta", 1, 650);
  order3.addItem("Garlic Bread", 1, 250);
  order3.addItem("Juice", 2, 120);
  pendingQueue.enqueue(order3);

  pendingQueue.displayAllOrders();

  cout << "PROCESSING ORDERS FROM QUEUE" << endl;

  cout << "Processing first order in queue..." << endl;
  Order processed1 = pendingQueue.dequeue();
  completedStack.push(processed1);

  cout << "Processing second order in queue..." << endl;
  Order processed2 = pendingQueue.dequeue();
  completedStack.push(processed2);

  pendingQueue.displayAllOrders();

  completedStack.displayInOrder();

  cout << "SYSTEM STATISTICS \nPending Orders: " << pendingQueue.getSize() << "\nCompleted Orders: 2 \nSystem Status: Operational" << endl;
  return 0;
}