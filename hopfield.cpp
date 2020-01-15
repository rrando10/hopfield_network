#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
using namespace std;

vector<vector<int> > patterns;
vector<vector<double> > weights;
vector<vector<int> > data;

//returns a random state (1 or -1)
int randState()
{
	random_device rd;
	mt19937 gen(rd());
	bernoulli_distribution d(0.3);

	if(d(gen))
		return 1;
	else
		return -1;
}

void initNet()
{
	vector<int> row(100);
	vector<double> wow(100);

	for(int i=0; i<50; i++){
		for(int j=0; j<100; j++)
			row[j] = randState();
		patterns.push_back(row);
	}

	for(int i=0; i<100; i++)
		weights.push_back(wow);
}

void printNet()
{
	cout<<"printing...\n\n";
	for(int i=0; i<50; i++){
		for(int j=0; j<15; j++)
			if(patterns[i][j] == -1)
				cout<<" ";
			else
				cout<<"*";	
		cout<<endl;
	}
}

void imprint(int p)
{
	int wSum;
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			if(i != j){
				wSum = 0;
				for(int k=0; k<p; k++)
					wSum += (patterns[k][i] * patterns[k][j]);
				weights[i][j] = (wSum / 100.00);
			}else{
				weights[i][j] = 0;
			}
		}
	}
}

int stability(int p)
{
	vector<int> net(100);
	bool isStable;
	int num = 0;
	double hSum = 0.0;
	int s;

	for(int k=0; k<p; k++){
		
		isStable = true;

		for(int i=0; i<100; i++){
			net[i] = patterns[k][i];
		}

		for(int i=0; i<100; i++){
			hSum = 0.0;
			for(int j=0; j<100; j++)
				hSum += (weights[i][j] * patterns[k][j]);

			if(hSum < 0.0)
				s = -1;
			else{
				s = 1;
			}	
			
			if(s != patterns[k][i]){
				isStable = false;
				break;
			}
		}
		
		if(isStable){
			num += 1;
		}
	}

	return num;
}

void printData()
{
	ofstream ofs;
	string file = "data.csv";
	ofs.open(file);

	for(int i=0; i<50; i++)
		ofs<<i<<",";
	ofs<<endl;

	for(int i=0; i<20; i++){
		for(int p=0; p<50; p++)
			ofs<<data[i][p]<<",";
		ofs<<endl;
	}
	ofs.close();
}
int main() {

	int p,i;
	vector<int> stable(50);

	for(i=0; i<20; i++){
		
		initNet();

		for(p=1; p<=50; p++){
			imprint(p);
			stable[p-1] = stability(p);
//			cout<<"stability("<<p<<"): "<<stable[p-1]<<endl;
		}

		data.push_back(stable);
		patterns.clear();
		weights.clear();
	}

	printData();
	return 0;
}

