#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "entity.h"

 void draw_map();
 void init_gibi();
 void create_gibi();
 void create_flowers();
 void init_flowers();
 void move_shadok(char );
 void move_gibi();
 int exist_flowers();
 void game_over();
	int main()
	{
	   
	   create_flowers();
	   create_gibi();
	   char c;
	  draw_map();
	   while ((c!=27&&steps)&&shadok.transistors<=num_of_transistors)
	    {
          c=getchar();
          move_shadok(c);
          move_gibi();
          if(!exist_flowers()) create_flowers();
          draw_map();
          
        }
      game_over();
	 return 0;
	}

 void draw_map()
  {
	  system("clear");
	   printf(" Transistors: %d\n Steps: %d\n\n",shadok.transistors,steps);
	    init_gibi();
	  init_flowers();
	  map[shadok.y] [shadok.x] = 20;
	  for(unsigned int i=0; i<SIZE_MAP_Y; i++)
	  {
		  printf("\t");
	   for(unsigned int j=0; j<SIZE_MAP_X; j++)
	    {
			
			if(!map[i][j]) printf(" . ");
			if(map[i][j]>=1&&map[i][j]<=9) printf("(%d)",map[i][j]);
			if(map[i][j]==20) printf(" X ");
			if(map[i][j]==21) printf(" Г ");
			if(j==SIZE_MAP_X-1) printf("\n");
		}
		}
  }	

