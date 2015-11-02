* makexpi.sh
Shell script that converts automatically Adium message styles found in
the current directory to .xpi files compatible with Instantbird.

* screenshot.manifest, the screenshot folder
Put this into the chrome folder of an Instantbird installation to take
automatically screenshots of all the variants of a message styles.
This is meant to be used automatically by the makexpi.sh script, to
produce screenshots of converted themes.

* teststyles.manifest, the teststyles folder
Reduced testcases of message styles that were used to test and debug
the magic copy feature.
 - simple is the simplest valid message style.
 - next uses grouping of consecutive messages.
 - multiroot doesn't wrap the content of each message into a single
   'root' element, so multiple DOM subtrees are inserted into the
   document for each message.
