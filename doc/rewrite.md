#Introduction

Rewrite rules are a powerful way to express a fractal system in a compact way.
They consist of three things, *Constants*, *Rewrite rules*, and a single *axiom*.

##Constants

Constants are the basic commands that are executed at the end of
recursion. They allow for a significant amount of customization and
often share their assigned letter with a Rewrite Rule. They have a
relatively simple syntax that allows for multiple instructions to a
single constant.
Defined in BNF they resemble this

```
<const> ::= <char> <equal-sign> <const-spec>
<const-spec> ::= <operation>|<operation> <const-spec>
<operation> ::= <d>|<u>|<f>|<r> <paren-left> <integer> <paren-right>| <l> <paren-left> <integer> <paren-right>
```

So a typical definition of the constants for a pythagoras tree would resemble this:

```
1=f,0=f,d=dl(45),u=ur(45)
```

For reference the characters have the following meanings:

|Character | Meaning|
|----------|--------|
|f         |move forwards|
|d         |push the cursor as it is onto the stack|
|u         |pop the cursor|
|l(<int>)  |Turn <int> degrees left|
|r(<int>)  |Turn <int> degrees right|

As you have observed above, constants may have multiple operations
performed, this allows for some curves to be defined with fewer
constants.

##Rewrite Rules

Rewrite rules are equivalent to nonterminals in context free
grammars. If that doesn't mean anything to you, that means that they
can lead to other Rewrite Rules or constants. They aren't quite the
same, as of writing they don't support alternatives, as that would not
make any sense as far as rewriting systems go.

```
<rewrite-rule> ::= <char> <equal-sign> <rewrite-operator>
<rewrite-operator> ::= <char> | <char> <rewrite-operator>
```

An example continuing the pythagoras tree definitions whose constants were defined in the examples in the previous section would look like this:
```
1=11,0=1d0u0
```

##The Axiom

The Axiom for a ruleset is the initial state of the rule. This is simpler than the above definitions as it takes the initial series of the rewrite rules and constants.

Continuing the pythagoras tree example previously, the axiom is much smaller ``0``. Which in that equates to starting on the leaf state.

#The Whole Example

```
CONSTANTS
1=f,0=f,d=dl(45),u=ur(45)
REWRITES
1=11,0=1d0u0
AXIOM
0
```
