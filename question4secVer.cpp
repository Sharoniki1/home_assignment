//Question 4 - Filesystem & args  

// Task: Implement the code as described in the main body, make sure to handle cases when the requested file is not found or the "files" directory doesn't exists and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code should be able to run in other windows, linux and other platforms (hint: '/' and '\' in file paths)


#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>

using namespace std;

void createFile(const char* path, char* message);
void readFile(const char* path);
void printFile(ifstream& file);

int main(int argc, char** argv)
{
    string input;
	cout << "Enter create/read: ";
	cin >> input;

	//If user passed "create" argument 
	//		Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files" under the current working directory  
	if(input == "create")
		createFile(argv[0], argv[1]);
    //else if user passed "read" argument 
	//		read a file named* argument2* from a folder named "files" under the current working directory and print it to the console
    else if(input == "read")
        readFile(argv[0]);

	//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the file c:\code\files\test1.txt with the content "Hello from Nir"
    createFile("C:/code/files/test1.txt", "Hello from Nir");
	//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed) 
	readFile("C:/code/files/test1.txt");

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}

void createFile(const char* path, char* message)
{
    _mkdir(path);
	ofstream file(path);
	file <<message;
	file.close();
}

void readFile(const char* path)
{
    ifstream file1(path);
	file1.open(path);
	if(file1.is_open())
	{
		int x;
		while(file1 >> x)
			cout << x << endl;

		printFile(file1);
		file1.close();
	}
	else
	{
		cout << "ERROR!\n";
	}
}

void printFile(ifstream& file)
{
	std::cout << file.rdbuf(); 
}
