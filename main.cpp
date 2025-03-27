
#include <iostream>
using namespace std;

const int SHORT_ARRAY_LENGTH = 5;
const int MEDIUM_ARRAY_LENGTH = 10;
const int LARGE_ARRAY_LENGTH = 20;

//Ian's main functions
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);
//Ian's helper functions
bool checkValidInput(const char currentChar, const char nextChar, const int pos);
bool inASCIIRange(const char currentChar);
int getASCIIPos(const char currentChar);
//Joe's main functions
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
//Joe's helper functions
int AddSubtractHelper(int characteristic1, int denominator1, int numerator1, int characteristic2, int denominator2, int numerator2, char sign);
int MultDivHelper(int characteristic, int numerator, int denominator);
int LCM(int a, int b);
int pow(int base, int exp);
int numSize(int num);
void resetResult(char result[], int len);
bool constructResult(int numerator, int denominator, char result[], int len);
int abs(int num);
//Test functions
void testCharacteristicAndMantissa();
void shouldConvert(const char number[], int expectedCharacteristic, int expectedNumerator, int expectedDenominator);
void shouldNotConvert(const char number[]);
void testMath();
void testAdd();
void testSubtract();
void testMultiply();
void testDivide();


int main()
{
    //Strong test functions which admittedly don't all work
    testCharacteristicAndMantissa();
    testMath();

    cout<<endl;

    //Initialize variables to test clean, nice inputs
    const char number[] = "15";
    const char secondNumber[] = "5.5";
    int c, n, d;
    int c1, n1, d1;

    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }

    if(characteristic(secondNumber, c1) && mantissa(secondNumber, n1, d1))
    {
        //do some math with c1, n1, and d1
        cout<<"c1: "<<c1<<endl;
        cout<<"n1: "<<n1<<endl;
        cout<<"d1: "<<d1<<endl;
    }

    cout<<endl;

    //room for 9 characters plus the null terminating character
    char answer[10];

    if(add(c, n, d, c1, n1, d1, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"+ | Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(subtract(c, n, d, c1, n1, d1, answer, 10)) {
        //display string with answer
        cout<<"- | Answer: "<<answer<<endl;
    }
    else {
        //display error message
        cout << "Error on subtract" << endl;
    }

    if(multiply(c, n, d, c1, n1, d1, answer, 10)) {
        //display string with answer
        cout<<"* | Answer: "<<answer<<endl;
    }
    else {
        //display error message
        cout << "Error on multiply" << endl;
    }

    if(divide(c, n, d, c1, n1, d1, answer, 10))
    {
        //display string with answer
        cout<<"/ | Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    cout<<endl;

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

    //We first check to see if we get a divide by zero error, and return false if we do
    if(d1 == 0 || d2 == 0) 
        return false;
    
    

    //Clears result from any previous operation function use
    resetResult(result, len);

    //We get the numerator and denominator (using characteristics, numerators, and demoninators) to avoid float/double math

    int finalDenominator = LCM(d1, d2);
    int finalNumerator;

    if(n1 == 0 && n2 == 0) {
        finalNumerator = c1 + c2;
        finalDenominator = 1;
    }
    else {
        finalNumerator = AddSubtractHelper(c1, d1, n1, c2, d2, n2, '+');
    }

    //Finally, we do the division, and put the result into the character array, returning false on errors and true on success

    if(!constructResult(finalNumerator, finalDenominator, result, len)) {
        return false;
    }

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{

    //We first check to see if we get a divide by zero error, and return false if we do
    if(d1 == 0 || d2 == 0) 
        return false;

    //Clears result from any previous operation function use
    resetResult(result, len);

    //We get the numerator and denominator (using characteristics, numerators, and demoninators) to avoid float/double math

    int finalDenominator = LCM(d1, d2);
    int finalNumerator;

    if(n1 == 0 && n2 == 0) {
        finalNumerator = c1 - c2;
        finalDenominator = 1;
    }
    else {
        finalNumerator = AddSubtractHelper(c1, d1, n1, c2, d2, n2, '-');
    }


    //Finally, we do the division, and put the result into the character array, returning false on errors and true on success

    if(!constructResult(finalNumerator, finalDenominator, result, len)) {
        return false;
    }

    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{

    //We first check to see if we get a divide by zero error, and return false if we do
    if(d1 == 0 || d2 == 0) 
        return false;

    //Clears result from any previous operation function use
    resetResult(result, len);

    
    //We get the numerator and denominator (using characteristics, numerators, and demoninators) to avoid float/double math

    int firstNumerator = MultDivHelper(c1, n1, d1);
    int secondNumerator = MultDivHelper(c2, n2, d2);

    int finalDenominator = d1 * d2;
    int finalNumerator = firstNumerator * secondNumerator;

    //Finally, we do the division, and put the result into the character array, returning false on errors and true on success

    if(!constructResult(finalNumerator, finalDenominator, result, len)) {
        return false;
    }

    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{

    //We first check to see if we get a divide by zero error, and return false if we do
    //Also checks for c2 here since this is the divide operation
    if(d1 == 0 || d2 == 0 || c2 == 0) 
        return false;

    //Clears result from any previous operation function use
    resetResult(result, len);

    //We get the numerator and denominator (using characteristics, numerators, and demoninators) to avoid float/double math

    int firstNumerator = MultDivHelper(c1, n1, d1);
    int secondNumerator = MultDivHelper(c2, n2, d2);

    int finalDenominator = d1 * secondNumerator;
    int finalNumerator = firstNumerator * d2;

    //Finally, we do the division, and put the result into the character array, returning false on errors and true on success

    if(!constructResult(finalNumerator, finalDenominator, result, len)) {
        return false;
    }
    
    return true;
}
//Helper function to calculate result of adding or subtracting the mantissa together
int AddSubtractHelper(int characteristic1, int denominator1, int numerator1, int characteristic2, int denominator2, int numerator2, char sign) {

    //Adjust for if we are adding or subtracting negative values
    if(characteristic1 < 0) {
        numerator1 *= -1;
    }

    if(characteristic2 < 0) {
        numerator2 *= -1;
    }

    //Adds an adjusted characteristic to numerator
    numerator1 += (characteristic1 * denominator1);

    numerator2 += (characteristic2 * denominator2);


    //We find the Least Common Multiple for our fraction math and then create multiply values for the numerators
    int newDenomenator = LCM(denominator1, denominator2);
    int mult1 = newDenomenator / denominator1;
    int mult2 = newDenomenator / denominator2;
    numerator1 *= mult1;
    numerator2 *= mult2;


    //Result depends on if we are adding or subtracting
    if(sign == '+')
        return numerator2 + numerator1;
    else if(sign == '-')
        return numerator1 - numerator2;
}


//Helper function to set up fractions for multiply and divide functions
int MultDivHelper(int characteristic, int numerator, int denominator) {
    if(characteristic < 0) {
        numerator *= -1;
    }
    
    int newCharacteristic = characteristic * denominator;
    int retVal = newCharacteristic + numerator;
    return retVal;
}


// Helper function to find the LCM for the denominators in the add/subtract helper function
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


//Helper function to use exponents
int pow(int base, int exp) {
    int num = 1;
    for(int i = 0; i < exp; i++) {
        num *= base;
    }

    return num;
}


//Helper function that determine digit count of numbers
int numSize(int num) {
    int retVal = 0;
    while(abs(num) > 0) {
        num /= 10;
        retVal++;
    }

    return retVal;
}


//Helper function that returns a number's absolute value
int abs(int num) {
    if(num < 0) {
        return num / -1;
    }
    else {
        return num;
    }
}


//Helper function that clears result character array from previous uses
void resetResult(char result[], int len) {
    for(int i = 0; i < len; i++) {
        result[i] = ' ';
    }
}


//Helper function to put the numerical result in a character array.
bool constructResult(int numerator, int denominator, char result[], int len) {

    //calculates the characteristic, and it's size. Also declare a variable in case of a negative result
    int finalResult = numerator / denominator;
    int resultSize = numSize(finalResult);
    int isNegative = 0;

    //First checks to see if result is zero with no remainder (mantissa)
    if(finalResult == 0 && numerator % denominator == 0) {
        result[0] = '0';
        result[1] = '\0';
        return true;
    }


    //Then checks if result is negative, and adjusts result[] accordingly

    if((finalResult < 0 || numerator < 0 || denominator < 0) && !(numerator < 0 && denominator < 0)) {
        result[0] = '-';
        isNegative++;

        if(resultSize + 1 >= len) {
            return false;
        }
    }

    //Checks if characteristic can be stored. If not, we return false

    if(resultSize >= len) {

        return false;
    }

    //Stores the characteristic into the result array

    for(int i = resultSize; i > 0; i--) {
        result[resultSize + isNegative - i] = '0' + (abs((finalResult / pow(10, i - 1) % 10)));
    }

    //If no mantissa, we add in null terminator.

    if(numerator % denominator == 0) {
        result[resultSize + isNegative] = '\0';
    }
    //else, we first check for if there was no characteristic at all, and adjust result accordingly for either case
    else {
        if(finalResult == 0) {
            result[resultSize + isNegative] = '0';
            result[resultSize + isNegative + 1] = '.';
            resultSize++;
        }
        else {
            result[resultSize + isNegative] = '.';
        }
        
        //Declare the starting position of our mantissa in the character array
        int mantissaStartPos = resultSize + 1 + isNegative;

        //Refactor resultSize and findalResult variable for this storage in the array
        resultSize = len - (resultSize + 2 + isNegative);
        finalResult = (abs(numerator) * pow(10, resultSize)) / abs(denominator);
        finalResult %= pow(10, resultSize);

        //Put ints one at a time into the array, and breaks if we are done early
        for(int i = 0; i < resultSize; i++) {
            if((finalResult / pow(10, (resultSize - 1) - i) % 10) == 0) {
                break;
            }
            result[mantissaStartPos + i] = '0' + (finalResult / pow(10, (resultSize - 1) - i) % 10);
        }
        result[mantissaStartPos + resultSize] = '\0';
    }

    return true;
}

//Functions brought over from Mark Mahoney's version for strong tests
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
void testMath()
{
    //add
    testAdd();
    testSubtract();
    testMultiply();
    testDivide();
}
//--
void testAdd()
{
    char shortArray[SHORT_ARRAY_LENGTH];
    char mediumArray[MEDIUM_ARRAY_LENGTH];
    char largeArray[LARGE_ARRAY_LENGTH];

    //should overflow
    if (add(2147483647, 0, 10, 2147483647, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
    {
        cout << "Error: overflow" << endl;
    }

    //0 + 0 = "0"
    add(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 0, 0, 10);
    add(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 0, 0, 10);
    add(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 0, 0, 10);

    //1 + 1 = "2"
    add(1, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 2, 0, 10);
    add(1, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 2, 0, 10);
    add(1, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 2, 0, 10);

    //4 + -1.5 = "2.5"
    add(4, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 2, 5, 10);
    add(4, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 2, 5, 10);
    add(4, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 2, 5, 10);

    //1.125 + 1.6R = "2.79"
    add(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 2, 79, 100);

    //1.125 + 1.6R = "2.7916666"
    add(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 2, 7916666, 10000000);

    //1.125 + 1.6R = "2.79166666666666666"
    add(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
    //can't use the convert function because the num/denom would overflow
    char expectedResult[] = "2.79166666666666666";
    for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
    {
        if (expectedResult[i] != largeArray[i])
        {
            cout << "Error: mismatch in C strings in add()." << endl
                << "Expected: " << expectedResult << " "
                << "Actual: " << largeArray
                << endl;
        }
    }
}
//--
void testSubtract()
{
    char shortArray[SHORT_ARRAY_LENGTH];
    char mediumArray[MEDIUM_ARRAY_LENGTH];
    char largeArray[LARGE_ARRAY_LENGTH];

    //0 - 0 = "0"
    subtract(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 0, 0, 10);
    subtract(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 0, 0, 10);
    subtract(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 0, 0, 10);

    //2 - 1 = "1"
    subtract(2, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 1, 0, 10);
    subtract(2, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 1, 0, 10);
    subtract(2, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 1, 0, 10);

    //1 - -1.5 = "2.5"
    subtract(1, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 2, 5, 10);
    subtract(1, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 2, 5, 10);
    subtract(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 2, 5, 10);

    //10.125 - 1.6R = "8.54"
    subtract(10, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 8, 54, 100);

    //1.125 - 10.6R = "-9.541666"
    subtract(1, 1, 8, 10, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, -0, 541666, 1000000);

    //1.125 - 10.6R = "-9.5416666666666666"
    subtract(1, 1, 8, 10, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
    //can't use the convert function because the num/denom would overflow
    char expectedResult[] = "-.54166666666666666";
    for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
    {
        if (expectedResult[i] != largeArray[i])
        {
            cout << "Error: mismatch in C strings in subtract()." << endl
                << "Expected: " << expectedResult << " "
                << "Actual: " << largeArray
                << endl;
        }
    }
}
//--
void testMultiply()
{
    char shortArray[SHORT_ARRAY_LENGTH];
    char mediumArray[MEDIUM_ARRAY_LENGTH];
    char largeArray[LARGE_ARRAY_LENGTH];

    //should overflow
    if (multiply(2147483647, 0, 10, 2147483647, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
    {
        cout << "Error: overflow" << endl;
    }

    //0 * 0 = "0"
    multiply(0, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 0, 0, 10);
    multiply(0, 0, 10, 0, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 0, 0, 10);
    multiply(0, 0, 10, 0, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 0, 0, 10);

    //3 * 2 = "6"
    multiply(3, 0, 10, 2, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 6, 0, 10);
    multiply(3, 0, 10, 2, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 6, 0, 10);
    multiply(3, 0, 10, 2, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 6, 0, 10);

    //3 * -1.5 = "-4.5"
    multiply(3, 0, 10, -1, 1, 2, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, -4, 5, 10);
    multiply(3, 0, 10, -1, 1, 2, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, -4, 5, 10);
    multiply(3, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, -4, 5, 10);

    //1.125 * 1.6R = "1.87"
    multiply(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 1, 87, 100);

    //1.125 * 1.6R = "1.875"
    multiply(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 1, 875, 1000);

    //1.125 * 1.6R = "1.875"
    multiply(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 1, 875, 1000);
}
//--
void testDivide()
{
    char shortArray[SHORT_ARRAY_LENGTH];
    char mediumArray[MEDIUM_ARRAY_LENGTH];
    char largeArray[LARGE_ARRAY_LENGTH];

    //cannot divide by zero
    if (divide(10, 0, 10, 0, 0, 10, shortArray, SHORT_ARRAY_LENGTH))
    {
        cout << "Error: cannot divide by zero" << endl;
    }

    //1+1/2 2+2/3 == 3/2 * 3/8 == 9/16
    divide(1, 1, 2, 2, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 0, 5625, 10000);
    divide(1, 1, 2, 2, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 0, 5625, 10000);
    divide(1, 1, 2, 2, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 0, 5625, 10000);

    //0 / 1 = "0"
    divide(0, 0, 10, 1, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 0, 0, 10);
    divide(0, 0, 10, 1, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 0, 0, 10);
    divide(0, 0, 10, 1, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 0, 0, 10);

    //6 / 3 = "2"
    divide(6, 0, 10, 3, 0, 10, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 2, 0, 10);
    divide(6, 0, 10, 3, 0, 10, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 2, 0, 10);
    divide(6, 0, 10, 3, 0, 10, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 2, 0, 10);

    //1.125 / 1.6R = "0.67"
    divide(1, 1, 8, 1, 2, 3, shortArray, SHORT_ARRAY_LENGTH);
    shouldConvert(shortArray, 0, 67, 100);

    //1.125 / 1.6R = "0.675"
    divide(1, 1, 8, 1, 2, 3, mediumArray, MEDIUM_ARRAY_LENGTH);
    shouldConvert(mediumArray, 0, 675, 1000);

    //1.125 / 1.6R = "0.675"
    divide(1, 1, 8, 1, 2, 3, largeArray, LARGE_ARRAY_LENGTH);
    shouldConvert(largeArray, 0, 675, 1000);

    //1 / -1.5 = "-.66666666666666666"
    divide(1, 0, 10, -1, 1, 2, largeArray, LARGE_ARRAY_LENGTH);
    char expectedResult1[] = "-.66666666666666666";
    for (int i = 0; i < LARGE_ARRAY_LENGTH; i++)
    {
        if (expectedResult1[i] != largeArray[i])
        {
            cout << "Error: mismatch in C strings in divide()." << endl
                << "Expected: " << expectedResult1 << " "
                << "Actual: " << largeArray
                << endl;
        }
    }
}
