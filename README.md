![C/C++ CI](https://github.com/Tracnac/fe/workflows/C/C++%20CI/badge.svg)

## Just have fun with a simple and highly comprehensible C source, that implement a small List/Scheme/Clojure parser.
### Big thanks to **rxi** to made this available under MIT licence.

### Tracnac
#### I will update this page with my goals, later.

# fe
A *tiny*, embeddable language implemented in ANSI C

```clojure
(set reverse (fn (lst)
  (let res nil)
  (while lst
    (set res (cons (car lst) res))
    (set lst (cdr lst))
  )
  res
))

(set animals '("cat" "dog" "fox"))

(print (reverse animals)) ; => ("fox" "dog" "cat")
```

## Overview
* Supports numbers, symbols, strings, pairs, lambdas, macros
* Lexically scoped variables, closures
* Small memory usage within a fixed-sized memory region — no mallocs
* Simple mark and sweep garbage collector
* hotloading library (In progress... New feature)
* Encapsuled documentation (In progress... New feature)
* Easy to use C API
* Portable ANSI C — works on 32 and 64bit
* Concise — less than 800 sloc (I will do my best :) )

---

* **[Demo Scripts](scripts)**
* **[C API Overview](doc/capi.md)**
* **[Language Overview](doc/lang.md)**
* **[Implementation Overview](doc/impl.md)**


## Contributing
The library focuses on being lightweight and minimal; pull requests will
likely not be merged. Bug reports and questions are welcome.


## License
This library is free software; you can redistribute it and/or modify it under
the terms of the MIT license. See [LICENSE](LICENSE) for details.
