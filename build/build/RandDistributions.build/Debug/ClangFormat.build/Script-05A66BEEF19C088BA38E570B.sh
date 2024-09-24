#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  /usr/local/bin/clang-format -i -style=file /Users/Kelson/Desktop/CS\ 3460/Random/Random/Assignment2.cpp
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  /usr/local/bin/clang-format -i -style=file /Users/Kelson/Desktop/CS\ 3460/Random/Random/Assignment2.cpp
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  /usr/local/bin/clang-format -i -style=file /Users/Kelson/Desktop/CS\ 3460/Random/Random/Assignment2.cpp
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  /usr/local/bin/clang-format -i -style=file /Users/Kelson/Desktop/CS\ 3460/Random/Random/Assignment2.cpp
fi

