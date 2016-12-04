#include <stdlib.h>
#include <stdio.h>
#include "Bitmap.h"
#include "list.h"
#include "CutBitmap.h"
#include <err.h>
#include "listB.h"
#include "SDLstuff.h"
#include "Matrix.h"
#include "SDL/SDL_image.h"
#include "loadLearningImage.h"
#include "Learning.h"
#include "string.h"

List* cutblockY(int *tab, Bitmap *b, List ** Psize)
{
	int Threshold = 0;
	int white = 0;
	int policeSize = 0;
	unsigned short yMinB = tab[2];
    unsigned short yMaxB = tab[2];
	int isStillBlack = 0;
	int firstblack = 1;
	List* res = empty_list();
	int ContinuePsize = 1;
	for(unsigned short y = tab[2];y <= tab[3];y++)
	{
		for(unsigned short x = tab[0]; x <= tab[1];x++)
		{
			//warnx("X%zu",x);
			unsigned short k= getPixel(b,x,y);
			if(k==0)
			  {isStillBlack = 1;
				//warnx("B: X%hu : Y%hu",x,y);
				white = 0;
				}
		}
		if(isStillBlack)
		{
		  if(ContinuePsize){
		    policeSize += 1;
		  }
			if(firstblack)
			{
				firstblack = 0;
				yMinB = y;
			}
		}
		else
		{
		  	
		  if(policeSize > 3 && Threshold == 0){
				Threshold =2*policeSize; //4
				//warnx("PoliceSize = %d    Y %d",policeSize,y);
				ContinuePsize = 0;
		  }
			if(Threshold!=0)
			{
				white += 1;
				if(white>Threshold || y+1 == tab[2] - tab[3])
				{
					//warnx("WHITETHRESHHHH : W %d    T %d",white,Threshold);
					yMaxB = y;
					int newBloc[4] = {tab[0],tab[1],yMinB,yMaxB};
				  res = push_front(newBloc,res);
					firstblack = 1;
					yMinB = tab[2];
					yMaxB = tab[2];
					//warnx("POLICE SIZE %d...... +%d",policeSize,y);
					newBloc[0] = policeSize;
					policeSize = 0;
					*Psize = push_front(newBloc,*Psize);
					isStillBlack = 0;
					white = 0;
					policeSize = 0;
					Threshold = 0;
					ContinuePsize = 1;
				}
			}
		}
		isStillBlack = 0;
	}
	//*PoliceSize= policeSize;
	//warnx("Psize%d",policeSize);
	//warnx("CUT Y");
	print_list(res);
        return res;
};



List* cutblockX(int* tab, Bitmap *b, int policeSize)
{
  warnx("In Cut X %d",policeSize); 
  //warnx("In Cut X %d",policeSize);
	int Threshold = 1.5*policeSize; 
	int white = 0;
	unsigned short xMinB = tab[0];
	unsigned short xMaxB = tab[0];
	unsigned short isStillBlack = 0;
	unsigned short firstblack = 1;

	//warnx("lel%d",tab[0]);
	//warnx("%d",tab[1]);
	List* res = empty_list();
	for (int x = tab[0]; x<= tab[1] ;x++)
	{

		for(int y = tab[2]; y<=tab[3];y++)
		{
			unsigned short k = getPixel(b,x,y);
			if(k==0&&isStillBlack !=1){
				isStillBlack = 1;
				//warnx("Black");
				white = 0;
			}
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
				//warnx("White %d",white);
				if(white > Threshold)
				{
				  warnx("Adding Element Threshold: %d",Threshold);
					xMaxB =x ;
					int newBloc[4] = {xMinB,xMaxB,tab[2],tab[3]};
				        res = push_front(newBloc,res);
					//list_push_front(result,b);
					firstblack =1;
					xMinB = tab[0];
					xMaxB = tab[0];
					white = 0;
					//Threshold = 0;
				}
				isStillBlack = 0;
			}
		}
	}
        //warnx("poooii%p\n",Poi->next->next);
	//print_list(res);
	//warnx("End of cutx");
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
	 //print_list(res);
	 //warnx("CutLine");
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
		  if (whitep >= Threshold)
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


