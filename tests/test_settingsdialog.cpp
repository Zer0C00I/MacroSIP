#include <QtTest>
#include "dialogs/SettingsDialog.h"
#include "models/Settings.h"

using namespace macrosip;

class TestSettingsDialog : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testLoadSaveRoundTrip();
};

void TestSettingsDialog::testDefaultState()
{
    SettingsDialog dlg;
    // Dialog should be constructible and have child widgets
    QVERIFY(dlg.children().count() > 0);
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

QTEST_MAIN(TestSettingsDialog)
#include "test_settingsdialog.moc"
