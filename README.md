# Paraglob 2
#### A fairly quick data structure for matching a string against a large list of patterns.

For example, given a list of patterns
```
{*og, do*, ca*, plant}
```
and an input string `dog`, paraglob will return
```
{*og, do*}
```
## How it works
For any pattern, there exist a set of sub-strings that a string must contain in
order for it to have any hope of matching against that pattern. We call these
meta-words. Here are some examples:

```
*og       -> |og|
dog*fish  -> |og| |fish|
```

When a pattern is added to a Paraglob the pattern is stored and is split into
its meta-words. Those meta words are then added to an Aho-Corasick data
structure that can be found in `multifast-ac`.

When Paraglob is given a query, it first gets the meta-words contained in the
query using `multifast-ac` then it builds a set of all patterns associated with
those meta-words and runs `fnmatch` on the input string and those patterns and
returns a vector of the ones that match.

## How to use it
Running `make` in its directory will compile `paraglob.out`. This is a small
benchmarking script that takes three parameters: the number of patterns to
generate, the number of queries to perform, and the percentage generated of
patterns that will match.

As an example, running `paraglob.out 10000 50 50` will add 10,000 patterns,
perform 50 queries on them (of which 50% should match), and then return the
results.

## Open issues
Presently, for large amounts of patterns, building Paraglob is slow. It takes
about 1.5 seconds to build for 10,000 items, 3 seconds for 20,000, and so on.
This is because of the time required to build the Aho-Corasick structure. It's
likely worthwhile to explore this more, and look into some alternate
implementations.

Here is a flame graph of Paraglob running the example command from above:

<img src="./flameGraphs/paraglob2_1.svg">
