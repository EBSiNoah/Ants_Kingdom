#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <unistd.h>
#include <map>
#include <cmath>
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
					if((*col).health<10)
					{
						cout<<" "<<(*col).health<<"  |";
					}
					else
					{
						cout<<" "<<(*col).health<<" |";
					}
					break;
				default:
					break;
			}
		}
		cout<<endl;
	}
}

void print_binary_kingdom(vector< vector<int> > binary_kingdom)
{
	vector< vector<int> >::iterator row;
	vector<int>::iterator col;
	
	for(row=binary_kingdom.begin();row!=binary_kingdom.end();row++)
	{
		for(col=(*row).begin();col!=(*row).end();col++)
		{
			cout<<" "<<(*col)<<" |";
		}
		cout<<endl;
	}
}

vector<int> where_to_go(vector< vector<int> > food_locates, vector< vector<int> > binary_kingdom, vector<int> start_point)
{
	int distance=0;
	int sp_x=0;
	int sp_y=0;
	int ep_x=0;
	int ep_y=0;
	int compare_distance=0;
	int side_idx=0;
	int food_idx=0;
	int mid=0;
	int front=0;
	int behind=0;
	vector<int> arounds;
	vector<int> coordinate_restore;
	vector<int> location;
	vector<int> go_here;
	vector< vector<int> > route;
	vector< vector<int> > sorted_distance;
	
	arounds.push_back(1);
	arounds.push_back(0);
	arounds.push_back(-1);
	arounds.push_back(0);
	arounds.push_back(0);
	arounds.push_back(1);
	arounds.push_back(0);
	arounds.push_back(-1);
	coordinate_restore.push_back(0);
	coordinate_restore.push_back(0);
	sp_x=start_point[0];
	sp_y=start_point[1];
	location.push_back(sp_x);
	location.push_back(sp_y);
	location.push_back(0);
	location.push_back(0);
	go_here.push_back(0);
	go_here.push_back(0);
	
	while(food_idx<food_locates.size())
	{
		side_idx=0;
		while(side_idx<arounds.size())
		{
			ep_x=food_locates[food_idx][0]+arounds[side_idx];
			ep_y=food_locates[food_idx][1]+arounds[side_idx+1];
			
			if( (ep_x>=0 && ep_x<binary_kingdom.size()) && (ep_y>=0 && ep_y<binary_kingdom.size()) && binary_kingdom[ep_x][ep_y]==0 )
			{
				coordinate_restore[0]=ep_x;
				coordinate_restore[1]=ep_y;
				distance=abs(sp_x - ep_x) + abs(sp_y - ep_y);
				if(sorted_distance.size()==0)
				{
					sorted_distance.push_back(coordinate_restore);
				}
				else
				{
					front=0;
					behind=sorted_distance.size()-1;
					while(front<=behind)
					{
						mid=(front+behind)/2;
						compare_distance = abs( sorted_distance[mid][0] - sp_x ) + abs( sorted_distance[mid][1] - sp_y );
						if(compare_distance > distance)
						{
							behind=mid-1;
						}
						else if(compare_distance < distance)
						{
							front=mid+1;
						}
						else
						{
							break;
						}
					}
					if(front > behind)
					{
						mid=front;
					}
					
					sorted_distance.insert(sorted_distance.begin()+mid, coordinate_restore);
				}
			}
			
			side_idx+=2;
		}
		food_idx++;
	}
	
	food_idx=0;
	while(food_idx<sorted_distance.size() && route.size()==0)
	{
		location[2]=sorted_distance[food_idx][0];
		location[3]=sorted_distance[food_idx][1];
		route=A_star_pathfind(binary_kingdom, location);
		food_idx++;
	}
	if(food_idx==sorted_distance.size()||route.size()==0)
	{
		go_here[0]=sp_x;
		go_here[1]=sp_y;
	}
	else
	{
		go_here[0]=route[1][0];
		go_here[1]=route[1][1];
	}
	
	arounds.clear();
	coordinate_restore.clear();
	location.clear();
	route.clear();
	sorted_distance.clear();
	
	return go_here;
}

