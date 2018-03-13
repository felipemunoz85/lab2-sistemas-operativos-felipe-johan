#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/*
 * Programa     : psinfo
 * Autor        : Johan Martinez - Luis Felipe Muñoz
 * compilacion	: gcc -Wall -o psinfo psinfo.c
*/
//Definiciones del programa
#define n 50
#define m 350

typedef struct {
  char proc_id[n];
  char name[m];
} process_info;

process_info setProcessInfo(FILE *file);

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("Número de argumentos no válido\n");
    return 1;
  }

  char ruta[n];

  /* capturando los PID */
  char processes_id[argc-2][50];
  process_info processes[argc - 2];
  int num_args, args_size = argc-2;
  for(num_args = 2; num_args < argc; num_args++){
    strcpy(processes_id[num_args-2], argv[num_args]);
  }

  int processes_size;

  for(processes_size = 0; processes_size < args_size; processes_size++){
    sprintf( ruta,"%s%s%s","/proc/",processes_id[processes_size],"/status");
    //printf("La ruta del archivo es: %s\n", ruta);
    FILE *fp = fopen(ruta, "rt");
    if(fp==NULL){
      printf("\nNo se cargo el archivo correctamente\n");
      exit(1);
    }

    processes[processes_size] = setProcessInfo(fp);
  }
  int j;

  printf("-- Información recolectada!\n");
  for(j = 0; j < args_size; j++){
    printf("Pid: %s\n...\n", processes[j].proc_id);
    printf("Nombre del proceso: %s\n...\n", processes[j].name);
  }

  return 0;
}

//Implementacion de funciones

process_info setProcessInfo(FILE *file){
  process_info process;
  int i;
  char * pch;
  char ln1[m];

  for(i=0;i<43;i++){
    fgets(ln1, m, file);

    pch = strtok (ln1,":");
    while (pch != NULL) {
      if (strcmp("Pid", pch) == 0){
        pch = strtok (NULL, ":");
        strcpy(process.proc_id, pch);
      }

      if (strcmp("Name", pch) == 0){
        pch = strtok (NULL, ":");
        strcpy(process.name, pch);
        //strcpy(process.name, varName);
      }
       pch = strtok (NULL, ":");
    }
  }
  fclose(file);
  return process;
}
