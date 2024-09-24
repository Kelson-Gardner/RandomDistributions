#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  make -f /Users/Kelson/Desktop/CS\ 3460/Random/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  make -f /Users/Kelson/Desktop/CS\ 3460/Random/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  make -f /Users/Kelson/Desktop/CS\ 3460/Random/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/Kelson/Desktop/CS 3460/Random/build"
  make -f /Users/Kelson/Desktop/CS\ 3460/Random/build/CMakeScripts/ReRunCMake.make
fi

