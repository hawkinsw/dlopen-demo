#include <stdio.h>
#include <dlfcn.h>

int main() {
  void *dl_handle = NULL;

  dl_handle = dlopen("./libplugin.so", RTLD_NOW);
  if (!dl_handle) {
    printf("Failed to open the plugin: %s\n", dlerror());
    return 1;
  }

  void (*user_plugin_function_handle)() = dlsym(dl_handle, "user_plugin_function");
  if (!user_plugin_function_handle) {
    printf("Failed to access to the user's plugin function: %s\n", dlerror());
    dlclose(dl_handle);
    return 1;
  }

  user_plugin_function_handle();

  dlclose(dl_handle);

  return 0;
}
