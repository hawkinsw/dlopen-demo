#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>

/**
 * This is a short program that demonstrates how to load a dynamic library
 * in a POSIX-compatible operating system (OS) and invoke a user-defined
 * function therein.
 *
 * The identifiers are named to match the scenario described in the README.md.
 */
int main() {

  bool loot_box_opened = true;

  /**
   * dl_handle will be the way we refer to the dynamic library. It
   * will be used as a parameter to many of the functions that refer
   * to that dynamic library.
   * 
   * It is like an HINSTANCE in Windows.
   */
  void *loot_plugin_handle = NULL;

  /**
   * This is a pointer to the function defined by Chris(tina)
   * in their plugin code that ACME will execute when a player opens a loot box.
   * These signatures are notoriously hard to read. The easiest way to learn how
   * to read a declaration in C/C++ is to 
   * a) learn the inside-out-clockwise-spiral rule (http://c-faq.com/decl/spiral.anderson.html)
   * b) use cdecl's explain functionality (cdecl on *NIX systems or online at https://cdecl.org/)
   *
   * This is a pointer to function that takes no parameters and returns
   * void.
   */
  void (*loot_box_opened_customization)() = NULL;

  /**
   * dlopen is the POSIX equivalent of the LoadLibrary function in Windows.
   * dlopen opens a dynamic library and returns a handle to its contents.
   *
   * This is using some preprocessor defines to load the dynamic library
   * from the same filesystem directory as the application itself.
   */
  loot_plugin_handle = dlopen(PLUGIN_DIR "/libloot_customization.so", RTLD_NOW);

  /**
   * If there is an error loading the loot customization library, then this code
   * will print out an error message and halt the game's execution.
   */
  if (!loot_plugin_handle) {
    printf("Failed to open the plugin that defines loot customization functionality: %s\n", dlerror());
    return 1;
  }

  /**
   * dlsym is the POSIX equivalent of the GetProcAddress function in Windows.
   * dlsym uses a handle to an already-loaded dynamic library and returns the
   * address of a symbol in that library.
   *
   * This is finding the address of a symbol with the `loot_box_opened_customization`.
   * Chris(tina) implements this function in their plugin.
   */
  loot_box_opened_customization = dlsym(loot_plugin_handle, "loot_box_opened_customization");

  /**
   * If there is an error finding that symbol in the dynamically loaded library,
   * then print an error and halt the game. Note that this error-handling code
   * "closes" the library handle. It has to close the handle here because at this
   * point the library was successfully loaded. See below for a description of the
   * dlclose function.
   */
  if (!loot_box_opened_customization) {
    printf("Failed to access to the loot customization functionality: %s\n", dlerror());
    dlclose(loot_plugin_handle);
    return 1;
  }

  /**
   * This is the fun part! 
   *
   * If the player opened a loot box, call Chris(tina)'s customization.
   */
  if (loot_box_opened)
    loot_box_opened_customization();

  /**
   * dlclose is the POSIX equivalent of the FreeLibrary in Windows.
   * dlclose unloads the dynamically loaded library and frees the associated
   * resources. Like Windows, in POSIX systems the dynamic loader uses reference
   * counting when loading a library. Therefore, only the "last" call to dlclose
   * will actually unload the shared library. See https://man7.org/linux/man-pages/man3/dlopen.3.html
   * for more information.
   */
  dlclose(loot_plugin_handle);

  return 0;
}
