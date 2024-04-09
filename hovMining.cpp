#include <stdio.h>
#include <stdlib.h>

struct Mining
{
    int index;
    int gold;
    int depth;
    Mining *left;
    Mining *right;
};

Mining *createMining(int index, int gold, int depth)
{
    Mining *newMining = (Mining *)malloc(sizeof(Mining));
    newMining->index = index;
    newMining->gold = gold;
    newMining->depth = depth;
    newMining->left = NULL;
    newMining->right = NULL;

    return newMining;
}

Mining *insertMining(Mining *temp, int index, int gold, int depth)
{
    if (temp == NULL)
    {
        return createMining(index, gold, depth);
    }
    else if (temp->index > index)
    {
        temp->left = insertMining(temp->left, index, gold, depth + 1); // Menaikkan kedalaman hanya saat bergerak ke kiri
    }
    else if (temp->index < index)
    {
        temp->right = insertMining(temp->right, index, gold, depth + 1); // Menaikkan kedalaman hanya saat bergerak ke kanan
    }
    else
    {
        temp->gold += gold; // Hanya tambahkan jumlah emas jika cave sudah ada
    }

    return temp;
}

void calculateGoldPerDepth(Mining *curr, int goldPerDepth[])
{
    if (curr != NULL)
    {
        goldPerDepth[curr->depth] += curr->gold;
        calculateGoldPerDepth(curr->left, goldPerDepth);
        calculateGoldPerDepth(curr->right, goldPerDepth);
    }
}

void printInOrder(Mining *curr)
{
    if (curr != NULL)
    {
        printInOrder(curr->left);
        printf("Cave: %d (depth %d), total gold production: %d\n", curr->index, curr->depth, curr->gold);
        printInOrder(curr->right);
    }
}

void displayMiningReport(Mining *root)
{
    int goldPerDepth[1000] = {0};
    calculateGoldPerDepth(root, goldPerDepth);

    printf("Mining Report\n");
    printf("=============\n");
    for (int i = 1; i < 1000; i++)
    {
        if (goldPerDepth[i] > 0)
        {
            printf("Depth %d: Total gold production = %d\n", i, goldPerDepth[i]);
        }
    }
}

int main()
{
    Mining *root = NULL;

    int choice;
    int returnToMainPage = 0;
    int index;
    int gold;

    do
    {
        if (returnToMainPage)
        {
            choice = 0;
            returnToMainPage = 0;
        }
        else
        {
            system("cls");
            puts("Hov Mining Simulator");
            puts("====================");
            puts("[1] Insert Mining Data");
            puts("[2] Display All Cave Data");
            puts("[3] Display Mining Report");
            puts("[4] Exit");
            printf(">> ");
            scanf("%d", &choice);
        }

        switch (choice)
        {
        case 1:
            system("cls");

            do
            {
                printf("Input Cave Index [1-999]     : ");
                scanf("%d", &index);
            } while (index < 1 || index > 999);

            do
            {
                printf("Input gold production [1-100]: ");
                scanf("%d", &gold);
            } while (gold < 1 || gold > 100);

            root = insertMining(root, index, gold, 1);

            printf("New Cave Detected.\n");
            printf("Total gold production for Cave %d is %d\n\n", index, gold);

            printf("Press Enter to continue...");
            getchar();
            getchar();
            returnToMainPage = 1;
            break;
        case 2:
            system("cls");
            printf("Displaying All Cave Data\n");
            printf("========================\n");
            printInOrder(root);
            printf("\n");

            printf("Press Enter to continue...");
            getchar();
            getchar();
            returnToMainPage = 1;
            break;
        case 3:
            system("cls");
            printf("Displaying Mining Report\n");
            printf("========================\n");
            displayMiningReport(root);
            printf("\n");

            printf("Press Enter to continue...");
            getchar();
            getchar();
            returnToMainPage = 1;
            break;
        case 4:
            system("cls");
            // Hapus semua data dari memori
            while (root != NULL) {
                free(root->left); // Hapus subtree kiri
                free(root->right); // Hapus subtree kanan
                Mining *temp = root;
                root = root->left; // Geser root ke kiri untuk menghapus node saat ini
                free(temp); // Hapus node saat ini
            }

            printf("Thank you for playing Hov Mining Simulator!\n");
            printf("Press Enter to exit...");
            getchar();
            getchar();
            exit(0);
            break;
        }

    } while (choice != 4);

    return 0;
}
