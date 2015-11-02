#!/bin/bash
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Attempt to update all the patches located in tools/patches/.
for i in tools/patches/*.patch
do
  # Clean the state of mozilla.
  hg -R mozilla update --clean
  # Apply the patch.
  hg -R mozilla patch --no-commit $i
  # Save the diff back into the patch.
  hg -R mozilla diff > $i
done

# Now attempt applying all the patches.
hg -R mozilla update --clean
./tools/patches/apply-patches.sh
