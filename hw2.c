#include <stdio.h>
#include <stdint.h>

typedef struct _bit_100
{
    unsigned long long _1st64b;
    unsigned long long _2nd64b;
}bit_100;

void _init(bit_100* bit_100);
char numOfElement(char* num);
char charToNum(char num);
unsigned long long hex_pow(unsigned long long num, char index);
void mk100bits(char* str_num, bit_100 *tmp100);
unsigned long long isOverflow(unsigned long long num1, unsigned long long num2);
void sum100b(bit_100* bit_100_1,bit_100* bit_100_2, bit_100* result);

int main(void) {
    bit_100 bit_100_1, bit_100_2, result;
    char num1[26], num2[26];
    _init(&bit_100_1);
    _init(&bit_100_2);
    _init(&result);
    printf("input num1 :");
    scanf("%s",num1);
    printf("input num2 :");
    scanf("%s",num2);
    
    mk100bits(num1, &bit_100_1);
    mk100bits(num2, &bit_100_2);
    sum100b(&bit_100_1, &bit_100_2, &result);
    printf("\n %09llx%016llx\n", bit_100_1._2nd64b, bit_100_1._1st64b);
    printf("+%09llx%016llx\n", bit_100_2._2nd64b, bit_100_2._1st64b);
    printf("--------------------------\n");
    printf(" %09llx%016llx\n", result._2nd64b, result._1st64b);

    return 0;
}

void _init(bit_100* bit_100) {
    bit_100->_1st64b=0;
    bit_100->_2nd64b=0;
}

char numOfElement(char* num) {
    int count=0;
    while(*(num+count) != '\0') {
        count++;
    }
    return count;
}

char charToNum(char num) {
    if('a'<=num && num<='z') {
        return num-'a'+10;
    }
    else if('A'<=num && num<='Z') {
        return num-'A'+10;
    }
    else {
        return num-'0';
    }
}

unsigned long long hex_pow(unsigned long long num, char count) {
    for(int i=0; i<count; i++) {
        num<<=4;
    }
    return num;
}

void mk100bits(char* str_num, bit_100 *tmp100) {
    int size=numOfElement(str_num);
    
    for(int i=0; i<size; i++) {
        if(i<16) { // 16 is to check whether a number exceeding 64 bits has been entered.
            tmp100->_1st64b += hex_pow(charToNum(str_num[(size-1)-i]),i);
        }
        else {
            tmp100->_2nd64b += hex_pow(charToNum(str_num[(size-1)-i]),i-16);
        }
    }
}

unsigned long long isOverflow(unsigned long long num1, unsigned long long num2) {
    if((num1+num2 < num1) && (num1+num2 < num2)) {
        return 1;
    }
    return 0;
}

void sum100b(bit_100* bit_100_1,bit_100* bit_100_2, bit_100* result) {
    result->_1st64b = bit_100_1->_1st64b + bit_100_2->_1st64b;
    result->_2nd64b = bit_100_1->_2nd64b + bit_100_2->_2nd64b + isOverflow(bit_100_1->_1st64b, bit_100_2->_1st64b);
    result->_2nd64b = result->_2nd64b & 0x0000000fffffffff; // If you erase this, this code may calculate up to 128 bits.
}