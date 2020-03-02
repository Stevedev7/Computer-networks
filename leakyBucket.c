#include <stdio.h>
#include <stdlib.h>
#define bucketSize 250
#define outRate 25

struct{
    int arrivalTime, weight;
} packet[15];

void readPackets(int n){
    int i;
    for(i = 0; i < n; i++){
        printf("Enter arrival time: ");
        scanf("%d", &packet[i].arrivalTime);
        printf("Enter packet size: ");
        scanf("%d", &packet[i].weight);
    }
}


void leakyBucket(){
    int excess = bucketSize, i, j = 0, rem = 0;
    for(i = 0; i <= 30; i++){
        if(packet[j].arrivalTime == i){
            if(packet[j].weight <= excess){
                rem = packet[j].weight + rem;
                excess = excess - packet[j].weight;
                printf("At time = %d: packet %d inserted into bucket, remaining bucket size = %d\n", i, j + 1, excess);
                j++;
            } else{
                printf("At time = %d: packet %d discarded, packet size is more than buffer size.\n", i, j + 1);
                j++;
            }
        }
        if((i % 5) == 0){
            if(rem >= outRate){
                rem -= outRate;
                excess += outRate;
                printf("At time = %d: 25 Kbyte are transfered\nFree available space in the bucket = %d\n", i, excess);
            } else if(rem > 0){
                excess += rem;
                printf("At time = %d: %d Kbyte are transfered\nFree available space in the bucket = %d\n", i, rem, excess);
                rem = 0;
            }
        }
    }
    while (rem != 0){
        if(rem < outRate){
            excess += rem;
            printf("At time = %d: %d Kbyte are transfered\nFree available space in the bucket = %d\n", i++, rem, excess);
            break;
        }
        rem -= outRate;
        excess += outRate;
        printf("At time = %d: %d Kbyte are transfered\nFree available space in the bucket = %d\n", i++, outRate, excess);
    }
    printf("Bucket is empty\n");

}

int main(){
    int n;
    system("clear");
    printf("Enter the number of packets: ");
    scanf("%d", &n);
    readPackets(n);
    leakyBucket();
    return 0;
}
