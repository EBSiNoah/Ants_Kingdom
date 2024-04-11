#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <cstdlib>
#include <ctime>
#include "path_finder.h"
using namespace std;

int binary_insert(vector< vector<int> > input_vec, vector<int> push_vec)
{
	int sp=0;
	int ep=input_vec.size()-1;
	int mid=0;
	
	while(sp<=ep)
	{
		mid=(sp+ep)/2;
		if(input_vec[mid][1]+input_vec[mid][2] > push_vec[1]+push_vec[2])
		{
			ep=mid-1;
		}
		else if(input_vec[mid][1]+input_vec[mid][2] < push_vec[1]+push_vec[2])
		{
			sp=mid+1;
		}
		else
		{
			break;
		}
	}
	
	if(sp>ep)
	{
		mid=sp;
	}
	
	return mid;
}

vector< vector<int> > A_star_pathfind(vector< vector<int> > input_map, vector<int> coordinate)
{
	int sp_x=coordinate[0];
	int sp_y=coordinate[1];
	int ep_x=coordinate[2];
	int ep_y=coordinate[3];
	int idx=0;
	int next_node_idx=0;
	int change_value_idx=0;
	int res_x=0;
	int res_y=0;
	int mid=0;
	int f_cost=0;
	int h_cost=0;
	vector< vector<int> > neighbors;
	vector< vector<int> > route;
	vector<int> col;//visited, g_cost, h_cost, own coordinate, parent coordinate
	vector<int> current;
	vector<int> restore;
	vector<int> next_current;
	map< vector<int>, vector<int> > info;
	//comfirm
	vector< vector<int> >::iterator row_itr;
	vector<int>::iterator col_itr;
	
	while(idx<7)
	{
		col.push_back(0);
		idx++;
	}
	idx=0;
	
	current.push_back(0);
	current.push_back(0);
	
	//start point initialize
	col[0]=1;
	col[1]=0;
	col[2]=abs(sp_x - ep_x)+abs(sp_y - ep_y);
	col[3]=sp_x;
	col[4]=sp_y;
	col[5]=sp_x;
	col[6]=sp_y;
	neighbors.push_back(col);
	current[0]=sp_x;
	current[1]=sp_y;
	info[current]=col;
	
	while(current[0]!=ep_x || current[1]!=ep_y)//until arrive at goal
	{
		restore.clear();
		restore.push_back(current[0]+1);
		restore.push_back(current[1]);
		restore.push_back(current[0]-1);
		restore.push_back(current[1]);
		restore.push_back(current[0]);
		restore.push_back(current[1]+1);
		restore.push_back(current[0]);
		restore.push_back(current[1]-1);
		
		idx=0;
		while(idx<restore.size())//look for neighbor
		{
			next_current.clear();
			res_x=restore[idx];
			res_y=restore[idx+1];
			next_current.push_back(res_x);
			next_current.push_back(res_y);
			
			//look for range in map size and and visitable
			//look for already visited and is not parent : (info[next_current][0]!=1) && (info[current][5]!=res_x&&info[current][6]!=res_y)
			if( ((res_x>=0&&res_x<input_map.size()) && (res_y>=0 && res_y<input_map[0].size())) && (input_map[res_x][res_y]!=1) )
			{
				if(info[next_current].empty())
				{
					col[0]=0;
					col[1]=info[current][1]+1;
					col[2]=abs(ep_x-res_x) + abs(ep_y-res_y);
					col[3]=res_x;
					col[4]=res_y;
					col[5]=current[0];
					col[6]=current[1];
					info[next_current]=col;
					mid=binary_insert(neighbors, col);
					neighbors.insert(neighbors.begin()+mid, col);
				}
				else if( !info[next_current].empty() && info[next_current][1]>info[current][1]+1 )
				{
					//how can I find this location at neighbors?
					change_value_idx=0;
					while(neighbors[change_value_idx][3]!=res_x || neighbors[change_value_idx][4]!=res_y)
					{
						change_value_idx++;
					}
					neighbors.erase(neighbors.begin()+change_value_idx);
					info[next_current][1]=info[current][1]+1;
					info[next_current][5]=current[0];
					info[next_current][6]=current[1];
					mid=binary_insert(neighbors, info[next_current]);
					neighbors.insert(neighbors.begin()+mid, info[next_current]);
				}
			}
			idx+=2;
		}
		
		//move current
		idx=0;
		while(idx<neighbors.size())
		{
			if(neighbors[idx][0]!=1)
			{
				f_cost=neighbors[idx][1]+neighbors[idx][2];
				break;
			}
			idx++;
		}
		//no way arrive to goal
		if(idx==neighbors.size())
		{
			return route;
		}
		
		h_cost=neighbors[idx][2];
		next_node_idx=idx;
		while(idx<neighbors.size() && neighbors[idx][1]+neighbors[idx][2]==f_cost)
		{
			if(neighbors[idx][2]<h_cost && neighbors[idx][0]==0)
			{
				h_cost=neighbors[idx][2];
				next_node_idx=idx;
			}
			idx++;
		}
		
		current[0]=neighbors[next_node_idx][3];
		current[1]=neighbors[next_node_idx][4];
		neighbors[next_node_idx][0]=1;
		info[current][0]=1;
	}
	
	//route
	route.push_back(current);
	while(current[0]!=sp_x || current[1]!=sp_y)
	{
		res_x=info[current][5];
		res_y=info[current][6];
		current[0]=res_x;
		current[1]=res_y;
		route.insert(route.begin(), current);
	}
	
	neighbors.clear();
	col.clear();
	current.clear();
	restore.clear();
	next_current.clear();
	info.clear();
	
	return route;
}