int main()
{
	int date=0;
	int count_obj=0;
	int x_point=0;
	int y_point=0;
	int side_idx=0;
	int food_idx=0;
	bool queen_ext=false;
	Cell restore_cell;
	vector<int> birth_cycle;
	vector<int> food_coordinate;
	vector<int> queen_coordinate;
	vector<int> arounds;
	vector<int> go_here;
	vector<int> iam_here;
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
	arounds.push_back(1);
	arounds.push_back(0);
	arounds.push_back(-1);
	arounds.push_back(0);
	arounds.push_back(0);
	arounds.push_back(1);
	arounds.push_back(0);
	arounds.push_back(-1);
	iam_here.push_back(0);
	iam_here.push_back(0);
	
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
		if(birth_cycle[2]<0 && count_obj<75 && queen_ext)
		{
			side_idx=0;
			while(side_idx<arounds.size())
			{
				if( (queen_coordinate[0]+arounds[side_idx]>=0 && queen_coordinate[0]+arounds[side_idx]<kingdom.size()) && (queen_coordinate[1]+arounds[side_idx+1]>=0 && queen_coordinate[1]+arounds[side_idx+1]<kingdom.size()) && kingdom[queen_coordinate[0]+arounds[side_idx]][queen_coordinate[1]+arounds[side_idx+1]].property==0 )
				{
					x_point=queen_coordinate[0]+arounds[side_idx];
					y_point=queen_coordinate[1]+arounds[side_idx+1];
					kingdom[x_point][y_point]=Cell(2);
					binary_kingdom[x_point][y_point]=1;
					count_obj++;
					break;
				}
				side_idx+=2;
			}
		}//end birth male
		
		//birth worker
		//consider about range, emptieness and fullness
		birth_cycle[3]=birth_cycle[3]<0?8:birth_cycle[3]-1;
		if(birth_cycle[3]<0 && count_obj<75 && queen_ext)
		{
			side_idx=0;
			while(side_idx<arounds.size())
			{
				if( (queen_coordinate[0]+arounds[side_idx]>=0 && queen_coordinate[0]+arounds[side_idx]<kingdom.size()) && (queen_coordinate[1]+arounds[side_idx+1]>=0 && queen_coordinate[1]+arounds[side_idx+1]<kingdom.size()) && kingdom[queen_coordinate[0]+arounds[side_idx]][queen_coordinate[1]+arounds[side_idx+1]].property==0 )
				{
					x_point=queen_coordinate[0]+arounds[side_idx];
					y_point=queen_coordinate[1]+arounds[side_idx+1];
					kingdom[x_point][y_point]=Cell(3);
					binary_kingdom[x_point][y_point]=1;
					count_obj++;
					break;
				}
				side_idx+=2;
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
			food_coordinate[0]=x_point;
			food_coordinate[1]=y_point;
			food_locates.push_back(food_coordinate);
			kingdom[x_point][y_point]=Cell(4);
			binary_kingdom[x_point][y_point]=1;
			count_obj++;
		}//end of create food
		
		//movement, feed, life cycle, etc
		x_point=0;
		while(x_point<kingdom.size())
		{
			y_point=0;
			while(y_point<kingdom[x_point].size())
			{
				restore_cell=kingdom[x_point][y_point];
				
				if(restore_cell.property==1)//queen
				{
					//life
					kingdom[x_point][y_point].life-=1;
					if(kingdom[x_point][y_point].life<=0 || kingdom[x_point][y_point].health<=0)//dead
					{
						kingdom[x_point][y_point]=Cell(0);
						binary_kingdom[x_point][y_point]=0;
						queen_ext=false;
						count_obj--;
					}
					else//alive
					{
						//feed
						if(!kingdom[x_point][y_point].rest)//ate yesterday
						{
							side_idx=0;
							while(side_idx<arounds.size())
							{
								//in range and is food
								if( (x_point+arounds[side_idx]>=0 && x_point+arounds[side_idx]<kingdom.size()) && (y_point+arounds[side_idx+1]>=0 && y_point+arounds[side_idx+1]<kingdom.size()) && (kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]].property==4) )
								{
									kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]].health-=1;
									kingdom[x_point][y_point].hunger=0;
									kingdom[x_point][y_point].rest=true;
									break;
								}
								side_idx+=2;
							}
							
							if(side_idx==arounds.size())//no food near by
							{
								kingdom[x_point][y_point].hunger+=1;
							}
							else if(side_idx<arounds.size() && kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]].health<=0)//food exist and clean plate
							{
								kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]]=Cell(0);
								binary_kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]]=0;
								count_obj--;
								food_idx=0;
								food_coordinate[0]=x_point+arounds[side_idx];
								food_coordinate[1]=y_point+arounds[side_idx+1];
								while(food_idx<food_locates.size() && food_locates[food_idx]!=food_coordinate)
								{
									food_idx++;
								}
								if(food_locates[food_idx]==food_coordinate)
								{
									food_locates.erase(food_locates.begin()+food_idx);
								}
							}
						}
						else//digestion complete
						{
							kingdom[x_point][y_point].rest=false;
						}
					
						//health
						if(kingdom[x_point][y_point].hunger>=5 && kingdom[x_point][y_point].hunger<10)
						{
							kingdom[x_point][y_point].health-=1;
						}
						else if(kingdom[x_point][y_point].hunger>=10)
						{
							kingdom[x_point][y_point].health=0;
						}
						else if(count_obj>=50 && count_obj<66)
						{
							kingdom[x_point][y_point].health-=2;
						}
						else if(count_obj>=66)
						{
							kingdom[x_point][y_point].health-=3;
						}
					}
				}
				else if(restore_cell.property==2||restore_cell.property==3)//male or worker
				{
					//life
					kingdom[x_point][y_point].life-=1;
					if(kingdom[x_point][y_point].life<=0 || kingdom[x_point][y_point].health<=0)//dead
					{
						kingdom[x_point][y_point]=Cell(0);
						binary_kingdom[x_point][y_point]=0;
						count_obj--;
					}
					else//alive
					{
						//feed
						if(!kingdom[x_point][y_point].rest)//ate yesterday
						{
							side_idx=0;
							while(side_idx<arounds.size())
							{
								//in range and is food
								if( (x_point+arounds[side_idx]>=0 && x_point+arounds[side_idx]<kingdom.size()) && (y_point+arounds[side_idx+1]>=0 && y_point+arounds[side_idx+1]<kingdom.size()) && (kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]].property==4) )
								{
									kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]].health-=1;
									kingdom[x_point][y_point].hunger=0;
									kingdom[x_point][y_point].rest=true;
									break;
								}
								side_idx+=2;
							}
							
							if(side_idx==arounds.size() && kingdom[x_point][y_point].travel_date!=date)//no food near by so move
							{
								kingdom[x_point][y_point].travel_date=date;
								kingdom[x_point][y_point].hunger+=1;
								restore_cell=kingdom[x_point][y_point];
								//let's move
								iam_here[0]=x_point;
								iam_here[1]=y_point;
								go_here=where_to_go(food_locates, binary_kingdom, iam_here);
								kingdom[x_point][y_point]=Cell(0);
								kingdom[go_here[0]][go_here[1]]=restore_cell;
//								cout<<x_point<<", "<<y_point<<" -> "<<go_here[0]<<", "<<go_here[1]<<endl;
//								cout<<endl;
								binary_kingdom[x_point][y_point]=0;
								binary_kingdom[go_here[0]][go_here[1]]=1;
								
							}
							else if(side_idx<arounds.size() && kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]].health<=0)//food exist and clean plate
							{
								kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]]=Cell(0);
								binary_kingdom[x_point+arounds[side_idx]][y_point+arounds[side_idx+1]]=0;
								count_obj--;
								food_idx=0;
								food_coordinate[0]=x_point+arounds[side_idx];
								food_coordinate[1]=y_point+arounds[side_idx+1];
								while(food_idx<food_locates.size() && food_locates[food_idx]!=food_coordinate)
								{
									food_idx++;
								}
								if(food_locates[food_idx]==food_coordinate)
								{
									food_locates.erase(food_locates.begin()+food_idx);
								}
							}
						}
						else//digestion complete
						{
							kingdom[x_point][y_point].rest=false;
						}
					
						//health
						if(kingdom[x_point][y_point].hunger>=5 && kingdom[x_point][y_point].hunger<10)
						{
							kingdom[x_point][y_point].health-=1;
						}
						else if(kingdom[x_point][y_point].hunger>=10)
						{
							kingdom[x_point][y_point].health=0;
						}
						else if(count_obj>=50 && count_obj<66)
						{
							kingdom[x_point][y_point].health-=2;
						}
						else if(count_obj>=66)
						{
							kingdom[x_point][y_point].health-=3;
						}
					}
				}
				
				y_point++;
			}
			x_point++;
		}//end
		
		print_kingdom(kingdom);
		cout<<endl;
//		print_binary_kingdom(binary_kingdom);
//		cout<<endl;
		sleep(1);
		date++;
	}
	return 0;
}
