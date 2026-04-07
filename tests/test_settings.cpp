#include <QtTest>
#include <QTemporaryDir>
#include <QSettings>
#include "models/Settings.h"

using namespace macrosip;

class TestSettings : public QObject {
    Q_OBJECT
private slots:
    void testConfigDir();
    void testContactsFile();
    void testCallsFile();
    void testSaveLoadRoundTrip();
    void testSaveLoadAccount();
    void testSaveLoadShortcuts();
    void testDefaultValues();
    void testNewFieldsRoundTrip();
    void testVideoFieldsRoundTrip();
    void testSetRunAtStartup();
};

void TestSettings::testConfigDir()
{
    const AppSettings &s = AppSettings::instance();
    QVERIFY(!s.configDir().isEmpty());
    QVERIFY(s.configDir().contains(QStringLiteral("MacroSIP")));
}

void TestSettings::testContactsFile()
{
    const AppSettings &s = AppSettings::instance();
    QVERIFY(s.contactsFile().endsWith(QStringLiteral("contacts.csv")));
    QVERIFY(s.contactsFile().startsWith(s.configDir()));
}

void TestSettings::testCallsFile()
{
    const AppSettings &s = AppSettings::instance();
    QVERIFY(s.callsFile().endsWith(QStringLiteral("calls.csv")));
    QVERIFY(s.callsFile().startsWith(s.configDir()));
}

void TestSettings::testSaveLoadRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    // Set some non-default values
    s.singleMode = false;
    s.vad = true;
    s.ec = false;
    s.sourcePort = 5070;
    s.rtpPortMin = 6000;
    s.rtpPortMax = 6100;
    s.autoAnswer = true;
    s.autoAnswerDelay = 5;
    s.dnd = true;
    s.callWaiting = false;
    s.forwardingNumber = QStringLiteral("100");
    s.forwardingDelay = 10;
    s.autoRecording = true;
    s.recordingPath = QStringLiteral("/tmp/records");
    s.alwaysOnTop = true;
    s.bringToFrontOnIncoming = false;
    s.enableLog = true;
    s.crashReport = true;
    s.headsetSupport = true;

    s.save();
    // Reset to defaults manually then reload
    s.singleMode = true;
    s.vad = false;
    s.ec = true;
    s.sourcePort = 5060;
    s.autoAnswer = false;
    s.headsetSupport = false;

    s.load();

    QCOMPARE(s.singleMode, false);
    QCOMPARE(s.vad, true);
    QCOMPARE(s.ec, false);
    QCOMPARE(s.sourcePort, 5070);
    QCOMPARE(s.rtpPortMin, 6000);
    QCOMPARE(s.rtpPortMax, 6100);
    QCOMPARE(s.autoAnswer, true);
    QCOMPARE(s.autoAnswerDelay, 5);
    QCOMPARE(s.dnd, true);
    QCOMPARE(s.callWaiting, false);
    QCOMPARE(s.forwardingNumber, QStringLiteral("100"));
    QCOMPARE(s.forwardingDelay, 10);
    QCOMPARE(s.autoRecording, true);
    QCOMPARE(s.recordingPath, QStringLiteral("/tmp/records"));
    QCOMPARE(s.alwaysOnTop, true);
    QCOMPARE(s.bringToFrontOnIncoming, false);
    QCOMPARE(s.enableLog, true);
    QCOMPARE(s.crashReport, true);
    QCOMPARE(s.headsetSupport, true);

    // Reset to defaults for other tests
    s.singleMode = true;
    s.vad = false;
    s.ec = true;
    s.sourcePort = 5060;
    s.rtpPortMin = 5000;
    s.rtpPortMax = 5100;
    s.autoAnswer = false;
    s.autoAnswerDelay = 0;
    s.dnd = false;
    s.callWaiting = true;
    s.forwardingNumber.clear();
    s.forwardingDelay = 0;
    s.autoRecording = false;
    s.recordingPath.clear();
    s.alwaysOnTop = false;
    s.bringToFrontOnIncoming = true;
    s.enableLog = false;
    s.crashReport = false;
    s.headsetSupport = false;
    s.save();
}

