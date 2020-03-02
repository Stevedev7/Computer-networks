/**************************************************************************
*  File Name   : HamCode.c
*
*  Description : Hamming Code generation for error detection and correction.
***************************************************************************/
#include<stdio.h>

#define MAX_SZ  50

int data[MAX_SZ],temp[MAX_SZ];
// finds 2^n
int power(int n)
{
	int i,p=1;
	for(i=1;i<=n;i++)
	{
		p=p*2;
	}
	return(p);
}
// computes parity bits, k= no. of data bits,r=no. of parity bits.
int find_parity_bits(int k, int r)
{
	int n,i,j;
	int err_sum = 0,cnt_ones;
    	n = j = 1;
	while(n < power(r))
	{
		i=n;
		cnt_ones=0;
		while(i<=(k+r))
		{
			for(j=0;j<n;j++)
			{
				if(temp[i+j]==1)
					cnt_ones++;
			}
			i=i+2*n;
		}
		if((cnt_ones%2)!=0)
		{
			temp[n]=1;
			err_sum += n ;
		}
		else
			temp[n]=0;
			n=n*2;
	}
      return err_sum;
}

//finds hamming code

int hamming_code(int k)
{
	int i,j,d=0;
    int r = 1; //r = no.of parity bits

    while(k > (power(r)-r-1))
		r++;

	j = k;
	for(i=1;i<=(k+r);i++)
	{
		if(i==power(d))
		{
			temp[i]=0;
			d++;
		}
		else
			temp[i]=data[j--];
	}

	return(r);
}

int  check_err(int err_pos,int r)
{
	int i;

	for(i=1;i < power(r) ; i = i * 2)
	{
		if(err_pos == i)
		{
			return 1;
		 }
	}
	return 0;
}
int main()
{

	int k,r;
	int err_pos,i;

	printf("no of databits\n");
	scanf("%d",&k);
	printf("enter the data to be transmitted(0's & 1's)\n");
	for(i=1;i<=k;i++)
		scanf("%d",&data[i]);

	r = hamming_code(k);   // find hamming code
	printf ("\nNo. of parity bits r = %d",r);
	find_parity_bits(k,r);

	printf("\n\nHamming code for the data:\n");
	for(i=1;i<=(k+r);i++)
		printf("%4d",temp[i]);

	// error detection and correction
     printf("\n\nenter the recieved  data:\n");
	for (i=1; i <= k+r; i++)
		scanf("%d", &temp[i]);

	err_pos =  find_parity_bits(k,r);

	if (err_pos != 0)
	{
if(check_err(err_pos,r))
		printf("\n\nParity bit P%d  is corrupted, data is fine", err_pos);
	    else
		{
			printf("\n\nData bit D%d is corrupted. ", err_pos);
			// flip the error bit
			temp[err_pos] = !(temp[err_pos]);
			printf("\n\nCorrected data bits with new parity bits\n");
			for(i=1;i<=(k+r);i++){
				printf("%4d",temp[i]);
            }
            printf("\n");
		}
	}
	else
		printf("No error");
	return 0;
}
