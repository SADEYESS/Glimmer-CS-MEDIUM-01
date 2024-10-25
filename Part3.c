#include <stdio.h>
#include <string.h>

char input[90], bignumber1[40], character[2], bignumber2[40];   //创建用来存储输入全部内容、两个大数和符号的四个字符数组

int main(){
    fgets(input, 90, stdin);      //使用 fgets 函数来读取输入的全部内容

    int i = 0, n1 = 0, n2 = 0;               //声明数组所使用的下标

    if(input[i] == '('){                     //如果第一个数是带括号的负数，跳过括号
        i += 1;
    }

    while( input[i] != ')' && input[i] != ' '){  //从输入中读取第一大数并存储到大数数组中，直到遇到空格或右括号为止
        bignumber1[n1] = input[i]; 
        i++;
        n1++;
    }

    if(input[0] != '(' ){                        //如果第一个数是正数，等效于没有左括号，让输入数组下标加 1 来跳过空格
        i += 1;                                  
    }
    else{                                        //如果第一个数是负数，有左括号和右括号，让输入数组下标加 2 来跳过空格
        i += 2;
    }

    character[0] = input[i];                 //跳过空格后读取输入的运算符号并存储到运算符号的数组中
    i += 2;                                  //使下标加 2 来跳过空格，来到负数的左括号或者正数的的最高位

    if(input[i] == '('){                     //如果第二个数是带括号的负数，跳过括号
        i++;
    }

    while( input[i] != ')' && input[i] != '\0' && input[i] != '\n'){    //将第二个大数存储到数组中
        bignumber2[n2] = input[i];
        i++;
        n2++;
    }

    printf("Bignumber1 is :%s\n", bignumber1);   //打印读取到的内容
    printf("BCharacter is :%s\n", character);
    printf("bignumber2 is :%s\n", bignumber2);

return 0; 
}