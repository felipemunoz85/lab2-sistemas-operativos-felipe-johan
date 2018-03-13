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
  char state[m];
  char vmpeak[m];
  char vmdata[m];
  char vmexe[m];
  char vmstk[m];
  char voluntary_ctxt_switches[m];
  char nonvoluntary_ctxt_switches[m];

} process_info;

process_info setProcessInfo(FILE *file);
void imprimeResultado(process_info info);

char mode[4];

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("Error al ingresar los argumentos!!\n");
    printf("Debe ingresar por lo menos un PID de proceso\n");
    printf("o los parametros -l, -r con la lista procesos\n");
    exit(1);
  } else {
    if(strcmp(argv[1], "-l") == 0){
      strcpy(mode, "list");
    } else if(strcmp(argv[1], "-r") == 0) {
      strcpy(mode, "file");
    } else {
      if(argc == 2){
        strcpy(mode, "read");
      } else {
        printf("Número de argumentos no válidos\n");
        exit(1);
      }
    }
  }

  char ruta[n];
  char filename[m] = "psinfo-report";

  /* capturando los PID */
  char processes_id[argc-2][50];
  process_info processes[argc - 2];
  int num_args, args_size = argc-2;

  if(strcmp(mode, "read") == 0) {
    strcpy(processes_id[0], argv[1]);
    args_size+=1;
  } else {
    for(num_args = 2; num_args < argc; num_args++){
      strcpy(processes_id[num_args-2], argv[num_args]);
      strcat(filename, "-");
      strcat(filename, argv[num_args]);
    }
  }

  strcat(filename, ".info");

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

  if(strcmp(mode, "list") == 0){
    printf("-- Información recolectada!\n");
    for(j = 0; j < args_size; j++){
      printf("Pid: %s\n...\n", processes[j].proc_id);
      printf("Nombre del proceso: %s\n...\n", processes[j].name);
    }
  } else if(strcmp(mode, "file") == 0){
    FILE *fileout = fopen(filename, "w");
    fprintf(fileout, "-- Información recolectada!\n");
    for(j = 0; j < args_size; j++){
      fprintf(fileout, "Pid: %s\n...\n", processes[j].proc_id);
      fprintf(fileout, "Nombre del proceso: %s\n...\n", processes[j].name);
    }
    fclose(fileout);
  } else if(strcmp(mode, "read") == 0){
    imprimeResultado(processes[0]);
  }
  return 0;
}

//Implementacion de funciones
void imprimeResultado(process_info info){
  printf("Nombre del proceso: %s \n", info.name);
  printf("Estado: %s", info.state);
  printf("Tamaño total de la imagen de memoria: %s \n", info.vmpeak);
  printf("Tamaño de la memoria en la región TEXT: %s \n", info.vmexe);
  printf("Tamaño de la memoria en la región DATA: %s \n", info.vmdata);
  printf("Tamaño de la memoria en la región STACK: %s \n", info.vmstk);
  printf("Número de cambios de contexto realizados (voluntarios - no voluntarios): %s  -  %s", info.voluntary_ctxt_switches,  info.nonvoluntary_ctxt_switches);
  printf("\n");
}

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
      }

      if (strcmp("State",pch) == 0){
        pch = strtok (NULL, ":");
        strcpy(process.state, pch);
      }

      if (strcmp("VmPeak",pch) == 0){
        pch = strtok (NULL, ":");
        strcpy(process.vmpeak, pch);
      }

      if (strcmp("VmExe",pch) == 0){
        pch = strtok (NULL, ":");
        strcpy(process.vmexe, pch);
      }

      if (strcmp("VmData",pch) == 0){
          pch = strtok (NULL, ":");
        strcpy(process.vmdata, pch);
      }

      if (strcmp("VmStk",pch) == 0){
          pch = strtok (NULL, ":");
        strcpy(process.vmstk, pch);
      }

      if (strcmp("voluntary_ctxt_switches", pch) == 0){
        pch = strtok (NULL, ":");
        strcpy(process.voluntary_ctxt_switches, pch);
      }
      if (strcmp("nonvoluntary_ctxt_switches", pch) == 0){
        pch = strtok (NULL, ":");
        if(pch != NULL){
          strcpy(process.nonvoluntary_ctxt_switches, pch);
        }
      }
      pch = strtok (NULL, ":");
    }
  }
  fclose(file);
  return process;
}