char *givemechar(List* coord, Bitmap *b)
{
	return 'A';
	struct listB* bmp_list = sendList(coord, b);
    struct listB* test = bmp_list;
    /*while (!is_emptyB(test))
    {
        printBitmap(test->bmp);
        test = test->next;
    }*/
    Mat* matrix =  listbmpToMat(bmp_list);

    //mPrintCompact(matrix,"GIVE ME CHAR");
    //freeB(bmp_list);
    char* res = getCharFromMat(matrix);
    mFree(matrix);
    return res;
	//return "AAAAA"; // DONT ADD THE /n I ADD IT IN THE DoALL fun
}


char* DoAll(Bitmap *b){
	char tz = malloc(4);
	char *s = &tz;
	int tab[4] = {0, b->width - 1, 0, b->height-1}; //IMG SIZE
	List* TmpSize = empty_list();
  List** PsizeL2 = &TmpSize;
	List *L = empty_list();
     L = cutblockY(tab,b,PsizeL2);
	//warnx("psize list");
	List* PsizeL = *PsizeL2;
	//print_list(PsizeL); SURTOUT NE PAS PRINT CETTE PUTAIN DE LISTE
	if(is_empty(L))
    {
		return NULL;
	}

	//print_list(L);
	FILE *f = fopen("OutPut","w");
	while(!is_empty(L))
	{
        int Psize = PsizeL->a;
		PsizeL = PsizeL->next;
  	    int P[4] = {L->a,L->b,L->c,L->d};

		List *L2 = empty_list();
  	    L2 = cutblockX(P,b,Psize);
		//print_list(L2);

	    L = L->next;
        
	    List * L3 = empty_list();
	    while(!is_empty(L2))
        {
		    // GETTING THE LINES
		    int T[4] = {L2->a,L2->b,L2->c,L2->d};
		    L3 = Cutlines(T,b);
		    L2 = L2 -> next;
		    //print_list(L3);
		    while(!is_empty(L3))
            {
			    //Getting the chars
			    int T[4] = {L3->a,L3->b,L3->c,L3->d};
			    List *l = Cutchars(T,b,Psize);
			    RafinedChar(l,b);
			    L3 = L3->next;
			    //END OF GETTING THE CHARS
			    //Adding char
					while(!is_empty(l)){
						fprintf(f,"A");
						l = l->next;
					}
			    //char *s = givemechar(l,b);
          //warnx("RES %s",s);
			    fprintf(f,"\n");
			    //warnx("done adding charsi %d", i);
	    	}
		//END OF GETTING THE LINES
	    }
	    fprintf(f,"\n\n ");
	}
	fclose(f);
    //warnx("WOWO");
	return s;
}

List* CutAll(Bitmap *b)
{
	int tab[4] = {0, b->width - 1, 0, b->height-1}; //IMG SIZE
	List* TmpSize = empty_list();
	List** PsizeL2 = &TmpSize;
	List *L = empty_list();
	L = cutblockY(tab,b,PsizeL2);
	//warnx("psize list");
	List* PsizeL = *PsizeL2;
	List *TOT = empty_list();
	//print_list(PsizeL); SURTOUT NE PAS PRINT CETTE PUTAIN DE LISTE
	if(is_empty(L))
	  {
		return NULL;
	}
	int BlocY = 0;
	int BlocX = 0;
	int LineC = 0;
     
 
	//print_list(L);
	while(!is_empty(L))
	{
	  BlocY += 1;
	  int Psize = PsizeL->a;
	  PsizeL = PsizeL->next;
	  int P[4] = {L->a,L->b,L->c,L->d};

	  List *L2 = empty_list();
	  L2 = cutblockX(P,b,Psize);
		//print_list(L2);

	  L = L->next;
        
	  List * L3 = empty_list();
	  while(!is_empty(L2))
        {
	  BlocX += 1;
		    // GETTING THE LINES
		    int T[4] = {L2->a,L2->b,L2->c,L2->d};
		    L3 = Cutlines(T,b);
		    L2 = L2 -> next;
		    //print_list(L3);
		    while(!is_empty(L3))
            {
	      LineC += 1;
			    //Getting the chars
			    int T[4] = {L3->a,L3->b,L3->c,L3->d};
			    List *l = Cutchars(T,b,Psize);
			    RafinedChar(l,b);
			    L3 = L3->next;
			    TOT = Merge(TOT,l);


	    	}
		//END OF GETTING THE LINES
	    }

	}
	warnx("CutY: %d    , CutX: %d      , LinesC:  %d   ",BlocY,BlocY,LineC);
	return TOT;
}

