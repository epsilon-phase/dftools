Table of Contents
=================

  * [Table of Contents](#table-of-contents)
  * [dftools](#dftools)
    * [Introduction](#introduction)
      * [Compiling](#compiling)
    * [Sierpinsky](#sierpinsky)
    * [LSystem](#lsystem)
    * [Geometry](#geometry)
    * [Everything else (As of now)](#everything-else-as-of-now)
      * [Reactions and raws](#reactions-and-raws)
  * [Software used in this](#software-used-in-this)


dftools
============
Tools for Dwarf Fortress. 

It has come to many people's attention that Dwarf Fortress' gui leaves a lot to be desired. There exist plugins that improve its usability these days, but often with intricate or large designs, inputting these proves tedious and therefore is error prone.

These tools are meant to remedy some of these problems.

Introduction
--------
The majority of tools in this repository are aimed at producing comma-separated-values files to use as input for quickfort or dfhack. Some of them are merely tests for functionality that has been written, so most of them probably won't be useful.

Some of them are however interesting and capable of being used for acts of great !!fun!!.

###Compiling

I've been developing this on linux, without any concessions to Windows or Mac, so there may be issues that are unresolved on both platforms, as there *are* issues unresolved on linux, but there aren't any libraries that are required other than a libc that has a unistd.h header with a ``getopt`` function

So typical instructions for linux looks like this:
```
cd dftools
make
```

magical, isn't it?

However there is no ``make install`` or similar utility to place them on your path. If you want that, then please consider moving the files that you want to a directory like `~/bin` which you would then add to the path.

Sierpinsky
----
Have you ever considered using a sierpinsky curve as the basis for your fortress? No, that's not surprising. In any case, it happens to be a starting point for the travelling salesman problem as it tends to provide a decent route for said salesman for no examination of the graph.

Currently the implementation is clumsy and duplicates code in the [rewrite](#LSystem).

LSystem
------------
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

Geometry
----
There are a number of functions meant to handle some simplistic
computational geometry. These are defined normally in
[geometry.h](src/geometry.h). The only ones that are numerically
stable are going to be the ones that have been reimplemented using the
code from Clipper. This is not much now, and there's a lot of work put
into it before switching to using Clipper. Work that lead to
inefficient and nonsensical algorithms that aren't guaranteed to work.

Everything else (As of now)
-------
Some of the headers have documentation. This fell apart some time ago, but the documentation where it exists is most likely still accurate.


###Reactions and raws

Some of the files are meant to read and generate [Dwarf Fortress raw files](http://dwarffortresswiki.org/index.php/DF2014:Raw_file) which the preceeding link can describe in further detail.

There is not currently a great deal of work done with these, because representing the whole of the raw file definitions requires replicating a large number of structures in the game. 

Due to that constraint and the overbearing complexity of the game as a whole, the only currently working example of this is the reaction reader and the material reader. However, the material reader does not handle the actual reading of the material due to a terrible implementation architecture which is too intensive to extend at the moment.


Software used in this
====

* [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
* [Clipper](http://www.angusj.com/delphi/clipper.php)
* [glibc](http://www.gnu.org/software/libc/)(for the getopt function in unistd.h)


