# regex-fa
Command line tool for regular expression matching, written in C++. 

The regex matching algorithm that's used is invented by **Ken Thompson** 
in 1960. It uses finite automata for pattern matching, as described by 
**Rus Coxx** in [this paper](https://swtch.com/~rsc/regexp/regexp1.html).

## Building

You need: cmake and a recent C++ compiler.

```bash
> git clone --recurse-submodules https://github.com/GeertArien/regex-fa.git
> cd regex-fa
> mkdir build
> cd build
> cmake ..
> cmake --build .
```

## Usage

#### Example
```
> ./regex-fa --regex lo.v.e.s. --input 'everyone loves regex tools'
```
#### Regex format
For the sake of convenience only regular expression in postfix notation are currently supported. With a '**.**' added as an
explicit concatenation operator. 

#### Supported operators

- **ab.** : concatentation operator, match *ab*  
- **ab|** : or operator, match *a or b*
- **a*** : match a sequence of *zero or more* 
- **a+** : match a sequence of *one or more* 
- **a?** : match *zero or one* 

## Testing

Building and running the tests:

```bash
> cd build
> cmake -DBUILD_TESTS=ON ..
> cmake --build .
> ./regex-fa-tests
```