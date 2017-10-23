#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<string>
using namespace std;

ofstream out("sudoku.txt");

void Print(vector<vector<int>> &num) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j)
			out << num[i][j] << " ";
		out << "\n";
	}
}


bool IsRight(vector<vector<int>> &num, int row, int col) {
	int v = num[row][col];
	for (int i = 0; i < row; ++i) {
		if (num[i][col] == v)
			return false;
	}
	for (int i = 0; i < col; ++i) {
		if (num[row][i] == v) {
			return false;
		}
	}
	int rowb = row / 3;
	rowb *= 3;
	int colb = col / 3;
	colb *= 3;
	int rowe = rowb + 2, cole = colb + 2;
	int i = rowb;
	int j = colb;
	for (int k = 0; k < 8; ++k) {
		if ((row != i) || (col != j)) {
			if (num[i][j] == v)
				return false;
		}
		else break;
		if (j == cole) {
			j = colb;
			++i;
		}
		else ++j;
	}
	return true;
}

bool Core(vector<vector<int>> &num, int row, int col) {
	vector<int> number = { 1,2,3,4,5,6,7,8,9 };
	int SIZE = number.size();
	
	while (!number.empty()) {
		//��ѡ1~9��ʣ�����
		int rn = rand() % SIZE;
		SIZE--;
		auto randnum = number.begin() + rn;
		num[row][col] = *randnum;
		number.erase(number.begin() + rn);
		//�ж��Ƿ����
		if (IsRight(num, row, col) == false)
			continue;
		//�ж��Ƿ����
		if ((row == 8) && (col == 8)) {
			return true;
		}
		int nextr, nextc;
		if (col == 8) {
			nextr = row + 1;
			nextc = 0;
		}
		else {
			nextr = row;
			nextc = col + 1;
		}

		bool next = Core(num, nextr, nextc);
		if (next)
			return true;
	}
	//�������������У�������ʧ��
	if (number.empty())
	{

		num[row][col] = -1;
		return false;
	}
}

int main(int argv, char* args[]) {
	int N;
	if (argv == 3) {
		stringstream s;
		s << args[2];
		s >> N;
	}
	else {
		cerr << "wrong intput" << endl;
		exit(1);
	}
	if ((strcmp("-c", args[1])) || (N <= 0)) {
		cerr << "wrong intput" << endl;
		exit(1);
	}
	
	if (!out) {
		cerr << "�޷��ҵ�sudoku.txt�ļ�" << endl;
		exit(1);
	}
	vector<vector<int>> num(9, vector<int>(9, 0));
	//cin >> N;
	//��һ�д�1��2��3��4��5��6��7��8��9��ʼ����
	vector<int> fst = { 7,1,2,3,4,5,6,8,9 };
	for (int i = 0; i < N; ++i) {
		for (int k = 0; k < 9; ++k) {
			num[0][k] = fst[k];
		}
		if (Core(num, 1, 0)) {
			Print(num);
			out << "\n";
		}

		//ȷ����һ�в����ظ�
		next_permutation(fst.begin(), fst.end());
	}
	out.close();
}