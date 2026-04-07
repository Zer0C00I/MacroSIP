#include <QtTest>
#include <QSlider>
#include <QRadioButton>
#include "dialogs/SettingsDialog.h"
#include "models/Settings.h"

using namespace macrosip;

class TestSettingsDialog : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testLoadSaveRoundTrip();
    void testNewAudioFieldsRoundTrip();
    void testNetworkFieldsRoundTrip();
    void testFeaturesFieldsRoundTrip();
    void testRecordingFieldsRoundTrip();
    void testAdvancedFieldsRoundTrip();
    void testVideoFieldsRoundTrip();
    void testTabCount();
};

void TestSettingsDialog::testDefaultState()
{
    SettingsDialog dlg;
    // Dialog should be constructible and have child widgets
    QVERIFY(dlg.children().count() > 0);

    // Verify tab count (Audio, Codecs, Network, Features, Recording, UI, Advanced, Video)
    auto *tabs = dlg.findChild<QTabWidget *>();
    QVERIFY(tabs != nullptr);
    QCOMPARE(tabs->count(), 8);
}

void TestSettingsDialog::testLoadSaveRoundTrip()
{
    AppSettings &settings = AppSettings::instance();

    // Set specific values
    settings.autoAnswer = true;
    settings.autoAnswerDelay = 3;
    settings.dnd = true;
    settings.callWaiting = false;
    settings.alwaysOnTop = true;
    settings.autoRecording = true;
    settings.recordingPath = QStringLiteral("/tmp/records");

    SettingsDialog dlg;
    dlg.loadSettings(settings);

    // Reset settings, then saveSettings should restore them
    settings.autoAnswer = false;
    settings.autoAnswerDelay = 0;
    settings.dnd = false;
    settings.callWaiting = true;
    settings.alwaysOnTop = false;
    settings.autoRecording = false;
    settings.recordingPath.clear();

    dlg.saveSettings(settings);

    QCOMPARE(settings.autoAnswer, true);
    QCOMPARE(settings.autoAnswerDelay, 3);
    QCOMPARE(settings.dnd, true);
    QCOMPARE(settings.callWaiting, false);
    QCOMPARE(settings.alwaysOnTop, true);
    QCOMPARE(settings.autoRecording, true);
    QCOMPARE(settings.recordingPath, QStringLiteral("/tmp/records"));

    // Restore defaults
    settings.autoAnswer = false;
    settings.autoAnswerDelay = 0;
    settings.dnd = false;
    settings.callWaiting = true;
    settings.alwaysOnTop = false;
    settings.autoRecording = false;
    settings.recordingPath.clear();
}

void TestSettingsDialog::testNewAudioFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    s.volumeRing        = 55;
    s.opusStereo        = true;
    s.swLevelAdjustment = true;
    s.soundEvents       = false;

    SettingsDialog dlg;
    dlg.loadSettings(s);

    // Reset
    s.volumeRing        = 100;
    s.opusStereo        = false;
    s.swLevelAdjustment = false;
    s.soundEvents       = true;

    dlg.saveSettings(s);

    QCOMPARE(s.volumeRing, 55);
    QCOMPARE(s.opusStereo, true);
    QCOMPARE(s.swLevelAdjustment, true);
    QCOMPARE(s.soundEvents, false);

    // Restore
    s.volumeRing        = 100;
    s.opusStereo        = false;
    s.swLevelAdjustment = false;
    s.soundEvents       = true;
}

void TestSettingsDialog::testNetworkFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    s.enableSTUN = true;
    s.stun       = QStringLiteral("stun.example.com");
    s.dnsSrvNs   = QStringLiteral("8.8.8.8");
    s.dnsSrv     = true;

    SettingsDialog dlg;
    dlg.loadSettings(s);

    // Reset
    s.enableSTUN = false;
    s.stun.clear();
    s.dnsSrvNs.clear();
    s.dnsSrv = false;

    dlg.saveSettings(s);

    QCOMPARE(s.enableSTUN, true);
    QCOMPARE(s.stun, QStringLiteral("stun.example.com"));
    QCOMPARE(s.dnsSrvNs, QStringLiteral("8.8.8.8"));
    QCOMPARE(s.dnsSrv, true);

    // Restore
    s.enableSTUN = false;
    s.stun.clear();
    s.dnsSrvNs.clear();
    s.dnsSrv = false;
}

void TestSettingsDialog::testFeaturesFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    s.autoAnswerMode     = QStringLiteral("all");
    s.dtmfMethod         = QStringLiteral("rfc2833");
    s.directoryOfUsers   = QStringLiteral("https://example.com/dir");
    s.defaultListAction  = QStringLiteral("call");
    s.randomPopupPosition = true;
    s.disableNameLookup  = true;

    SettingsDialog dlg;
    dlg.loadSettings(s);

    // Reset
    s.autoAnswerMode.clear();
    s.dtmfMethod.clear();
    s.directoryOfUsers.clear();
    s.defaultListAction.clear();
    s.randomPopupPosition = false;
    s.disableNameLookup   = false;

    dlg.saveSettings(s);

    QCOMPARE(s.autoAnswerMode, QStringLiteral("all"));
    QCOMPARE(s.dtmfMethod, QStringLiteral("rfc2833"));
    QCOMPARE(s.directoryOfUsers, QStringLiteral("https://example.com/dir"));
    QCOMPARE(s.defaultListAction, QStringLiteral("call"));
    QCOMPARE(s.randomPopupPosition, true);
    QCOMPARE(s.disableNameLookup, true);

    // Restore
    s.autoAnswerMode.clear();
    s.dtmfMethod.clear();
    s.directoryOfUsers.clear();
    s.defaultListAction.clear();
    s.randomPopupPosition = false;
    s.disableNameLookup   = false;
}

