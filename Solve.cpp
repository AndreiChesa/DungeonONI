#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

ifstream f("dungeon.in");
ofstream g("dungeon.out");

int n;
int teste;


bool viz[100005];
vector<int> G[100005];
vector<int> G2[100005];
int per[100005];

/*
void backt(int nod, int k, int last_color)
{
	viz[nod] = true;
	x[k] = nod;
	k++;

	if (k == 2 * n + 1)
	{
		gasit = true;
		for (int i = 1; i <= 2 * n; i++)
		{
			g << x[i] << ' ';
		}
		g << '\n';
		return;
	}

	for (auto it : G[nod])
	{
		if (gasit)
			return;
		if (nod == 1)
		{
			if (it.culoare == 3)
			{
				if (!viz[it.nod])
				{
					viz[it.nod] = true;
					backt(it.nod, k, it.culoare);
					viz[it.nod] = false;
				}
			}
		}
		else {
			if(!viz[it.nod] && it.culoare != last_color)
			{
				viz[it.nod] = true;
				backt(it.nod, k, it.culoare);
				viz[it.nod] = false;
			}
		}
	}
}

void dfs(int nod, int color)
{
	viz[nod] = 1;
	for (auto it : G[nod])
	{
		if (nod == 1)
		{
			if (it.culoare == 3)
			{
				dfs(it.nod, it.culoare);
			}
		}
		else {
			if (it.culoare != color && !viz[it.nod])
			{
				if (!viz[it.nod])
				{
					dfs(it.nod, it.culoare);
				}
			}
		}
	}
	g << nod << ' ';
}*/

void perechi(int nod, int parinte)
{
	for (auto it : G[nod])
	{
		if (it != parinte)
		{
			perechi(it, nod);
		}
	}

	if (per[nod] == 0 && per[parinte] == 0)
	{
		per[nod] = parinte;
		per[parinte] = nod;
	}
}

vector<int>ans;
void dfs2(int nod)
{
	viz[nod] = 1;
	ans.push_back(nod);
	for (auto it : G2[nod])
	{
		if (!viz[it])
		{
			dfs2(it);
		}
	}
}

int main()
{
	f >> teste;
	/*
	while (teste--)
	{
		f >> n;
		for(int i = 1;i<=2*n;i++)
		{
			G[i].clear();
		}

		for (int i = 1; i <= n-1; i++)
		{
			int x, y;
			f >> x >> y;
			G[x].push_back({ y,1 });
			G[y].push_back({ x,1 });
		}

		for(int i = 1;i <= n-1; i++)
		{
			int x, y;
			f >> x >> y;
			G[x].push_back({ y,2 });
			G[y].push_back({ x,2 });
		}

		for (int i = 1; i <= n; i++)
		{
			int x, y;
			f >> x >> y;
			G[x].push_back({ y,3 });
			G[y].push_back({ x,3 });
		}

		for(int i = 1;i<=2*n;i++)
		{
			viz[i] = false;
		}

		gasit = 0;
		backt(1, 1, 0);

		if (!gasit)
		{
			g << -1 << '\n';
		}
	}*/

	while (teste--)
	{
		f >> n;
		for (int i = 1; i <= 2 * n; i++)
		{
			G[i].clear();
			G2[i].clear();
			viz[i] = false;
			per[i] = 0;
		}
		for (int i = 1; i <= n - 1; i++)
		{
			int x, y;
			f >> x >> y;
			G[x].push_back(y);
			G[y].push_back(x);
		}

		for (int i = 1; i <= n - 1; i++)
		{
			int x, y;
			f >> x >> y;
			G[x].push_back(y);
			G[y].push_back(x);
		}

		for (int i = 1; i <= n; i++)
		{
			int x, y;
			f >> x >> y;
			G2[x].push_back(y);
			G2[y].push_back(x);
		}

		perechi(1, 0);
		perechi(n+1, 0);

		bool invalid = 0;
		for (int i = 1; i <= 2 * n; i++)
		{
			if (per[i] == 0)
			{
				invalid = 1;
			}
			G2[i].push_back(per[i]);
		}

		if (invalid)
		{
			g << -1 << '\n';
			continue;
		}

		ans.clear();

		dfs2(1);

		if (ans.size() != 2 * n)
		{
			g << -1 << '\n';
			continue;
		}
		for(auto it : ans)
		{
			g << it << ' ';
		}
		g << '\n';
	}
}