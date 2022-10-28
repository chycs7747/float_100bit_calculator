#include <iostream>
#include <string>
#include <cmath>
using namespace std;


class _int100b {
    private:
        uint64_t int64bF; //F:front (64~128)
        uint64_t int64bB; //B:back  (0~63)
        void string_to_num(string char100b);
    public:
        _int100b();
        _int100b(const char* char100b);
        uint64_t get_int64bF();
        uint64_t get_int64bB();
}; 

class Mantissa {
    private: // this will be private
        uint64_t mantissaF;
        uint64_t mantissaB;
    public:
        Mantissa();
        //Mantissa(uint64_t mantissaF, uint64_t mantissaB);
        uint64_t get_mantissaF();
        uint64_t get_mantissaB();
        void set_mantissa(uint64_t mantissaF, uint64_t mantissaB);
        void _init_mantissa();
        void operator<<(int shampt);
        void operator>>(int shampt);
        int operator>(const Mantissa& target);
        int operator<(const Mantissa& target);
        int operator==(const Mantissa& target);

};

class _float100b  {
    private:
        bool signBit;
        int exponent;
        Mantissa mantissa;
        //mantissa b가 int 100b를 상속했다
    public:
        _float100b();
        _float100b(const char* char100b);
        bool get_sign_bit();
        int get_exponent();
        Mantissa& get_mantissa();
        void print_float();
        void operator<<(int shampt);
        void operator>>(int shampt);
        int operator>(const _float100b& target);
        int operator<(const _float100b& target);
        int operator==(const _float100b& target);
        
};
/////////// main

int main(void) {
    _int100b result("7FFFFFF7eCFFFFFFFFFFFFFFF");
    Mantissa a;
    Mantissa b;
    /*
    a.mantissaF = 0x3;
    a.mantissaB = 1;
    b.mantissaF = 0x4;
    b.mantissaB = 0;
    */
    _float100b firstFloat("7FFFFFF7eCFFFFFFFFFFFFFFF");
    _float100b secondFloat("7FFFFFF7eCFFFFFFFFFFFFFFF");
    firstFloat.print_float();
    if(firstFloat > secondFloat) {
        cout << "success!" << endl;
    }
    if(a>b) {cout<< "a is bigger"<<endl;}


    printf("%09llx%016llx\n", result.get_int64bF(), result.get_int64bB());
}

//_int100b part
_int100b::_int100b() {}
_int100b::_int100b(const char* char100b) : int64bF(0), int64bB(0) {
    string_to_num(char100b);
}
void _int100b::string_to_num(string char100b) {
    int pivot = 9;
    uint64_t *tmpNum = &int64bF;
    for(int i=0; i<char100b.length(); i++) { //length will be 25(4bits * 25)
        if(i==pivot) {
            tmpNum = &int64bB;
        }
        if( char100b[i] >= 'A' && char100b[i] <= 'F' )  {              
            *tmpNum = *tmpNum * 16 + char100b[i] - 'A' + 10;
        }
        else if ( char100b[i] >= 'a' && char100b[i] <= 'f' ) {       
            *tmpNum = *tmpNum * 16 + char100b[i] - 'a' + 10;
        }
        else if ( char100b[i] >= '0' && char100b[i] <= '9' ) {       
            *tmpNum = *tmpNum * 16 + char100b[i] - '0';      
        }
    
    }
}
uint64_t _int100b::get_int64bF() {return int64bF;}
uint64_t _int100b::get_int64bB() {return int64bB;}

//Mantissa part
Mantissa::Mantissa() {mantissaF = 0x40; mantissaB = 0;}
uint64_t Mantissa::get_mantissaF(){return mantissaF;}
uint64_t Mantissa::get_mantissaB(){return mantissaB;}
void Mantissa::set_mantissa(uint64_t mantissaF, uint64_t mantissaB) {
    this->mantissaF += mantissaF;
    this->mantissaB = mantissaB;
}
void Mantissa::operator<<(int shampt) {
    for(int i=0; i<shampt; i++) {
        mantissaF = (mantissaB>>63) ? (mantissaF<<1)+1 : mantissaF<<1;
        mantissaB = mantissaB<<1 & ~(0x0000000000000000);
    }
}
void Mantissa::operator>>(int shampt) {
    for(int i=0; i<shampt; i++) {
        mantissaB = (mantissaF & 1) ? (mantissaB>>1)+0x8000000000000000: mantissaB>>1;
        mantissaF >>= 1;
    }
}
int Mantissa::operator>(const Mantissa& target) {
    if(mantissaF > target.mantissaF || ((mantissaF==target.mantissaF) && mantissaB > target.mantissaB)) {
        return 1;
    }
    else {
        return 0;
    }
}
int Mantissa::operator<(const Mantissa& target) {
    if(mantissaF < target.mantissaF || ((mantissaF==target.mantissaF) && mantissaB < target.mantissaB)) {
        return 1;
    }
    else {
        return 0;
    }
}
int Mantissa::operator==(const Mantissa& target) {
    if((mantissaF == target.mantissaF) && (mantissaB == target.mantissaB)) {
        return 1;
    }
    else {
        return 0;
    }
}


//_float100b part
_float100b::_float100b() {}
_float100b::_float100b(const char* char100b) {
    _int100b int100b(char100b);
    signBit = int100b.get_int64bF() & 0x800000000;
    exponent = (int100b.get_int64bF() & 0x7ffffffc0) >> 6;
    mantissa.set_mantissa(int100b.get_int64bF()&0x000000000000003f, int100b.get_int64bB()&0xffffffffffffffff);
}
bool _float100b::get_sign_bit(){return signBit;}
int _float100b::get_exponent(){return exponent;}
Mantissa& _float100b::get_mantissa() {return mantissa;}
void _float100b::print_float() {
    cout << hex;
    cout << "signBit: " << signBit << endl;
    cout << "exponent: " << exponent << endl;
    cout << "mantissaF: " << (mantissa.get_mantissaF() & 0x3f) << endl;
    cout << "mantissaB: " << mantissa.get_mantissaB() << endl;
    cout << "hiddenBit: " << ((mantissa.get_mantissaF() & 0x40)>>6) << endl;
}
void _float100b::operator<<(int shampt) {
    exponent+=shampt;
    mantissa<<shampt;
}
void _float100b::operator>>(int shampt) {
    exponent-=shampt;
    mantissa>>shampt;
}
int _float100b::operator>(const _float100b& target) {
    if (exponent > target.exponent) {
        return 1;
    }
    else if((exponent==target.exponent) && mantissa>target.mantissa) {
        return 1;
    }
    else {
        return 0;
    }
}
int _float100b::operator<(const _float100b& target) {
    if (exponent < target.exponent) {
        return 1;
    }
    else if((exponent==target.exponent) && mantissa<target.mantissa) {
        return 1;
    }
    else {
        return 0;
    }
}
int _float100b::operator==(const _float100b& target) {
    if((exponent == target.exponent) && (mantissa == target.mantissa)) {
        return 1;
    }
    else {
        return 0;
    }
}