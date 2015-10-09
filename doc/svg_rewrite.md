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

```
   "Rewrites":{
    "1":"11",
    "0":"1[l0]r0"
	}
```


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
|"Custom Operations"|complex type|Used to specify more complicated operations, such as turns with different angles, or compound operations|

###Custom Operations

With the inclusion of this feature, this piece of software is as feature complete as the previous one.

This feature allows for definition of additional constants. Custom
constant operations start at five and continue for the rest of the
range of 32 bit integer types. They are defined in another section
which is not necessary for most l-systems.

``
  "Custom Operations":{
  "5":[{"t":0,"val":1.414}]
  }
``

The section above specifies an additional forward movement operator
which moves by the forward step times 1.414(the square root of two to
three places). This is convenient for the sierpinsky curve in
particular and is taken from the `"Custom Operations"` section of that
[file](../sierpinsky-filling.json). Custom operations may be more
space efficient during computation, for example, the same file could
define a custom operation for the only occasionally needed "Turn right
by 90 degrees" command, instead of using two right turns by 45
degrees. It should not alter the output svg at all, except for cases
where the forward commands are called differently than typical. 
