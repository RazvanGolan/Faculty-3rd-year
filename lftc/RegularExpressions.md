# Regular Expressions

## Exercise 1
In a text, there are calendar dates in the format 'day/month/year', where the day and month consist of 1-2 digits, and the year consists of 2 or 4 digits. Write a regular expression that finds all such dates. It is not necessary to validate the calendar dates.
Ex: Ion was born on 21/5/1990, and Maria on 7/12/92.

```regexp
\b\d{1,2}/\d{1,2}/\d{2,4}\b
```

## Exercise 2
Propose a text that contains a character sequence matching the regular expression:

```regexp
[A-Z][a-zA-Z]*,[a-z]+ [0-9]+(\/.)*(\.|\?)
```

Example: Hello, are you free on 2/3/2025?

## Exercise 3
Write a regular expression that tests a simplified syntax for character classes. These must start with `[` and end with `]`;
optionally, `^` may appear after `[`. Inside, there can be individual characters or character ranges.
A character can be plain or prefixed with `\`.

Valid examples: `[abc]` `[^0-9]` `[\r\n\t ]` `[., !?;\-]` `[\\]`

Invalid examples (should not be recognized): `[\]` `[\\\]` `[a`

```regexp
\[\^?(\\.|[^\]\\])+\]
```