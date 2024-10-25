//除法运算来不及完成了QAQ

#include <stdio.h>
#include <string.h>

char input[90], bignumber1[41], character[2], bignumber2[41], sum[80];

void GetNumbers(char* input, char* bignumber1, char* character, char* bignumber2){
    fgets(input, 90, stdin);                 //使用 fgets 函数来读取输入的全部内容

    int i = 0, n1 = 0, n2 = 0;               //声明数组所使用的下标

    if(input[i] == '('){                     //如果第一个数是带括号的负数，跳过括号
        i += 1;
    }

    while( input[0] == '(' && input[i] == '-' || (input[i] >= '0' && input[i] <= '9') && input[i] != ')' ){  //根据题目输入格式要求对循环条件进行更改，因为没有了空格，循环直到遇到非数字的运算符号或右括号为止
        bignumber1[n1] = input[i]; 
        i++;
        n1++;
    }

    if(input[i] == ')'){                     //如果第一个数是带括号的负数，跳过右括号
        i += 1;
    }

    character[0] = input[i];                 //跳过空格后读取输入的运算符号并存储到运算符号的数组中
    i += 1;                                  //使下标加 2 来跳过空格，来到负数的左括号或者正数的的最高位

    if(input[i] == '('){                     //如果第二个数是带括号的负数，跳过括号
        i++;
    }

    while( input[i] != ')' && input[i] != '\0' && input[i] != '\n'){    //将第二个大数存储到数组中
        bignumber2[n2] = input[i];
        i++;
        n2++;
    }
}

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

void RemoveMinus(char* bignumberN ,int sizeN){
    for (int i = 1; i <= sizeN; i++) {                    //使两数组内的数的位置整体前移一位，取代负号的位置，方便运算
        bignumberN[i - 1] = bignumberN[i];
    }
}

