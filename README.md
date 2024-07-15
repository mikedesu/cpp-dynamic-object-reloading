# C/C++ hot reloading

This repo demonstrates an example of hot reloading C/C++ code in a running application. The code is based on a blog post by Theo Penavaire:

[https://theo-penavaire.medium.com/loading-of-a-c-class-from-a-shared-library-modern-c-722d6a830a2b](https://theo-penavaire.medium.com/loading-of-a-c-class-from-a-shared-library-modern-c-722d6a830a2b)

-----

## Building

To build the project, run the following commands:

```
make clean && make
```

## Running

```
./main
```

```
./maincpp
```

-----

## Research

The only way we are able to prevent name-mangling is for C-style functions. We can implement arbitrary C-style functions using `extern "C" {}` in order to prevent the name-mangling that would normally occur on compilation. This allows us to "export" functions from a shared library and call them from the main application.

The initial hope with this research was to find an easy way to implement dynamic class reloading for development of games and other software.

While the initial results are hopeful, in order to make use of this in my existing game would require significant refactoring which I am, at this moment, unwilling to go through lol.

-----

## Social Media

If you found this repo useful, please reach out to me:

- [https://ko-fi.com/evildojo666](https://ko-fi.com/evildojo666)
- [https://www.twitter.com/evildojo666](https://www.twitter.com/evildojo666)
- [https://twitch.tv/evildojo666](https://twitch.tv/evildojo666)
- [https://www.evildojo.com](https://www.evildojo.com)

