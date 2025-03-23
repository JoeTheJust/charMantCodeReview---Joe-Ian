
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);
bool checkValidInput(const char currentChar, const int pos);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

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

    // //room for 9 characters plus the null terminating character
    // char answer[10];
    // int c1, n1, d1;
    // int c2, n2, d2;

    // //initialize the values
    // c1 = 1;
    // n1 = 1;
    // d1 = 2;

    // c2 = 2;
    // n2 = 2;
    // d2 = 3; 

    // //if the c-string can hold at least the characteristic
    // if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    // {
    //     //display string with answer 4.1666666 (cout stops printing at the null terminating character)
    //     cout<<"Answer: "<<answer<<endl;
    // }
    // else
    // {
    //     //display error message
    //     cout<<"Error on add"<<endl;
    // }

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
        //Make sure the input for the current character is valid
        if(checkValidInput(numString[i], i))
        {
            //If there is a negative sign (pos 0)
            if(numString[i] == '-' && i == 0) 
            {
                
                isNegative = true;
            }
            //If the character ASCII range falls in the range of 0-9
            else if(numString[i] >= '0' && numString[i] <= '9') 
            {
                //Multiply the previous number by 10 to add the next digit in the number
                c = c * 10;
                //Subtract the current character from '0' to get their integer type.
                c += numString[i] - '0';
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
    if(isNegative && ret) {
        c = -c;
    }

    return ret;
}
//--
bool checkValidInput(const char currentChar, const int pos)
{
    //Return value
    bool ret = false;
    
    //If a char is a '0'-'9'
    if(currentChar >= '0' && currentChar <= '9')
    {
        ret = true;
    }
    //If the first char is a sign +/-
    else if((currentChar == '+' || currentChar == '-') && pos == 0)
    {
        ret = true;
    }
    //If a char is a space or decimal
    else if(currentChar == ' ' || currentChar == '.') 
    {
        ret = true;
    }

    return ret;
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
