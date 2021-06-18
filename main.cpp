#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <math.h>
#include <vector>
#include <stack>
#include <string>

using namespace std;

//making the two string inputs equal length
string LengthEqual(string in1, string in2) {
    //first find the length of the two inputs
    int len1 = in1.length();
    int len2 = in2.length();

    //when the length of the input1 is longer than the input2
    if (len1 > len2) {
        //do tthis while loop when the length are not equal
        while (len1 != len2) {
            in2 = '0' + in2; //we add zero infront of the strings
            len2 = in2.length();
        }
        //return the equal lengthed input 2
        return in2;
    //when the length of the input2 is longer than the input 1
    } else if (len2 > len1) {
        //continue this until the two inputs have same length
        while (len1 != len2) {
            in1 = '0' + in1; //we add zero infront of the strings
            len1 = in1.length(); //update the length information
        }
        //return the length
        return in1;
    }

    return "return";
}

string addition(string char_input1, string char_input2, int baseNumber){
	//getting the input
	//input is string 1, string 2, base number
	int c = 0;

	//intialiseing the vector that holds the int inputs
	vector<int> int_input1(char_input1.size());
	vector<int> int_input2(char_input2.size());
	int size1 = char_input1.size();
	int size2 = char_input2.size();

	//convert the number input into arrays
	for(int i=0;i<size1;i++) {
		int_input1[i]=char_input1[i] - '0';
	}
	 for(int i=0;i<size2;i++) {
		int_input2[i]=char_input2[i]- '0';
	}

	//when the digits are different, fill it with 0
	int len = int_input1.size()-int_input2.size();
	int diff = abs(len);
	if (int_input1.size() > int_input2.size()) {
		for(int i=0;i < diff;i++)
		{
			//this will fill num with 0, and make both inputs to have same digits
			int_input2.insert(int_input2.begin(),0);
		}
	} else {
		for(int i=0; i  < diff; i++)
		{
			int_input1.insert(int_input1.begin(),0);
		}
	}

	//find the input with bigger size to use it for the later for loop
	int n;
	if (int_input1.size() > int_input2.size()) {
		n = int_input1.size();
	} else {
		n = int_input2.size();
	}

	vector<int> sum; //initialsing the sum
	//School method of addition
	for (int i = n-1; i > -1; i--) {
		int temp = c + int_input1[i] + int_input2[i]; //answer of the 
		sum.push_back(temp % baseNumber);
		c = temp / baseNumber;
	}
	sum.push_back(c);

	string str = "";

	for (int i = size1-1;i > -1; i--) {
		if (i == size1-1 && sum[i] != 0) str = to_string(sum[i]) + str;
		else if (i != sum.size()-1) str = to_string(sum[i]) + str;
	}

	reverse(str.begin(),str.end());

    return str;
}


//this is the basic mulplication
string Multi (string in1, string in2, int base) {
    //the variables that will be used
    string sum;
    int n1 = in1.length();
    int n2 = in2.length();

    //when input 1 has only one digit
    if (n2!=1) {
        //this counts how many times you are actually multiplying
        int counter = stoi(in1);
        while (counter != 0) {
            //add them up until counter hits zero.
            //it is additon, but it will equal to multiplication
            sum = addition(in2,sum,base);
            counter--;
        }
        //return the number
        return sum;

    //now when the input 2 has only one digit
    } else if (n1 != 1) {
        //same function
        int counter = stoi(in2);
        while (counter != 0) {
            sum = addition(in1,sum,base);
            counter--;
        }
        return sum;

    } else {
        //in case when both numbers can be length of one
        int counter = stoi(in2);
        while (counter != 0) {
            sum = addition(in1,sum,base);
            counter--;
        }
        return sum;
    }
}

string Karatsuba(string in1, string in2, int base) {
    string answer = "";

    //find which string has longer length
    int length = max(in1.length(), in2.length());
    int k = length/2; //find the midpoint of the length

    //as this is recrusive function, we start write the base case
    //stop the recursion when the size of the input is 1
    //when the number is lower than 4, do the multiplication
    if (in1.length() == 1 || in2.length() == 1) {
        //if one of the inputs has zero, we return 0.
        //this is to reduce the error that can happen in the multi function
        if (stoi(in1) == 0 || stoi(in2) == 0) {
            return "0";
        } else {
            //if the number is not zero, we use multi function
            return Multi(in1,in2,base);
        }
    }

    //make the length equal
    if (in1.length() > in2.length()) {
        in2 = LengthEqual(in1, in2);  
    } else if (in2.length() > in1.length()) {
        in1 = LengthEqual(in1,in2);
    }

    //separates the two integers
    string a0 = in1.substr(0,k);
    string a1 = in1.substr(k);
    string b0 = in2.substr(0,k);
    string b1 = in2.substr(k);

    //multiply the numbers
    string a1b0 = Karatsuba(a1,b0,base);
    string a0b1 = Karatsuba(a0,b1,base);
    string tmp = Karatsuba(a1b0,a0b1,base);
    string p2 = Karatsuba(a1,b1,base);
    string p0 = Karatsuba(a0,b0,base);

    int len = in1.length();
    int k_l = len/2;
    int len_k = len - k_l;
    int counter = 2 * len_k;

    while (counter != 0) {
    	p2 = p2 + "0";
    	counter--;
    }
    counter = len_k;
    while (counter != 0) {
    	tmp = tmp + "0";
    	counter--;
    }
    //add them up
    answer = addition(p2,tmp,base);
    answer = addition(answer,p0,base);

    return answer;
}

int main() {

	//getting the input
	//input is string 1, string 2, base number
	string char_input1;
	string char_input2;
	int baseNumber;
	int c = 0; //initialise the carrier

	//getting the input
	cin >> char_input1;
	cin >> char_input2;
	cin >> baseNumber;

	//intialiseing the vector that holds the int inputs
	vector<int> int_input1(char_input1.size());
	vector<int> int_input2(char_input2.size());
	int size1 = char_input1.size();
	int size2 = char_input2.size();

	//convert the number input into arrays
	for(int i=0;i<size1;i++)
	{
		int_input1[i]=char_input1[i] - '0';
	}
	 for(int i=0;i<size2;i++)
	{
		int_input2[i]=char_input2[i]- '0';
	}

	//when the digits are different, fill it with 0
	int len = int_input1.size()-int_input2.size();
	int diff = abs(len);
	if (int_input1.size() > int_input2.size()) {
		for(int i=0;i < diff;i++)
		{
			//this will fill num with 0, and make both inputs to have same digits
			int_input2.insert(int_input2.begin(),0);
		}
	} else {
		for(int i=0; i  < diff; i++)
		{
			int_input1.insert(int_input1.begin(),0);
		}
	}

	//find the input with bigger size to use it for the later for loop
	int n;
	if (int_input1.size() > int_input2.size()) {
		n = int_input1.size();
	} else {
		n = int_input2.size();
	}

	vector<int> sum; //initialsing the sum
	//School method of addition
	for (int i = n-1; i > -1; i--) {
		int temp = c + int_input1[i] + int_input2[i]; //answer of the 
		sum.push_back(temp % baseNumber);
		c = temp / baseNumber;
	}
	sum.push_back(c);

	//output the result of the addition
	for (int i = size1-1; i > -1; i--) {
		//inhibiting the first zero output
		if (i == size2-1 && sum[i] != 0) cout << sum[i];
		else if (i != sum.size()-1) cout << sum[i];

	}
	cout << " " << Multi(char_input1,char_input2,baseNumber) << endl;
	//cout << " " << Karatsuba(char_input1,char_input2,baseNumber) << endl;;
	return 0;
}
