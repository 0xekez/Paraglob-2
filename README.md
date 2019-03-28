# Paraglob 2
A (hopefully) very fast way to get all values associated with keys that match a glob in a dictionary-like structure.

For example, given a map with the associations:

```
dog -> 1
fog -> 2
cat -> 3
```

Calling `myGlob.getPattern("*og");` would yield a std::vector containing `[1, 2]`.

This is not at all close to being done yet. <b>TODO</b> still:

  1. Migrate current implementation to C++11/17 using more `std::` features.
  2. Run speed tests.
  3. Integrate into Zeek scripting language.
