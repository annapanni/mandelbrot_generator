#include <stdio.h>
#include <complex.h>
#define Finesse 2000.0

int korlatos_e(double complex c){
  double complex zn =  c;
  for (int i = 1; i < 100; i++) {
    zn = zn*zn + c;
    if (cabs(zn)>2){
      return i;
    }
  }
  return -20;
}

int main(void) {
  FILE *f = fopen("mandelbrot.json", "w");
  fprintf(f, "[\n");
  int i, j;
  for (i=0; i<=2*Finesse; i++){
    fprintf(f, "[");
    for (j=0; j<=3*Finesse;j++){
      double complex c = (double)(j-Finesse*2)/Finesse + I*(double)((i-Finesse)/Finesse);
      fprintf(f, "%d,", korlatos_e(c));
    }
    double complex c = (double)(j-Finesse*2)/Finesse + I*(double)((i-Finesse)/Finesse);
    fprintf(f, "%d],\n", korlatos_e(c));
  }
  fprintf(f, "[");
  for (j=0; j<=3*Finesse;j++){
    double complex c = (double)(j-Finesse*2)/Finesse + I*(double)((i-Finesse)/Finesse);
    fprintf(f, "%d,", korlatos_e(c));
  }
  double complex c = (double)(j-Finesse*2)/Finesse + I*(double)((i-Finesse)/Finesse);
  fprintf(f, "%d]\n", korlatos_e(c));


  fprintf(f, "]\n");
  fclose(f);
  return 0;
}
