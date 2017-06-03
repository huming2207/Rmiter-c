# RMIT2iCal
Previously called "Rmiter-c". Just an unofficial, pure C99 implementation of RMIT University's myRMIT timetable crawling tool, converting myRMIT timetable to iCalendar!

**This project is not maintained and/or affiliated with RMIT University and their staffs. Meanwhile this project contains reverse engineering works, as a result it should be only used as education and research purposes.**

## How to compile 
### 1. Installing toolchain, cmake, libcurl, etc.

If you are using Debian, Ubuntu or Deepin Linux, you may need to run this command to install.

```
apt-get install libcurl4-openssl-dev build-essential automake autoconf m4 cmake libtool
```

If you are using macOS, you may need to install these items by using [Homebrew](https://brew.sh).

```
brew install cmake automake autoconf libcurl m4
```

### 2. Installing gumbo-parser

[Gumbo-parser](https://github.com/google/gumbo-parser) is a great pure C HTML5 parser implementation made by Google. 

If you are using macOS, you can install it by using [Homebrew](https://brew.sh):

```
brew install gumbo-parser
```

If you are using Debian/Ubuntu, then you need to compile it by yourself. Please refer to [Gumbo-parser](https://github.com/google/gumbo-parser) project page follow their readme and get it installed.

### 3. Compile this project

Clone it to your local drive first, of course:

```
git clone https://github.com/huming2207/Rmiter-c.git
```

Then run:

```
cmake .
```

...and:

```
make
```

...then run:

```
./rmiter-c
```

...and enjoy this buggy project (literally) lol! 😂

## To-do list

- [x] Login simulation
- [x] ICS file writing
- [x] Timetable parsing
- [ ] Timetable iterating for whole semester 

## Acknowledgements

- Google for their [Gumbo-parser](https://github.com/google/gumbo-parser)
- Curl and [Libcurl](https://curl.haxx.se/libcurl/c/libcurl.html)
- cJSON library (in `./cJSON`)
- All the teachers of [Advanced Programming Techniques](http://www1.rmit.edu.au/courses/004068) who taught me ANSI C programming 😂