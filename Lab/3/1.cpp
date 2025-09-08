#include<iostream>
using namespace std;

class Matrix
{
	int r;
	int c;
	int** mat;
	
	public:
	
	Matrix(int rr, int cc)
	{
		allocate(rr,cc);
	}
	
	~Matrix()
	{
		deallocate();
	}
		
	void allocate(int rr, int cc)
	{
		r = rr;
		c = cc;
		
		mat = new int*[r];
		for(int i = 0; i < r; i++)
		{
			mat[i] = new int[c];
		}
		
		//initially, set all values to 0
		
		for(int i = 0; i < r; i++)
		{
			for(int j = 0; j < c; j++)
			{
				mat[i][j] = 0;
			}
		}
	}
	
	void enterValues()
	{
		for(int i = 0; i < r; i++)
		{
			for(int j = 0; j < c; j++)
			{
				cout << "Enter value at row " << i << ", col " << j << ": ";
				cin >> mat[i][j];
		    }
		}
	}
	
	void deallocate()
	{
		for(int i = 0; i < r; i++)
		{
			delete[] mat[i];
		}
		delete[] mat;
	}
	
	void resize(int rr, int cc)
	{
		int** nm = new int*[rr];
		for(int i = 0; i < rr; i++)
		{
			nm[i] = new int[cc];
			for(int j = 0; j < cc; j++)
			{
				if(i < r && j < c)
				{
					nm[i][j] = mat[i][j];
				}
				else 
				{
					nm[i][j] = 0;
				}
				
			}
		}
		
		deallocate();
		mat = nm;
		c = cc;
		r = rr;
	}
	
	void transpose()
	{
		int** nm = new int*[c];
		for(int i = 0; i < c; i++)
		{
			nm[i] = new int[r];
			for(int j = 0; j < r; j++)
			{
				nm[i][j] = mat[j][i];
			}
		}
		
		deallocate();
		mat = nm;
		int t = r;
		r = c;
		c = t;
	}
	
	void print()
	{
		for(int i = 0; i < r; i++)
		{
			for(int j = 0; j < c; j++)
			{
				int s = i + j;
				if(s % 2 == 1)
				{
					cout << mat[i][j] + 2 << " ";
				}
				else 
				{
					cout << mat[i][j] << " ";
				}
			}
			cout << endl;
		}
	}
	
};

int main()
{
	int r,c;
	cout << "Enter rows and columns: ";
	cin >> r >> c;
	Matrix m(r,c);
	
	m.enterValues();
	m.print();
	
	int r2, c2;
	cout << "Enter new rows and columns: ";
	cin >> r2 >> c2;
	m.resize(r2,c2);
	cout << "Resized matrix:" << endl;
	m.print();
	
	
	cout<< "Transpose:" << endl;
	m.transpose();
	m.print();
	
	return 0;
}