#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class _int100b {
    private:
        uint64_t int64bF; //F:front (64~128)
        uint64_t int64bB; //B:back  (0~63)
        void string_to_num(string char100b);
        void int_to_string();
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
        void set_mantissaF(uint64_t num);
        void set_mantissaB(uint64_t num);
        void set_mantissa(uint64_t mantissaF, uint64_t mantissaB);
        void _init_mantissa();
        bool isOverflowed(uint64_t num1, uint64_t num2);
        int operator>(const Mantissa& target);
        int operator<(const Mantissa& target);
        int operator==(const Mantissa& target);
        void operator=(const Mantissa& target);
        Mantissa operator<<(int shampt);
        Mantissa operator>>(int shampt);
        Mantissa operator~();
        Mantissa operator+(const Mantissa& target);

};

class _float100b  {
    private:
        bool signBit;
        int exponent;
        Mantissa mantissa;
    public:
        _float100b();
        _float100b(const char* char100b);
        _float100b(bool signBit, int exponent, Mantissa manitssa);
        bool get_sign_bit();
        int get_exponent();
        Mantissa& get_mantissa();
        void set_signBit(bool signBit);
        void set_exponent(int exponent);
        _float100b get_abs(const _float100b num);
        void print_float();
        void print_normalize();
        int operator>(const _float100b& target);
        int operator<(const _float100b& target);
        int operator==(const _float100b& target);
        void operator=(const _float100b& target);
        _float100b operator<<(int shampt);
        _float100b operator>>(int shampt);
        _float100b operator+(const _float100b& target);
        
};
/////// main