void AddNumbers(char* bignumber1, char* bignumber2, int maxsize){       //因为要多次使用加法运算，将加法运算写为函数，方便调用，功能同 Step 2
    int ten = 0;                                          //定义用来表示两数之和大于等于 10 时的进位数，由于个位不会接受进位，将进位数初始化为0

    for(int i = maxsize - 1; i >= 0; i--){                //从个位开始对两个大数的每一位分别求和                                      
        sum[i + 1] = ( ( (bignumber1[i] - '0') + (bignumber2[i] - '0') ) + ten) % 10  + '0';  //计算当前两数的某一位的和，保留两数之和的个位，如有从上一位的进位则加上1
        ten = ( (bignumber1[i] - '0') + (bignumber2[i] - '0') + ten) / 10;                    //每次循环时计算两数的和，如果当前计算的两位数有进位，则进位数的值赋为1，在下一次循环计算更高一位数时就加上1
    }
    sum[0] = ten + '0';                                   //表示进位情况
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

void MinusNumbers(char* bigone, char* smallone, int maxsize){       //创建一个用于减法运算的函数
    int ten = 0;                                                    //定义表示借位的数，由于个位不会被借位，将借位数初始化为0
    
    for(int i = maxsize - 1; i >= 0; i--){           
        int MinuesedNum = (bigone[i] - '0')  - ten - (smallone[i] - '0');   //利用 for 循环计算每一位数做差的情况

        if( MinuesedNum < 0){                                               //如果两数的差值小于 0，需要向高位借位
            MinuesedNum += 10;                                              //借位后当前位加 10
            ten = 1;                                                        //记录借位
        }
        else{                                                               //如果两数之差为正则无需借位
            ten = 0;                                                        
        }
        sum[i+1] = MinuesedNum + '0';                               //存储计算结果
    }
    sum[0] = '0';                                                   //为配合下面的打印条件，最高位为 0
}

void MultiplyNumbers(char* bigone, char* smallone){
    int bigsize   = strlen(bigone);                     //分别求得大小两数的长度
    int smallsize = strlen(smallone);

    for(int i = 0; i < 80; i++){                        //利用 for 循环将每个元素设置为 '0'
        sum[i] = '0';                                  
    }

    for (int n1 = bigsize - 1; n1 >= 0; n1--){       
        int ten = 0;                                    //初始化进位数
        for (int n2 = smallsize - 1; n2 >= 0; n2--){
            int FormerSum = (sum[n1 + n2 + 1] - '0');   //获取上一步运算当前位的值
            int SumNow = (bigone[n1] - '0') * (smallone[n2] - '0') + FormerSum + ten;  //运算本步骤某位的值
            sum[n1 + n2 + 1] = (SumNow % 10) + '0';     //将新得到的某位的值的个位存入结果数组
            ten = SumNow / 10;                          //为进位数赋值
        }
        sum[n1] = (sum[n1] - '0') + ten + '0';          //处理进位，得到最终值
    }
}
//////////////////////////////////////////////////////// 未完成
int DivisionNumbers(char* bigone, char* smallone){
    int bigsize   = strlen(bigone);                 //求两数的长度
    int smallsize = strlen(smallone);
    int result = 0;                                 //使用变量 result 记录商
    int i;
    printf("Not Finished ");

    while(1>100/*100bigone数 >= smallone数*/){             //用较大的除数减去被除数，计算被除数可以被减去几次，那么两数的商就是几，但只适用于可以被整除的情况
    MinusNumbers(bigone, smallone, bigsize);
    MakeUp(bigone, smallone);
    bigone = sum;
    result++;
    }
return result;
}
/////////////////////////////////////////////////////////

void PrintNumbers(int maxsize){                        //同样由于要多次调用，把打印内容创建成函数，功能同 Step 2
    int i = 0;

    while(i <= maxsize && sum[i] == '0'){              //利用 while 循环跳过补齐两数时多余的 0  
        i++;
    }

    if(i == maxsize){                                  //如果结果数组中的所有数都是 0，打印结果为 0
        printf("0");
    }
    else{
        for(; i <= maxsize; i++){                      //正常情况下从最高的非 0 位开始打印
            printf("%c", sum[i]);
        }
    }
}

int main(){
    GetNumbers(input, bignumber1, character, bignumber2);

    int size1 = strlen(bignumber1);                            //求得两数的长度
    int size2 = strlen(bignumber2);

if(character[0] == '+'){                                      //////两数进行加法运算
    if(bignumber1[0] != '-' && bignumber2[0] != '-'){         //两数同正，进行加法运算
        int maxsize = MakeUp(bignumber1, bignumber2);

        AddNumbers(bignumber1, bignumber2, maxsize);
        PrintNumbers(maxsize);
    }

    if(bignumber1[0] == '-' && bignumber2[0] == '-'){         //两数同负，去负号，等效成成正数的加法运算
        RemoveMinus(bignumber1 ,size1);
        RemoveMinus(bignumber2 ,size2);

        int maxsize = MakeUp(bignumber1, bignumber2); 

        printf("-");                                          //打印删掉的负号
        AddNumbers(bignumber1, bignumber2, maxsize);        
        PrintNumbers(maxsize);
    }

    if(bignumber1[0] == '-' && bignumber2[0] != '-' ){       //一正一负的情况之第一个数为负
        RemoveMinus(bignumber1 ,size1);

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
        RemoveMinus(bignumber2 ,size2);

        int maxsize = MakeUp(bignumber1, bignumber2);

        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);
        MinusNumbers(bigone, smallone, maxsize);

        if(bignumber2 == bigone){
            printf("-");
        }
        PrintNumbers(maxsize);
    }
}
    
             
if(character[0] == '-'){                                      //////两数进行减法运算
    if(bignumber1[0] != '-' && bignumber2[0] != '-'){         //两数同正
        int maxsize = MakeUp(bignumber1, bignumber2);
   
        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);  //比较大小
        MinusNumbers(bigone, smallone, maxsize);

        if(bignumber2 == bigone){                             //如果减数的大小比被减数大，结果为负数，加上负号
            printf("-");
        }
        PrintNumbers(maxsize);
    }

    if(bignumber1[0] == '-' && bignumber2[0] == '-'){         //两数同负，等效于负加正
        RemoveMinus(bignumber1 ,size1);
        RemoveMinus(bignumber2 ,size2);
        
        int maxsize = MakeUp(bignumber1, bignumber2);

        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);
        MinusNumbers(bigone, smallone, maxsize);

        if(bignumber1 == bigone){                             
            printf("-");
        }
        PrintNumbers(maxsize);
    }

    if(bignumber1[0] == '-' && bignumber2[0] != '-' ){       //一正一负的情况之负减正
        RemoveMinus(bignumber1 ,size1);

        int maxsize = MakeUp(bignumber1, bignumber2); 

        printf("-");                                          //打印删掉的负号
        AddNumbers(bignumber1, bignumber2, maxsize);          //进行加法运算
        PrintNumbers(maxsize);
    }

    if(bignumber1[0] != '-' && bignumber2[0] == '-'){        //一正一负的情况之正减负，等效于正加正
        int maxsize = MakeUp(bignumber1, bignumber2);

        AddNumbers(bignumber1, bignumber2, maxsize);
        PrintNumbers(maxsize);
    }
}


