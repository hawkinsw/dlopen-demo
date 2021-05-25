#include <stdio.h>

/**
 * This is a function internal to the plugin that does the plugin's actual work.
 * Chris(tina) does not want the ACME player to be able to call this function
 * directly. They label the function with a special attribute to keep this
 * symbol from being exported. The use of the special attribute is akin to
 * the use of the __declspec syntax in Windows.
 */
__attribute__((visibility("hidden"))) void function_that_plugin_uses_internally(void) {
  printf("Uh oh! This loot box was a trap!\n"
         "Sometimes you control the loot "
         "and sometimes the loot controls you!\n");
}

/**
 * This is the function that ACME will call when a player opens a loot box. Chris(tina)
 * defines whatever custom behavior they want. Chris(tina) labels the function with a
 * special attribute to "export" it to ACME. The use of the special attribute is akin to
 * the use of the __declspec syntax in Windows.
 */
__attribute__((visibility("default"))) void loot_box_opened_customization(void) {
  function_that_plugin_uses_internally();
}
