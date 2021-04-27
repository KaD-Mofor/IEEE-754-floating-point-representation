#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
//Function prototypes
void welcomeText();
int userInputChoice();
string hexadecimalInput();
double decimalInput();
string hex2Bin(string);
string decimal2IEEE(double);
void displayBin(string);
void displayIEEE(string);
bool doAnother();


int main() {
	/*This program receives user input as hexadecimals or decimals,
	and converts them to either binary or IEEE floating point numbers.
	It is a menu driven program, designed to be user friendly.*/

	int choice;     //To hold user's choice.
	double dec = 0;  //To hold the decimal input
	string result = "";  //To hold binary output
	string hexa = ""; //To hold the hexadecimal input
	bool goAgain = true;    //Allow user to continue or quit.

	welcomeText();          //Welcome text fucntion

	do
	{
		choice = userInputChoice();   //get user's choice of input.
		//call the appropriate input function based on input choice.
		switch (choice)
		{
		case 2: result = hex2Bin(hexadecimalInput());
			break;
		case 1: result = decimal2IEEE(decimalInput());
			break;
		case 3: exit(0);
		}

		//Display result
		if (choice == 1 )
		{
			displayIEEE(result);
		}
		else
		{
			displayBin(result);
		}		
		
		goAgain = doAnother();

	} while (goAgain);


	return 0;
}


//A welcome text
void welcomeText()
{
	cout << "\n----------------------------WELCOME-------------------------\n"
		<< "\nEnter a decimal or hexadecimal number and the program \n"
		<< "will convert it to either a binary or IEEE representation\n" << endl;
		
}

//This function gets the number type to be converted.
int userInputChoice()
{
	int userInput;       //To hold user's choice.
	cout << "\nWhat do you want to convert? \n"
		<< "[1] - Decimal to IEEE representation \n"
		<< "[2] - Hexa-decimal to Binary\n"
		<< "[3] - Exit the program\n";
	cin >> userInput;
	while (userInput != 1 && userInput != 2 && userInput != 3)
	{
		cout << "\nInvalid entry!\n";
		cout << "\nWhat do you want to convert? \n"
			<< "[1] - Decimal to IEEE representation \n"
			<< "[2] - Hexa-decimal to Binary\n"
			<< "[3] - Exit the program\n";
		cin >> userInput;
	}
	return userInput;
}


//haxadecimal input function
string hexadecimalInput()
{
	string number;      
	cout << "\nEnter the Hexadecimal number you want to convert: ";
	cin >> number;
	//Input validation
	while (number.length() > 20)
	{
		cout << "\nEnter a Hexadecimal no greater than 20 characters: ";
		cin >> number;
	}

	return number;
}


//Decimal input function
double decimalInput()
{
	double number;
	cout << "\nEnter the decimal number you want to convert: ";
	cin >> number;
	//Input validation
	while (number < -1000 || number > 1000)
	{
		cout << "\nEnter a decimal no less than -1000 and no greater than 1000: ";
		cin >> number;
	}
	return number;
}