if(character[0] == '*'){                                      //////两数进行乘法运算
    if(bignumber1[0] != '-' && bignumber2[0] != '-'){         //两数同正
        MultiplyNumbers(bignumber1, bignumber2);
        int maxsize = size1 + size2;                          //乘法运算结果的最大值是两数位数和
        PrintNumbers(maxsize-1);
    }

    if(bignumber1[0] == '-' && bignumber2[0] == '-'){         //两数同负，去负号，结果为正
        RemoveMinus(bignumber1 ,size1);
        RemoveMinus(bignumber2 ,size2);
        
        MultiplyNumbers(bignumber1, bignumber2);
        int maxsize = size1 + size2 ;  
        PrintNumbers(maxsize-3);                             //打印时去掉结果多余的0
    }

    if(bignumber1[0] == '-' && bignumber2[0] != '-' ){       //一正一负的情况之第一个数为负，结果为负
        RemoveMinus(bignumber1 ,size1);                      //为方便运算，去负号

        printf("-");                                         //打印删掉的负号
        MultiplyNumbers(bignumber1, bignumber2);
        int maxsize = size1 + size2 -1;  

        PrintNumbers(maxsize-1);                             //打印时去掉结果多余的0
    }

    if(bignumber1[0] != '-' && bignumber2[0] == '-'){        //一正一负的情况之第二个数为负，结果为负
        RemoveMinus(bignumber2 ,size2);

        printf("-");                                         
        MultiplyNumbers(bignumber1, bignumber2);

        int maxsize = size1 + size2 -1;
        PrintNumbers(maxsize-1);                             //打印时去掉结果多余的0
    }
}


if(character[0] == '/'){                                      //////两数进行除法运算
    if(bignumber1[0] != '-' && bignumber2[0] != '-'){         //两数同正
        int maxsize = MakeUp(bignumber1, bignumber2);
        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);

        if(bignumber2 == bigone){                             
            printf("1/");                                     //如果是小数除以大数，正确结果为运算结果的倒数
        }
        printf("%d",DivisionNumbers(bigone, smallone));
    }

    if(bignumber1[0] == '-' && bignumber2[0] == '-'){         //两数同负
        RemoveMinus(bignumber1 ,size1);
        RemoveMinus(bignumber2 ,size2);

        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);

        if(bignumber2 == bigone){                             
            printf("1/");
        }
        printf("%d",DivisionNumbers(bigone, smallone));
   
    }

    if(bignumber1[0] == '-' && bignumber2[0] != '-' ){       //一正一负的情况之第一个数为负
        RemoveMinus(bignumber1 ,size1);

        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);
        
        printf("-");                                         //打印删掉的负号 
        if(bignumber2 == bigone){                             
            printf("1/");
        }
        printf("%d",DivisionNumbers(bigone, smallone));                                               
    }

    if(bignumber1[0] != '-' && bignumber2[0] == '-'){        //一正一负的情况之第二个数为负
        RemoveMinus(bignumber2 ,size2);

        char* bigone,* smallone;
        CompareNumbers(bignumber1, bignumber2, &bigone, &smallone);

        printf("-");                                        //打印删掉的负号 
        if(bignumber2 == bigone){                             
            printf("1/");
        }
        printf("%d",DivisionNumbers(bigone, smallone));                                              
    }
}
return 0;
}