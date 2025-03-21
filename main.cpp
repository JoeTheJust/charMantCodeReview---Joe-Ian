
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

//Joe's implementation of helper functions
int HelperMantissa(int denominator1, int numerator1, int denominator2, int numerator2, char sign);
int LCM(int a, int b);
int pow(int base, int exp);
int numSize(int num);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3; 

    

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    c1 = 24;
    n1 = 3;
    d1 = 4;


    c2 = 4;
    n2 = 4;
    d2 = 5;

    if(subtract(c1, n1, d1, c2, n2, d2, answer, 10)) {
        cout<<"Answer: "<<answer<<endl;
    }
    else {
        cout << "Error on subtract" << endl;
    }

    // if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    // {
    //     //display string with answer
    //     cout<<"Answer: "<<answer<<endl;
    // }
    // else
    // {
    //     //display error message
    //     cout<<"Error on divide"<<endl;
    // }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    // result[0] = '4';
    // result[1] = '.';
    // result[2] = '1';
    // result[3] = '6';
    // result[4] = '6';
    // result[5] = '6';
    // result[6] = '6';
    // result[7] = '6';
    // result[8] = '6';
    // result[9] = '\0';

    int finDenominator = LCM(d1, d2);

    int finNumerator = HelperMantissa(d1, n1, d2, n2, '+') + ((c1 + c2) * finDenominator);


    int finResult = finNumerator / finDenominator;
    int resultSize = numSize(finResult);
    for(int i = resultSize; i > 0; i--) {
        result[resultSize - i] = '0' + ((finResult / pow(10, i - 1) % 10));
    }


    if(finNumerator % finDenominator == 0) {
        result[resultSize] = '\0';
    }
    else {
        result[resultSize] = '.';

        int mantissaStart = resultSize + 1;

        resultSize = len - (resultSize + 2);
        finResult = (finNumerator * pow(10, resultSize)) / finDenominator;
        finResult %= pow(10, resultSize);
        cout << finResult << endl;
        for(int i = 0; i < resultSize; i++) {
            result[mantissaStart + i] = '0' + (finResult / pow(10, (resultSize - 1) - i) % 10);
        }

        result[mantissaStart + resultSize] = '\0';
    }


    return true;
}

int HelperMantissa(int denominator1, int numerator1, int denominator2, int numerator2, char sign) {
    int newDenomenator = LCM(denominator1, denominator2);
    int mult1 = newDenomenator / denominator1;
    int mult2 = newDenomenator / denominator2;

    numerator1 *= mult1;
    numerator2 *= mult2;

    if(sign == '+')
        return numerator2 + numerator1;
    else if(sign == '-')
        return numerator2 - numerator1;

}

int LCM(int a, int b) {
    int greater;
    int smaller;

    if(a >= b) {
        greater = a;
        smaller = b;
    }
    else {
        greater = b;
        smaller = a;
    }

    int add = greater;
    
    while(greater % smaller != 0) {
        greater += add;
    }

    return greater;
}

int pow(int base, int exp) {
    int num = 1;
    for(int i = 0; i < exp; i++) {
        num *= base;
    }

    return num;
}

int numSize(int num) {
    int retVal = 0;
    while(num > 0) {
        num /= 10;
        retVal++;
    }

    return retVal;
}

//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers


    int finDenominator = LCM(d1, d2);

    int finNumerator = HelperMantissa(d1, n1, d2, n2, '-') + ((c1 - c2) * finDenominator);


    int finResult = finNumerator / finDenominator;
    int resultSize = numSize(finResult);
    cout << finResult << endl;
    for(int i = resultSize; i > 0; i--) {
        result[resultSize - i] = '0' + ((finResult / pow(10, i - 1) % 10));
    }


    if(finNumerator % finDenominator == 0) {
        result[resultSize] = '\0';
    }
    else {
        result[resultSize] = '.';

        int mantissaStart = resultSize + 1;

        resultSize = len - (resultSize + 2);
        finResult = (finNumerator * pow(10, resultSize)) / finDenominator;
        finResult %= pow(10, resultSize);
        cout << finResult << endl;
        for(int i = 0; i < resultSize; i++) {
            result[mantissaStart + i] = '0' + (finResult / pow(10, (resultSize - 1) - i) % 10);
        }

        result[mantissaStart + resultSize] = '\0';
    }

    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
    return true;
}
