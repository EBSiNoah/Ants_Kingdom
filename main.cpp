#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <unistd.h>
#include <map>
#include "cell_class.h"
#include "path_finder.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

vector< vector<Cell> > kingdom_init(void)
{
	int idx=0;
	Cell cells(0);
	vector<Cell> col;
	vector< vector<Cell> > kingdom;
	while(idx<10)
	{
		col.push_back(cells);
		idx++;
	}
	idx=0;
	while(idx<10)
	{
		kingdom.push_back(col);
		idx++;
	}
	return kingdom;
}

vector< vector<int> > binary_kingdom_init(void)
{
	int idx=0;
	vector<int> col;
	vector< vector<int> > binary_kingdom;
	while(idx<10)
	{
		col.push_back(0);
		idx++;
	}
	idx=0;
	while(idx<10)
	{
		binary_kingdom.push_back(col);
		idx++;
	}
	return binary_kingdom;
}

void print_kingdom(vector< vector<Cell> > kingdom)
{
	vector< vector<Cell> >::iterator row;
	vector<Cell>::iterator col;
	
	for(row=kingdom.begin();row!=kingdom.end();row++)
	{
		for(col=(*row).begin();col!=(*row).end();col++)
		{
			switch((*col).property)
			{
				case 0:
					cout<<"    |";
					break;
				case 1:
					cout<<" aQ |";
					break;
				case 2:
					cout<<" aM |";
					break;
				case 3:
					cout<<" aW |";
					break;
				case 4:
					cout<<" "<<(*col).health<<" |";
					break;
				default:
					break;
			}
		}
		cout<<endl;
	}
}

int main()
{
	int date=0;
	int count_obj=0;
	int x_point=0;
	int y_point=0;
	bool queen_ext=false;
	Cell restore_cell;
	vector<int> birth_cycle;
	vector<int> food_coordinate;
	vector<int> queen_coordinate;
	vector< vector<Cell> > kingdom;
	vector< vector<int> > binary_kingdom;
	vector< vector<int> > food_locates;
	srand(time(nullptr));
	
	kingdom=kingdom_init();
	binary_kingdom=binary_kingdom_init();
	
	birth_cycle.push_back(0);//default
	birth_cycle.push_back(0);//queen : 3
	birth_cycle.push_back(1);//male : 3
	birth_cycle.push_back(1);//worker : 8
	birth_cycle.push_back(0);//food : 8
	queen_coordinate.push_back(0);
	queen_coordinate.push_back(0);
	food_coordinate.push_back(0);
	food_coordinate.push_back(0);
	
	//second time loop
	while(date<7200)
	{
		cout<<"date : "<<date<<endl;
		
		if(!queen_ext)//birth of the queen
		{
			birth_cycle[1]=birth_cycle[1]<0?3:birth_cycle[1]-1;
			if(birth_cycle[1]<0 && count_obj<75)
			{
				x_point=rand()%10;
				y_point=rand()%10;
				restore_cell=kingdom[x_point][y_point];
				while(restore_cell.property!=0)
				{
					x_point=rand()%10;
					y_point=rand()%10;
					restore_cell=kingdom[x_point][y_point];
				}
				queen_ext=true;
				kingdom[x_point][y_point]=Cell(1);
				binary_kingdom[x_point][y_point]=1;
				queen_coordinate[0]=x_point;
				queen_coordinate[1]=y_point;
				birth_cycle[1]=4;
				count_obj++;
			}
		}//end of the queen birth
		
		//birth male
		//consider about range, emptieness and fullness
		birth_cycle[2]=birth_cycle[2]<0?3:birth_cycle[2]-1;
		if(birth_cycle[2]<0 && count_obj<75)
		{
			if(queen_coordinate[0]+1<kingdom.size() && kingdom[queen_coordinate[0]+1][queen_coordinate[1]].property==0)
			{
				x_point=queen_coordinate[0]+1;
				y_point=queen_coordinate[1];
				kingdom[x_point][y_point]=Cell(2);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
			else if(queen_coordinate[0]-1>=0 && kingdom[queen_coordinate[0]-1][queen_coordinate[1]].property==0)
			{
				x_point=queen_coordinate[0]-1;
				y_point=queen_coordinate[1];
				kingdom[x_point][y_point]=Cell(2);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
			else if(queen_coordinate[1]+1<kingdom.size() && kingdom[queen_coordinate[0]][queen_coordinate[1]+1].property==0)
			{
				x_point=queen_coordinate[0];
				y_point=queen_coordinate[1]+1;
				kingdom[x_point][y_point]=Cell(2);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
			else if(queen_coordinate[1]-1>=0 && kingdom[queen_coordinate[0]][queen_coordinate[1]-1].property==0)
			{
				x_point=queen_coordinate[0];
				y_point=queen_coordinate[1]-1;
				kingdom[x_point][y_point]=Cell(2);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
		}//end birth male
		
		//birth worker
		//consider about range, emptieness and fullness
		birth_cycle[3]=birth_cycle[3]<0?8:birth_cycle[3]-1;
		if(birth_cycle[3]<0 && count_obj<75)
		{
			if(queen_coordinate[0]+1<kingdom.size() && kingdom[queen_coordinate[0]+1][queen_coordinate[1]].property==0)
			{
				x_point=queen_coordinate[0]+1;
				y_point=queen_coordinate[1];
				kingdom[x_point][y_point]=Cell(3);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
			else if(queen_coordinate[0]-1>=0 && kingdom[queen_coordinate[0]-1][queen_coordinate[1]].property==0)
			{
				x_point=queen_coordinate[0]-1;
				y_point=queen_coordinate[1];
				kingdom[x_point][y_point]=Cell(3);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
			else if(queen_coordinate[1]+1<kingdom.size() && kingdom[queen_coordinate[0]][queen_coordinate[1]+1].property==0)
			{
				x_point=queen_coordinate[0];
				y_point=queen_coordinate[1]+1;
				kingdom[x_point][y_point]=Cell(3);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
			else if(queen_coordinate[1]-1>=0 && kingdom[queen_coordinate[0]][queen_coordinate[1]-1].property==0)
			{
				x_point=queen_coordinate[0];
				y_point=queen_coordinate[1]-1;
				kingdom[x_point][y_point]=Cell(3);
				binary_kingdom[x_point][y_point]=1;
				count_obj++;
			}
		}//end birth worker
		
		//create food
		birth_cycle[4]=birth_cycle[4]<0?8+rand()%5:birth_cycle[4]-1;
		if(birth_cycle[4]<0 && count_obj<75)
		{
			x_point=rand()%10;
			y_point=rand()%10;
			restore_cell=kingdom[x_point][y_point];
			while(restore_cell.property!=0)
			{
				x_point=rand()%10;
				y_point=rand()%10;
				restore_cell=kingdom[x_point][y_point];
			}
			kingdom[x_point][y_point]=Cell(4);
			binary_kingdom[x_point][y_point]=1;
			count_obj++;
		}//end of create food
		
		/*
		x_point=0;
		while(x_point<kingdom.size())
		{
			y_point=0;
			while(y_point<kingdom[x_point].size())
			{
				restore_cell=kingdom[x_point][y_point];
				
				y_point++;
			}
			x_point++;
		}
		*/
		print_kingdom(kingdom);
		cout<<endl;
		sleep(1);
		date++;
	}
	return 0;
}
