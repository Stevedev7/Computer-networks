#include <stdio.h>
struct {
    /* data */
    int cost, via;
}routeTable[10][10];

int n;

void buildRouteTable(int i){
    int j, k, newCost = 0;
    for(j = 0; j < n; j++){
        for (k = 0; k < n && j != i; k++){
            if (routeTable[i][j].cost != 999){
                /* code */
                newCost = routeTable[i][j].cost + routeTable[j][k].cost;
                if(routeTable[i][k].cost > newCost){
                    routeTable[i][k].cost = newCost;
                    routeTable[i][k].via = routeTable[i][j].via;
                }
            }
        }
    }
}

void findPath(int i, int j){
    printf("%c", 'A' + i);
    if(i != j){
        printf(" --> ");
        findPath(routeTable[i][j].via, j);
    }
}

void dispRouteTable(int i){
    int j;
    printf("\nFinal Routing Table for %c: ", 'A' + i);
    printf("\n\tDestination\tCost\tOutgoing line");
    printf("\n\t-----------\t----\t-------------\n");
    for(j = 0; j < n; j++){
        printf("\n\t\t%c", 'A' + j);
        printf("\t%d", routeTable[i][j].cost);
        printf("\t%c\n", 'A' + routeTable[i][j].via);
    }
}

void readRouteTable(){
    int i, j;
    printf("Enter the initial routing table (if no direct node, enter 999)\n");
    for(i = 0; i < n; i++){
        printf("\nRouting table for %c\n", 'A' + i);
        for(j = 0; j < n; j++){
            if( i == j){
                routeTable[i][j].cost = 0;
            } else{
                printf("--> %c: ", 'A' + j);
                scanf("%d", &routeTable[i][j].cost);
            }
            if(routeTable[i][j].cost != 999){
                routeTable[i][j].via = j;
            } else{
                routeTable[i][j].via = 999;
            }
        }
    }
}
int main(){
    int source, destination, i, option;

    printf("Enter the number of routers: ");
    scanf("%d", &n);
    readRouteTable();
    for(i = 0; i < n; i++){
        buildRouteTable(i);
    }
    for(i = 0; i < n; i++){
        dispRouteTable(i);
    }
    do{
        printf("\nEnter the source node(0 to %d): ", n-1);
        scanf("%d", &source);
        printf("\nEnter the destination node(0 to %d): ", n-1);
        scanf("%d", &destination);
        if(source > (n - 1) || destination > (n - 1)){
            printf("\nRoute doesn't exist");
        } else{
            findPath(source, destination);
            printf("\nThe cost of the shortest route is:\t%d\n", routeTable[source][destination].cost);
        }
        printf("\nDo you want to continue?(0/1):\n");
        scanf("%d", &option);
    }while(option);

    return 0;
}
