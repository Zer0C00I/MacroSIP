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

    QTabWidget *m_tabs = nullptr;
    QDialogButtonBox *m_buttonBox = nullptr;

    // Audio
    QComboBox *m_audioInputCombo = nullptr;
    QComboBox *m_audioOutputCombo = nullptr;
    QComboBox *m_audioRingCombo = nullptr;
    QLineEdit *m_ringtoneEdit = nullptr;
    QCheckBox *m_micAmplificationCheck = nullptr;
    QCheckBox *m_localDtmfCheck = nullptr;

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
    QCheckBox *m_dnsSrvCheck = nullptr;
    QCheckBox *m_rportCheck = nullptr;

    // Features
    QCheckBox *m_autoAnswerCheck = nullptr;
    QSpinBox *m_autoAnswerDelaySpin = nullptr;
    QCheckBox *m_dndCheck = nullptr;
    QCheckBox *m_callWaitingCheck = nullptr;
    QLineEdit *m_forwardingEdit = nullptr;
    QSpinBox *m_forwardingDelaySpin = nullptr;
    QLineEdit *m_denyIncomingEdit = nullptr;

    // Recording
    QLineEdit *m_recordingPathEdit = nullptr;
    QCheckBox *m_autoRecordCheck = nullptr;

    // UI
    QComboBox *m_langPackCombo = nullptr;
    QCheckBox *m_alwaysOnTopCheck = nullptr;
    QCheckBox *m_bringToFrontCheck = nullptr;
};

} // namespace macrosip