void init_gibi()
 {
	 for(unsigned int i=0; i<C_GIBI;i++)
		  map[gibi[i].y][gibi[i].x]=21;
 }

  void create_gibi()
   {
	   
	  srand(time(NULL));
	   for (unsigned int i=0; i<C_GIBI;i++)
	    {   
			
			unsigned prev_x=gibi[i].x,prev_y=gibi[i].y;
			for(unsigned j=0;j<C_FLOWER; j++)
			{
			while(prev_x==gibi[i].x||prev_y==gibi[i].y||(gibi[i].x==flower[j].x&&gibi[i].y==flower[j].y))
			{
			  gibi[i].x=rand()%SIZE_MAP_X;
			  gibi[i].y=rand()%SIZE_MAP_Y;
		    }
		    }
		}
   }
 
 void create_flowers()
  {
	srand(time(NULL));
	   for (unsigned int i=0; i<C_FLOWER;i++)
	    { 
			unsigned prev_x=flower[i].x,prev_y=flower[i].y;
			for(unsigned int j=0; j<C_GIBI; j++)
			 {
				while(prev_x==flower[i].x||prev_y==flower[i].y||(flower[i].x==gibi[j].x&&flower[i].y==gibi[j].y) )
				{
					flower[i].x=rand()%SIZE_MAP_X;
					flower[i].y=rand()%SIZE_MAP_Y;
					flower[i].transistors=rand()%8+1;
					flower[i].exist=1;
				} 
		     }
	    }
  }
 
 void init_flowers()
  {
	  for(unsigned int i=0; i<C_FLOWER; i++)
	 if(flower[i].exist)  map[flower[i].y][flower[i].x]=flower[i].transistors;
  }

 void move_shadok(char dir)
  {

	  
	  map[shadok.y][shadok.x]=0; 
	  switch(dir)
	   {
		   case 'w':
		   case 'W':
		    if(shadok.y)
		        { 
				  shadok.y--; 
				  steps--;
				}
		   break;
		   
		   case 'S':
		   case 's':
		   if(shadok.y!=SIZE_MAP_Y-1) 
		        {
				  shadok.y++; 
				  steps--;
				}
		   break;
		   
		   case 'A':
		   case 'a':
		   if(shadok.x) 
		        {
				 shadok.x--; 
				 steps--;
		        }
		   break;
		   
		   case 'D':
		   case 'd':
		   if(shadok.x!=SIZE_MAP_X-1) 
		      {
			   shadok.x++; 
			   steps--;
		      }
		   break; 
		   
		   case 'Q':
		   case 'q':
		    if(shadok.x>=0&&shadok.y>0)
		       {
				   shadok.x--;
				   shadok.y--;
				   steps--;
			   }
		   break;
		   
		   case 'E':
		   case 'e':
		    if(shadok.x<SIZE_MAP_X&&shadok.y>0)
		       {
				   shadok.x++;
				   shadok.y--;
				   steps--;
			   }
		   break;
		   
		   case 'Z':
		   case 'z':
		    if(shadok.x>0&&shadok.y<SIZE_MAP_Y)
		       {
				   shadok.x--;
				   shadok.y++;
				   steps--;
			   }
		   break;
		   
		   case 'X':
		   case 'x':
		    if(shadok.x<SIZE_MAP_X&&shadok.y<SIZE_MAP_Y)
		       {
				   shadok.x++;
				   shadok.y++;
				   steps--;
			   }
		   break;
	   }
	    srand(time(NULL));
	    for(unsigned int i=0; i<C_FLOWER; i++)
	     {
	      if (shadok.x==flower[i].x&&shadok.y==flower[i].y)
	       {
			shadok.transistors+=flower[i].transistors;
			flower[i].transistors=0;
			flower[i].x=rand()%SIZE_MAP_X;
			flower[i].y=rand()%SIZE_MAP_Y;
			flower[i].transistors=rand()%8+1;
		   }
         }
	 
  }

  void move_gibi()
   {
	   for(unsigned int i=0; i<C_GIBI; i++)
	     {
			 double low_way=1000.;
			 unsigned low_x,low_y;
			 
			 
			 for(unsigned int j=0;j<C_FLOWER; j++)
			   {
				 if((sqrt( pow(((double)gibi[i].x-(double)flower[j].x),2)+pow(((double)gibi[i].y-(double)flower[j].y),2) )<low_way)&&flower[j].exist)
				  {
				   low_way=sqrt( pow(((double)gibi[i].x-(double)flower[j].x),2)+pow(((double)gibi[i].y-(double)flower[j].y),2) );
				   low_x=flower[j].x;
				   low_y=flower[j].y;
			      } 
			     
			  }
			 
			 map[gibi[i].y][gibi[i].x]=0;
			 
			  if(gibi[i].x>low_x&&gibi[i].y>low_y)
			   {
				  if(map[gibi[i].y-1][gibi[i].x-1]!=21&&map[gibi[i].y-1][gibi[i].x-1]!=20)
				   {
				    gibi[i].x--;
				    gibi[i].y--;
			       }
			   }
			   else
			   if(gibi[i].x<low_x&&gibi[i].y<low_y)
			   {
				 if(map[gibi[i].y+1][gibi[i].x+1]!=21&&map[gibi[i].y+1][gibi[i].x+1]!=20)
				   { 
				     gibi[i].x++;
				     gibi[i].y++;
				   }
			   }
			   else
			    if(gibi[i].x>low_x&&gibi[i].y<low_y)
			   {
				    if(map[gibi[i].y+1][gibi[i].x-1]!=21&&map[gibi[i].y+1][gibi[i].x-1]!=20)
				   { 
				     gibi[i].x--;
				     gibi[i].y++;
				   }
			   }
			  else
			   if(gibi[i].x<low_x&&gibi[i].y>low_y)
			   {
				  if(map[gibi[i].y-1][gibi[i].x+1]!=21&&map[gibi[i].y-1][gibi[i].x+1]!=20)
				   { 
					   gibi[i].x++;
					   gibi[i].y--;
				   }
			   }
			   else
			   if(gibi[i].x==low_x&&gibi[i].y>low_y)
			    {
					if(map[gibi[i].y-1][gibi[i].x]!=21&&map[gibi[i].y-1][gibi[i].x]!=20)
				   { 
				     gibi[i].y--;
				   }
			    }
			   else
			   if(gibi[i].x==low_x&&gibi[i].y<low_y)
			    {
					if(map[gibi[i].y+1][gibi[i].x]!=21&&map[gibi[i].y+1][gibi[i].x]!=20)
				     gibi[i].y++;
			    }
			   else
			    if(gibi[i].y==low_y&&gibi[i].x<low_x)
			     {
					 if(map[gibi[i].y][gibi[i].x+1]!=21&&map[gibi[i].y][gibi[i].x+1]!=20)
				      gibi[i].x++;
			     }
			   else
			    if(gibi[i].y==low_y&&gibi[i].x>low_x)
			    {
				   if(map[gibi[i].y][gibi[i].x-1]!=21&&map[gibi[i].y][gibi[i].x-1]!=20)
				    gibi[i].x--;
			    }
			    
			    for(unsigned j=0;j<C_FLOWER; j++)
			     {
					 if(gibi[i].x==flower[j].x&&gibi[i].y==flower[j].y&&flower[j].exist)
					 flower[j].exist=0;
				 }
		 }
		
   }
   
   int exist_flowers()
    {
		int ex=0;
		for(unsigned int i=0; i<C_FLOWER; i++)
			   if(flower[i].exist) ex++;
      return ex;
	}

void game_over()
 {
	
	 if(steps==0)
	  {
		   system("clear");
		  if(shadok.transistors>=num_of_transistors)
		    {
				printf("\n\n\n\n\t\t   YOU WIN!!!   \t\t\n\n");
			}
			else
			{
				printf("\n\n\n\n\t\t    YOU LOOSE...   \t\t\n\n");
			}
	  }
	  else
	  {
		if(shadok.transistors>=num_of_transistors)
		    {
				 system("clear");
				printf("\n\n\n\n\t\t   YOU WIN!!!   \t\t\n\n");
			}  
	  }
 }
