#include<stdio.h>

#define MAX_SZ  50

int data[MAX_SZ], temp[MAX_SZ];
int power(int n){
	int i, p = 1;
	for(i = 1; i <= n; i++){
		p = p * 2;
	}
	return(p);
}

int findParityBits(int k, int r){
	int n, i, j;
	int errorSum = 0,countOnes;
    	n = j = 1;
	while(n < power(r)){
		i = n;
		countOnes = 0;
		while(i <= (k + r)){
			for(j = 0; j < n; j++){
				if(temp[i + j] == 1){
					countOnes++;
				}
			}
			i = i + 2 * n;
		}
		if((countOnes % 2) != 0){
			temp[n] = 1;
			errorSum += n ;
		}
		else{
			temp[n] = 0;
		}
		n = n * 2;
	}
    return errorSum;
}

int hammingCode(int k){
	int i, j, d = 0;
    int r = 1;
    while(k > (power(r) - r - 1)){
		r++;
	}
	j = k;
	for(i = 1; i <= (k + r); i++){
		if(i == power(d)){
			temp[i] = 0;
			d++;
		}
		else
			temp[i] = data[j--];{
		}
	}
	return(r);
}

int  checkError(int errorPosition,int r){
	int i;
	for(i = 1; i < power(r) ; i = i * 2){
		if(errorPosition == i){
			return 1;
		 }
	}
	return 0;
}

int main(){
	int k, r;
	int errorPosition, i;

	printf("no of databits\n");
	scanf("%d", &k);
	printf("enter the data to be transmitted(0's & 1's)\n");
	for(i = 1; i <= k; i++){
		scanf("%d", &data[i]);
	}
	r = hammingCode(k);
	printf ("\nNo. of parity bits r = %d", r);
	findParityBits(k, r);

	printf("\n\nHamming code for the data:\n");
	for(i = 1; i <= (k + r); i++){
		printf("%4d", temp[i]);
	}
     printf("\n\nenter the recieved  data:\n");
	for (i = 1; i <= k + r; i++){
		scanf("%d", &temp[i]);
	}
	errorPosition =  findParityBits(k,r);
	if (errorPosition != 0) {
		if(checkError(errorPosition,r)){
			printf("\n\nParity bit P%d  is corrupted, data is fine", errorPosition);
	    }else{
			printf("\n\nData bit D%d is corrupted. ", errorPosition);
			temp[errorPosition] = !(temp[errorPosition]);
			printf("\n\nCorrected data bits with new parity bits\n");
			for(i = 1; i <= (k + r); i++){
				printf("%4d", temp[i]);
            }
            printf("\n");
		}
	}
	else
	printf("No error");
	return 0;
}
