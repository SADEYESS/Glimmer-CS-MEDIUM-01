#include <stdio.h>
#include <string.h>

char bignumber1[41], bignumber2[41], sum[42];             //39位数，如果有符号就40位，还有最后的结束符

int MakeUp(char* bignumber1,char* bignumber2){            //创建一个在两数长短不一致时对较短数补 0 的函数,同 Step 2
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

void AddNumbers(char* bignumber1, char* bignumber2, int maxsize){       //因为要多次使用加法运算，将加法运算写为函数，方便调用，功能同 Step 2

    int ten = 0;                                          //定义用来表示两数之和大于等于10时的进位数，由于个位不会接受进位，将进位数初始化为0

    for(int i = maxsize - 1; i >= 0; i--){                //从个位开始对两个大数的每一位分别求和                                      
        sum[i + 1] = ( ( (bignumber1[i] - '0') + (bignumber2[i] - '0') ) + ten) % 10  + '0';  //计算当前两数的某一位的和，保留两数之和的个位，如有从上一位的进位则加上一
        ten = ( (bignumber1[i] - '0') + (bignumber2[i] - '0') + ten) / 10;                    //每次循环时计算两数的和，如果当前计算的两位数有进位，则进位数的值赋为1，在下一次循环计算更高一位数时就加上1
    }
    sum[0] = ten + '0';  
}

void CompareNumbers(char* bignumber1, char* bignumber2, char **bigone,char** smallone){      //为配合减法运算，需要用大数减去小数，创建一个用来比较两数大小的函数
    int size1 = strlen(bignumber1);                     
    int size2 = strlen(bignumber2);

    if(size1 != size2){                                                 //如果两数位数不等，则位数长的数更大
        * bigone   = size1 > size2 ? bignumber1 : bignumber2;
        * smallone = size1 < size2 ? bignumber1 : bignumber2;
    }

    if(size1 == size2){                                                 //如果两数位数相等，则从最高位逐一比较每隔数大小，高位大的数大
        for(int i = 0; i < size1 ; i++){
            if (bignumber1[i] > bignumber2[i]){
                * bigone   = bignumber1;
                * smallone = bignumber2;
            break;
            }

            else if (bignumber1[i] < bignumber2[i]){
                * bigone   = bignumber2;
                * smallone = bignumber1;
            break;
            }

            else{                                                      //如果两数相等，较大数和较小数可以在两数中任意取值
                * bigone   = bignumber1;
                * smallone = bignumber2;
            }
        }
    }
}

void MinusNumbers(char* bigone, char* smallone, int maxsize){      //创建一个用于减法运算的函数
    int ten = 0;                                                   //ten 在这里表示被借位的情况
    
    for(int i = maxsize - 1; i >= 0; i--){     
        int minuesednum = (bigone[i] - '0')  - ten - (smallone[i] - '0');   //利用 for 循环计算每一位数做差的情况
        if( minuesednum < 0){                                               //如果两数的差值小于 0，需要向高位借位
            minuesednum += 10;                                              //借位后当前位加 10
            ten = 1;                                                        //记录借位的情况
        }

        else{                                                               //如果两数之差位正则无需借位
            ten = 0;                                                      
        }
        sum[i + 1] = minuesednum + '0';                           //存储计算结果
    }
    sum[0] = '0';                                                 //为配合下面的打印条件，最高位为 0
}

void PrintNumbers(int maxsize){                        //同样由于要多次调用，把打印内容创建成函数
    int i = 0;

    while (i < maxsize && sum[i] == '0'){               //利用 while 循环绕过结果前多余的 0  
        i++;
    }

    if (i == maxsize){                                  //如果遍历完数组中的所有内容都是 0，打印结果为 0
        printf("0");
    }
    else {
        for (; i <= maxsize; i++){                       //正常情况下从非 0 位开始打印
            printf("%c", sum[i]);
        }
    }
}

int main(){
    scanf("%39s",bignumber1);                             //以字符串形式把两个大数存储到数组中，限制输入的长度
    scanf("%39s",bignumber2);

    int size1 = strlen(bignumber1);                       //求得第一个数的长度
    int size2 = strlen(bignumber2);

    if(bignumber1[0] != '-' && bignumber2[0] != '-'){         //两数同正，进行加法运算
        int maxsize = MakeUp(bignumber1, bignumber2);

        AddNumbers(bignumber1, bignumber2, maxsize);
        PrintNumbers(maxsize);
    }

    if(bignumber1[0] == '-' && bignumber2[0] == '-'){         //两数同负，去负号，等效成成正数的加法运算
        for (int i = 1; i <= size1; i++) {                    //使两数组内的数的位置整体前移一位，取代负号的位置，方便运算
            bignumber1[i - 1] = bignumber1[i];
        }

        for (int i = 1; i <= size2; i++) {
            bignumber2[i - 1] = bignumber2[i];
        }

        int maxsize = MakeUp(bignumber1, bignumber2); 

        printf("-");                                          //打印删掉的负号
        AddNumbers(bignumber1, bignumber2, maxsize);          //进行加法运算
        PrintNumbers(maxsize);
    }
             
    if(bignumber1[0] == '-' && bignumber2[0] != '-' ){       //一正一负的情况之第一个数为负
        for (int i = 1; i <= size1; i++) {                   //去负号
        bignumber1[i - 1] = bignumber1[i];
        }

        int maxsize = MakeUp(bignumber1, bignumber2);
   
        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);  //比较大小
        MinusNumbers(bigone, smallone, maxsize);

        if(bignumber1 == bigone){                            //如果负数的大小比正数大，结果为负数，加上负号
            printf("-");
        }
        PrintNumbers(maxsize);
    }

    if(bignumber1[0] != '-' && bignumber2[0] == '-'){       //一正一负的情况之第二个数为负，内容同上
        for (int i = 1; i <= size2; i++) {                
        bignumber2[i - 1] = bignumber2[i];
        }

        int maxsize = MakeUp(bignumber1, bignumber2);

        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);
        MinusNumbers(bigone, smallone, maxsize);

        if(bignumber2 == bigone){
            printf("-");
        }
        PrintNumbers(maxsize);
    } 
return 0;
}
