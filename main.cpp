
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);
bool checkValidInput(const char currentChar, const char nextChar, const int pos);
bool inASCIIRange(const char currentChar);
int getASCIIPos(const char currentChar);

void testCharacteristicAndMantissa();
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(const char number[]);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    testCharacteristicAndMantissa();

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //If the c-string is empty, return false
    if(numString[0] == '\0')
    {
        return false;
    }

    //Counter for the position of the current character in the c-string
    int i = 0;
    //Initialize number to 0
    c = 0;
    //Bool for if a number is negative
    bool isNegative = false;
    //Return bool for valid input
    bool ret = true;

    //Keep checking characters until we reach a decimal point or end of c-string if the number is just a integer 
    while(numString[i] != '.' && numString[i] != '\0') 
    {
        //Make sure the input for the current character is valid, use the current character, next character, and position.
        if(checkValidInput(numString[i], numString[i+1], i))
        {
            //If there is a negative sign (At pos 0)
            if(numString[i] == '-' && i == 0) 
            {
                
                isNegative = true;
            }
            //If the character ASCII range falls in the range of 0-9
            else if(inASCIIRange(numString[i])) 
            {
                //Multiply the previous number by 10 to add the next digit in the number
                c *= 10;
                //Subtract the current character from '0' to get their integer type.
                c += getASCIIPos(numString[i]);
            }
            
            i++;
        }

        //Otherwise return an error on input message
        else 
        {
            ret = false;
            break;
        }
    }

    //If there was a negative sign and the input was valid, change the sign of c
    if(isNegative && ret) 
    {
        c = -c;
    }

    return ret;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    int i = 0;

    //Set numerator to 0 and denominator to 1 assuming there is no mantissa (base case)
    numerator = 0;
    denominator = 1;

    //Bool to start parsing the mantissa once we reach a '.'
    bool startParsing = false;
    //Return bool for valid input
    bool ret = true;

    while(numString[i] != '\0') {
        //Make sure the input for the current character is valid
        if(checkValidInput(numString[i], numString[i+1], i))
        {
            //If we've already reached a '.'
            if(startParsing)
            {
                //If we reach another decimal then something is wrong
                if(numString[i] == '.')
                {
                    ret = false;
                    break;
                }
                //For every number after the decimal
                if(inASCIIRange(numString[i])) 
                {
                    //Same logic as the characteristic() function 
                    numerator *= 10;
                    numerator += getASCIIPos(numString[i]);

                    //Increase denominator by 10
                    denominator*= 10;
                    
                }
            }

            //Else check if the current character is a '.'
            else if(numString[i] == '.' && !startParsing) 
            {
                //Ready to parse
                startParsing = true;
            }

            i++;
        }

        //Otherwise return an error on input message
        else 
        {
            ret = false;
            break;
        }
    }

    //If we have a bunch of trailing zeros after the decimal for some reason, make sure the denominator is 1
    if(numerator == 0 && ret) 
    {
        denominator = 1;
    }

    return ret;
}
//--
bool checkValidInput(const char currentChar, const char nextChar, const int pos)
{
    //Return value assuming the input is invalid
    bool ret = false;

    //If a char is a '0'-'9'
    if(inASCIIRange(currentChar))
    {
        ret = true;
    }
    //If the first char is a sign +/-, the next character must be a number or decimal
    else if((currentChar == '+' || currentChar == '-') && (inASCIIRange(nextChar) || nextChar == '.') && pos == 0)
    {
        ret = true;
    }
    //If a char is a space or decimal. If a decimal there must be a number after it.
    else if((currentChar == ' ') || ((currentChar == '.')) && (inASCIIRange(nextChar)))
    {
        ret = true;
    }


    return ret;
}    
//--
//Helper Function to Check if the current character is in the ASCII range of '0'-'9'
bool inASCIIRange(char currentChar) {
    if(currentChar >= '0' && currentChar <= '9')
    {
        return true;
    }
    
    else 
    {
        return false;
    }
}
//--
//Helper Function to get the position of the current character in the ASCII table relative to '0'
int getASCIIPos(const char currentChar)
{
    return currentChar - '0';   
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    result[0] = '4';
    result[1] = '.';
    result[2] = '1';
    result[3] = '6';
    result[4] = '6';
    result[5] = '6';
    result[6] = '6';
    result[7] = '6';
    result[8] = '6';
    result[9] = '\0';

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
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
void testCharacteristicAndMantissa()
{
    //number with a non-zero characteristic a decimal point and a non-zero mantissa
    shouldConvert("123.456", 123, 456, 1000);
    shouldConvert("    123.456", 123, 456, 1000);
    shouldConvert("123.456    ", 123, 456, 1000);
    shouldConvert("    123.456    ", 123, 456, 1000);
    
    //unary plus/minus
    shouldConvert("+123.456", 123, 456, 1000);
    shouldConvert("   +123.456", 123, 456, 1000);
    shouldConvert("+123.456   ", 123, 456, 1000);
    shouldConvert("   +123.456   ", 123, 456, 1000);
    shouldConvert("-123.456", -123, 456, 1000);
    shouldConvert("   -123.456", -123, 456, 1000);
    shouldConvert("-123.456   ", -123, 456, 1000);
    shouldConvert("    -123.456   ", -123, 456, 1000);

    //number with a zero characteristic and a non-zero mantissa
    shouldConvert("0.456", 0, 456, 1000);
    shouldConvert("   0.456", 0, 456, 1000);
    shouldConvert("0.456   ", 0, 456, 1000);
    shouldConvert("   0.456   ", 0, 456, 1000);
    
    //number with no characteristic digits and a non-zero mantissa
    shouldConvert(".456", 0, 456, 1000);
    shouldConvert("    .456", 0, 456, 1000);
    shouldConvert(".456   ", 0, 456, 1000);
    shouldConvert("   .456   ", 0, 456, 1000);
    
    //number with a non-zero characteristic and no mantissa
    shouldConvert("0", 0, 0, 10);
    shouldConvert("-0", -0, 0, 10);
    shouldConvert("123456", 123456, 0, 10);
    shouldConvert("   123456", 123456, 0, 10);
    shouldConvert("123456   ", 123456, 0, 10);
    shouldConvert("   123456   ", 123456, 0, 10);
    
    //unary plus/minus
    shouldConvert("-123456", -123456, 0, 10);
    shouldConvert("   -123456", -123456, 0, 10);
    shouldConvert("-123456   ", -123456, 0, 10);
    shouldConvert("   -123456   ", -123456, 0, 10);
    shouldConvert("+123456", 123456, 0, 10);
    shouldConvert("   +123456", 123456, 0, 10);
    shouldConvert("+123456   ", 123456, 0, 10);
    shouldConvert("   +123456   ", 123456, 0, 10);

    //number with a non-zero characteristic and a zero mantissa
    shouldConvert("123456.0", 123456, 0, 10);
    shouldConvert("   123456.0", 123456, 0, 10);
    shouldConvert("123456.0   ", 123456, 0, 10);
    shouldConvert("   123456.0   ", 123456, 0, 10);
    
    //unary plus/minus
    shouldConvert("-123456.0", -123456, 0, 10);
    shouldConvert("   -123456.0", -123456, 0, 10);
    shouldConvert("-123456.0   ", -123456, 0, 10);
    shouldConvert("   -123456.0   ", -123456, 0, 10);
    shouldConvert("+123456.0", 123456, 0, 10);
    shouldConvert("   +123456.0", 123456, 0, 10);
    shouldConvert("+123456.0   ", 123456, 0, 10);
    shouldConvert("   +123456.0   ", 123456, 0, 10);

    //check leading and trailing zeros
    shouldConvert("000123.456", 123, 456, 1000);
    shouldConvert("123.45600000", 123, 456, 1000);
    shouldConvert("00000123.45600000", 123, 456, 1000);
    
    //unary plus/minus
    shouldConvert("-000123.456", -123, 456, 1000);
    shouldConvert("-123.45600000", -123, 456, 1000);
    shouldConvert("-00000123.45600000", -123, 456, 1000);
    shouldConvert("+000123.456", 123, 456, 1000);
    shouldConvert("+123.45600000", 123, 456, 1000);
    shouldConvert("+00000123.45600000", 123, 456, 1000);

    //significant zeros in mantissa
    shouldConvert("123.00000456", 123, 456, 100000000);
    shouldConvert("-123.00000456", -123, 456, 100000000);
    shouldConvert("+123.00000456", 123, 456, 100000000);

    //these should fail
    shouldNotConvert("");
    shouldNotConvert("   ");
    shouldNotConvert(".");
    shouldNotConvert("+");
    shouldNotConvert("-");
    shouldNotConvert("..");
    shouldNotConvert("+.");
    shouldNotConvert("-.");
    shouldNotConvert("c");
    shouldNotConvert("cat");
    shouldNotConvert("-cat");
    shouldNotConvert("123.");
    shouldNotConvert("123.   ");
    shouldNotConvert("123.456+");
    shouldNotConvert("123.456 +");
    shouldNotConvert("123.456 cat");
    shouldNotConvert("123.cat");
    shouldNotConvert("cat.456");
    shouldNotConvert("+-123.456");
    shouldNotConvert("1.23.456");
    shouldNotConvert(".123.456");
    shouldNotConvert("--123.456");
    shouldNotConvert("123   456");
    shouldNotConvert("123  .  456");
    shouldNotConvert("  123  .  456");
    shouldNotConvert("127.0.0.1");
}
//--
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator)
{
    int c, n, d;

    //if the conversion from C string to integers can take place
    if (characteristic(number, c) && mantissa(number, n, d))
    {
        if (c == expectedCharacteristic && n == expectedNumerator && d == expectedDenominator)
        {
            //test passes, do not print anything on a successful test
        }
        else
        {
            cout << "Test failed: '" << number << "' "
                << "was parsed but did not produce the expected results" << endl;

            if (expectedCharacteristic != c)
            {
                cout << "expected characteristic: " << expectedCharacteristic << " "
                    << "actual characteristic: " << c << endl;
            }

            if (expectedNumerator != n)
            {
                cout << "expected numerator: " << expectedNumerator << " "
                    << "actual numerator: " << n << endl;

            }

            if (expectedDenominator != d)
            {
                cout << "expected denominator: " << expectedDenominator << " "
                    << "actual denominator: " << d << endl;
            }
        }
    }
    else
    {
        cout << "Test failed: '" << number << "' "
            << "was NOT parsed when it should have been." << endl;
        if (expectedCharacteristic != c)
        {
            cout << "expected characteristic: " << expectedCharacteristic << " "
                << "actual characteristic: " << c << endl;
        }

        if (expectedNumerator != n)
        {
            cout << "expected numerator: " << expectedNumerator << " "
                << "actual numerator: " << n << endl;

        }

        if (expectedDenominator != d)
        {
            cout << "expected denominator: " << expectedDenominator << " "
                << "actual denominator: " << d << endl;
        }
    }
}
//--
void shouldNotConvert(const char number[])
{
    int c, n, d;

    //if the conversion from C string to integers can take place
    if (characteristic(number, c) && mantissa(number, n, d))
    {
        cout << "Test failed: '" << number << "' "
            << "was parsed when it should NOT have been." << endl;
    }
}
//--
