#include <stdio.h>
#include <string.h>

char bignumber1[40], bignumber2[40], sum[41];             //创建用于存储两个大数和它们的和的字符数组

int MakeUp(char* bignumber1,char* bignumber2){            //创建一个在两数长短不一致时对较短数补 0 的函数
    int size1 = strlen(bignumber1);                       //求得第一个数的长度
    int size2 = strlen(bignumber2);                       //求得第二个数的长度
    int maxsize = size1 > size2 ? size1 : size2;          //求两数中较长数的长度
    int minsize = size1 < size2 ? size1 : size2;          //求两数中较短数的长度
    char* MinSizeNum = size1 < size2 ? bignumber1 : bignumber2;      //定义指针数组用来对较短数进行补 0 操作
    
    for(int i = minsize-1 ; i >= 0; i--){                 //为了与较长的数对齐，使用 for 循环来把较短数的有效位移到末尾
        MinSizeNum[i + (maxsize - minsize)] = MinSizeNum[i];
    }
    
    for(int i = 0; i < maxsize - minsize; i++){           //使用 for 循环来为较短数与较长数相差的高位补上 0
        MinSizeNum[i] = '0';
    }
return maxsize;                                           //由于数字长度在下面打印运算结果时还会用到，所以使函数返回求得的长度值
}

int main(){
    scanf("%39s",bignumber1);                             //以字符串形式把两个大数存储到数组中，限制输入的长度
    scanf("%39s",bignumber2);
                                 
    int maxsize = MakeUp(bignumber1,bignumber2);          //如果两数位数不等，进行补零操作

    int ten = 0;                                          //定义用来表示两数之和大于等于10时的进位数，由于个位不会接受进位，将进位数初始化为0
    for(int i = maxsize - 1; i >= 0; i--){                //从个位开始对两个大数的每一位分别求和                                      
        sum[i + 1] = ( ( (bignumber1[i] - '0') + (bignumber2[i] - '0') ) + ten) % 10  + '0';  //计算当前两数的某一位的和，保留两数之和的个位，如有从上一位的进位则加上一
        ten = ( (bignumber1[i] - '0') + (bignumber2[i] - '0') + ten) / 10;                    //每次循环时计算两数的和，如果当前计算的两位数有进位，则进位数的值赋为1，在下一次循环计算更高一位数时就加上1
    }
    sum[0] = ten + '0';                                   //考虑两数的最高位进位的情况

    int size1 = strlen(bignumber1);                       //求得第一个数的长度
    int size2 = strlen(bignumber2);

    if (sum[0] != '0'){                                  //如果最高位有进位，正常打印结果
        for (int i = 0; i <= maxsize; i++){              //利用 for 循环从最高位打印两数的和
            printf("%c", sum[i]);
        }
    } 
    else{                                               //如果两位数长度相等且第一位没有进位，为了使输出格式符合题目要求，不打印第一位的 0
        for (int i = 1; i <= maxsize; i++){
            printf("%c", sum[i]);
        }
    }
return 0;
}