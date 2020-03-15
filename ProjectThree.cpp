#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <istream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <map>
#include "Queue.h"
using namespace cop4530;
using namespace std;
void print(vector<string>& Cities, vector< vector<int> >& Matrix);
void BFS(string & source, string & destination, vector<string>& Cities, vector< vector<int> >& Matrix);
void Menu(vector<string>& Cities, vector< vector<int> >& Matrix);
int main(int argc, char* argv[])
{
	//Atlanta =  0 100   -1   50   -1   -1    -1   100
	vector < vector<int>>Matrix; //holds the 2D numbers
	vector<string>Cities; //read into the cities
	int citynumber;
	string line;

	ifstream Readme;
	Readme.open(argv[1]);
	Readme.open("proj3.input");
	if (!Readme) {
		cerr << "Unable to open file";
		exit(1); 
	}
	getline(Readme, line);
	citynumber = stoi(line); //should hold number; eg: 8
	int zero = 0;
	
	while (zero < citynumber)
	{
		getline(Readme, line);
		Cities.push_back(line); //should read first then push back each city into the vector.
		zero++; //increment
	}
	for (int i = 0; i < citynumber; ++i) 
	{
		vector<int>vt;
		int price;
		for (int j = 0; j < citynumber; ++j) {
			Readme >> price;
			vt.push_back(price);
		}
		Matrix.push_back(vt); //Matrix will contain the 2D vector
	}
	Readme.close();
	print(Cities, Matrix);
	Menu(Cities, Matrix);
	
}
void print(vector<string>& Cities, vector< vector<int> >& Matrix)
{
	cout << Cities.size() << endl;
	for (int i = 0; i < Cities.size(); i++)
		cout << Cities.at(i) << '\n';
	/*
	for (std::vector<std::vector<int>>::size_type i = 0; i < Cities.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j < Cities.size(); j++)
		{
			std::cout << setw(5) << setprecision(2) << fixed << Matrix[i][j] << "  ";
		}
		std::cout << std::endl;
	}*/
		cout << '\n';
		cout << "Direct Flight Between Cities" << endl;
		cout << "-------------------------------------------------" << endl;
		for (int i = 0; i < Cities.size(); i++) {
			cout << Cities[i] << ":" << '\n';
			for (int j = 0; j < Cities.size(); j++)
			{
				int a = Matrix[i][j];
				if (a != -1 && a != 0)
				{
					cout << "   " << Cities.at(j) << "," << " " << "$" << a << endl;
				}
			}
			//cout << endl;
		}
		cout << "-------------------------------------------------" << endl;
}
void BFS(string& source, string& destination, vector<string>& Cities, vector< vector<int> >& Matrix) //BFS
{
	//first Check if the cities are connected.
	bool connect = false;
	vector<string>Connected;
	vector<int>P;
	Connected.push_back(source);
	Connected.push_back(destination);
	for (int i = 0; i < Connected.size(); i++)
	{
		std::vector<string>::iterator it = std::find(Cities.begin(), Cities.end(), Connected[i]);
		if (it != Cities.end())
		{
			P.push_back(std::distance(Cities.begin(), it)); //should return position
		}
	}
	//print path if connected
	int price = 0;
	int z = 1;
	for (int i = 0; i < Connected.size() - 1; i++)
	{
		int a = Matrix[P[i]][P[z]];
		if (a != -1 && a != 0)
		{
			connect = true;
			price += a;
			z++;
		}
		else
			break;
	}
	if (connect == true)
	{
		std::cout << source << "->" << destination << " " << "$" << price << endl; //print the path
		return;
	}

	vector<string>Padre; //parent nodes
	vector<string>Hijo;//child nodes
	vector<string>Visited; //keeps each VISITED city.
	std::vector<string>::iterator it;
	Queue<string> Q; //keeps each city.
	string Hold = source;
	int find = 0;
	int i;
	Q.push(source); //push source into Queue

	while (!Q.empty())
	{
		if (Q.back() == destination)
			break;
		for (int k = 0; k < Cities.size(); k++)
		{
			if (Q.front() == Cities.at(k))
			{
				find = k;
				break;
			}
		}
		for (i = find; i <= find; i++)
		{
			for (int j = 0; j < Cities.size(); j++)
			{

				int a = Matrix[i][j];
				if (a != -1 && a != 0) //a!= 0;
				{
					it = std::find(Visited.begin(), Visited.end(), Cities.at(j));
					if (it != Visited.end())
					{
						continue;
					}
					else
					{
						if (Cities.at(j) == destination)
						{

							Padre.push_back(Q.front());
							Hijo.push_back(Cities.at(j));
							Q.push(Cities.at(j));
							break;
						}
						Padre.push_back(Q.front());
						Hijo.push_back(Cities.at(j));
						Q.push(Cities.at(j));
					}
				}
			}
		}


		Visited.push_back(Q.front());
		Q.pop();

	}
	//Print the Path
	vector<string>ThePath;
	string compare;
	int Price = 0;
	//Padre and Hijo
	ThePath.push_back(Q.back());
	compare = Padre[Padre.size() - 1];
	for (int i = Padre.size() - 1; i >= 0; i--)
	{
		if (compare == Hijo[i])
		{
			ThePath.push_back(compare);
			compare = Padre[i];
			if (compare == source)
			{
				ThePath.push_back(source);
				break;
			}
		}
	}

	vector<int>Position;
	for (int i = 0; i < ThePath.size(); i++)
	{
		std::vector<string>::iterator it = std::find(Cities.begin(), Cities.end(), ThePath[i]);
		if (it != Cities.end())
		{
			Position.push_back(std::distance(Cities.begin(), it)); //should return position
		}
	}
	int sum = 0;
	int j = 1;
	for (int i = 0; i < ThePath.size() - 1; i++)
	{
		int a = Matrix[Position[i]][Position[j]];
		sum += a;
		j++;
	}
	std::reverse(ThePath.begin(), ThePath.end());
	for (auto i = ThePath.begin(); i != ThePath.end(); ++i)
	{
		std::cout << " " << *i << " ";
		if (i != ThePath.end() - 1)
			cout << "->";
	}
	cout << "$" << sum;
	cout << '\n';

}
void Menu(vector<string>& Cities, vector< vector<int> >& Matrix)
{
	string entry;
	string source, destination;
	do {
		cout << '\n';
		cout << "Source City: ";
		getline(cin, source);
		
		cout << "Destination : ";
		getline(cin, destination);
		cout << "\n";
		cout << "finding min hop route...." << endl;
		if (source == destination)
			cout << source << " " << "$" << "0" << endl;
		else if (std::find(Cities.begin(), Cities.end(), source) == Cities.end())
		{
			cout << "path not found, " << "source city: " << source << " not on the map" << endl;
		}
		else if (std::find(Cities.begin(), Cities.end(), destination) == Cities.end())
		{
			cout << "path not found, " << "destination city: " << destination << " not on the map" << endl;
		}
		else
			BFS(source, destination, Cities, Matrix);
		
			cout << "Search Another Route? (Y/N)";
			getline(cin, entry);
			while (entry != "Y" && entry != "y" && entry != "N" && entry != "n")
			{
				cout << "Search Another Route? (Y/N)";
				getline(cin, entry);
			}


	} while (entry != "N" || entry == "n");
}