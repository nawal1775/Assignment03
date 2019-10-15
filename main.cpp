#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

//function to check if two delimiters are pair
bool ArePair(char opening,char closing)
{
	if(opening == '(' && closing == ')') return true;
	else if(opening == '{' && closing == '}') return true;
	else if(opening == '[' && closing == ']') return true;
	return false;
}

int main(int argc, char** argv)
{
    string fileName; //string to hold the file name and location
    cout << "Enter File name and location: " <<endl;
    getline(cin, fileName); //get the input of the user, getline is used so whitespaces in the file name are captured as well

    //creating a new fstream object to give it the fileName to open, ios::in = the file is input
    fstream file(fileName.c_str(), ios::in);
    //if file failed to open
    if (!file)
    {
        cout << "Invorrect file name or location!" << endl;
        return 0; //terminate the program
    }

    //use char data type to replace T
    GenStack<char> stack(100);
    GenStack<int> lineStack(100); //this stores the line number of each delimiter

    int lineNum = 1; // to show the user the line where an error exists

    // return false when the end of file has not been reached
    while (!file.eof())
    {
        string line;
        getline(file, line); //get one line from the file and store it in the string called line

        bool stopParsing = false; //when inside a string don't process it
        //loop on all the characters the line
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '\'' || line[i] == '"') //if current char is ' or " then set the flag
            {
                if (!stopParsing)
                {
                    stopParsing = true;
                }
                else
                {
                    stopParsing = false;
                }

                continue;
            }

            if (stopParsing)
            {
                continue;
            }
            //if the current character is ( or { or [
            if(line[i] == '(' || line[i] == '{' || line[i] == '[')
            {
                stack.push(line[i]); //push this character onto the stack
                lineStack.push(lineNum);
            }
            //else if the current character is ) or } or ]
            else if (line[i] == ')' || line[i] == '}' || line[i] == ']')
            {
                //if the stack is empty => no matching opening delimiter
                //or if stack is not empty, check if the last opening delimiter matches this closing one
                char lastOpeiningDelimiter; //char to store the peek of the stack => last opening delimiter
                stack.peek(lastOpeiningDelimiter);
                if (stack.isEmpty())
                {
                    //output an error and indicate
                    cout << "Syntax error in line " << lineNum << " expected opening of this delimiter" << line [i] << endl;
                }
                //if delimiters do not match
                else if (!ArePair(lastOpeiningDelimiter, line[i]))
                {
                    //indicate the error
                    cout << "Syntax error in line " << lineNum << " " << lastOpeiningDelimiter << " does not match with " << line[i] << endl;
                }
                stack.pop();
                lineStack.pop();
            }
        }
        // increment the line number by 1
        lineNum++;
    }

    //stack is not empty so some opened delimiters do not have a closing one
    if (!stack.isEmpty())
        {
            // pop all the delimiters 
            while (!stack.isEmpty())
            {
                char missingClosing;
                int line;
                stack.pop(missingClosing);
                lineStack.pop(line);
                cout << "Syntax error in line " << line << " missing closing for " << missingClosing << endl;
            }
        }
    cout << "File inspection Finished!" << endl;
    file.close(); //close the file

    return 0;
}
