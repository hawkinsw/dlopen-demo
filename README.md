### POSIX Dynamic Library Loading Demonstration

This is a short program the demonstrates how to load a dynamic library
in a POSIX operating system (OS) and invoke a user-defined function therein.

#### Scenario

In this demo, we are going to play the role of a software architect, Riley, who is engineering
a massive software game named _Age of Control: Machine Expanse_, or _ACME_. The architect's boss,
Zoe, sent us this email:

```
Riley, 

Please add functionality to ACME that allows third-party content developers to print a custom
message to the console when a loot box is opened.

Thanks,
Zoe
```

To implement Zoe's request, we are going to engineer ACME so that a plugin writer can build
a shared library that implements the `loot_box_opened_customization` function. ACME will attempt
to load the plugin and call that function when a player opens a loot box.

Chris(tina) is our customer, the plugin writer. They are going to write the custom functionality
that executes when a loot box is opened.

#### Building

This demo uses the `cmake` system. 

1. Check out the code in a directory named `dlopen-demo`. 
2. In a directory _at the same level_, create a directory named `dlopen-demo-build`.
   Your directory hierarchy should look like this:

   ```
   /path/to/somewhere/
                      dlopen-demo/
                      dlopen-demo-build/
   ```

3. `cd` in to the `dlopen-demo-build` directory.
4. Execute `cmake ../dlopen-demo/`
5. Execute `make`.

#### Running

Once you have built the demo, running it is easy.

1. Make sure that you are in the `dlopen-demo-build` directory.
2. `./acme`.

If everything went according to plan, you should see a message printed to the screen.
Better luck next time you play ACME.
