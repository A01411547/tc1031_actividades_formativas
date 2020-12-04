#ifndef ACT_H
#define ACT_H


unsigned int sumaIterativa(unsigned int n){
  unsigned int suma=0;
  for (int i=1;i<=n;i++){
    suma+=i;

  }
return suma;


}

unsigned int sumaRecursiva(unsigned int n){
  unsigned int total=0;
  if (n!=0){
    total=n+sumaRecursiva(n-1);
    return total;
  }
  return 0;
}

unsigned int sumaDirecta(unsigned int n){
unsigned int fin=((n*(n+1))/2);
return fin;

}
#endif
