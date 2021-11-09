#include <stdio.h>

int main()
{
    const int STATE_NUM_START = 0, STATE_AFTER_SIGN = 1, STATE_NUM = 2, STATE_OP = 3;
    int state = STATE_NUM_START; // State
    double result = 0;           // Result
    char last_op = '+';          // The last operator
    int num_sign = 1;            // The sign of the operand
    double num = 0;              // Operand
    double num_factor = 1;       // Floating point
    int next = 0;                // Get next char?
    int pos = 0;                 // Input position
    char c = getchar();          // Get a char from input
    while (c != EOF)
    {
        if (next == 1)
        {
            c = getchar();
            pos++;
        }

        // Debug
        printf("c = %c(%d)\tlast_op = %c\tresult = %8f\tnum = %8f\tstate = %d\n", c, c, last_op, result, num, state);

        switch (state)
        {
        // Switch to other states base on the input.
        case STATE_NUM_START:
            if (c == '+')
            {
                num_sign = 1;
                state = STATE_AFTER_SIGN;
                next = 1;
            }
            else if (c == '-')
            {
                num_sign = -1;
                state = STATE_AFTER_SIGN;
                next = 1;
            }
            else if ((c == '.') || (c >= '0' && c <= '9'))
            {
                state = STATE_NUM;
                next = 0;
            }
            else if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                // omit spaces
                next = 1;
            }
            else if (c == EOF)
            {
                next = 0;
            }
            else
            {
                printf("Unexpected char at pos %d, '%c'\n", pos, c);
                return 1;
            }
            break;
        case STATE_AFTER_SIGN:
            if ((c == '.') || (c >= '0' && c <= '9'))
            {
                state = STATE_NUM;
                next = 0;
            }
            else if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                // omit spaces
                next = 1;
            }
            else if (c == EOF)
            {
                next = 0;
            }
            else
            {
                printf("Unexpected char at pos %d, '%c'\n", pos, c);
                return 1;
            }
            break;
        // Process operands and evaluate the statement from left to right.
        // TODO: Additional code required to process operator precedence.
        case STATE_OP:
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=')
            {
                switch (last_op)
                {
                case '+':
                    result += num * num_sign;
                    break;
                case '-':
                    result -= num * num_sign;
                    break;
                case '*':
                    result *= num * num_sign;
                    break;
                case '/':
                    result /= num * num_sign;
                    break;
                }

                // printf("%f%c", num * num_sign, c);

                // End
                if (c == '=')
                {
                    printf("--> %f\n", result);
                    return 0;
                }

                num = 0;
                num_sign = 1;
                num_factor = 1;
                last_op = c;
                state = STATE_NUM_START;
                next = 1;
            }
            else if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                // omit spaces
                next = 1;
            }
            else if (c == EOF)
            {
                next = 0;
            }
            else
            {
                printf("Unexpected char at pos %d, '%c'\n", pos, c);
                return 1;
            }
            break;
        // Process the following digits of a number.
        case STATE_NUM:
            // Switch to data state if the input is not a digit.
            if (c == '.')
            {
                num_factor = 0.1;
                next = 1;
            }
            else if (c >= '0' && c <= '9')
            {
                if (num_factor == 1)
                {
                    num *= 10;
                    num += (c - '0');
                }
                else
                {
                    num += (c - '0') * num_factor;
                    num_factor /= 10;
                }
                next = 1;
            }
            else
            {
                state = STATE_OP;
                next = 0;
            }
            break;
        }
    }

    return 0;
}