void TestSettingsDialog::testRecordingFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    s.recordingFormat = QStringLiteral("wav");

    SettingsDialog dlg;
    dlg.loadSettings(s);

    // Reset
    s.recordingFormat = QStringLiteral("mp3");

    dlg.saveSettings(s);
    QCOMPARE(s.recordingFormat, QStringLiteral("wav"));

    // Test mp3 path
    s.recordingFormat = QStringLiteral("mp3");
    dlg.loadSettings(s);
    s.recordingFormat = QStringLiteral("wav");
    dlg.saveSettings(s);
    QCOMPARE(s.recordingFormat, QStringLiteral("mp3"));

    // Restore
    s.recordingFormat = QStringLiteral("mp3");
}

void TestSettingsDialog::testAdvancedFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    s.handleMediaButtons = true;
    s.multiMonitor       = true;
    s.handleIpChanges    = true;
    s.disableMessaging   = true;
    s.enableLog          = true;
    s.enableLocalAccount = true;
    s.crashReport        = true;
    s.updatesInterval    = QStringLiteral("daily");
    s.runAtStartup       = true;
    s.headsetSupport     = true;

    SettingsDialog dlg;
    dlg.loadSettings(s);

    // Reset
    s.handleMediaButtons = false;
    s.multiMonitor       = false;
    s.handleIpChanges    = false;
    s.disableMessaging   = false;
    s.enableLog          = false;
    s.enableLocalAccount = false;
    s.crashReport        = false;
    s.updatesInterval.clear();
    s.runAtStartup       = false;
    s.headsetSupport     = false;

    dlg.saveSettings(s);

    QCOMPARE(s.handleMediaButtons, true);
    QCOMPARE(s.multiMonitor, true);
    QCOMPARE(s.handleIpChanges, true);
    QCOMPARE(s.disableMessaging, true);
    QCOMPARE(s.enableLog, true);
    QCOMPARE(s.enableLocalAccount, true);
    QCOMPARE(s.crashReport, true);
    QCOMPARE(s.updatesInterval, QStringLiteral("daily"));
    QCOMPARE(s.runAtStartup, true);
    QCOMPARE(s.headsetSupport, true);

    // Restore
    s.handleMediaButtons = false;
    s.multiMonitor       = false;
    s.handleIpChanges    = false;
    s.disableMessaging   = false;
    s.enableLog          = false;
    s.enableLocalAccount = false;
    s.crashReport        = false;
    s.updatesInterval.clear();
    s.runAtStartup       = false;
    s.headsetSupport     = false;
}

void TestSettingsDialog::testVideoFieldsRoundTrip()
{
    AppSettings &s = AppSettings::instance();

    s.videoEnabled = false;
    s.videoBitrate = 1024;
    s.videoH264    = true;
    s.videoH263    = true;
    s.videoVP8     = true;
    s.videoVP9     = false;

    SettingsDialog dlg;
    dlg.loadSettings(s);

    // Reset
    s.videoEnabled = true;
    s.videoBitrate = 0;
    s.videoH264    = false;
    s.videoH263    = false;
    s.videoVP8     = false;
    s.videoVP9     = false;

    dlg.saveSettings(s);

    QCOMPARE(s.videoEnabled, false);
    QCOMPARE(s.videoBitrate, 1024);
    QCOMPARE(s.videoH264, true);
    QCOMPARE(s.videoH263, true);
    QCOMPARE(s.videoVP8, true);
    QCOMPARE(s.videoVP9, false);

    // Restore
    s.videoEnabled = true;
    s.videoBitrate = 0;
    s.videoH264    = false;
    s.videoH263    = false;
    s.videoVP8     = false;
    s.videoVP9     = false;
}

void TestSettingsDialog::testTabCount()
{
    SettingsDialog dlg;
    auto *tabs = dlg.findChild<QTabWidget *>();
    QVERIFY(tabs != nullptr);

    // Verify tab names
    QCOMPARE(tabs->tabText(0), dlg.tr("Audio"));
    QCOMPARE(tabs->tabText(1), dlg.tr("Codecs"));
    QCOMPARE(tabs->tabText(2), dlg.tr("Network"));
    QCOMPARE(tabs->tabText(3), dlg.tr("Features"));
    QCOMPARE(tabs->tabText(4), dlg.tr("Recording"));
    QCOMPARE(tabs->tabText(5), dlg.tr("UI"));
    QCOMPARE(tabs->tabText(6), dlg.tr("Advanced"));
    QCOMPARE(tabs->tabText(7), dlg.tr("Video"));
}

QTEST_MAIN(TestSettingsDialog)
#include "test_settingsdialog.moc"
