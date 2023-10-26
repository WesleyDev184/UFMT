#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

#define MAX_PATH 4096
#define MAX_DEPTH 1

struct ArqInfo
{
  char name[MAX_PATH];
  struct stat st;
  int espacamento;
};

typedef struct ArqInfo ArqInfo;

void listFiles(const char *dirPath, int depth, ArqInfo *fileInfo);
void printFile(const ArqInfo *fileInfo, int depth);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("[ERROR] Uso: %s <diretorio ou arquivo>\n", argv[0]);
    exit(1);
  }

  const char *caminho = argv[1];
  struct stat main_stat;
  int profundidade = 0;
  int numArquivos = 0;

  ArqInfo mainFileInfo; // Variável para armazenar informações do arquivo/diretório principal.

  printf("%-25s %-15s %-20s %-25s %-20s\n\n", "Nome", "I-node", "Tamanho (bytes)", "Data de Modificação", "Proprietário");

  if (lstat(caminho, &main_stat) < 0)
  {
    perror("Erro ao obter informações do arquivo/diretório");
    exit(1);
  }

  strncpy(mainFileInfo.name, caminho, MAX_PATH);
  mainFileInfo.st = main_stat;
  mainFileInfo.espacamento = profundidade;

  if (S_ISDIR(main_stat.st_mode))
  {
    listFiles(caminho, profundidade, &mainFileInfo);
  }
  else
  {
    // É um arquivo, então exiba suas informações.
    printFile(&mainFileInfo, profundidade);
  }

  return 0;
}

void printFile(const ArqInfo *fileInfo, int depth)
{
  for (int i = 0; i < depth; i++)
  {
    printf("   ");
  }

  printf("%s", S_ISDIR(fileInfo->st.st_mode) ? "/" : ""); // Adiciona '/' se for um diretório
  printf("%-25s %ld %8ldB", fileInfo->name, fileInfo->st.st_ino, fileInfo->st.st_size);

  char date_buffer[20];
  strftime(date_buffer, sizeof(date_buffer), "%b %d %H:%M", localtime(&fileInfo->st.st_mtime));
  printf("%25s", date_buffer);

  struct passwd *pw = getpwuid(fileInfo->st.st_uid);
  printf("%12s\n", pw ? pw->pw_name : "..");
}

void listFiles(const char *dirPath, int depth, ArqInfo *fileInfo)
{
  DIR *d;
  struct dirent *dir;
  struct stat st;
  d = opendir(dirPath);

  if (!d)
  {
    perror("Erro ao abrir diretório");
    return;
  }

  while ((dir = readdir(d)) != NULL)
  {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
    {
      continue;
    }

    char fullPath[MAX_PATH];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, dir->d_name);

    if (lstat(fullPath, &st) < 0)
    {
      perror("Erro ao obter informações do arquivo/diretório");
      return;
    }

    ArqInfo childFileInfo; // Variável para armazenar informações do arquivo/diretório filho.
    strncpy(childFileInfo.name, dir->d_name, MAX_PATH);
    childFileInfo.st = st;
    childFileInfo.espacamento = depth;

    printFile(&childFileInfo, depth); // Exibe as informações do arquivo/diretório.

    if (S_ISDIR(st.st_mode) && depth < MAX_DEPTH)
    {
      listFiles(fullPath, depth + 1, &childFileInfo);
    }
  }

  closedir(d);
}
