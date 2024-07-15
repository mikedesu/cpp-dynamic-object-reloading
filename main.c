#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int checksum_value = 0;

void checksum_file(char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if (file == NULL) {
    printf("Failed to open file\n");
    return;
  }
  checksum_value = 0;

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc(size);
  fread(buffer, 1, size, file);

  for (int i = 0; i < size; i++) {
    checksum_value += buffer[i];
  }

  free(buffer);
  fclose(file);
}

int main() {

  char *filepath = "./test.so";
  checksum_file(filepath);
  printf("Checksum: %d\n", checksum_value);

  void *handle = dlopen(filepath, RTLD_LAZY);
  if (handle == NULL) {
    printf("dlopen failed: %s\n", dlerror());
    return 1;
  }

  while (1) {

    int old_checksum_value = checksum_value;

    checksum_file(filepath);
    printf("Checksum: %d\n", checksum_value);

    if (old_checksum_value != checksum_value) {
      printf("Checksum changed, reloading file...\n");
      dlclose(handle);
      handle = dlopen(filepath, RTLD_LAZY);
      if (handle == NULL) {
        printf("dlopen failed: %s\n", dlerror());
        return 1;
      }
    }

    void (*test)() = dlsym(handle, "test");

    if (test == NULL) {
      printf("dlsym failed: %s\n", dlerror());
      return 1;
    }

    test();

    sleep(5);
  }

  dlclose(handle);

  return 0;
}