void TestSettings::testSaveLoadAccount()
{
    AppSettings &s = AppSettings::instance();

    s.account.server = QStringLiteral("sip.example.com");
    s.account.username = QStringLiteral("testuser");
    s.account.domain = QStringLiteral("example.com");
    s.account.password = QStringLiteral("secret");
    s.account.port = 5080;
    s.account.publish = true;
    s.account.ice = true;

    s.save();

    s.account.clear();
    QVERIFY(s.account.server.isEmpty());

    s.load();

    QCOMPARE(s.account.server, QStringLiteral("sip.example.com"));
    QCOMPARE(s.account.username, QStringLiteral("testuser"));
    QCOMPARE(s.account.domain, QStringLiteral("example.com"));
    QCOMPARE(s.account.password, QStringLiteral("secret"));
    QCOMPARE(s.account.port, 5080);
    QCOMPARE(s.account.publish, true);
    QCOMPARE(s.account.ice, true);

    // Reset
    s.account.clear();
    s.save();
}

void TestSettings::testSaveLoadShortcuts()
{
    AppSettings &s = AppSettings::instance();

    s.shortcuts.clear();
    Shortcut sc1;
    sc1.label = QStringLiteral("Speed 1");
    sc1.number = QStringLiteral("100");
    sc1.type = 1;
    s.shortcuts.append(sc1);

    Shortcut sc2;
    sc2.label = QStringLiteral("Speed 2");
    sc2.number = QStringLiteral("200");
    sc2.type = 0;
    s.shortcuts.append(sc2);

    s.save();

    s.shortcuts.clear();
    QVERIFY(s.shortcuts.isEmpty());

    s.load();

    QCOMPARE(s.shortcuts.size(), 2);
    QCOMPARE(s.shortcuts[0].label, QStringLiteral("Speed 1"));
    QCOMPARE(s.shortcuts[0].number, QStringLiteral("100"));
    QCOMPARE(s.shortcuts[0].type, 1);
    QCOMPARE(s.shortcuts[1].label, QStringLiteral("Speed 2"));
    QCOMPARE(s.shortcuts[1].number, QStringLiteral("200"));
    QCOMPARE(s.shortcuts[1].type, 0);

    // Reset
    s.shortcuts.clear();
    s.save();
}

void TestSettings::testDefaultValues()
{
    const AppSettings &s = AppSettings::instance();
    QCOMPARE(s.sourcePort, 5060);
    QCOMPARE(s.rtpPortMin, 5000);
    QCOMPARE(s.rtpPortMax, 5100);
    QCOMPARE(s.ec, true);
    QCOMPARE(s.vad, false);
    QCOMPARE(s.localDTMF, true);
    QCOMPARE(s.rport, true);
    QCOMPARE(s.callWaiting, true);
}

