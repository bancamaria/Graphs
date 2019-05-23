#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge
{
	int x, y;
};

#pragma region Havel-Hakimi

bool cmphh(pair<int, int>& a, pair<int, int>& b)
{
	return a.second > b.second;
}


vector <pair<int, int> > sort_interclass(vector <pair<int, int> > a, vector <pair<int, int> > b)
{
	vector<pair<int, int> > aux;
	int i = 0, j = 0;
	while (i < a.size() && j < b.size())
	{
		if (a[i].second > b[j].second)
		{
			aux.push_back(a[i++]);
		}
		else
		{
			aux.push_back(b[j++]);
		}
	}

	while (i < a.size())
		aux.push_back(a[i++]);

	while (j < b.size())
		aux.push_back(b[j++]);

	return aux;
}

vector<edge> havel_hakimi(vector<int> seq)
{
	//Necesary conditions
	int n = seq.size();
	int sum = 0;
	for (auto x : seq)
	{
		//Check for negative degree
		if (x<0 || x>n - 1)
			return vector<edge>();
		sum += x;
	}

	//Check for odd sum
	if (sum % 2 != 0)
		return vector<edge>();

	//Try to make graph

	vector<edge> answer;
	//Create a pair of sequence +node id
	vector<pair<int, int> > vpair;
	int id = 0;
	for (auto x : seq)
	{
		vpair.push_back({ id,x });
		id++;
	}
	//Sort sequence
	sort(vpair.begin(), vpair.end(), cmphh);

	while (!vpair.empty())
	{
		//All deegrees are 0
		if (vpair[0].second == 0)
			return answer;

		for (int i = 1; i <= vpair[0].second; i++)
		{
			//Can't create graph
			if (vpair[i].second == 0)
				return vector<edge>();

			vpair[i].second--;
			answer.push_back({ vpair[0].first,vpair[i].first });
		}

		//sort interclasare
		vpair = sort_interclass(vector<pair<int, int>>(vpair.begin() + 1, vpair.begin() + vpair[0].second + 1), vector<pair<int, int>>(vpair.begin() + vpair[0].second + 1, vpair.end()));
	}
	return answer;
}

#pragma endregion

int main()
{
	///Havel Hakimi
	cout << "HavelHakimi \n";
	vector<edge> answ = havel_hakimi({ 3,4,2,1,3,4,1,2 });
	if (answ.empty())
	{
		cout << "Secventa incorecta\n";
	}
	else
	{
		for (auto e : answ)
			cout << e.x + 1 << " " << e.y + 1 << "\n";
	}

}
