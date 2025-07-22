#include <stdio.h>
#include <stdlib.h>

int main() {
    system("cls");
    float draw, dep, transfer;
    char name[24];
    float balance = 5000;
    int account, account1, account2;
    int type;
    int transaction = 1;

    printf("\n\t\t\t\tBANKING SYSTEM\n\n");
    printf("Enter your name: ");
    scanf("%s", name);
    printf("\nPlease enter your account no.: ");
    scanf("%d", &type);

    while (transaction == 1) {
        int option;
        printf("\nChoose what you want to do:\n");
        printf("1 - Balance Enquiry\n");
        printf("2 - Deposit\n");
        printf("3 - Withdraw\n");
        printf("4 - Transfer\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Your current balance is: %.2f $\n", balance);
                break;
            case 2:
                printf("How much money do you want to deposit: ");
                scanf("%f", &dep);
                if (dep > 0 && dep <= 20000) {
                    printf("%.2f $ deposited in your account.\n", dep);
                    balance += dep;
                } else if (dep > 20000) {
                    printf("You can't deposit that much amount in one time.\n");
                } else {
                    printf("Invalid deposit amount.\n");
                }
                break;
            case 3:
                printf("How much money do you want to withdraw: ");
                scanf("%f", &draw);
                if (draw <= balance && draw <= 20000) {
                    printf("%.2f $ withdrawn.\n", draw);
                    balance -= draw;
                } else if (draw > 20000) {
                    printf("You can't withdraw that much amount in one time.\n");
                } else {
                    printf("You don't have enough money.\n");
                }
                break;
            case 4:
                printf("Account you want to transfer to: ");
                scanf("%d", &account2);
                printf("How much amount: ");
                scanf("%f", &transfer);
                if (balance >= transfer) {
                    printf("%.2f Rs successfully transferred.\n", transfer);
                    balance -= transfer;
                } else {
                    printf("You do not have sufficient balance.\n");
                }
                break;
            default:
                printf("Invalid transaction.\n");
        }

        transaction = 0;
        while (transaction != 1 && transaction != 2) {
            printf("Do you want to do another transaction? (1. Yes 2. No): ");
            scanf("%d", &transaction);
        }
    }

    printf("\nThank you for using our banking system!\n");
    return 0;
}

