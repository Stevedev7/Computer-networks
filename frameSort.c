#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE 3

typedef struct p {
    int sequenceNumber;
    char data[SIZE + 1];
} p;

p *readData, *transferData;
time_t t;

int divide(char *message) {
    int messagelen, numberOfPackets, i, j;
    messagelen = strlen(message);
    numberOfPackets = messagelen/SIZE;

    if ((messagelen%SIZE) != 0) {
        numberOfPackets++;
    }
    
    readData = (p*) malloc(sizeof(p) * numberOfPackets);
    for (i = 0; i < numberOfPackets; ++i) {
        readData[i].sequenceNumber = i + 1;{
        for (j = 0; (j < SIZE)&&(*message!='\0'); ++j, ++message)
            readData[i].data[j] = *message;
        }
        readData[i].data[j] = '\0';
    }

    printf("\nThe Message has been divided as follows\n");
    printf("\np No.\tData\n\n");
    for (i = 0; i < numberOfPackets; ++i){
        printf(" %d\t\t%s\n", readData[i].sequenceNumber, readData[i].data);
    }
    return numberOfPackets;
}

void shuffle(int numberOfPackets) {
    int *status;
    int i, j, transfer;

    srand(time(&t));
    status = (int*) calloc(numberOfPackets, sizeof(int));
    transferData = (p*) malloc(sizeof(p) * numberOfPackets);

    for (i = 0; i < numberOfPackets;) {
        transfer = rand()%numberOfPackets;
        if (status[transfer] != 1) {
            transferData[i].sequenceNumber = readData[transfer].sequenceNumber;
            strcpy(transferData[i].data, readData[transfer].data);
            ++i;
            status[transfer] = 1;
        }
    }
    free(status);
}

void sortFrames(int numberOfPackets) {
    p temp;
    int i, j;

    for (i = 0; i < numberOfPackets; ++i) {
        for (j = 0; j < numberOfPackets - (i + 1); ++j) {
            if (transferData[j].sequenceNumber > transferData[j + 1].sequenceNumber) {
                temp.sequenceNumber = transferData[j].sequenceNumber;
                strcpy(temp.data, transferData[j].data);
                transferData[j].sequenceNumber = transferData[j + 1].sequenceNumber;
                strcpy(transferData[j].data, transferData[j + 1].data);
                transferData[j + 1].sequenceNumber = temp.sequenceNumber;
                strcpy(transferData[j + 1].data, temp.data);
            }
        }
    }
}

void receive(int numberOfPackets) {
    int i;
    printf("\nps received in the following order\n");
    for (i = 0; i < numberOfPackets; ++i) {
        printf("%4d", transferData[i].sequenceNumber);
    }
    sortFrames(numberOfPackets);

    printf("\n\nps in order after sorting..\n");
    for (i = 0; i < numberOfPackets; ++i) {
        printf("%4d", transferData[i].sequenceNumber);
    }
    printf("\n\nMessage received is :\n");
    for (i = 0; i < numberOfPackets; ++i) {
        printf("%s", transferData[i].data);
    }
    printf("\n");
}

int main() {
    char message[25];
    int numberOfPackets;
    printf("\nEnter The message to be transfermitted :\n");
    scanf("%[^\n]", message);
    numberOfPackets = divide(message);
    shuffle(numberOfPackets);
    receive(numberOfPackets);
    free(readData);
    free(transferData);
    return 0;
}
