#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define len 3
using namespace std;

int main(){
	srand(time(NULL));
	int Q[len] = {},A[len] = {},a;
	for(int i = 0;i<len;i++){
		Q[i] = rand()%10;
	}
	while(1){
		int count_A = 0,count_B = 0;
		printf("enter your answer(%d number): ",len);
		scanf("%d",&a);
		for(int i = (len-1);i>=0;i--){
			A[i] = a%10;
			a = a/10;
		}
		//A
		for(int i = 0;i<len;i++){
			for(int j = 0;j<len;j++){
				if(A[i]==Q[j]){
					count_A++;
					break;
				}
			}
		}
		//B
		for(int i = 0;i<len;i++){
			if(A[i]==Q[i]){
				count_B++;
			}
		}

		if(count_A==len&&count_B==len){
			printf("You Win!!!");
			break;
		}
		printf("currect valum: %d\ncurrect position: %d\n",count_A,count_B);
	}

}
