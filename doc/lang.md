# Language

## Forms

### Special-forms
##### (let sym val)
Creates a new binding of `sym` to the value `val` in the current environment.

##### (set sym val)
Sets the existing binding of `sym` to the value `val`; in lieu of an
existing binding the global value is set.

##### (if cond then else ...)
If `cond` is true evaluates `then`, else evaluates `else` — `else` and `then`
statements can be chained to replicate the functionality of else-if blocks.

```clojure
> (set x 2)
nil
> (if (== x 1) "one"
      (== x 2) "two"
      (== x 3) "three"
      "?")
two
```

##### (fn params ...)
Creates a new function.

```clojure
> (set sqr (fn (n) (* n n)))
nil
> (sqr 4)
16
```

##### (mac params ...)
Creates a new *macro*.
```clojure
> (set incr (mac (x) (list 'set x (list '+ x 1))))
nil
> (set n 0)
nil
> (incr n)
nil
> n
1
```

##### (while cond ...)
If `cond` evaluates to true evaluates the rest of its arguments and keeps
repeating until `cond` evaluates to `nil`.

```clojure
> (set i 0)
nil
> (while (< i 3)
    (print i)
    (set i (+ i 1))) ; or (set i (++ i))
0
1
2
nil
```

##### (quote val)
Returns `val` unevaluated.

```clojure
> (quote (hello world))
(hello world)
```

##### (and ...)
Evaluates each argument until one results in `nil` — the last argument's value
is returned if all the arguments are true.

##### (or ...)
Evaluates each argument until one results in true, in which case that arguments
value is returned — `nil` is returned if no arguments are true.

##### (do ...)
Evaluates each of its arguments and returns the value of the last one.

### Functions
##### (cons car cdr)
Creates a new pair with the given `car` and `cdr` values.

##### (car pair)
Returns the `car` of the `pair` or `nil` if `pair` is `nil`.

##### (cdr pair)
Returns the `cdr` of the `pair` or `nil` if `pair` is `nil`.

##### (setcar pair val)
Sets the `car` of `pair` to `val`.

##### (setcdr pair val)
Sets the `cdr` of `pair` to `val`.

##### (list ...)
Returns all its arguments as a list.
```clojure
> (list 1 2 3)
(1 2 3)
```

##### (atom x)
Returns true if `x` is not a pair, otherwise `nil`.

##### (print ...)
Prints all it's arguments to `stdout`, each separated by a space and followed by
a new line.

##### (! val)
Returns true if `val` is `nil`, else returns `nil`
```clojure
> (! 1)
nil
```

##### (== a b)
Returns true if the values `a` and `b` are equal in value. Numbers and strings
are equal if equivalent, all other values are equal only if it is the same
underlying object.

##### (< a b)
Returns true if the numerical value `a` is less than `b`.

##### (<= a b)
Returns true if the numerical value `a` is less than or equal to `b`.

##### (> a b)
Returns true if the numerical value `a` is greater than `b`.

##### (>= a b)
Returns true if the numerical value `a` is greater than or equal to `b`.

##### (+ ...)
Adds all its arguments together.

##### (- ...)
Subtracts all its arguments, left-to-right.

##### (* ...)
Multiplies all its arguments.

##### (/ ...)
Divides all its arguments, left-to-right.

##### (++ a)
Add 1 to the numerical value `a`.

##### (-- a)
Subtract 1 to the numerical value `a`.
