#include <iostream>

union {
    float a;
    int b;
}fp;

int main(void) {
    double num1 = 1.0;
    //float num2 = 0.0100000000000000000000010
    fp.a = 0.25000008940696716;// + 0.0100000000000000000000010;
    
    std::cout << std::hex << fp.b <<std::endl; 

    unsigned char ap = 0 - 1;
    std::cout << std::dec << (int)ap << std::endl;

    unsigned char sh = 0x80;
    sh = (char)sh >> 1;
    std::cout << std::hex << (int)sh << std::endl;
    
}