int main(void) {
    static char float100b_1[26], float100b_2[26];
    cout << "input denormalized expression" << endl;
    cout << "input first float point: ";
    cin >> float100b_1;
    cout << "input second float point: ";
    cin >> float100b_2;
    
    //_float100b firstFloat("3ffffff8a6fa00000fa6fa00004");
    //_float100b secondFloat("3fffffff0f0f0000000000000");
    _float100b firstFloat(float100b_1);
    _float100b secondFloat(float100b_2);
    _float100b third;
    firstFloat.print_normalize();
    secondFloat.print_normalize();
    third = (firstFloat + secondFloat);
    cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ";
    cout << "answer " << endl;
    third.print_float();
    cout << "normalized answer" << endl;
    third.print_normalize();

    //printf("%09llx%016llx\n", result.get_int64bF(), result.get_int64bB());
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
void Mantissa::set_mantissaF(uint64_t num) {
    mantissaF = num;
}
void Mantissa::set_mantissaB(uint64_t num) {
    mantissaB = num;
}
void Mantissa::set_mantissa(uint64_t mantissaF, uint64_t mantissaB) {
    this->mantissaF = (mantissaF | 0x40);
    this->mantissaB = mantissaB;
}
bool Mantissa::isOverflowed(uint64_t num1, uint64_t num2) {
    if((num1+num2<num1) && (num1+num2)<num2) {
        return 1;
    }
    else {
        return 0;
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
void Mantissa::operator=(const Mantissa& target) {
    this->set_mantissa(target.mantissaF,target.mantissaB);
}
Mantissa Mantissa::operator<<(int shampt) {
    Mantissa tmpMantissa = *this;
    for(int i=0; i<shampt; i++) {
        tmpMantissa.mantissaF = (mantissaB>>63) ? (mantissaF<<1)+1 : mantissaF<<1;
        tmpMantissa.mantissaB = mantissaB<<1 & ~(0x0000000000000000);
    }
    return tmpMantissa;
}
Mantissa Mantissa::operator>>(int shampt) {
    Mantissa tmpMantissa = *this;
    for(int i=0; i<shampt; i++) {
        tmpMantissa.mantissaB = (mantissaF & 1) ? (mantissaB>>1)+0x8000000000000000: mantissaB>>1;
        tmpMantissa.mantissaF >>= 1;
    }
    return tmpMantissa;
}
Mantissa Mantissa::operator~() {
    Mantissa tmpMantissa = *this;
    tmpMantissa.mantissaF = ~tmpMantissa.mantissaF;
    tmpMantissa.mantissaB = (~tmpMantissa.mantissaB) + 1;
    return tmpMantissa;
}

Mantissa Mantissa::operator+(const Mantissa& target) {
    Mantissa tmpMantissa = *this;
    tmpMantissa.mantissaF += target.mantissaF + isOverflowed(tmpMantissa.mantissaB, target.mantissaB);
    tmpMantissa.mantissaB += target.mantissaB;
    return tmpMantissa;
}

//_float100b part
_float100b::_float100b() {

}
_float100b::_float100b(const char* char100b) {
    _int100b int100b(char100b);
    //printf("%09llx%016llx\n", int100b.get_int64bF(), int100b.get_int64bB());
    signBit = int100b.get_int64bF() & 0x800000000;
    exponent = (int100b.get_int64bF() & 0x7ffffffc0) >> 6;
    mantissa.set_mantissa(int100b.get_int64bF()&0x000000000000003f, int100b.get_int64bB()&0xffffffffffffffff);
}
_float100b::_float100b(bool signBit, int exponent, Mantissa mantissa) {
    this->signBit = signBit;
    this->exponent = exponent;
    this->mantissa = mantissa;
}
bool _float100b::get_sign_bit(){return signBit;}
int _float100b::get_exponent(){return exponent;}
Mantissa& _float100b::get_mantissa() {return mantissa;}
void _float100b::set_signBit(bool signBit) {this->signBit = signBit;}
void _float100b::set_exponent(int exponent) {this->exponent = exponent;}
_float100b _float100b::get_abs(const _float100b num) {
    _float100b tmpNum = num;
    tmpNum.set_signBit(0);
    return tmpNum;
}
void _float100b::print_float() {
    cout << hex;
    cout << "signBit: " << signBit << endl;
    cout << "exponent: " << dec << exponent << endl;
    cout << "mantissaF: " << dec << (mantissa.get_mantissaF() & 0x3f) << endl;
    cout << "mantissaB: " << dec << mantissa.get_mantissaB() << endl;
    cout << "hiddenBit: " << dec << ((mantissa.get_mantissaF() & 0x40)>>6) << endl;
}

void _float100b::print_normalize() {
    int count=0;
    _float100b tmpNum = *this;
    if((tmpNum.mantissa.get_mantissaF()&0x40)!=0) {
        tmpNum.mantissa = tmpNum.mantissa << 1;
        count++;
    }
    cout << ((tmpNum.mantissa.get_mantissaF()&0x40)>>6) << ".";
    for(int i=0; i<70; i++) {
        cout << (tmpNum.mantissa.get_mantissaF() & 0x20);
        tmpNum.mantissa = (tmpNum.mantissa << 1);
    }
    cout << " * 2^(" << exponent - 0x1fffffff - count << ")" << endl;
}

int _float100b::operator>(const _float100b& target) {
    if(signBit > target.signBit) {
        return 1;
    }
    else if(exponent > target.exponent) {
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
    if(signBit < target.signBit) {
        return 1;
    }
    else if(exponent < target.exponent) {
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
    if((signBit == target.signBit) && (exponent == target.exponent) && (mantissa == target.mantissa)) {
        return 1;
    }
    else {
        return 0;
    }
}
void _float100b::operator=(const _float100b& target) {
    this->set_signBit(target.signBit);
    this->set_exponent(target.exponent);
    this->mantissa = target.mantissa;
}
_float100b _float100b::operator<<(int shampt) {
    _float100b tmpFloat100b = *this;
    tmpFloat100b.exponent+=shampt;
    tmpFloat100b.mantissa = mantissa<<shampt;
    return tmpFloat100b;
}
_float100b _float100b::operator>>(int shampt) {
    _float100b tmpFloat100b = *this;
    tmpFloat100b.exponent-=shampt;
    tmpFloat100b.mantissa>>shampt;
    return tmpFloat100b;
}
_float100b _float100b::operator+(const _float100b& target) {
    _float100b tmpTarget = target;
    if((signBit == 0) && (target.signBit==0)) {
        if(*this > target) {
            tmpTarget.mantissa = tmpTarget.mantissa>>(exponent-target.exponent);
            tmpTarget.mantissa = mantissa + tmpTarget.mantissa;
            if((tmpTarget.mantissa.get_mantissaF() & 0x40) == 1) {
                exponent++;
                tmpTarget.mantissa = tmpTarget.mantissa>>1;
            }
            return _float100b(signBit, exponent, tmpTarget.mantissa); // target.mantissa>>(exponent-target.exponent) impossible!
        }
        else if(*this < target) {
            mantissa = mantissa>>(tmpTarget.exponent-exponent);
            tmpTarget.mantissa = mantissa + tmpTarget.mantissa;
            if((tmpTarget.mantissa.get_mantissaF() & 0x40) == 1) {
                tmpTarget.exponent++;
                mantissa = mantissa>>1;
            }
            return _float100b(signBit, tmpTarget.exponent, mantissa>>(tmpTarget.exponent-exponent));
        }
        else {
            tmpTarget.mantissa = mantissa + tmpTarget.mantissa;
            return _float100b(signBit, exponent+1, tmpTarget.mantissa>>1);
        }
    }
    else if((signBit == 1) && (target.signBit == 1)) {
        if(*this > target) {
            tmpTarget.mantissa = tmpTarget.mantissa>>(exponent-target.exponent);
            tmpTarget.mantissa = mantissa + tmpTarget.mantissa;
            if((tmpTarget.mantissa.get_mantissaF() & 0x40) == 1) {
                exponent++;
                tmpTarget.mantissa = tmpTarget.mantissa>>1;
            }
            return _float100b(signBit, exponent, tmpTarget.mantissa); // target.mantissa>>(exponent-target.exponent) impossible!
        }
        else if(*this < target) {
            mantissa = mantissa>>(tmpTarget.exponent-exponent);
            tmpTarget.mantissa = mantissa + tmpTarget.mantissa;
            if((tmpTarget.mantissa.get_mantissaF() & 0x40) == 1) {
                tmpTarget.exponent++;
                mantissa = mantissa>>1;
            }
            return _float100b(signBit, tmpTarget.exponent, mantissa>>(tmpTarget.exponent-exponent));
        }
        else {
            tmpTarget.mantissa = mantissa + tmpTarget.mantissa;
            return _float100b(signBit, exponent+1, tmpTarget.mantissa>>1);
        }
    }
    else if(signBit != tmpTarget.signBit) {
        if(get_abs(*this) > get_abs(tmpTarget)) {
            tmpTarget.mantissa = (tmpTarget.mantissa>>(exponent-tmpTarget.exponent));
            Mantissa tmpMantissa = ~tmpTarget.mantissa;
            tmpTarget.mantissa.set_mantissa(mantissa.get_mantissaF() + tmpMantissa.get_mantissaF() + tmpMantissa.isOverflowed(tmpMantissa.get_mantissaB(),1),mantissa.get_mantissaB() + tmpMantissa.get_mantissaB());
            return _float100b(tmpTarget.get_sign_bit(), tmpTarget.get_exponent(), tmpTarget.mantissa);
        }
        else if(get_abs(*this) < get_abs(tmpTarget)) {
            mantissa = mantissa>>(tmpTarget.exponent-exponent);
            Mantissa tmpMantissa = ~mantissa;
            tmpMantissa.set_mantissaB(tmpMantissa.get_mantissaB()+1);
            tmpTarget.mantissa.set_mantissa(mantissa.get_mantissaF() + tmpMantissa.get_mantissaF() + tmpMantissa.isOverflowed(tmpMantissa.get_mantissaB(),1),mantissa.get_mantissaB() + tmpMantissa.get_mantissaB());
            return _float100b(tmpTarget.get_sign_bit(), tmpTarget.get_exponent(), tmpTarget.mantissa);
        }
        else {
            Mantissa tmpNum;
            tmpNum.set_mantissaF(0);
            return _float100b(0,0,tmpNum);
        }
    }
    Mantissa man;
    return _float100b(0,0,man);
}



