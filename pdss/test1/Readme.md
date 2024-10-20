# Test 1

## Lambda Expressions and Java Streams
The project called `good-lambdas -streams` is from my teacher and can be found [here](https://github.com/MarioRivis/good-lambdas-streams)
Remeber:
- use peek and set 
- use distinct before sorted
- for reverse sorting just put sorted(Comparator.Comparint("foo")**.reversed**)
- if you want to get average(), make sure you use **MapToInt** not Map
- use `orElseThrow(() -> new Exception("bar"))`'
- use `.getAsInt()` to return the result an int
- `.min()` returns an OptionalInt so you have to use `.getAsInt()` after
