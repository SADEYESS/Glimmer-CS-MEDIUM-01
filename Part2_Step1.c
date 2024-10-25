#include <stdio.h>

char bignumber[40];   //2¹²⁸-1的值有39位数，由于字符串数组最后一位是 '\0' ，因此定义一个元素个数为 40 的数组

int main(){
    scanf("%s",bignumber);    //输入大数
    printf("%s",bignumber);   //输出大数
return 0;
}