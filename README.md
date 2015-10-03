# dftools
Tools for Dwarf Fortress. 

It has come to many people's attention that Dwarf Fortress' gui leaves a lot to be desired. There exist plugins that improve its usability these days but often with intricate or large designs, it proves tedious to create these ingame. These tools are meant to remedy this.

##Introduction
The majority of tools in this repository are aimed at producing comma-separated-values files to use as input for quickfort or dfhack. Some of them are merely tests for functionality that has been written, so most of them probably won't be useful.

Some of them are however interesting and capable of being used for acts of great !!fun!!.

###LSystem generation in rewrite.

Rewrite is an utility that is capable of taking a json specification
and iterating over lsystems quickly. These lsystems are among the
easiest to write of fractals, and are quite capable of producing a
lovely tree as in pythagoras tree, or a dragon curve, which is
space-filling and wonderful. In principle it is possible to create
lsystems for many different sorts of curves.

The [main documentation](doc/rewrite.md) may be fragmentary and confused at the moment, but it contains a whole example and nearly everything that needs to be known in order to write your own.

Invocation of this utility works as such
```
./rewrite -i <iterations> -r <l-system-spec> -o <output> -s scale
```

The `-i` option controls the number of times that the system is iterated into. The [pythagoras-tree](pythagoras-tree.json) takes about 4 to look recognizable. The [dragon-curve](dragon-curve.json) takes about ten to look recognizable.

The `-r` option controls which file is read for specification

The `-o` option controls the file that it writes to.

The `-s` controls the scale, which is the amount that each "forward" instruction moves the cursor forwards.

###Everything else (As of now)

Some of the headers have documentation. This fell apart some time ago, but the documentation where it exists is most likely still accurate.
