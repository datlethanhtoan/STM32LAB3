#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
int main() {
    double ANS = 0;
    char expression[256];
    char operator;
    double num1, num2;
    int errorCheck = 0;
    char num2_str[20];
    char temp[30];
    FILE *ansFile = fopen("ans.txt", "r");
    if (ansFile != NULL) 
    {
        fscanf(ansFile, "%lf", &ANS);
        fclose(ansFile);
    } 
    else 
    {
        ansFile = fopen("ans.txt", "w");
        if (ansFile != NULL) 
        {
            fprintf(ansFile, "%.2lf\n", ANS);
            fclose(ansFile);
        }
    }
    while (1) {
        printf(">> ");
        scanf("%s", expression);
        
        if (strcmp(expression, "EXIT") == 0) 
        {
            break;
        } 
        else 
        {
            scanf(" %c", &operator);
            scanf(" %s", num2_str);

            if (strcmp(expression, "ANS") == 0) 
            {
                num1 = ANS;
            } else 
            {
                num1 = atof(expression);
            }
            if (strcmp(num2_str, "ANS") == 0) 
            {
                num2 = ANS;
            } else 
            {
                num2 = atof(num2_str);
            }

            double result = 0;

            switch (operator) 
            {
                case '+':
                    result = add(num1, num2);
                    break;
                case '-':
                    result = sub(num1, num2);
                    break;
                case '*':
                    result = mul(num1, num2);
                    break;
                case '/':
                    if (num2 == 0) 
                    {
                        errorCheck = 1;
                        printf("MATH ERROR\n");
                    } else 
                    {
                        result = divine(num1, num2);
                    }
                    break;
                case '%':
                    if (num2 == 0) 
                    {
                        errorCheck = 1;
                        printf("MATH ERROR\n");
                    } else 
                    {
                        result = modulo(num1, num2);
                    }
                    break;
                default:
                    errorCheck = 1;
                    printf("SYNTAX ERROR\n");
            }

            if (errorCheck == 0) 
            {
                printf("%.2lf\n", result);
                ANS = result;

                ansFile = fopen("ans.txt", "w");
                if (ansFile != NULL) 
                {
                    fprintf(ansFile, "%.2lf\n", ANS);
                    fclose(ansFile);
                }
            }

            errorCheck = 0;
            scanf("%s", temp);
            system("clear");
        }
    }

    return 0;
}