//Converts hexadecimal into binary
string hex2Bin(string s)
{
	string bin = "";  //To hold the converted number

    //Using map, design a table and match the hexadecimals to binary
	map<char, string> table =
	{
		{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, 
		{'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, 
		{'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
		{'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
	};
				 
	//Converting
	for (int i = 0; i < s.length(); i++) {
		bin += table [ toupper(s[i]) ];
	}
	
	return bin;
}

string decimal2IEEE(double number)
{
    int s = 0;              //sign of the number(0 = positive, 1 = negative)
    vector<string> IEEE;
    vector<int> digit_bit;
    vector<string> reverseDigit_bit;
    vector<int> decimal_bit;
    vector<int> exponent_bit;
    vector<string> mantissa_bit;

    //Check if number is negative and convert it to an absolute value
    if (number < 0) {
        number *= -1;
        s = 1; 
    }

    //Split number to digit and decimal portions
    int digit_part = (int)number;                //integer part of the number
    double decimal_part = number - digit_part;  //decimal part of the number

    //Convert the integer part to binary
    while (digit_part > 0)
    {
        digit_bit.push_back(digit_part % 2);
        digit_part /= 2;
    }

    //Get the exponent and convert to binary
    int exponent = 127 + digit_bit.size() - 1;
    //If exponent is less than 127, add 1 back.
    if (exponent <= 126)
        exponent++;

    while (exponent > 0)
    {
        exponent_bit.push_back(exponent % 2);
        exponent /= 2;
    }
    //Adjust exponent to 8 bite if less than 
    if (exponent_bit.size() < 8)
        exponent_bit.push_back(0);

    //Convert the decimal part to binary
    while (decimal_part != 0) {
        decimal_part *= 2;

        if (decimal_part >= 1)
        {
            decimal_bit.push_back(1);
            decimal_part--;
        }
        else
        {
            decimal_bit.push_back(0);
        }
    }

    //Take out the first element of the vector
    digit_bit.pop_back();

    //Reversing the digit vector to get the numbers from bottom - top
    for (int i = digit_bit.size() - 1; i >= 0; i--) {
        reverseDigit_bit.push_back(to_string(digit_bit.at(i)));
    }

    //Prepend the S value to the IEEE vector
    IEEE.push_back(to_string(s));

    //Append Exponent to IEEE
    for (int i = exponent_bit.size() - 1; i >= 0; i--) {
        IEEE.push_back(to_string(exponent_bit.at(i)));
    }

    //Append Reversed digit portion to the IEEE vector.
    for (int i = 0; i < reverseDigit_bit.size(); i++)
    {
        IEEE.push_back(reverseDigit_bit.at(i));
    }

    //Append decimal portion to the IEEE vector.
    for (int i = 0; i < decimal_bit.size(); i++)
    {
        IEEE.push_back(to_string(decimal_bit.at(i)));
    }
    //Adjust IEEE to 32 bite
    if (IEEE.size() < 32)
    {
        while (IEEE.size() < 32)
        {
            IEEE.push_back("0");
        }
    }
    else
    {
        while (IEEE.size() > 32)
        {
            IEEE.pop_back();
        }
    }

    //Get the mantissa and adjust it to 23 bite
    mantissa_bit.insert(mantissa_bit.begin(), IEEE.begin() + 9, IEEE.end());

    for (auto it = mantissa_bit.begin(); it != mantissa_bit.end(); ++it)

        if (mantissa_bit.size() < 23)
        {
            while (mantissa_bit.size() < 23)
            {
                mantissa_bit.push_back("0");
            }
        }
        else
        {
            while (mantissa_bit.size() > 23)
            {
                mantissa_bit.pop_back();
            }
        }

    cout << "\n*************************************************************" << endl;
    //Display the sign    
    cout << "\nS: " << s << endl;

    //Display mantissa
    cout << "\nMantissa (f): ";
    for (int i = 0; i < mantissa_bit.size(); i++) {
        cout << mantissa_bit.at(i);
    }
    cout << "\nMatissa count: " << mantissa_bit.size() << " bite" << endl;

    //Display exponent_bit vector
    cout << "\nExponent: " << digit_bit.size() + 127 << endl;
    cout << "Exponent binary notation: ";
    for (int i = exponent_bit.size() - 1; i >= 0; i--) {
        cout << exponent_bit.at(i);
    }
    cout << endl;

    string ieee = "";

    //Display IEEE vector
    for (int i = 0; i < IEEE.size(); i++) {
        ieee += IEEE.at(i);
    }
    cout << "\nIEEE count: " << IEEE.size() << " bite" << endl;

    return ieee;
}


void displayBin(string b)
{
    cout << "\n*************************************************************" << endl;
	cout << "\nThe binary equivalent is : "<<b;
	cout << "\n=============================================================" << endl;
}

void displayIEEE(string b)
{
	cout << "\nIEEE-754 representation: "<<b;
	cout << "\n=============================================================" << endl;
}

//This function permits user to quit or continue the program
bool doAnother()
{
	int another;
	cout << "\nDo you want to convert another number? \n"
		<< "[0] - No\n"
		<< "[1] - Yes\n";
	cin >> another;
	while (another != 0 && another != 1)
	{
		cout<<"\nInvalid entry!\n"
			<< "\nDo you want to convert another number? \n"
			<< "[0] - No\n"
			<< "[1] - Yes\n";
		cin >> another;
	}
	if (another==0)
		return false;
}
