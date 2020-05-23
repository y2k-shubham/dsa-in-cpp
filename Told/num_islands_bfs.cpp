//Leetcode : https://leetcode.com/problems/number-of-islands/
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
	bool issafe(int i,int j,int n, int m)
	{
		if((i >= 0 && i < n )&&(j >= 0 && j < m))
			return true;
		return false;
	}

	void bfs(int i, int j, vector<vector<char>>& grid,vector<vector<int> >&visited,int n,int m) {
		queue<pair<int,int> >q;
		q.push(make_pair(i,j));
		int x,y;
		while(!q.empty()) {
			pair<int,int>p;
			p = q.front();
			q.pop();
			x = p.first;
			y = p.second;

				if(issafe(x,y+1,n,m) && grid[x][y+1] == '1' && !visited[x][y+1]) {
					visited[x][y+1] = 1;
					q.push(make_pair(x,y+1));
				}
				if(issafe(x+1,y,n,m) && grid[x+1][y] == '1' && !visited[x+1][y]) {
					visited[x+1][y] = 1;
					q.push(make_pair(x+1,y));
				}
				if(issafe(x,y-1,n,m) && grid[x][y-1] == '1' && !visited[x][y-1]) {
					visited[x][y-1] = 1;
					q.push(make_pair(x,y-1));
				}
				if(issafe(x-1,y,n,m) && grid[x-1][y] == '1' && !visited[x-1][y]) {
					visited[x-1][y] = 1;
					q.push(make_pair(x-1,y));
				}

		}

	}

	int numIslands(vector<vector<char>>& grid) {

		int n = grid.size();
		if(n == 0)
			return 0;
		int m = grid[0].size();
		if(m == 0)
			return 0;
		int ctr = 0;
		//  int visited[n][m];
		//memset(visited,0,sizeof(visited[0][0])*n*m);
		vector<vector<int> >visited;
		for(int i = 0; i < n; i++) {
			vector<int>temp;

			for(int k = 0; k < m; k++) {
				temp.push_back(0);
			}

			visited.push_back(temp);
		}

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(grid[i][j] == '1' && !visited[i][j]) {
					visited[i][j] = 1;
					printf("calling bfs on (%d, %d)\n", i, j);
					bfs(i,j,grid,visited,n,m);
					ctr++;
				}
			}
		}
		return ctr;

	}
};

	int main()
	{
		vector<vector<char> >vec;
		int m,n;
		cin>>m>>n;
		for(int i = 0; i < m; i++) {
		vector<char>temp;
		vec.push_back(temp);
		for(int j = 0; j < n; j++) {
			char c;
			cin>>c;
			vec[i].push_back(c);
		//	cout<<vec[i][j]<<" ";
		}
		//cout<<endl;
		}
	/*for(int i = 0; i < m; i++) {
		//vector<char>temp;
		//vec.push_back(temp);
		for(int j = 0; j < n; j++) {
			//char c;
			//cin>>c;
			//vec[i].push_back(c);
			cout<<vec[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	Solution ob;

	int res = ob.numIslands(vec);
	cout<<res<<endl;
	return 0;
}
/*
4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

4 5
1 1 1 1 0
1 1 0 1 0
1 1 0 0 0
0 0 0 0 0

1 159
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/
