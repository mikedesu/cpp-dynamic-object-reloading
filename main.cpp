#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "HelloWorld.h"

#include <memory>

using std::shared_ptr;

int checksum_value = 0;

void checksum_file(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if (file == NULL) {
    printf("Failed to open file\n");
    return;
  }
  checksum_value = 0;

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = new char[size];
  fread(buffer, 1, size, file);

  for (int i = 0; i < size; i++) {
    checksum_value += buffer[i];
  }

  free(buffer);
  fclose(file);
}

int main() {
  const char *filepath = "./HelloWorld.so";
  checksum_file(filepath);
  printf("Checksum: %d\n", checksum_value);

  void *handle = dlopen(filepath, RTLD_NOW | RTLD_LAZY);
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
      handle = dlopen(filepath, RTLD_NOW | RTLD_LAZY);
      if (handle == NULL) {
        printf("dlopen failed: %s\n", dlerror());
        return 1;
      }
    }

    // void (*test)() = dlsym(handle, "test");
    // void *test = (void *) dlsym(handle, "test");
    // void *test = (void *) dlsym(handle, "test");

    // void *(*allocator)() = (void *(*)())dlsym(handle, "allocator");
    HelloWorld *(*allocator)() =
        (HelloWorld * (*)()) dlsym(handle, "allocator");

    // void * allocator(void);
    // allocator = (void *)dlsym(handle, "allocator");
    if (allocator == NULL) {
      printf("dlsym failed: %s\n", dlerror());
      return 1;
    }

    void *(*deallocator)(void *) =
        (void *(*)(void *))dlsym(handle, "deallocator");
    if (deallocator == NULL) {
      printf("dlsym failed: %s\n", dlerror());
      return 1;
    }

    void (*helloprint)(HelloWorld *) =
        (void (*)(HelloWorld *))dlsym(handle, "helloprint");

    shared_ptr<HelloWorld> helloWorld(allocator(), deallocator);

    helloWorld->hello();

    helloprint(helloWorld.get());

    // deallocator(helloWorld);

    sleep(5);
  }

  dlclose(handle);

  return 0;
}
