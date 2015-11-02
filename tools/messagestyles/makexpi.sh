#!/bin/bash
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# interesting environment variables:
#  HOMEPAGE
#  VERSION
#  AUTHOR
#  ICON
#  INSTANTBIRD_DIR
#  INSTANTBIRD_CMD

APP_ID={33cb9019-c295-46dd-be21-8c4936574bee}
APP_CURRENT_VERSION=0.2a1
APP_MIN_VERSION=$APP_CURRENT_VERSION
APP_MAX_VERSION=0.2 # $APP_CURRENT_VERSION

if [ "$HOMEPAGE" ]; then
  HOMEPAGE_URL=" <em:homepageURL>`echo $HOMEPAGE | sed 's/&/\\\&amp;/g'`</em:homepageURL>"
fi

if [ "$VERSION" ]; then
  ADDON_VERSION=`echo "$VERSION" |tr A-Z a-z| tr -dc [a-z0-9].`
else
  ADDON_VERSION="1.0"
fi

if [ "$AUTHOR" ]; then
  ADDON_CREATOR=`echo "$AUTHOR" | sed 's/&/\\\&amp;/g'`
else
  ADDON_CREATOR="Unknown author"
fi

function ensurecase()
{
  goodname=./$1
  currentname=`find . | grep -i ^\./$1$`
  if [ -e "$currentname" ]; then
    if [ "$currentname" != "$goodname" ]; then
      echo "  Fixing case: $currentname --> $goodname" >&1
      mv "$currentname" "$goodname"
    fi
  fi
}

function installRdfTemplate () {
  cat << EOF
<?xml version="1.0"?>

<RDF xmlns="http://www.w3.org/1999/02/22-rdf-syntax-ns#" 
     xmlns:em="http://www.mozilla.org/2004/em-rdf#">

<Description about="urn:mozilla:install-manifest">
 <em:id>@ADDON_ID@</em:id>
 <em:name>@ADDON_NAME@</em:name>
 <em:version>@ADDON_VERSION@</em:version>
 <em:description>@ADDON_DESCRIPTION@</em:description>
 <em:creator>@ADDON_CREATOR@</em:creator>
@ADDON_ICON@
@HOMEPAGE_URL@
 <em:targetApplication>
  <Description>
   <em:id>@APP_ID@</em:id>
    <em:minVersion>@APP_MIN_VERSION@</em:minVersion>
    <em:maxVersion>@APP_MAX_VERSION@</em:maxVersion>
  </Description>
 </em:targetApplication>
</Description>

</RDF>
EOF
}

function installRdfGlobal () {
  cat << EOF
<?xml version="1.0"?>

<RDF xmlns="http://www.w3.org/1999/02/22-rdf-syntax-ns#" 
     xmlns:em="http://www.mozilla.org/2004/em-rdf#">

<Description about="urn:mozilla:install-manifest">
 <!-- nsIUpdateItem type for a Multiple Item Package -->
 <em:type>32</em:type>
 <em:id>@ADDON_ID@</em:id>
 <em:name>@ADDON_NAME@</em:name>
 <em:version>@ADDON_VERSION@</em:version>
 <em:creator>@ADDON_CREATOR@</em:creator>
 <em:description>Adium Message Styles automatically converted</em:description>
@HOMEPAGE_URL@
 <em:targetApplication>
  <Description>
   <em:id>@APP_ID@</em:id>
    <em:minVersion>@APP_MIN_VERSION@</em:minVersion>
    <em:maxVersion>@APP_MAX_VERSION@</em:maxVersion>
  </Description>
 </em:targetApplication>
</Description>

</RDF>
EOF
}

echo In "$1":

# prepare the workdir
rm -rf workdir
mkdir workdir
cd workdir

# extract .zip and .tgz files
filename=`find "../$1" -name '*.zip' |head -n 1`
if [ -n "$filename" ]; then
  echo " Extracting `basename $filename`"
  filename=`basename -s .zip $filename`
  find "../$1" -name '*.zip' -exec unzip -q {} \;
else
  filename=`find "../$1" -name '*.tgz' |head -n 1`
  if [ -n "$filename" ]; then
    echo " Extracting `basename $filename`"
    filename=`basename -s .tgz $filename`
    find "../$1" -name '*.tgz' -exec tar xf {} \;
  fi
fi

# remove all the unwanted files that MacOS X stuffs into zip archives
rm -rf __MACOSX
find . -name '._*' -exec rm {} \;

# extract dmg files, replace with the content
# there's probably at most 1 dmg file, so don't bother with a loop
dmgfile=`find . -name '*.dmg' |head -n1`
if [ -n "$dmgfile" ]; then
  echo " Extracting "`basename "$dmgfile"`""
  mkdir dmg
  echo "  Attaching volume"
  hdiutil attach "$dmgfile" -mountpoint dmg -quiet
  echo "  Copying .AdiumMessageStyle bundles"
  find dmg -name '*.AdiumMessageStyle' -exec cp -r {} . \; 2>/dev/null
  echo "  Ejecting volume"
  hdiutil detach dmg -quiet
  rmdir dmg
fi

# remove unwanted .DS_Store files
find . -name .DS_Store -exec rm {} \;

styles=`find . -iname '*.AdiumMessageStyle' 2>/dev/null`
if [ -z "$styles" ]; then
  echo No .AdiumMessageStyle bundle >&2
  echo Failed!
  echo
  exit 42
fi
export IFS='
'

