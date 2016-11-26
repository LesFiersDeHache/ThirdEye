#include <stdlib.h>
#include <stdio.h>
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include <err.h>
#include "SDLstuff.h"
#include "SDL/SDL_image.h"
List* cutblockY(int *tab, Bitmap *b, int* PoliceSize)
{
	int Threshold = 0;
	int white = 0;
	int policeSize = 0;
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
	*PoliceSize= policeSize; 
        return res;
};



List* cutblockX(int* tab, Bitmap *b, int* policeSize)
{
	int Threshold = 4* *policeSize;
	int white = 0;
	unsigned short xMinB = tab[0];
	unsigned short xMaxB = tab[0];
	unsigned short isStillBlack = 0;
	unsigned short firstblack = 1;

	//warnx("%d",tab[0]);
	//warnx("%d",tab[1]);
	List* res = empty_list();
	for (long x = tab[0]; x<= tab[1] ;x++)
	{
	 //warnx("X  %d",x);
		for(int y = tab[2]; y<=tab[3];y++)
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
 	 List*res = empty_list();
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
	 			yMaxB = y;

				int newBloc[4] = {tab[0],tab[1],yMinB,yMaxB};
				res =push_front(newBloc,res);

				
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
	
	 return res;
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
  List* res= empty_list();
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
		  if (whitep > Threshold+5)
		    {
		      int newBloc[4] = {xMinB,x,tab[2],tab[3]};
		      res = push_front(newBloc,res);
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
		  int newBloc[4] = {xMinB,x,tab[2],tab[3]};
		  res = push_front(newBloc,res);
		  
		  blackp = 0;
		  xMinB = x;
		}
	      whitep += 1;
	    }
	  isStillBlack = 0;
	}
    }
 
  return res;
};

void RafinedChar(List* l2,Bitmap *bmp){//remplace les coordonnées avec des mieu
	int b= 1;
	List *l = l2;
	while(!is_empty(l))
	{
		for(int y = l->c; y<l->d&&b;y++){
			
			for(int x = l->a;x<l->b&&b;x++){
				if(getPixel(bmp,x,y) ==0){
					l->c = y;
					b = 0;
				}
			}
		}
		b = 1;
		l = l->next;
	}
	
	while(!is_empty(l2))
	{
		for(int y = l2->d; y>l2->c&&b;y--){
			
			for(int x = l2->a;x<l2->b&&b;x++){
				if(getPixel(bmp,x,y) ==0){
					l2->d = y;
					b = 0;
				}
			}
		}
		b = 1;
		l2 = l2->next;
	}

}

Bitmap DrawLines(Bitmap *bmp,List *L)
{
  Bitmap k;
  bitmapInit(&k, bmp->width,bmp->height);
  k = *bmp;
  while(!is_empty(L))
    {
      int tab[4] = {L->a,L->b,L->c,L->d};
      for(int i =tab[0] ; i <tab[1];i++)
	{
	  setPixel(&k,i,tab[2],5);
	  setPixel(&k,i,tab[3],5);
	}
      for(int i = tab[2]; i<tab[3];i++)
	{
	  setPixel(&k,tab[0],i,5);
	  setPixel(&k,tab[1],i,5);
	}
      L = L->next;
    }
  return k;
}


List* CutAll(Bitmap *b)
{
  int tab[4] = {0, b->width - 1, 0, b->height-1}; //IMG SIZE
  int Psize = 0;
/*
  List *L = empty_list();
  L = cutblockX(tab,b,&Psize);//CA MARCHE CA
  print_list(L);
  int ta[4] = {L->a,L->b,L->c,L->d};
  List *L2 = empty_list();
  L2 = cutblockY(ta,b,&Psize);

  warnx("LIST2");
  print_list(L2);
  
  List* M = empty_list();
  M = Merge(L, L2);
  print_list(M);

  */
  List *L = empty_list();
  L = cutblockY(tab,b,&Psize);
  List *L2 = empty_list();
  int P[4] = {L->a,L->b,L->c,L->d};
  L2 = cutblockX(P,b,&Psize);
  L = L->next;
  //List *L3 = empty_list();
  while(!is_empty(L))
  {
	int T[4] = {L->a,L->b,L->c,L->d};
	
	L2 = Merge(L2,cutblockX(T,b,&Psize));
	L= L->next;
  }
  //print_list(L2);

  freeList(L);

  List *L3 = empty_list();
  int Q[4] = {L2->a,L2->b,L2->c,L2->d};
  L3 = Cutlines(Q,b);
  L2 = L2->next;
  while(!is_empty(L2))
  {
	int T[4] = {L2->a,L2->b,L2->c,L2->d};

	L3 = Merge(L3,Cutlines(T,b));
	L2 = L2 -> next;
  }
  //print_list(L3);

  freeList(L2);

  List *L4 = empty_list();
  int Y[4] = {L3->a,L3->b,L3->c,L3->d};
  L4 = Cutchars(Y,b,Psize);
  RafinedChar(L4,b);
  L3 = L3->next;
  while(!is_empty(L3))
  {
	int T[4] = {L3->a,L3->b,L3->c,L3->d};
	List *l = Cutchars(T,b,Psize);
	RafinedChar(l,b);
	L4 = Merge(L4,l);
	L3 = L3->next;
  }
  freeList(L3);  

  //print_list(L4);

  /*List *L5 = empty_list();
  int R[4] = {L4->a,L4->b,L4->c,L4->d};
  L5 = Cutlines(R,b);
  warnx("YYYYYY");
  L4 = L4->next;
  while(!is_empty(L4))
  {
	int T[4] = {L4->a,L4->b,L4->c,L4->d};
	warnx("TTTTTTTTTTTT");
	L5 = Merge(L5,Cutlines(T,b));
	L4 = L4->next;
  }

  freeList(L4);
  print_list(L5);*/


  return L4;
  

  //MERGE THE LIST M Here
  /*
  // CA CEST TA FONCTION DAVANT GL
  while(->next != 0)
    {
      warnx("/nIn While");
      list2 = Merge(Poi2,cutblockX(Poi1->data,b,&policeSize));
      nes(Bitmap *bmp,struct list *L)
{
  while(L != 0)
    {
      int tab[4] = L->data;
      for(int i =tab[0] ; i <tab[1];i++)
	{
	  setPixel(bmp,i,tab[2],1);
	  setPixel(bmp,i,tab[3],1);
	}
      for(int i = tab[2]; i<tab[3];i++)
	{
	  setPixel(bmp,tab[0],i,1);
	  setPixel(bmp,tab[1],i,1);
	}
      L = L->next;
    }
}Poi2 = list2;
      Poi1 = Poi1->next;
    }
  warnx("Wallah");
  print_list(list2);*/
  }
 


