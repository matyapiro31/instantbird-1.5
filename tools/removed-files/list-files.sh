#!/bin/bash
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.


# ref is the current version
ref="0.2b2"
# versions is the list of old versions we want to compare
versions="0.1.2 0.1.3 0.1.3.1 0.2a1 0.2b1 0.2b2"

mkdir -p list

for i in $ref $versions; do
  echo Listing files in $i
  # Windows
  unzip -l $i/instantbird-*.en-US.win32.zip |grep 'instantbird/'|sed 's@.*instantbird/@@' |sort > list/$i-win.txt

  # Linux
  tar -tf $i/instantbird-*.en-US.linux-i686.tar.bz2 |grep 'instantbird/'|sed 's@.*instantbird/@@' |sort > list/$i-linux.txt

  # Mac
  mkdir dmg-$i
  hdiutil attach $i/instantbird-*.en-US.mac.dmg -mountpoint dmg-$i -quiet
  find dmg-$i/Instantbird.app/Contents/MacOS -type f |grep 'Instantbird.app/Contents/MacOS/'|sed 's@.*/Instantbird.app/Contents/MacOS/@@' |sort > list/$i-mac.txt
  hdiutil detach dmg-$i -quiet
  rmdir dmg-$i
done
exit 0

for os in win linux mac; do
  for i in $versions; do
    diff list/$i-$os.txt list/$ref-$os.txt |egrep '^< ' |sed 's/^< //' > list/removed-files-$os-$i
    diff list/$i-$os.txt list/$ref-$os.txt |egrep '^> ' |sed 's/^> //' > list/added-files-$os-$i
  done
done

# replace .dll/.dylib/.so suffixes and lib prefixes so that the files become comparable
cat list/removed-files-win-* |sed 's/\([A-Za-z0-9]*\)\.dll/@DLL_PREFIX@\1@DLL_SUFFIX@/' |sort |uniq > removed-files-win
cat list/removed-files-linux-* |egrep -v '/$' |sed 's/lib\([A-Za-z0-9]*\)\.so/@DLL_PREFIX@\1@DLL_SUFFIX@/' |sort |uniq > removed-files-linux
cat list/removed-files-mac-* |sed 's/lib\([A-Za-z0-9]*\)\.dylib/@DLL_PREFIX@\1@DLL_SUFFIX@/' |sort |uniq > removed-files-mac

# merge the 3 resulting files mostly by hand

# to check the result of the merge:
# python mozilla/config/Preprocessor.py -Fsubstitution -DXP_WIN -DDLL_PREFIX=@DLL_PREFIX@ -DDLL_SUFFIX=@DLL_SUFFIX@ instantbird/installer/removed-files.in|sort > rm-win
# diff ../hg.instantbird.org/rm-win removed-files-win
