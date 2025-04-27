#include <stdio.h>
#include <string.h>

#define MAX 100

struct Account {
    char name[50];
    int acc_no;
    float balance;
};

struct Account users[MAX];
int count = 0;

void createAccount() {
    printf("Enter Name: ");
    scanf("%s", users[count].name);
    printf("Enter Account Number: ");
    scanf("%d", &users[count].acc_no);
    users[count].balance = 0;
    printf("Account Created Successfully!\n");
    count++;
}

int findAccount(int acc_no) {
    for (int i = 0; i < count; i++) {
        if (users[i].acc_no == acc_no) {
            return i;  // Return index of account
        }
    }
    return -1;  // Not found
}

void deposit() {
    int acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    
    int idx = findAccount(acc_no);
    if (idx == -1) {
        printf("Account Not Found!\n");
    } else {
        printf("Enter amount to deposit: ");
        scanf("%f", &amount);
        users[idx].balance += amount;
        printf("Amount Deposited Successfully!\n");
    }
}

void withdraw() {
    int acc_no;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    
    int idx = findAccount(acc_no);
    if (idx == -1) {
        printf("Account Not Found!\n");
    } else {
        printf("Enter amount to withdraw: ");
        scanf("%f", &amount);
        if(amount > users[idx].balance) {
            printf("Insufficient Balance!\n");
        } else {
            users[idx].balance -= amount;
            printf("Amount Withdrawn Successfully!\n");
        }
    }
}

void checkBalance() {
    int acc_no;
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    
    int idx = findAccount(acc_no);
    if (idx == -1) {
        printf("Account Not Found!\n");
    } else {
        printf("Account Holder: %s\n", users[idx].name);
        printf("Account Number: %d\n", users[idx].acc_no);
        printf("Available Balance: %.2f\n", users[idx].balance);
    }
}

int main() {
    int choice;
    while(1) {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: printf("Thank you!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
