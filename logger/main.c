#include <stdio.h>
#include <unistd.h>

int main() {
  FILE *log_file = fopen("../game.log", "r");
  if (log_file == NULL) {
    perror("Error opening log file");
    return 1;
  }

  fseek(log_file, 0, SEEK_END);     // Go to the end of the file
  long file_size = ftell(log_file); // Get the current file size

  printf("Reading logs:\n");
  while (1) {
    sleep(1); // Check every second

    fseek(log_file, 0, SEEK_END);
    long new_file_size = ftell(log_file);

    if (new_file_size > file_size) {
      fseek(log_file, file_size, SEEK_SET); // Go to the last position

      char buffer[1024];
      while (fgets(buffer, sizeof(buffer), log_file) != NULL) {
        printf("%s", buffer); // Display the new line
      }

      file_size = new_file_size; // Update the file size
    }
  }
}
