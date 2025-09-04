#include <stdio.h>
#include <string.h>

char *endings[] = {"ing", "ed", "en", "s", "ion"};

void stemming(char input[]) {
    int len = strlen(input);

    if (len > 3 && strcmp(&input[len - 3], endings[0]) == 0) { 
        input[len - 3] = '\0';
    }
    else if (len > 2 && strcmp(&input[len - 2], endings[1]) == 0) {  
        input[len - 2] = '\0';
    }
    else if (len > 2 && strcmp(&input[len - 2], endings[2]) == 0) {  
        input[len - 2] = '\0';
    }
    else if (len > 1 && strcmp(&input[len - 1], endings[3]) == 0) {  
        input[len - 1] = '\0';
    }
    else if (len > 3 && strcmp(&input[len - 3], endings[4]) == 0)  // ion
        input[len - 3] = '\0';
}

int main() {
    char input[5][50];

    printf("Enter the 5 strings for stemming:\n");
    for(int i=0;i<5;i++){
      scanf("%s", input[i]);  
      stemming(input[i]);
      printf("After stemming: %s\n", input[i]);
    }

    return 0;
}