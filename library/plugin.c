#include <stdio.h>

__attribute__((visibility("hidden"))) void function_that_plugin_uses_internally(void) {
  printf("This is a user plugin function doing its work.\n");
}
__attribute__((visibility("default"))) void user_plugin_function(void) {
  function_that_plugin_uses_internally();
}
