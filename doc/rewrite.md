#Introduction

Rewrite rules are a powerful way to express a fractal system in a compact way.
They consist of three things, *Constants*, *Rewrite rules*, and a single *axiom*.

The specifications are defined in a json file.

##Constants

Constants are the basic commands that are executed at the end of
recursion. They allow for a significant amount of customization and
often share their assigned letter with a Rewrite Rule. They are defined in the "Constant" object in a json file.
```
"Constant":[
	{
	    "key":"1",
	    "value":[
		{
		    "op_type":0,
		    "op_args":0
		}
	    ]
	},
	{
	    "key":"0",
	    "value":[
		{
		    "op_type":0,
		    "op_args":0
		}
	    ]
	},
	{
	    "key":"d",
	    "value":[
		{
		    "op_type":1,
		    "op_args":0
		},
		{
		    "op_type":3,
		    "op_args":45
		}
	]
	},
	{
	    "key":"u",
	    "value":[
		{
		    "op_type":2,
		    "op_args":0
		},
		{
		    "op_type":4,
		    "op_args":45
		}
	    ]
	}
    ]
```

|op_type | Meaning|
|----------|--------|
|0         |move forwards|
|1         |push the cursor as it is onto the stack|
|2         |pop the cursor|
|3(<int>)  |Turn <int> degrees left|
|4(<int>)  |Turn <int> degrees right|

Any of the above operations' arguments are defined in the ``op_args`` key.

As you have observed above, constants may have multiple operations
performed, this allows for some curves to be defined with fewer
constants.

##Rewrite Rules

Rewrite rules are equivalent to nonterminals in context free
grammars. If that doesn't mean anything to you, that means that they
can lead to other Rewrite Rules or constants. They aren't quite the
same, as of writing they don't support alternatives, as that would not
make any sense as far as rewriting systems go.

An example continuing the pythagoras tree definitions whose constants were defined in the examples in the previous section would look like this:
```
    "Rewrite":[
	{
	    "key":"1",
	    "value":"11"
	},
	{
	    "key":"0",
	    "value":"1d0u0"
	}
    ],
```
##The Axiom

The Axiom for a ruleset is the initial state of the rule. This is simpler than the above definitions as it takes the initial series of the rewrite rules and constants.

Continuing the pythagoras tree example previously, the axiom is much smaller ``"Axiom":"0"``. Which in that equates to starting on the leaf state.

#The Whole Example

```
{
    "Constant":[
	{
	    "key":"1",
	    "value":[
		{
		    "op_type":0,
		    "op_args":0
		}
	    ]
	},
	{
	    "key":"0",
	    "value":[
		{
		    "op_type":0,
		    "op_args":0
		}
	    ]
	},
	{
	    "key":"d",
	    "value":[
		{
		    "op_type":1,
		    "op_args":0
		},
		{
		    "op_type":3,
		    "op_args":45
		}
	    ]
	},
	{
	    "key":"u",
	    "value":[
		{
		    "op_type":2,
		    "op_args":0
		},
		{
		    "op_type":4,
		    "op_args":45
		}
	    ]
	}
    ],
    "Rewrite":[
	{
	    "key":"1",
	    "value":"11"
	},
	{
	    "key":"0",
	    "value":"1d0u0"
	}
    ],
    "Axiom":"0"
}
```
