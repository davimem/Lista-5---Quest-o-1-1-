#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef double (*equacoes)();
#define N 3
#define b 1/10.
#define g 1/15.

double S(double x, double y[N])
{
  return (-b*y[0]*y[1]);       
}

double I(double x, double y[N])
{
  return (-g*y[1] + b*y[0]*y[1]);   
}

double R(double x, double y[N])
{
  return g*y[1];      
}

double* LeVetor(char *nome,int *m)
{
  FILE *fp;
  int i;
  double *v;
  
  fp=fopen(nome,"r");
  
  fscanf(fp,"%d",m);

  v=malloc(sizeof(double) * (*m));
  
  for(i=0;i<*m; i++)
  {
    fscanf(fp,"%lf",&v[i]);
  }
  
  return v;
}

void RungeKutta2Ord(double x, double *y, double h, double xi, double xf)
{
  int i;
  double *k1=calloc(N, sizeof(double));
  double *k2=calloc(N, sizeof(double));
  double *k3=calloc(N, sizeof(double));
  double *k4=calloc(N, sizeof(double));
  double *yp=calloc(N, sizeof(double));
  double *ypp=calloc(N, sizeof(double));
  equacoes f[N]={S,I,R};

  for(x=xi; x<xf; x+=h)
  {
  
    for(i=0; i<N; i++)
    {
      k1[i]=h*f[i](x,y);
      yp[i]=y[i]+k1[i]/2;
    }
    
    for(i=0; i<N; i++)
    {
      k2[i]=h*f[i](x+h/2,yp);
      ypp[i]=y[i]+k2[i]/2;
    }
    
    for(i=0; i<N; i++)
    {
      k3[i]=h*f[i](x+h/2,ypp);
      yp[i]=y[i]+k3[i];
    }
    
    for(i=0; i<N; i++)
    {
      k4[i]=h*f[i](x+h,yp);
    }
    
    for(i=0; i<N; i++)
    {
      y[i]+=1/6.*(k1[i]+2*k2[i]+2*k3[i]+k4[i]);
    }
    
    printf("%g %g %g %g\n", x, y[0], y[1], y[2]);
  }
}

int main(int argc, char *argv[]) 
{
  int m;
  double *y, x, xi, xf, h;
  y=LeVetor("ini.dat",&m);
  xi=0;
  xf=200;
  h=0.1;
  
  RungeKutta2Ord(x, y, h, xi, xf);
}