resdir=`pwd`
for theme in $styles; do
  # first get some information we need about this theme
  echo " Processing $theme:"
  name=`echo "$theme"| sed 's/.[Aa]dium[Mm]essage[Ss]tyle$//'`
  name=`basename $name`
  packagename=`echo $name |tr A-Z a-z| tr -dc [a-z0-9]-`

  cd "$theme"/
  # just in case...
  chmod -R u+w .

  # flatten the directory structures. We don't want the Contents or
  # Resources folders
  if [ -d Contents ]; then
    mv Contents/{,.}* . 2>/dev/null
    rmdir Contents
  fi
  if [ -d Resources ]; then
    mv Resources/{,.}* . 2>/dev/null
    rmdir Resources
  fi

  # fix the case
  ensurecase "Info.plist"
  ensurecase "main.css"
  ensurecase "Footer.html"
  ensurecase "Header.html"
  ensurecase "Status.html"
  ensurecase "NextStatus.html"
  ensurecase "Variants"
  ensurecase "Incoming"
  ensurecase "Incoming/Content.html"
  ensurecase "Incoming/Context.html"
  ensurecase "Incoming/NextContent.html"
  ensurecase "Incoming/NextContext.html"
  ensurecase "Incoming/buddy_icon.png"
  ensurecase "Outgoing"
  ensurecase "Outgoing/Content.html"
  ensurecase "Outgoing/Context.html"
  ensurecase "Outgoing/NextContent.html"
  ensurecase "Outgoing/NextContext.html"
  ensurecase "Outgoing/buddy_icon.png"

  if [ "$ICON" ]; then
    echo "  Copying icon $ICON"
    cp "$resdir/../$ICON" .
  fi
  # make the chrome
  rm -rf "$resdir/chrome"
  mkdir "$resdir/chrome"
  echo "  Creating $packagename.jar"
  zip -q -D -0 -r "$resdir/chrome/$packagename.jar" *
  echo skin $packagename classic/1.0 jar:chrome/$packagename.jar!/ > "$resdir/chrome.manifest"
  cd - >/dev/null

  # generate install.rdf
  ADDON_ID=messagestyle-$packagename@addons.instantbird.org
  ADDON_NAME=$name
  if [ "$ICON" ]; then
    ADDON_ICON=" <em:iconURL>chrome://$packagename/skin/$ICON</em:iconURL>"
  fi

  ADDON_DESCRIPTION=`grep -A 1 CFBundleGetInfoString "$theme"/Info.plist|tail -n 1 | sed 's/.*<string>//;s@</string>.*@@; s@/@\\\\/@g'`

  installRdfTemplate |sed "s/@APP_ID@/$APP_ID/; 
                           s/@ADDON_ID@/$ADDON_ID/;
                           s/@ADDON_NAME@/$ADDON_NAME/;
                           s|@ADDON_ICON@|$ADDON_ICON|;
                           s|@HOMEPAGE_URL@|$HOMEPAGE_URL|;
                           s/@ADDON_VERSION@/$ADDON_VERSION/;
                           s/@ADDON_DESCRIPTION@/$ADDON_DESCRIPTION/;
                           s/@ADDON_CREATOR@/$ADDON_CREATOR/;
                           s/@APP_MIN_VERSION@/$APP_MIN_VERSION/;
                           s/@APP_MAX_VERSION@/$APP_MAX_VERSION/" > install.rdf

  # create the resulting XPI bundle
  echo "  Creating $packagename.xpi"
  zip -q -D -r $packagename.xpi install.rdf chrome.manifest chrome/

  if [ "$INSTANTBIRD_DIR" ]; then
    mkdir -p ../screenshots

    if [ -z "$INSTANTBIRD_CMD" ]; then
      INSTANTBIRD_CMD="/instantbird-bin"
    fi

    echo skin $packagename classic/1.0 jar:$packagename.jar!/ > "$INSTANTBIRD_DIR/chrome/$packagename.manifest"
    cp chrome/$packagename.jar "$INSTANTBIRD_DIR/chrome/"
    eval SAVE_PATH=$(pwd)/../screenshots/ THEME=$packagename $INSTANTBIRD_DIR$INSTANTBIRD_CMD
    rm -f "$INSTANTBIRD_DIR/chrome/$packagename.jar" "$INSTANTBIRD_DIR/chrome/$packagename.manifest"
  fi
done

# create the resulting XPI bundle
mkdir -p ../result/
packages=$(echo "$styles" | wc -l)
if [ $packages -eq 1 ]; then
  echo " Moving to $filename.xpi"
  mv $packagename.xpi ../result/$filename.xpi
else
  packagename=`echo $filename |tr A-Z a-z| tr -dc [a-z0-9]-`
  ADDON_NAME=$name
  if [ "$TITLE" ]; then
    ADDON_NAME=$TITLE
    packagename=`echo $TITLE |tr A-Z a-z| tr -dc [a-z0-9]-`
  fi
  ADDON_ID=messagestyle-$packagename@addons.instantbird.org

  echo " Creating: $filename.xpi"
  installRdfGlobal |sed "s/@APP_ID@/$APP_ID/; 
                         s/@ADDON_ID@/$ADDON_ID/;
                         s/@ADDON_NAME@/$ADDON_NAME/;
                         s|@HOMEPAGE_URL@|$HOMEPAGE_URL|;
                         s/@ADDON_VERSION@/$ADDON_VERSION/;
                         s/@ADDON_CREATOR@/$ADDON_CREATOR/;
                         s/@APP_MIN_VERSION@/$APP_MIN_VERSION/;
                         s/@APP_MAX_VERSION@/$APP_MAX_VERSION/" > install.rdf

  zip -q -0 ../result/$filename.xpi install.rdf *.xpi
fi

cd ..
rm -r workdir

echo "Done!"
echo
