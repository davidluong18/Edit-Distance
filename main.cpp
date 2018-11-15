#include <iostream>
#include <string>
using namespace std;
/*
This program is written in C++ in Visual Studio 2017.
The code should be able to be compiled in any C++ compiler.
The program interface is through the command prompt and the output is similar 
to the example website provided.
The program will ask for both strings and provide the output specified.
*/

class EditDistance
{
public:
	EditDistance(string str1_, string str2_)
	{
		str1 = str1_;
		str2 = str2_;
		len1 = str1.size() + 1;
		len2 = str2.size() + 1;
		matrix = new int*[len1];
		for (int i = 0; i < len1; ++i)
			matrix[i] = new int[len2];
		for (int i = 0; i < len1; i++)
			matrix[i][0] = i;
		for (int i = 0; i < len2; i++)
			matrix[0][i] = i;
	}
	
	void runEdit()
	{
		for (int j = 1; j < len2; j++)
		{
			for (int i = 1; i < len1; i++)
			{
				if (str1.at(i - 1) == str2.at(j - 1))
					matrix[i][j] = matrix[i - 1][j - 1];
				else if (matrix[i - 1][j - 1] < matrix[i][j - 1] 
					&& matrix[i - 1][j - 1] < matrix[i - 1][j])
					matrix[i][j] = matrix[i - 1][j - 1] + 1;
				else if (matrix[i - 1][j] < matrix[i][j - 1])
					matrix[i][j] = matrix[i - 1][j] + 1;
				else
					matrix[i][j] = matrix[i][j - 1] + 1;
			}
		}
	}

	void backTrack()
	{
		string align1, align2;
		int i = len1 - 1, j = len2 - 1;

		while (i > 0 || j > 0)
		{
			if (i > 0 && j > 0 && matrix[i - 1][j - 1] <= matrix[i][j - 1] 
				&& matrix[i - 1][j - 1] <= matrix[i - 1][j])
			{
				align1.push_back(str1.at(i - 1));
				align2.push_back(str2.at(j - 1));
				i--;
				j--;
			}
			else if (j == 0 || i < 0 && matrix[i - 1][j] < matrix[i][j - 1])
			{
				align1.push_back(str1.at(i - 1));
				align2.push_back('_');
				i--;
			}
			else 
			{
				align1.push_back('_');
				align2.push_back(str2.at(j - 1));
				j--;
			}
		}

		reverse(align1.begin(), align1.end());
		reverse(align2.begin(), align2.end());
		cout << "Alignment is: " << endl;
		cout << align1 << endl << align2 << endl;
	}

	void printMatrix()
	{
		cout << "      ";
		for (int i = 0; i < len1 - 1; i++)
		{
			cout << str1.at(i) << "  ";
		}
		cout << endl << "   ";

		for (int i = 0; i < len1; i++)
		{
			cout << matrix[i][0] << "  ";
		}
		cout << endl;

		for (int j = 1; j < len2; j++)
		{
			cout << str2.at(j-1) << "  ";
			for (int i = 0; i < len1; i++)
			{
				cout << matrix[i][j] << "  ";
			}
			cout << endl;
		}
		cout << "Edit Distance is: " << matrix[len1 - 1][len2 - 1] << endl;
	}

	~EditDistance() 
	{
		for (int i = 0; i < len1; ++i)
			delete [] matrix[i];
		delete [] matrix;
	}
private:
	string str1, str2;
	int len1, len2;
	int** matrix;
};


int main()
{
	string str1, str2;
	cout << "Enter first string:";
	cin >> str1;
	cout << endl << "Enter second string:";
	cin >> str2;

	EditDistance distance(str1, str2);

	distance.runEdit();
	distance.printMatrix();
	distance.backTrack();

	return 0;
}
