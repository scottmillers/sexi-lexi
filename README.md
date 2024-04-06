# Sexi Lexi

A lexical analyzer parser in C that uses the following BNF notation:

Subject: Assignment description
P ::= S
S ::= V:=E | read(V) | write(E) | if C: then S fi | if C: then S else S fi | S;S
C ::= E < E | E > E | E = E | E <> E | E <= E | E >= E | ( C )
E ::= T | E + T | E - T
T ::= F | T * F | T / F | T % F
F ::= (E) | O | N | V
O ::= ++V | --V
V ::= a | b | … | y | z | aV | bV | … | yV | zV
N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N

## Using Make

```
$make
```

```
make clean
```

To compile and run use:
```
make run
```


