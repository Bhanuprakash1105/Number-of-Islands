#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <streambuf>
#include <string>

using namespace std;

typedef long long int li;

void check_around(auto &b, const li i, const li j, const li r, const li c)
{
	if(i < 0 || i >= r || j < 0 || j >= c) { return; }

	li p[] = { i-1, i, i+1 };
	li q[] = { j-1, j, j+1 };

	for(li x = 0; x < 3; ++x) {
		for(li y = 0; y < 3; ++y) {
			if(p[x] < 0 || p[x] >= r || q[y] < 0 || q[y] >= c || (p[x] == i && q[y] == j)) {
				continue;
			}
			if(b[p[x]][q[y]].first && !b[p[x]][q[y]].second) {
				b[p[x]][q[y]].second = true;
				check_around(b, p[x], q[y], r, c);
			}
			b[p[x]][q[y]].second = true;
		}
	}
}

li NumberOf_Islands(auto &b, li r, li c)
{
	li count = 0;
	for(li i = 0; i < r; ++i) {
		for(li j = 0; j < c; ++j) {
			if(b[i][j].first && !b[i][j].second) {
				b[i][j].second = true;
				check_around(b, i, j, r, c);
				count++;
			}
			b[i][j].second = true;
		}
	}
	return count;
}

int main(int argc, char const *argv[])
{
	bool flag = true;

	fstream in(argv[1], ios::in);
	if(!in) { cout <<"\n> Error: Input file not found\n"<< endl; flag = false; }
	streambuf *cinbuf = cin.rdbuf();
	if(argc == 3 && flag) { cin.rdbuf(in.rdbuf()); } else { in.close(); }
	
	if(argc == 3 && flag) {
		cout <<"\n> Proceeding with IO entered in command arguments"<< endl;
	} else {
		cout <<"\n> Proceeding with STD-IO (terminal input and output)"<< endl;
	}
	
	fstream out(argv[2], ios::out);
	streambuf *coutbuf = cout.rdbuf();
	if(argc == 3 && flag) { cout.rdbuf(out.rdbuf()); } else { out.close(); }

	li r, c, temp;
	cout <<"\n> No.of rows and columns of matrix: ";
	cin >> r >> c;

	if(r <= 0 || c <= 0) { cout <<"\n> Invalid Input\n"<< endl; return 0; }

	cout <<"\n> Values into array:\n";

	vector < vector < pair <bool, bool> > > b(r, vector < pair <bool, bool> > (c, { false, false }));

	cout <<"\n> Columns-> ";
	for (li i = 0; i < c; ++i) { cout << i+1 <<" "; } cout << endl;
	for (li i = 0; i < r; ++i)
	{
		cout <<"\n> Row["<< i+1 <<"] -> ";
		for (li j = 0; j < c; ++j)
		{
			cin >> temp;
			if(temp < 0 || temp > 1)
			{
				cout <<"\n> Invalid Input\n"<< endl; return 0;

			} else { b[i][j].first = temp; }
		}
	}

	cout <<"\n> The Matrix\n"<< endl;
	for (li i = 0; i < r; ++i)
	{
		for (li j = 0; j < c; ++j) {
			cout <<" "<< b[i][j].first;
		} cout << endl;
	}

	li n = NumberOf_Islands(b, r, c);

	if(argc == 3) { cin.rdbuf(cinbuf); cout.rdbuf(coutbuf); }

	cout <<"\n> No.of islands: "<< n << endl << endl;

	if(argc == 3 && flag) {
		in.close(); out.close();
		fstream fobj(argv[2], ios::out);
		fobj << n << endl;
		fobj.close();
	}

	return 0;
}