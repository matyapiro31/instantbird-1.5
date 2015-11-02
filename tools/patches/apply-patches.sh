#!/bin/bash
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.


# attempt to apply all the patches located in tools/patches/
for i in tools/patches/*.patch
do
  newfiles=`grep -A 1 -- '--- /dev/null' "$i" |grep -v -- '--- /dev/null'| \
    sed 's@+++ b/@@; s/'$'\t''.*//'`
  movedfiles=
  for f in $newfiles
  do
    if [ -f "mozilla/$f" ]; then
      mv "mozilla/$f" "mozilla/$f.backup"
      movedfiles="$movedfiles $f"
    else
      echo not found  
    fi
  done
  # first, check if this patch applies
  patch --dry-run -N -p1 -d mozilla/ <$i >/dev/null 2>/dev/null
  if [ $? = 0 ]; then
    # it works, just apply it
    patch -p1 -d mozilla/ <$i
  else
    for f in $movedfiles
    do
      mv mozilla/$f.backup mozilla/$f
    done
    # it doesn't apply, check if it is already applied
    patch --dry-run -R -N -p1 -d mozilla/ <$i >/dev/null 2>/dev/null
    if [ $? = 0 ]; then
      echo $i already applied
    else
      # either way, it doesn't apply. Display a warning showing the problem
      echo error: $i failed to apply >&2
      echo --------
      patch --dry-run -N -p1 -d mozilla/ <$i
      echo --------
      error=1
    fi
  fi
done

if [ $error ]; then
  exit 1
fi
