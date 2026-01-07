#include <stdio.h>

int main() {
    char dest[50] = "Hello";
    char src[] = " World";
    
    int i = 0;
    while (dest[i]) i++;
    
    int j = 0;
    while (src[j]) {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    
    int len = 0;
    while (dest[len]) len++;
    
    printf("Concatenated: %s\n", dest);
    printf("Length: %d\n", len);
    
    return 0;
}