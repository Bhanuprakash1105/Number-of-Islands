#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

set< pair<int, int> > s;

void check_around(bool **b, int r, int c, int i, int j)
{
	if(!(i >= 0 && i < r && j >= 0 && j < c)) { return; }

	int x[3] = {i-1, i, i+1}; int y[3] = {j-1, j, j+1};
	
	for (int p = 0; p < 3; ++p)
	{
		for (int q = 0; q < 3; ++q)
		{
			if(x[p] >= 0 && x[p] < r && y[q] >= 0 && y[q] < c) {
				
				int t1 = x[p], t2 = y[q];

				if(s.count(make_pair(t1, t2))) { continue; } else if(b[t1][t2])
				{
					s.insert(make_pair(t1, t2)); check_around(b, r, c, t1, t2);
				}
			
			}
		}
	}
}

int NumberOf_Islands(bool **b, int r, int c)
{
	int count = 0;
	
	for (int i = 0; i < r; ++i) {
		
		for (int j = 0; j < c; ++j) {

			if(s.find(make_pair(i, j)) != s.end()) { continue; } else if(b[i][j])
			{				
				count++; s.insert(make_pair(i, j));
				
				check_around(b, r, c, i, j);
			}
		}
	}
	return count;
}

int main()
{
	int r, c, temp;
	cout <<"\n> No.of rows and columns of matrix: ";
	cin >> r >> c;

	if(r <= 0 || c <= 0) { cout <<"\n> Invalid Input\n"<< endl; return 0; }

	cout <<"\n> Values into array:\n";
	bool **b = new bool*[r];
	cout <<"\n> Columns-> ";
	for (int i = 0; i < c; ++i) { cout << i+1 <<" "; } cout << endl;
	for (int i = 0; i < r; ++i)
	{
		b[i] = new bool[c];
		cout <<"\n> Row["<< i+1 <<"] -> ";
		for (int j = 0; j < c; ++j)
		{
			cin >> temp;
			if(temp < 0 || temp > 1)
			{
				cout <<"\n> Invalid Input\n"<< endl; return 0;

			} else { b[i][j] = temp; }
		}
	}

	cout <<"\n> The Matrix\n"<< endl;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j) {
			cout <<" "<< b[i][j];
		} cout << endl;
	}

	int n = NumberOf_Islands(b, r, c);
	cout <<"\n> No.of islands: "<< n << endl;

	cout << endl;
	return 0;
}