# sqlitec


# grammar

```
<sqlite-cli-command> ::= <sqlite-command> | <dot-command>

<sqlite-command> ::= "SELECT" <select-options> ";"

<dot-command> ::= "." <dot-command-name> <dot-command-options>

<dot-command-name> ::= "open" | "tables" | "schema" | "exit"

<dot-command-options> ::= <identifier> | <dot-command-name> <identifier> | <dot-command-name>

<select-options> ::= <select-target> <from-clause> <where-clause>

<select-target> ::= "*" | <column-list>

<column-list> ::= <column-name> | <column-name> "," <column-list>

<from-clause> ::= "FROM" <table-name>

<where-clause> ::= "WHERE" <condition>

<condition> ::= <column-name> "=" <value>

<value> ::= <number> | <string>

<number> ::= <digit>+

<string> ::= "'" <characters> "'"

<characters> ::= <character>*

<character> ::= <letter> | <digit> | <symbol>

<letter> ::= "A" | "B" | ... | "Z" | "a" | "b" | ... | "z"

<digit> ::= "0" | "1" | "2" | ... | "9"

<symbol> ::= any symbol character

```