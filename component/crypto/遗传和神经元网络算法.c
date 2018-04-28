#include<fstream.h>   
 #include <iostream>   
 #include <conio.h>    
 #include <time.h>    
 #include "malloc.h"   
 #include <math.h>   
 #include "stdlib.h"   
    
    
 int n=0;//��ʾ������Ԫ����   
 int o=0;//��ʾ�����Ԫ����   
 int h=0;//��ʾ������Ԫ����   
 double e=0;//��ʾ���   
 double s=0;//����   
 double a=0;//ѧϰ   
 int num=0;//ѵ������   
 double **X;//��ʾ����   
 double *XY1;   
 double *XY3;   
 double *XY2;//��Ÿ�����Ԫ������ֵ   
 double **Y;//������һ�е�����ֵ   
 double **W1,**WChangei;//��ʾ�����Ȩֵ   
 double **W2,**WChangeo;//������һ�е�Ȩֵ   
 double *DX2,*DX3;//��Ÿ������   
 double *IHB,*HOB;//���뷧ֵ   
 ifstream fin("output.txt");   
 ifstream fin2("test2.txt");   
 ifstream fin1("GAdata.txt");   
 double dblErr=0;   
 double **individual,**Tindividual;//��ʼ��ȺT��temp   
 double *bestChrom;//��Ѹ���Ⱦɫ��   
 double *fitness;//����Ⱥ����Ӧ��   
 double minFitness=100.0;   
 double pc;//�������   
 double pm;//�������   
 int popsize;//��Ⱥ��С   
 int lchrom;//Ⱦɫ�峤��   
 int gen;//��ǰ������   
 int maxgen;//���������   
 double sumfitness;//�ܵ���Ӧ��   
 double rl=0;   
 int *b;double *bTemp;//��ʱ����   
 static double oldrand[55];   
 static int jrand;   
 static double rndx2;   
 static int rndcalcflag;   
 void advance_random();   
 int flip(double);rnd(int, int);   
 void randomize();   
 double randomnormaldeviate();   
 double randomperc(),rndreal(double,double);   
 void warmup_random(double);   
 void forward(int);   
 void forward1(int);   
 double randab(double , double );   
    
 void advance_random()  /* ����55������� */   
 {   
     int j1;   
     double new_random;   
     for(j1 = 0; j1 < 24; j1++)   
     {   
         new_random = oldrand[j1] - oldrand[j1+31];   
         if(new_random < 0.0) new_random = new_random + 1.0;   
         oldrand[j1] = new_random;   
     }   
     for(j1 = 24; j1 < 55; j1++)   
     {   
         new_random = oldrand [j1] - oldrand [j1-24];   
         if(new_random < 0.0) new_random = new_random + 1.0;   
         oldrand[j1] = new_random;   
     }   
 }   
    
 int flip(double prob) /* ��һ�����ʲ���0��1 */   
 {   
     if(randab(-1.0,1.0) <= prob)   
         return(1);   
     else   
         return(0);   
 }   
    
 void randomize()  /* �趨��������Ӳ���ʼ������������� */   
 {   
     float randomseed=1.0;   
     int j1;   
     for(j1=0; j1<=54; j1++)   
       oldrand[j1] = 0.0;   
     jrand=0;   
       do   
         {   
                
              printf("���������[0-1]:");   
               scanf("%f", &randomseed);   
          }   
         while((randomseed < 0.0) || (randomseed > 1.0));   
     warmup_random(randomseed);   
 }   
    
 double randomnormaldeviate() /* ���������׼�� */   
 {   
     double t, rndx1;   
     if(rndcalcflag)   
     {   rndx1 = sqrt(- 2.0*log((double) randomperc()));   
         t = 6.2831853072 * (double) randomperc();   
         rndx2 = rndx1 * sin(t);   
         rndcalcflag = 0;   
         return(rndx1 * cos(t));   
     }   
     else   
     {   
         rndcalcflag = 1;   
         return(rndx2);   
     }   
 }   
    
 double randomperc() /*��⺯��random()������ͬ, ����[0,1]֮��һ������� */   
 {   
     jrand++;   
     if(jrand >= 55)   
     {   
         jrand = 1;   
         advance_random();   
     }   
     return((double) oldrand[jrand]);   
 }   
    
 int rnd(int low, int high) /*������low��high֮�����һ���������*/   
 {   
     int i;   
     double randomperc();   
     if(low >= high)   
         i = low;   
     else   
     {   
         i =(int)((randomperc() * (high - low + 1)) + low);   
         if(i > high) i = high;   
     }   
     return(i);   
 }   
    
    
 void warmup_random(double random_seed)  /* ��ʼ�������������*/   
 {   
     int j1, ii;   
     double new_random, prev_random;   
    
     oldrand[54] = random_seed;   
     new_random = 0.000000001;   
     prev_random = random_seed;   
     for(j1 = 1 ; j1 <= 54; j1++)   
     {   
         ii = (21*j1)%54;   
         oldrand[ii] = new_random;   
         new_random = prev_random-new_random;   
         if(new_random<0.0) new_random = new_random + 1.0;   
         prev_random = oldrand[ii];   
     }   
     advance_random();   
     advance_random();   
     advance_random();   
     jrand = 0;   
 }   
    
 void initPop()   
 {   
     fin1>>popsize>>pc>>pm>>maxgen;   
     lchrom=n*h+h*o+h+o;   
     fitness=new double[popsize+1];   
     bestChrom=new double[lchrom+1];   
     individual=new double*[popsize+1];   
     Tindividual=new double*[popsize+1];   
     for(int i=1;i<=popsize;i++)   
     {   
         Tindividual[i]=new double[lchrom+1];   
         individual[i]=new double[lchrom+1];   
         for(int j=1;j<=lchrom;j++)   
         {   
             //individual[i][j]=(double)randomperc();   
             individual[i][j]=randab(-1.0,1.0);   
             cout<<individual[i][j]<<endl;   
         }   
            
     }   
        
     b=new int[popsize+1];   
     bTemp=new double[lchrom+1];   
 }   
 void initPop1()   
 {   
     lchrom=n;   
     fitness=new double[popsize+1];   
     bestChrom=new double[lchrom+1];   
     individual=new double*[popsize+1];   
     Tindividual=new double*[popsize+1];   
     for(int i=1;i<=popsize;i++)   
     {   
         Tindividual[i]=new double[lchrom+1];   
         individual[i]=new double[lchrom+1];   
         for(int j=1;j<=lchrom;j++)   
         {   
             individual[i][j]=randab(-1.0,1.0);   
         }   
            
     }   
        
     b=new int[popsize+1];   
     bTemp=new double[lchrom+1];   
 }   
 void Swap2(int &a,int &b)   
 {   
     int temp;   
     temp=a;   
     a=b;   
     b=temp;   
 }   
    
 void Swap(double &a,double &b)   
 {   
     double temp;   
     temp=a;   
     a=b;   
     b=temp;   
 }   
 int Partition(double a[],int b[],int p,int r)   
 {   
     int i=p,j=r+1;   
     double x=a[p];   
     while(true)   
     {   
         while(a[++i]>x);   
         while(a[--j]<x);   
         if(i>=j) break;   
         Swap(a[i],a[j]);   
         Swap2(b[i],b[j]);   
            
     }   
     a[p]=a[j];   
     a[j]=x;   
     return j;   
 }   
 void QuickSort(double a[],int b[],int p,int r)   
 {   
     if(p<r)   
     {   
         int q=Partition(a,b,p,r);   
         QuickSort(a,b,p,q-1);   
         QuickSort(a,b,q+1,r);   
     }   
 }   
    
 void setFitness()   
 {   
        
         for(int g=1;g<=popsize;g++)   
         {   
                
             for(int i=1;i<=n;i++)   
                 for(int j=1;j<=h;j++)   
                     W1[i][j]=individual[g][(i-1)*h+j];   
    
             for(i=1;i<=h;i++)   
                 for(int j=1;j<=o;j++)   
                     W2[i][j]=individual[g][n*h+(i-1)*o+j];   
                 for(i=1;i<=h;i++)   
                     IHB[i]=individual[g][n*h+h*o+i];   
                 for(i=1;i<=o;i++)   
                     HOB[i]=individual[g][n*h+h*o+h+i];   
    
                 double dblTotal=0.0;   
                 for(int iSample=1;iSample<=num;iSample++)   
                 {   
                     forward(iSample);   
                     dblErr=0.0;   
                     for(i=1;i<=o;i++)   
                     dblErr+=0.5*(Y[iSample][i]-XY3[i])*(Y[iSample][i]-XY3[i]);   
                     dblTotal+=dblErr;//�����   
                 }   
                 fitness[g]=dblTotal;   
                 if(minFitness>dblTotal)   
                 {cout<<"dblTotal"<<dblTotal<<endl;   
                     minFitness=dblTotal;   
                     for(int i=1;i<=lchrom;i++)   
                         bestChrom[i]=individual[g][i];   
                        
                 }   
         }   
         //����   
            
         for(g=1;g<=popsize;g++)   
         b[g]=g;   
         QuickSort(fitness,b,1,popsize);   
         for(g=1;g<=popsize;g++)   
             for(int i=1;i<=popsize;i++)   
             {   
                 if(b[i]==g)   
                 {   
                     for(int j=1;j<=lchrom;j++)   
                     {   
                         bTemp[j]=individual[g][j];   
                         individual[g][j]=individual[i][j];   
                         individual[i][j]=bTemp[j];   
                     }   
                 }   
             }   
    
 }   
 void setFitness1()   
 {   
        
         for(int g=1;g<=popsize;g++)   
         {   
    
             double dblTotal=0.0;   
             forward1(g);   
             for(int i=1;i<=o;i++)   
                 dblTotal=XY3[i];   
                     //�����   
                
             fitness[g]=dblTotal;   
             if(minFitness>dblTotal)   
             {cout<<"dblTotal1"<<dblTotal<<endl;   
                 minFitness=dblTotal;   
                 for(int i=1;i<=lchrom;i++)   
                         bestChrom[i]=individual[g][i];   
                        
             }   
         }   
         //����   
            
         for(g=1;g<=popsize;g++)   
         b[g]=g;   
         QuickSort(fitness,b,1,popsize);   
         for(g=1;g<=popsize;g++)   
             for(int i=1;i<=popsize;i++)   
             {   
                 if(b[i]==g)   
                 {   
                     for(int j=1;j<=lchrom;j++)   
                     {   
                         bTemp[j]=individual[g][j];   
                         individual[g][j]=individual[i][j];   
                         individual[i][j]=bTemp[j];   
                     }   
                 }   
             }   
    
 }   
 void preselect()   
 {   
     sumfitness=0;   
     for(int j=1;j<=popsize;j++)   
         sumfitness+=fitness[j];   
 }   
    
 int select()   
 {   
     double sum, pick;   
     int i;   
     pick=randab(-1.0,1.0);   
     sum = 0;   
     if(sumfitness != 0)   
     {   
         for(i = 1; (sum < pick) && (i <=popsize); i++)   
             sum += (double)(fitness[i]/sumfitness);   
     }   
     else   
         i = rnd(1,popsize);   
     return(i-1);   
 }   
 void crossover(int x1,int x2)//��������   
 {   
     if(flip(pc))   
     {   
         rl=randab(-1.0,1.0);   
     for(int i=1;i<=popsize;i++)   
         individual[x1][i]=individual[x1][i]*rl+individual[x2][i]*(1-rl);   
     for(i=1;i<=popsize;i++)   
         individual[x2][i]=individual[x2][i]*rl+individual[x1][i]*(1-rl);   
     }   
    
 }   
    
    
 void mutation(int x)//����   
 {   
     for(int i=1;i<=lchrom;i++)   
     {   
         if(flip(pm))    
             //individual[x][i]=randomperc();   
             individual[x][i]=randab(-1.0,1.0);   
             //esle individual[temp][i]=1+   
     }   
 }   
    
 void generation()   
 {   
   int mate1, mate2, j = 0;   
   /*  ÿ������ǰ����Ԥѡ */   
   setFitness();   
   preselect();   
   /* ѡ��, ����, ���� */   
   do   
     {   
       /* ��ѡ������� */   
       mate1 = select();   
       mate2 = select();   
    
       /* ����ͱ��� */   
       crossover(mate1,mate2);   
       for(int g=1;g<=lchrom;g++)   
       {   
           Tindividual[j+1][g]=individual[j+1][g];   
           Tindividual[j+2][g]=individual[j+2][g];   
       }   
       mutation(j+1);   
       mutation(j+2);   
       /* ����, ������Ӧ�� */   
       j = j + 2;   
     }   
   while(j < (popsize-1));   
   for(int i=1;i<=popsize;i++)   
       for(int j=1;j<=lchrom;j++)   
           individual[i][j]=Tindividual[i][j];   
    
 }   
 void generation1()   
 {   
   int mate1, mate2, j = 0;   
   /*  ÿ������ǰ����Ԥѡ */   
   setFitness1();   
   preselect();   
   /* ѡ��, ����, ���� */   
   do   
     {   
       /* ��ѡ������� */   
       mate1 = select();   
       mate2 = select();   
    
       /* ����ͱ��� */   
       crossover(mate1,mate2);   
       for(int g=1;g<=lchrom;g++)   
       {   
           Tindividual[j+1][g]=individual[j+1][g];   
           Tindividual[j+2][g]=individual[j+2][g];   
       }   
       mutation(j+1);   
       mutation(j+2);   
       /* ����, ������Ӧ�� */   
       j = j + 2;   
     }   
   while(j < (popsize-1));   
   for(int i=1;i<=popsize;i++)   
       for(int j=1;j<=lchrom;j++)   
           individual[i][j]=Tindividual[i][j];   
    
 }   
    
 double randab(double a, double b)   
 {   
          
   double temp=((float)(rand()-rand())/32767*0.1);   
 if(temp<0) temp=temp*-1.0;   
   return temp;   
 }   
 void init()   
 {   
     srand((unsigned int)time((time_t *)NULL));   
     fin>>n;   
     fin>>o;   
     fin>>h;   
     fin>>e;   
     fin>>s;   
     fin>>a;   
     fin>>num;   
     W1=new double *[n+1];   
     for(int j=1;j<=n;j++)   
     {   
         W1[j]=new double[h+1];   
         for(int i=1;i<=h;i++)   
             W1[j][i]=randomperc();//randab(-1.0,1.0);   
     }   
     W2=new double *[h+1];   
     for(j=1;j<=h;j++)   
     {   
         W2[j]=new double[o+1];   
         for(int i=1;i<=o;i++)   
             W2[j][i]=randomperc();//randab(-1.0,1.0);   
     }   
     IHB=new double[h+1];   
     for(j=1;j<=h;j++)   
         IHB[j]=randomperc();//randab(-1.0,1.0);   
     HOB=new double[o+1];   
     for(j=1;j<=o;j++)   
         HOB[j]=randomperc();//randab(-1.0,1.0);   
        
     WChangei=new double *[n+1];   
     for(j=1;j<=n;j++)   
     {   
         WChangei[j]=new double[h+1];   
         for(int i=1;i<=h;i++)   
             WChangei[j][i]=0.0;   
     }   
     WChangeo=new double *[h+1];   
     for(j=1;j<=h;j++)   
     {   
         WChangeo[j]=new double[o+1];   
         for(int i=1;i<=o;i++)   
             WChangeo[j][i]=0.0;   
     }   
        
        
     DX3=new double[o+1];   
     for(j=1;j<=o;j++)   
         DX3[j]=0.0;   
     DX2=new double[h+1];   
     for(j=1;j<=h;j++)   
         DX2[j]=0.0;   
        
    
        
     XY1=new double[n+2];   
     XY2=new double[h+1];   
     XY3=new double[o+1];   
     X=new double *[num+1];   
     for(j=1;j<=num;j++)   
         X[j]=new double[n+2];   
     Y=new double*[num+1];   
     for(j=1;j<=num;j++)   
         Y[j]=new double[o+1];   
        
 }   
 void readXY()   
 {   
     for(int j=1;j<=num;j++)   
     {   
         for(int i=1;i<=n;i++)   
         {   
             fin>>X[j][i];   
         }   
         for(i=1;i<=o;i++)   
         fin>>Y[j][i];   
     }   
        
 }   
    
 void forward(int iSample)   
 {   
 //���ݵ�iSample��������ǰ�����   
     int i,j;   
     double sum=0.0;   
    
     //���������   
     for(i=1;i<=n;i++)   
         XY1[i]=X[iSample][i];   
        
     //��������   
        
     for(j=1;j<=h;j++){   
         sum=0.0;   
         for(i=1;i<=n;i++)               
             sum+=XY1[i]*W1[i][j];;   
            
         sum-=IHB[j];    
         XY2[j]=1.0/(1.0+exp(-sum));   
     }   
            
     //�������   
     for(j=1;j<=o;j++){   
         sum=0.0;   
         for(i=1;i<=h;i++)   
             sum+=XY2[i]*W2[i][j];   
         sum-=HOB[j];    
         XY3[j]=1.0/(1.0+exp(-sum));   
     }   
        
 }   
 void forward1(int g)   
 {   
 //���ݵ�iSample��������ǰ�����   
     int i;   
     double sum=0.0;   
    
     //���������   
     for(int j=1;j<=lchrom;j++)   
     {   
        
         XY1[j]=individual[g][j];   
    
     }   
     //��������   
        
     for(j=1;j<=h;j++){   
         sum=0.0;   
         for(i=1;i<=n;i++)               
             sum+=XY1[i]*W1[i][j];;   
            
         sum-=IHB[j];    
         XY2[j]=1.0/(1.0+exp(-sum));   
     }   
            
     //�������   
     for(j=1;j<=o;j++){   
         sum=0.0;   
         for(i=1;i<=h;i++)   
             sum+=XY2[i]*W2[i][j];   
         sum-=HOB[j];    
         XY3[j]=1.0/(1.0+exp(-sum));   
     }   
        
 }   
    
 void backward(int iSample)   
 {   
        
     int i,j;   
        
     //������   
     for(i=1;i<=o;i++)   
         DX3[i]=XY3[i]*(1-XY3[i])*(Y[iSample][i]-XY3[i]);   
        
     //�������   
     double sum=0.0;   
     for(j=1;j<=h;j++){   
         sum=0.0;   
         for(i=1;i<=o;i++)   
             sum+=DX3[i]*W2[j][i];   
         DX2[j]=XY2[j]*(1-XY2[j])*sum;   
     }   
     //�������㣭���Ȩ��   
        
     double dblChange;   
     for(j=1;j<=h;j++)   
         for(i=1;i<=o;i++){   
             dblChange=DX3[i]*XY2[j];   
             W2[j][i]=W2[j][i]+s*dblChange+a*WChangeo[j][i];   
             WChangeo[j][i]=dblChange;   
         }   
        
     //�������룭����Ȩ��   
     for(i=1;i<=n;i++)   
         for(j=1;j<=h;j++){   
             dblChange=DX2[j]*XY1[i];   
             W1[i][j]=W1[i][j]+s*dblChange+a*WChangei[i][j];    
             WChangei[i][j]=dblChange;   
         }   
     //�޸���ֵ   
     for(j=1;j<=o;j++)   
         HOB[j]-=s*DX3[j];     
     for(i=1;i<=h;i++)    
         IHB[i]-=s*DX2[i];    
     //�������   
     dblErr=0.0;   
     for(i=1;i<=o;i++)   
         dblErr+=0.5*(Y[iSample][i]-XY3[i])*(Y[iSample][i]-XY3[i]);   
        
 }   
    
 void learn()   
 {   
     int count=0;   
     double dblError=1.0;   
     int iSample=1;   
     double dblTotal;   
     while(dblError>e)   
     {   
         dblTotal=0.0;   
         for(iSample=1;iSample<=num;iSample++){   
             forward(iSample);   
             backward(iSample);   
             dblTotal+=dblErr;//�����   
         }   
         if(dblTotal/dblError>1.04)   
         {//��̬�ı�ѧϰ����   
            s*=0.7;   
            
         }   
         else{   
            s*=1.05;   
         }   
         count++;   
         dblError=dblTotal;   
         ///////////��ʾѵ�����κ����//////   
        
     }   
     cout<<count<<endl;   
 }   
    
    
    
 void getWBFormChrom()   
 {   
     for(int i=1;i<=n;i++)   
         for(int j=1;j<=h;j++)   
                 W1[i][j]=bestChrom[(i-1)*h+j];   
    
     for(i=1;i<=h;i++)   
         for(int j=1;j<=o;j++)   
                 W2[i][j]=bestChrom[n*h+(i-1)*o+j];   
     for(i=1;i<=h;i++)   
             IHB[i]=bestChrom[n*h+h*o+i];   
     for(i=1;i<=o;i++)   
             HOB[i]=bestChrom[n*h+h*o+h+i];   
    
 }   
    
    
 void main()   
 {   
    
    
         //˼�룺����GA��ѵ�������磬����GA�������������Ž�!   
         randomize();   
         init();   
         readXY();   
         initPop();   
         for(int i=1;i<=maxgen;i++)   
             generation();   
         getWBFormChrom();   
         learn();   
         initPop1();   
         for(i=1;i<=1;i++)   
             generation1();   
    
            
    
 }    



  
