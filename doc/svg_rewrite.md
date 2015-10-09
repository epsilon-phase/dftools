#Introduction

`svg_rewrite` is a program meant to produce output in well formatted,
correct, svg(scalable-vector-graphics) from a description of an
L-System and a number of iterations. The main difference between this
program and the previous `rewrite` program is that the svg produced is
the primary feature, and therefore is much cleaner, and placed inside
a "path" element, enhancing the efficiency of the output
significantly.

As was the case previously, `svg_rewrite` takes a json specification
of an L-System, however this format is incompatible with the previous
format, and therefore merits additional explaination.

##Program Arguments

|Option name| Option taken | purpose   |
|-----------|--------------|-----------|
|-c         |filename.csv  |Instructs the program to also produce a csv file with digging patterns inside|
|-o         |output-file.svg|the svg output|
|-r     |rule-file(*.json)|the rule specification|
|-i     |<int> | specifies the number of iterations|

##Rule File specification

The new format for rule specification is significantly more concise,
however it does not allow multiple operations or varying angles to be
present, unlike the previous version of the program.

###Constants
Constants are defined as a single object in this version, rather than a long list. The example below is from the pythagoras tree example.
```
"Constants":{
  "1":0,
  "0":0,
  "[":3,
  "r":2,
  "]":4,
  "l":1
  }
```
The first column (before the colon) inside the definition is the
character which has is assigned the operation in the second(after the
colon). The second column is one of five integers which corresponds to
a single action.

|Integer|action|
|-------|------|
|0|moves forwards|
|1|turns left|
|2|turns right|
|3|push the position and angle of the cursor|
|4|pop the position and angle of the cursor|

###Rewrite rules

Rewrite rules are also defined in a similar way, however the second
column(the value of the key value pair), is a string which replaces
the key over the course of an iteration. So continuing the definition
of the pythagoras tree, the resulting structure is below.

``` "Rewrites":{
    "1":"11",
    "0":"1[l0]0"
	}```


The characters in the strings are however normally either characters
that specify a rewrite rule or a constant, though it is possible to
use other characters, but to no effect. Rewrite rules can share a
character with a constant.

###The axiom

The axiom remains largely unchanged from its previous iteration. That
is to say that it is specified using syntax like `"Axiom":"0"` for the
pythagoras tree. The axiom is simply the initial state of the string prior to being rewritten. So for a pythagoras tree, it starts at rule `"0"`.

###Other options

There are additional options that are important in the definition of an l-system. These are used to specify the angles of turns(for both right and left independantly), the amount the cursor moves forward when moved forwards. Other options may be added as necessary later.

|Option name|arguments|Purpose|
|-----------|---------|-------|
|"left turn"|number  |The angle turned when turning left.|
|"right turn"|number|The angle turned when turning right.|
|"forward step"|number|The amount moved forwards|