void TestSettings::testNewFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    // Set non-default values for all new fields
    s.recordingFormat    = QStringLiteral("wav");
    s.dtmfMethod         = QStringLiteral("rfc2833");
    s.autoAnswerMode     = QStringLiteral("all");
    s.soundEvents        = false;
    s.randomPopupPosition = true;
    s.multiMonitor       = true;
    s.disableNameLookup  = true;
    s.updatesInterval    = QStringLiteral("daily");
    s.runAtStartup       = true;
    s.enableLocalAccount = true;
    s.disableMessaging   = true;
    s.handleIpChanges    = true;
    s.handleMediaButtons = true;
    s.directoryOfUsers   = QStringLiteral("https://example.com/users");
    s.defaultListAction  = QStringLiteral("call");
    s.volumeRing         = 42;

    s.save();

    // Reset to defaults
    s.recordingFormat    = QStringLiteral("mp3");
    s.dtmfMethod.clear();
    s.autoAnswerMode.clear();
    s.soundEvents        = true;
    s.randomPopupPosition = false;
    s.multiMonitor       = false;
    s.disableNameLookup  = false;
    s.updatesInterval.clear();
    s.runAtStartup       = false;
    s.enableLocalAccount = false;
    s.disableMessaging   = false;
    s.handleIpChanges    = false;
    s.handleMediaButtons = false;
    s.directoryOfUsers.clear();
    s.defaultListAction.clear();
    s.volumeRing         = 100;

    s.load();

    QCOMPARE(s.recordingFormat, QStringLiteral("wav"));
    QCOMPARE(s.dtmfMethod, QStringLiteral("rfc2833"));
    QCOMPARE(s.autoAnswerMode, QStringLiteral("all"));
    QCOMPARE(s.soundEvents, false);
    QCOMPARE(s.randomPopupPosition, true);
    QCOMPARE(s.multiMonitor, true);
    QCOMPARE(s.disableNameLookup, true);
    QCOMPARE(s.updatesInterval, QStringLiteral("daily"));
    QCOMPARE(s.runAtStartup, true);
    QCOMPARE(s.enableLocalAccount, true);
    QCOMPARE(s.disableMessaging, true);
    QCOMPARE(s.handleIpChanges, true);
    QCOMPARE(s.handleMediaButtons, true);
    QCOMPARE(s.directoryOfUsers, QStringLiteral("https://example.com/users"));
    QCOMPARE(s.defaultListAction, QStringLiteral("call"));
    QCOMPARE(s.volumeRing, 42);

    // Reset
    s.recordingFormat    = QStringLiteral("mp3");
    s.dtmfMethod.clear();
    s.autoAnswerMode.clear();
    s.soundEvents        = true;
    s.randomPopupPosition = false;
    s.multiMonitor       = false;
    s.disableNameLookup  = false;
    s.updatesInterval.clear();
    s.runAtStartup       = false;
    s.enableLocalAccount = false;
    s.disableMessaging   = false;
    s.handleIpChanges    = false;
    s.handleMediaButtons = false;
    s.directoryOfUsers.clear();
    s.defaultListAction.clear();
    s.volumeRing         = 100;
    s.save();
}

void TestSettings::testVideoFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    s.videoEnabled = false;
    s.videoCodec   = QStringLiteral("H264");
    s.videoBitrate = 2048;
    s.videoH264    = true;
    s.videoH263    = true;
    s.videoVP8     = true;
    s.videoVP9     = false;
    s.cameraDevice = QStringLiteral("USB Camera 1");

    s.save();

    // Reset
    s.videoEnabled = true;
    s.videoCodec.clear();
    s.videoBitrate = 0;
    s.videoH264    = false;
    s.videoH263    = false;
    s.videoVP8     = false;
    s.videoVP9     = false;
    s.cameraDevice.clear();

    s.load();

    QCOMPARE(s.videoEnabled, false);
    QCOMPARE(s.videoCodec, QStringLiteral("H264"));
    QCOMPARE(s.videoBitrate, 2048);
    QCOMPARE(s.videoH264, true);
    QCOMPARE(s.videoH263, true);
    QCOMPARE(s.videoVP8, true);
    QCOMPARE(s.videoVP9, false);
    QCOMPARE(s.cameraDevice, QStringLiteral("USB Camera 1"));

    // Reset
    s.videoEnabled = true;
    s.videoCodec.clear();
    s.videoBitrate = 0;
    s.videoH264    = false;
    s.videoH263    = false;
    s.videoVP8     = false;
    s.videoVP9     = false;
    s.cameraDevice.clear();
    s.save();
}

void TestSettings::testSetRunAtStartup()
{
    QTemporaryDir tmpDir;
    QVERIFY(tmpDir.isValid());

    // setRunAtStartup uses XDG config location, but we can verify the
    // static method creates and removes the file by calling it and
    // checking the expected path.
    const QString configDir =
        QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    const QString desktopFile = configDir + QStringLiteral("/autostart/macrosip.desktop");

    // Enable
    AppSettings::setRunAtStartup(true);
    QVERIFY(QFile::exists(desktopFile));

    // Verify content
    QSettings ds(desktopFile, QSettings::IniFormat);
    QCOMPARE(ds.value(QStringLiteral("Desktop Entry/Type")).toString(),
             QStringLiteral("Application"));
    QCOMPARE(ds.value(QStringLiteral("Desktop Entry/Name")).toString(),
             QStringLiteral("MacroSIP"));
    QVERIFY(!ds.value(QStringLiteral("Desktop Entry/Exec")).toString().isEmpty());

    // Disable
    AppSettings::setRunAtStartup(false);
    QVERIFY(!QFile::exists(desktopFile));
}

QTEST_GUILESS_MAIN(TestSettings)
#include "test_settings.moc"
