/*
    Author: Natalia Czyzewska

    A low-power nuclear reactor controller
    No considered rules (3.x, 5.x, 7.x, 12.x) have been violated
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

/*
Set standard input nonblocking, so that all stdio functions will return EOF (or a short read) when there is no more data.
Then restore the original state of standard input.
*/
void fdrain(FILE *const in) {
    if (in) {
        int const descriptor = fileno(in);
        int       dummy;
        long      flags;

        flags = fcntl(descriptor, F_GETFL);
        fcntl(descriptor, F_SETFL, flags | O_NONBLOCK);

        do {
            dummy = getc(in);
        } while (dummy != EOF);

        fcntl(descriptor, F_SETFL, flags);
    }
}

void switchOnMotor(int temperatures[], const int thresh[], int dangerous_condition) {
    printf("\nSwitching on a motor...\n");
    
    while(dangerous_condition) {
        for(int i=0; i<3; i++) {
            if(temperatures[i] >= thresh[i]) {
                printf("Temperature of T%d: %d (M%d = ON)\n", i+1, --temperatures[i], i+1);

                if(temperatures[i] < thresh[i]) {
                    printf("M%d = OFF\n", i+1);
                    dangerous_condition--;
                }
            }
        }
        sleep(2);
    }
    
    printf("Returning to normal operation...");
}

void monitorMeasures(int temperatures[], const int thresh[]) {
    int dangerous_condition = 0;
    
    for(int i=0; i<3; i++) {
        temperatures[i] = rand() % 40 + 1;
        printf("T%d: %d\n", i+1, temperatures[i]);

        if(temperatures[i] > thresh[i]) {
            printf("WARNING: temperature of T%d exceeds its threshold\n", i+1);
            dangerous_condition++;
        }
    }

    if(dangerous_condition) {
        switchOnMotor(temperatures, thresh, dangerous_condition);
    }

    fdrain(stdin);
}

void printCommands() {
    printf("List of commands:\n");
    printf("    ENTER - get measurements of temperature sensors\n");
    printf("    h - display the list of commands\n");
    printf("    q - quit\n\n");
}

int main() {
    printf("========================================\n");
    printf("A low-power nuclear reactor controller\n");
    printf("========================================\n");
    printCommands();
    
    srand(time(NULL));

    // Temperature sensors
    int temperatures[3];
    // Thresholds
    const int thresh[3] = {38, 30, 25};

    printf("===========\n");
    printf("Thresholds\n");
    printf("===========\n");
    for(int i=0; i<3; i++) {
        printf("%d: %d\n", i+1, thresh[i]);
    }

    while(1) {
        char c = getchar();
        if(c == '\n') {
            monitorMeasures(temperatures, thresh);
            printf("\n");
        } else if(c == 'h') {
            getchar();
            printCommands();
        } else if(c == 'q') {
            break;
        }
    }
    
    return 0;
}