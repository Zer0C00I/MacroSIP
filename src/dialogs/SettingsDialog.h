#pragma once

#include <QDialog>
#include <QTabWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSlider>
#include <QRadioButton>

namespace macrosip {

class AppSettings;

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() override = default;

    void loadSettings(const AppSettings &settings);
    void saveSettings(AppSettings &settings) const;

private Q_SLOTS:
    void onApply();
    void onBrowseRecordingPath();
    void onCodecMoveUp();
    void onCodecMoveDown();

Q_SIGNALS:
    void applied();

private:
    void setupUi();
    QWidget *createAudioTab();
    QWidget *createCodecsTab();
    QWidget *createNetworkTab();
    QWidget *createFeaturesTab();
    QWidget *createRecordingTab();
    QWidget *createUiTab();
    QWidget *createAdvancedTab();
    QWidget *createVideoTab();

    QTabWidget *m_tabs = nullptr;
    QDialogButtonBox *m_buttonBox = nullptr;

    // Audio
    QComboBox *m_audioInputCombo = nullptr;
    QComboBox *m_audioOutputCombo = nullptr;
    QComboBox *m_audioRingCombo = nullptr;
    QLineEdit *m_ringtoneEdit = nullptr;
    QCheckBox *m_micAmplificationCheck = nullptr;
    QCheckBox *m_localDtmfCheck = nullptr;
    QSlider *m_volumeRingSlider = nullptr;
    QCheckBox *m_opusStereoCheck = nullptr;
    QCheckBox *m_swLevelAdjustCheck = nullptr;
    QCheckBox *m_soundEventsCheck = nullptr;

    // Codecs
    QListWidget *m_codecList = nullptr;
    QCheckBox *m_vadCheck = nullptr;
    QCheckBox *m_ecCheck = nullptr;
    QCheckBox *m_forceCodecCheck = nullptr;

    // Network
    QSpinBox *m_sourcePortSpin = nullptr;
    QSpinBox *m_rtpPortMinSpin = nullptr;
    QSpinBox *m_rtpPortMaxSpin = nullptr;
    QLineEdit *m_stunEdit = nullptr;
    QCheckBox *m_enableStunCheck = nullptr;
    QLineEdit *m_dnsSrvNsEdit = nullptr;
    QCheckBox *m_dnsSrvCheck = nullptr;
    QCheckBox *m_rportCheck = nullptr;

    // Features
    QCheckBox *m_autoAnswerCheck = nullptr;
    QSpinBox *m_autoAnswerDelaySpin = nullptr;
    QComboBox *m_autoAnswerModeCombo = nullptr;
    QCheckBox *m_dndCheck = nullptr;
    QCheckBox *m_callWaitingCheck = nullptr;
    QLineEdit *m_forwardingEdit = nullptr;
    QSpinBox *m_forwardingDelaySpin = nullptr;
    QLineEdit *m_denyIncomingEdit = nullptr;
    QLineEdit *m_directoryEdit = nullptr;
    QComboBox *m_defaultActionCombo = nullptr;
    QCheckBox *m_randomPopupCheck = nullptr;
    QCheckBox *m_disableNameLookupCheck = nullptr;
    QComboBox *m_dtmfMethodCombo = nullptr;

    // Recording
    QLineEdit *m_recordingPathEdit = nullptr;
    QCheckBox *m_autoRecordCheck = nullptr;
    QRadioButton *m_recordMp3Radio = nullptr;
    QRadioButton *m_recordWavRadio = nullptr;

    // UI
    QComboBox *m_langPackCombo = nullptr;
    QCheckBox *m_alwaysOnTopCheck = nullptr;
    QCheckBox *m_bringToFrontCheck = nullptr;

    // Advanced
    QCheckBox *m_handleMediaButtonsCheck = nullptr;
    QCheckBox *m_multiMonitorCheck = nullptr;
    QCheckBox *m_handleIpChangesCheck = nullptr;
    QCheckBox *m_disableMessagingCheck = nullptr;
    QCheckBox *m_enableLogCheck = nullptr;
    QCheckBox *m_enableLocalAccountCheck = nullptr;
    QCheckBox *m_crashReportCheck = nullptr;
    QComboBox *m_updatesIntervalCombo = nullptr;
    QCheckBox *m_runAtStartupCheck = nullptr;
    QCheckBox *m_headsetSupportCheck = nullptr;

    // Video (stub)
    QCheckBox *m_videoEnabledCheck = nullptr;
    QComboBox *m_cameraCombo = nullptr;
    QComboBox *m_videoCodecCombo = nullptr;
    QSpinBox *m_videoBitrateSpin = nullptr;
    QCheckBox *m_videoH264Check = nullptr;
    QCheckBox *m_videoH263Check = nullptr;
    QCheckBox *m_videoVP8Check = nullptr;
    QCheckBox *m_videoVP9Check = nullptr;
};

} // namespace macrosip
