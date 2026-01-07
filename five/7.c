#include <stdio.h>
#include <string.h>

void sort(char *names[], int n)
{
    char *temp;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (strcmp(names[j], names[j + 1]) > 0)
            {
                temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }
}

int main()
{
    char *books[] =
    {
        "The Great Gatsby",
        "To Kill a Mockingbird",
        "1984",
        "Pride and Prejudice",
        "Moby Dick"
    };
    
    int n = sizeof(books) / sizeof(books[0]);
    
    printf("排序前:\n");
    
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", books[i]);
    }
    
    sort(books, n);
    
    printf("\n排序后:\n");
    
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", books[i]);
    }
    
    return 0;
}