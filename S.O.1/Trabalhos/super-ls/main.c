#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <libgen.h>
#include <stdbool.h>

// Structure to store file information
typedef struct stat Stat;

typedef struct fileInfo
{
  char name[1024];
  bool is_directory;
  Stat file_stat;
  int depth;
} FileInfo;

// Prototypes
void print_dir_header(const char *nameDir, int depth);
void format_date(char *buffer, size_t size, time_t timestamp);
void print_file_info(const FileInfo *file_info, const char *parent_name);
void list_directory_sorted(const char *dir_path, int depth, int parent_depth, FileInfo *files, int *file_count);

void print_dir_header(const char *nameDir, int depth)
{
  printf("\033[1;34m");
  for (int i = 0; i < depth; ++i)
  {
    printf("  ");
  }
  printf("/%-29s\033[0m", nameDir);
}

void format_date(char *buffer, size_t size, time_t timestamp)
{
  struct tm *tm_info;
  tm_info = localtime(&timestamp);
  strftime(buffer, size, "%b %d %H:%M", tm_info);
}

// Function to print information about a file or directory
void print_file_info(const FileInfo *file_info, const char *parent_name)
{
  char filename[1024];
  strncpy(filename, file_info->name, sizeof(filename) - 1);
  filename[sizeof(filename) - 1] = '\0'; // Ensure null-termination

  const char *basename_result = basename(filename);

  if (file_info->is_directory)
  {
    if (parent_name == NULL)
    {
      print_dir_header(basename_result, file_info->depth);
    }
    else
    {
      printf("\033[1;36m%-30s\033[0m", basename_result);
    }
  }
  else
  {
    for (int i = 0; i < file_info->depth; ++i)
    {
      printf("  ");
    }
    printf("%-30s", basename_result);
  }

  printf("%-16lo\t", file_info->file_stat.st_ino);

  // Print file size in bytes, kilobytes, or megabytes
  long size = file_info->file_stat.st_size;
  if (size >= 1024 * 1024)
  {
    printf("%7.2f MB", size / (1024.0 * 1024));
  }
  else if (size >= 1024)
  {
    printf("%7.2f KB\t", size / 1024.0);
  }
  else
  {
    printf("%7ld B\t", size);
  }

  struct passwd *pw = getpwuid(file_info->file_stat.st_uid);

  printf("%-12s", pw ? pw->pw_name : "..");

  char date_buffer[20];
  format_date(date_buffer, sizeof(date_buffer), file_info->file_stat.st_mtime);
  printf("%-16s", date_buffer);

  printf("\n");
}

// Function to list files and directories in a given directory up to a certain depth
void list_directory_sorted(const char *dir_path, int depth, int parent_depth, FileInfo *files, int *file_count)
{
  if (depth == 0)
  {
    return;
  }

  DIR *dir;
  struct dirent *entry;

  // Open the directory
  if ((dir = opendir(dir_path)) == NULL)
  {
    perror("opendir");
    exit(EXIT_FAILURE);
  }

  // Read entries in the directory
  while ((entry = readdir(dir)) != NULL)
  {
    // Create a path for the current entry
    char entry_path[1024];
    snprintf(entry_path, sizeof(entry_path), "%s/%s", dir_path, entry->d_name);

    // Retrieve information about the entry
    Stat entry_stat;
    if (stat(entry_path, &entry_stat) == -1)
    {
      perror("stat");
      exit(EXIT_FAILURE);
    }

    // Check if the entry is a directory
    if (S_ISDIR(entry_stat.st_mode))
    {
      // Ignore special directories "." and ".."
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      {
        continue;
      }

      // List information about directories
      strncpy(files[*file_count].name, entry_path, sizeof(files[*file_count].name));
      files[*file_count].is_directory = true;
      files[*file_count].file_stat = entry_stat;
      files[*file_count].depth = parent_depth; // Use parent_depth for directory depth
      (*file_count)++;

      // Recursively list subdirectories with decreased depth
      list_directory_sorted(entry_path, depth - 1, parent_depth + 1, files, file_count);
    }
    else
    {
      // List information about files
      strncpy(files[*file_count].name, entry_path, sizeof(files[*file_count].name));
      files[*file_count].is_directory = false;
      files[*file_count].file_stat = entry_stat;
      files[*file_count].depth = parent_depth; // Use parent_depth for file depth
      (*file_count)++;
    }
  }

  // Close the directory
  closedir(dir);
}

int main(int argc, char *argv[])
{
  // Check for the correct number of command-line arguments
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <directory or file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Get the path and depth from the command-line arguments
  char *path = argv[1];
  int depth = 2;

  // Print information for the given path
  printf("Listing information for: %s\n\n", path);
  printf("%-30s%-8s\t\t\t    %-8s\t%-8s    %-8s\n", "Name", "Inode", "Size", "Owner", "Last Modified");
  printf("\n");

  // Allocate space for FileInfo structs
  FileInfo *files = malloc(1024 * sizeof(FileInfo));
  if (!files)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  int file_count = 0;

  // Retrieve information about the given path
  Stat path_stat;
  if (stat(path, &path_stat) == -1)
  {
    perror("stat");
    exit(EXIT_FAILURE);
  }

  // Check if the path is a directory
  if (S_ISDIR(path_stat.st_mode))
  {
    // If it's a directory, list its contents up to the specified depth
    list_directory_sorted(path, depth, 0, files, &file_count);
  }
  else
  {
    // If it's a file, print its information
    strncpy(files[file_count].name, path, sizeof(files[file_count].name));
    files[file_count].is_directory = false;
    files[file_count].file_stat = path_stat;
    files[file_count].depth = 0;
    file_count++;
  }

  // Print information for each file or directory
  for (int i = 0; i < file_count; i++)
  {
    if (files[i].is_directory)
    {
      print_file_info(&files[i], NULL);
    }
    else
    {
      print_file_info(&files[i], basename(files[i].name));
    }
  }

  // Free allocated memory
  free(files);

  return 0;
}
