#include <stdlib.h>
#include <stdio.h>
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include "err.h"

List* cutblockY(int *tab, Bitmap *b, int* PoliceSize)
{
	int Threshold = 0;
	int policeSize = 0;
	int white = 0;
	unsigned short yMinB = tab[2];
	unsigned short yMaxB = tab[2];
	int isStillBlack = 0;
	int firstblack = 1;
	List* res = empty_list();
	for(unsigned short y = tab[2];y <= tab[3];y++)
	{
		for(unsigned short x = tab[0]; x <= tab[1];x++)
		{
			unsigned short k= getPixel(b,x,y);
			if(k==0)
			  {isStillBlack = 1;}
		}
		if(isStillBlack)
		{
			policeSize += 1;
			if(firstblack)
			{
				firstblack = 0;
				yMinB = y;
			}
		}
		else
		{
		  	
			if(policeSize > 3 && Threshold == 0)
				Threshold =4*policeSize;
			if(Threshold!=0)
			{
				white += 1;
				if(white>Threshold || y+1 == tab[2] - tab[3])
				{
					yMaxB = y;
					int newBloc[4] = {tab[0],tab[1],yMinB,yMaxB};
				        res = push_front(newBloc,res);
					firstblack = 1;
					yMinB = tab[2];
					yMaxB = tab[2];
					policeSize = *PoliceSize;
					isStillBlack = 0;
					white = 0;
					policeSize = 0;
					Threshold = 0;
				}
			}
		}
		isStillBlack = 0;
	}
        return res;
};

/*

List* cutblockX(int* tab, Bitmap *b, int* policeSize)
{
  warnx("InCutblockX");
  warnx("%d",tab[0]);
  warnx("%d",tab[1]);
	int Threshold = 4* *policeSize;
	int white = 0;
	unsigned short xMinB = tab[0];
	unsigned short xMaxB = tab[0];
	unsigned short isStillBlack = 0;
	unsigned short firstblack = 1;

	//warnx("%d",tab[0]);
	//warnx("%d",tab[1]);
	List* res = empty_list();

	for (unsigned short x = tab[0]; x<= tab[1] ;x++)
	{
	  //warnx("\nX");
		for(unsigned short y = tab[2]; y<=tab[3];y++)
		{
			unsigned short k = getPixel(b,x,y);
			if(k==0)
				isStillBlack = 1;
		}
		if(isStillBlack)
		{
			if (firstblack)
			{
				firstblack = 0;
				xMinB =x;
			}
			isStillBlack = 0;
		}
		else
	       {
			if(firstblack==0)
			{
				white+= 1;
				if(white > Threshold)
				{
					xMaxB =x ;
					int newBloc[4] = {xMinB,xMaxB,tab[2],tab[3]};
					printf("%d\n", xMinB);
					printf("%d\n",xMaxB);
				        res = push_front(newBloc,res);
					//list_push_front(result,b);
					firstblack =1;
					xMinB = tab[0];
					xMaxB = tab[0];
					white = 0;
					Threshold = 0;
				}
				isStillBlack = 0;
			}
		}
	}
        //warnx("poooii%p\n",Poi->next->next);
	return res;
};

List* Cutlines(int* tab,Bitmap *b)
{
	 unsigned short yMinB = tab[2];
	 unsigned short yMaxB = tab[2];
	 unsigned short x = tab[0];
	 unsigned short isStillBlack = 0;
	 unsigned short firstblack = 1;
	 unsigned short isblack = 0;
	 unsigned short initblock = 0;

	 int height = tab[3] -1;

	 for(unsigned short y = tab[2]; y <= tab[3];y++)
	 {
	 	while(x <= tab[1] && !isblack)
	 	{
	 		unsigned short k = getPixel(b,x,y);
	 		if(k==0)
	 		{
	 			isblack = 1;
	 			isStillBlack =1;
	 		}
	 		x+=1;
	 	}
	 	x = tab[0];
	 	if(isStillBlack&& y != height)
	 	{
	 		if(firstblack)
	 		{
	 			firstblack = 0;
	 			initblock = 1;
	 			yMinB = y;
	 		}
	 	}
	 	else
	 	{
	 		if(initblock)
	 		{
	 			printf("%d\n",yMinB);
	 			printf("%d\n",y);
	 			yMaxB = y;

				int newBloc[4] = {tab[0],tab[1],yMinB,yMaxB};
				Poi = list_push_front(Poi,newBloc);

				
	 			yMinB = tab[2];
	 			yMaxB = tab[2];
	 			isblack = 0;
	 			isStillBlack = 0;
	 			firstblack = 1;
	 			initblock = 0;
	 		}
	 	}
	 	isStillBlack = 0;
	 	isblack = 0;
	 }
	 print_list(Poi);
	 return Poi;
};


List* Cutchars(int *tab, Bitmap *b, int PoliceSize)
{
  short isStillBlack = 0;
  short firstblack = 0;
  float temp = 0.3 * (float)PoliceSize;
  int Threshold = (int)temp;
  unsigned short xMinB = tab[0];
  

  int blackp = 0;
  int whitep = 0;
  for (unsigned short x = tab[0]; x <= tab[1];x++)
    {
      for (unsigned short y = tab[2]; y <= tab[3]; y++)
	{
	  unsigned short k = getPixel(b,x,y);
	  if (k == 0)
	    {
	      isStillBlack = 1;
	      if (!firstblack)
		firstblack = 1;
	    }
	}
      if (firstblack)
	{
	  if (isStillBlack)
	    {
	      if (blackp == 0)//First Time we got black
		{
		  if (whitep > Threshold)
		    {
		      int newBloc[4] = {xMinB,x,tab[2],tab[3]};
		      Poi = list_push_front(Poi,newBloc);
		    }
		  xMinB = x;
		  whitep = 0;
		}
	      blackp += 1;
	    }
	  else
	    {
	      if (blackp > 0)//First Time we got white
		{
		  printf("TAB2 %d\n",tab[2]);
		  printf("TAB3 %d\n",tab[3]);
		  int newBloc[4] = {xMinB,x,tab[2],tab[3]};
		  Poi = list_push_front(Poi,newBloc);
		  
		  blackp = 0;
		  xMinB = x;
		}
	      whitep += 1;
	    }
	  isStillBlack = 0;
	}
    }
  print_list(Poi);
  return Poi;
};



List* CutAll(Bitmap *b)
{
  int tab[4] = {0, b->width - 1, 0, b->height}; //IMG SIZE


  // Poi1 = &list1;
  //Poi2 = &list2;
  
  
  int policeSize;
  cutblockY(tab,b,&policeSize,point);
  printf("%p",point);
  warnx("Before");
  print_list(point);
  

  /*int tab2[4] = {0,799,175,495};
  Poi2 = cutblockX(tab2,b,&policeSize);
   warnx("LOLOL%p\n",Poi2->next->next);
   print_list(Poi2);*/
     /*
  struct list *Poi2 = list2;
  print_list(list2);
  
  Poi1 = Poi1->next;*/
  /*
  while(Poi1->next != 0)
    {
      warnx("/nIn While");
      list2 = Merge(Poi2,cutblockX(Poi1->data,b,&policeSize));
      Poi2 = list2;
      Poi1 = Poi1->next;
    }
  warnx("Wallah");
  print_list(list2);
  return &Poi1;
  }
  */


