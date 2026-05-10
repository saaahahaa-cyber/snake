#include<stdio.h>
int main(){
    int a,b;
    while(scanf("%d %d",&a,&b)==2){
        if(a==100||b==100){
            break;
        }
        else{
            printf("%d\n",a+b);
        }
    }
    return 0;
}