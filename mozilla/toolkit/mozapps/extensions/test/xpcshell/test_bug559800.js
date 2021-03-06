/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 */

// This verifies that deleting the database from the profile doesn't break
// anything

const EXTENSIONS_DB = "extensions.sqlite";

const profileDir = gProfD.clone();
profileDir.append("extensions");

// getting an unused port
Components.utils.import("resource://testing-common/httpd.js");
let gServer = new HttpServer();
gServer.start(-1);
gPort = gServer.identity.primaryPort;

function run_test() {
  createAppInfo("xpcshell@tests.mozilla.org", "XPCShell", "1", "1.9.2");

  writeInstallRDFForExtension({
    id: "addon1@tests.mozilla.org",
    version: "1.0",
    updateURL: "http://localhost:" + gPort + "/data/test_update.rdf",
    targetApplications: [{
      id: "xpcshell@tests.mozilla.org",
      minVersion: "1",
      maxVersion: "1"
    }],
    name: "Test Addon 1",
  }, profileDir);

  startupManager();

  do_test_pending();

  run_test_1();
}

function end_test() {
  gServer.stop(do_test_finished);
}

function run_test_1() {
  AddonManager.getAddonByID("addon1@tests.mozilla.org", function(a1) {
    do_check_neq(a1, null);
    do_check_eq(a1.version, "1.0");

    shutdownManager();

    let db = gProfD.clone();
    db.append(EXTENSIONS_DB);
    db.remove(true);

    do_execute_soon(check_test_1);
  });
}

function check_test_1() {
  startupManager(false);

  AddonManager.getAddonByID("addon1@tests.mozilla.org", function(a1) {
    do_check_neq(a1, null);
    do_check_eq(a1.version, "1.0");

    let db = gProfD.clone();
    db.append(EXTENSIONS_DB);
    do_check_true(db.exists());
    do_check_true(db.fileSize > 0);

    end_test();
  });
}
