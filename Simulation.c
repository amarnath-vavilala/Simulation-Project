#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50        // Maximum number of orders
#define MAX_ITEMS 10  // Maximum items per order

// Structure to store order details
typedef struct {
    int orderID;
    char customerName[50];
    char address[100];
    char status[20];
    char items[MAX_ITEMS][50];
    int itemCount;
} Order;

Order queue[MAX];   // Queue array
int front = -1, rear = -1;  // Queue pointers

// Shop catalog
char shopItems[5][50] = {
    "Laptop", "Mouse", "Keyboard", "Phone", "Charger"
};

// Check if queue is full
int isFull() {
    return (rear == MAX - 1);
}

// Check if queue is empty
int isEmpty() {
    return (front == -1 || front > rear);
}

// Add order to queue
void enqueue(int id, char name[], char addr[], int itemCount, char items[][50]) {
    if (isFull()) {
        printf("\nQueue is FULL!\n");
        return;
    }
    if (front == -1) front = 0;  // First element
    rear++;
    queue[rear].orderID = id;
    strcpy(queue[rear].customerName, name);
    strcpy(queue[rear].address, addr);
    strcpy(queue[rear].status, "Pending");
    queue[rear].itemCount = itemCount;
    for (int i = 0; i < itemCount; i++) {
        strcpy(queue[rear].items[i], items[i]);
    }
    printf("\nOrder %d added successfully!\n", id);
}

// Process (remove) order from queue
void dequeue() {
    if (isEmpty()) {
        printf("\nQueue is EMPTY!\n");
    } else {
        printf("\nProcessing Order %d\n", queue[front].orderID);
        printf("Customer: %s\nAddress: %s\n", queue[front].customerName, queue[front].address);
        printf("Items:\n");
        for (int i = 0; i < queue[front].itemCount; i++) {
            printf(" - %s\n", queue[front].items[i]);
        }
        strcpy(queue[front].status, "Processed");
        front++;  // Move front pointer
    }
}

// Display all orders
void displayQueue() {
    if (isEmpty()) {
        printf("\nNo orders.\n");
    } else {
        printf("\nOrders in System:\n");
        printf("---------------------------------------------\n");
        for (int i = front; i <= rear; i++) {
            printf("OrderID: %d | Customer: %s | Address: %s | Status: %s\n",
                   queue[i].orderID,
                   queue[i].customerName,
                   queue[i].address,
                   queue[i].status);
            printf("Items:\n");
            for (int j = 0; j < queue[i].itemCount; j++) {
                printf(" - %s\n", queue[i].items[j]);
            }
            printf("---------------------------------------------\n");
        }
    }
}

int main() {
    int choice, id, itemCount;
    char name[50], addr[100], items[MAX_ITEMS][50];

    while (1) {
        printf("\n--- Delivery Queue Simulation ---\n");
        printf("1. Add Delivery Order\n");
        printf("2. Process Next Order\n");
        printf("3. Display All Orders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Order ID: ");
                scanf("%d", &id);
                getchar(); // clear buffer
                printf("Enter Customer Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // remove newline
                printf("Enter Address: ");
                fgets(addr, sizeof(addr), stdin);
                addr[strcspn(addr, "\n")] = 0;

                printf("\nAvailable Shop Items:\n");
                for (int i = 0; i < 5; i++) {
                    printf("%d. %s\n", i + 1, shopItems[i]);
                }

                printf("Enter number of items to order (max %d): ", MAX_ITEMS);
                scanf("%d", &itemCount);
                getchar();
                for (int i = 0; i < itemCount; i++) {
                    int choiceItem;
                    printf("Select item %d (1-5): ", i + 1);
                    scanf("%d", &choiceItem);
                    getchar();
                    if (choiceItem >= 1 && choiceItem <= 5) {
                        strcpy(items[i], shopItems[choiceItem - 1]);
                    } else {
                        printf("Invalid choice. Skipping.\n");
                        strcpy(items[i], "Unknown");
                    }
                }
                enqueue(id, name, addr, itemCount, items);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                printf("\nExiting simulation...\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }
    return 0;
    
}

