#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/*
 * Programa     : psinfo
 * Autor        : Johan Martinez
 * compilacion	: gcc -Wall -o psinfo psinfo.c
*/
//Definiciones del programa
#define n 50
#define m 350

int main(int argc, char *argv[])
{
  if(argc != 2){
    printf("Error al ingresar el argumento\n");
    return 1;
  }
  char * pch;
  char ln1[m];
  char ruta[n];

  sprintf( ruta,"%s%s%s","/proc/",argv[1],"/status");
  //printf("La ruta del archivo es: %s\n", ruta);
  FILE *fp = fopen(ruta, "rt");
  if(fp==NULL){  
    printf("\nNo se cargo el archivo correctamente\n");
    exit(1);
  }
      char varName[n];
      char varEstado[n];
      char varTam1[n];
      char varTam2[n];
      char varTam3[n];
      char varTam4[n];
      char varNroCambios1[n];
      char varNroCambios2[n];
  for(int i=0;i<53;i++){
      fgets(ln1, m, fp);

      pch = strtok (ln1,":");
      while (pch != NULL)
      {
	if (strcmp("Name",pch) == 0)
  	{
  	  pch = strtok (NULL, ":");
	  strcpy(varName, pch);
 	}
	if (strcmp("State",pch) == 0)
  	{
  	  pch = strtok (NULL, ":");
	  strcpy(varEstado, pch);
 	}
	if (strcmp("VmPeak",pch) == 0)
  	{
  	  pch = strtok (NULL, ":");
	  strcpy(varTam1, pch);
 	}
	if (strcmp("VmExe",pch) == 0)
  	{
  	  pch = strtok (NULL, ":");
	  strcpy(varTam2, pch);
 	}
	if (strcmp("VmData",pch) == 0)
  	{
  	  pch = strtok (NULL, ":");
	  strcpy(varTam3, pch);
 	}
	if (strcmp("VmStk",pch) == 0)
  	{
  	  pch = strtok (NULL, ":");
	  strcpy(varTam4, pch);
 	}
	if (strcmp("voluntary_ctxt_switches", pch) == 0)
  	{
  	  pch = strtok (NULL, ":");
	  int len = strlen(pch);
	  strncpy(varNroCambios1, pch, len-1);
 	}
	if (strcmp("nonvoluntary_ctxt_switches", pch) == 0)
  	{
	  pch = strtok (NULL, ":");
	  strcpy(varNroCambios2, pch);
 	}
	 pch = strtok (NULL, ":");

      }
  }



printf("Nombre del proceso: %s", varName);
printf("Estado: %s", varEstado);
printf("Tamaño total de la imagen de memoria: %s", varTam1);
printf("     Tamaño de la memoria en la región TEXT: %s", varTam2);
printf("     Tamaño de la memoria en la región DATA: %s", varTam3);
printf("     Tamaño de la memoria en la región STACK: %s", varTam4);
strcat(varNroCambios1, "   -");
strcat(varNroCambios1, varNroCambios2);
printf("Número de cambios de contexto realizados (voluntarios - no voluntarios): %s\n", varNroCambios1);

  fclose(fp); 


  return 0;

}

//Implementacion de funciones

