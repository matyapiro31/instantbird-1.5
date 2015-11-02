/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * These tests check the auto-update facility of the background thumbnail
 * service.
 */

const imports = {};
Cu.import("resource://gre/modules/BackgroundPageThumbs.jsm", imports);
registerCleanupFunction(function () {
  imports.BackgroundPageThumbs._destroy();
});

function runTests() {
  let numNotifications = 0;
  const URL = "http://mochi.test:8888/browser/toolkit/components/thumbnails/test/thumbnails_update.sjs?simple";

  function observe(subject, topic, data) {
    is(topic, "page-thumbnail:create", "got expected topic");
    is(data, URL, "data is our test URL");
    if (++numNotifications == 2) {
      // This is the final notification and signals test success...
      Services.obs.removeObserver(observe, "page-thumbnail:create");
      next();
    }
  }

  Services.obs.addObserver(observe, "page-thumbnail:create", false);
  // Create a tab - we don't care what the content is.
  yield addTab(URL);
  let browser = gBrowser.selectedBrowser;

  // Capture the screenshot.
  PageThumbs.captureAndStore(browser, function () {
    // We've got a capture so should have seen the observer.
    is(numNotifications, 1, "got notification of item being created.");
    // The capture is now "fresh" - so requesting the URL should not cause
    // a new capture.
    imports.BackgroundPageThumbs.captureIfStale(URL);
    is(numNotifications, 1, "still only 1 notification of item being created.");

    // Now we will go behind the back of the thumbnail service and change the
    // mtime of the file to be in the past.
    let fname = PageThumbsStorage.getFilePathForURL(URL);
    let file = Cc["@mozilla.org/file/local;1"].createInstance(Ci.nsIFile);
    file.initWithPath(fname);
    ok(file.exists(), fname + " doesn't exist");
    // Set it as very stale...
    file.lastModifiedTime = Date.now() - 1000000000;
    // Ask for it to be updated.
    imports.BackgroundPageThumbs.captureIfStale(URL);
    // But it's async, so wait - our observer above will call next() when
    // the notification comes.
  });
  yield undefined; // wait for callbacks to call 'next'...
}
