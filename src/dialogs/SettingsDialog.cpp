#include "SettingsDialog.h"
#include "models/Settings.h"

#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

namespace macrosip {

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Settings"));
    setupUi();
}

// ---------------------------------------------------------------------------
// loadSettings / saveSettings
// ---------------------------------------------------------------------------

void SettingsDialog::loadSettings(const AppSettings &s)
{
    // Audio
    m_ringtoneEdit->setText(s.ringtone);
    m_micAmplificationCheck->setChecked(s.micAmplification);
    m_localDtmfCheck->setChecked(s.localDTMF);
    m_volumeRingSlider->setValue(s.volumeRing);
    m_opusStereoCheck->setChecked(s.opusStereo);
    m_swLevelAdjustCheck->setChecked(s.swLevelAdjustment);
    m_soundEventsCheck->setChecked(s.soundEvents);

    int idx = m_audioInputCombo->findText(s.audioInputDevice);
    if (idx >= 0) m_audioInputCombo->setCurrentIndex(idx);
    idx = m_audioOutputCombo->findText(s.audioOutputDevice);
    if (idx >= 0) m_audioOutputCombo->setCurrentIndex(idx);
    idx = m_audioRingCombo->findText(s.audioRingDevice);
    if (idx >= 0) m_audioRingCombo->setCurrentIndex(idx);

    // Codecs
    m_codecList->clear();
    const QStringList codecs = s.audioCodecs.split(QLatin1Char(' '),
                                                    Qt::SkipEmptyParts);
    for (const auto &codec : codecs) {
        auto *item = new QListWidgetItem(codec, m_codecList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
    }
    m_vadCheck->setChecked(s.vad);
    m_ecCheck->setChecked(s.ec);
    m_forceCodecCheck->setChecked(s.forceCodec);

    // Network
    m_sourcePortSpin->setValue(s.sourcePort);
    m_rtpPortMinSpin->setValue(s.rtpPortMin);
    m_rtpPortMaxSpin->setValue(s.rtpPortMax);
    m_stunEdit->setText(s.stun);
    m_enableStunCheck->setChecked(s.enableSTUN);
    m_dnsSrvNsEdit->setText(s.dnsSrvNs);
    m_dnsSrvCheck->setChecked(s.dnsSrv);
    m_rportCheck->setChecked(s.rport);

    // Features
    m_autoAnswerCheck->setChecked(s.autoAnswer);
    m_autoAnswerDelaySpin->setValue(s.autoAnswerDelay);
    idx = m_autoAnswerModeCombo->findData(s.autoAnswerMode);
    if (idx >= 0) m_autoAnswerModeCombo->setCurrentIndex(idx);
    m_dndCheck->setChecked(s.dnd);
    m_callWaitingCheck->setChecked(s.callWaiting);
    m_forwardingEdit->setText(s.forwardingNumber);
    m_forwardingDelaySpin->setValue(s.forwardingDelay);
    m_denyIncomingEdit->setText(s.denyIncoming);
    m_directoryEdit->setText(s.directoryOfUsers);
    idx = m_defaultActionCombo->findData(s.defaultListAction);
    if (idx >= 0) m_defaultActionCombo->setCurrentIndex(idx);
    m_randomPopupCheck->setChecked(s.randomPopupPosition);
    m_disableNameLookupCheck->setChecked(s.disableNameLookup);
    idx = m_dtmfMethodCombo->findData(s.dtmfMethod);
    if (idx >= 0) m_dtmfMethodCombo->setCurrentIndex(idx);

    // Recording
    m_recordingPathEdit->setText(s.recordingPath);
    m_autoRecordCheck->setChecked(s.autoRecording);
    if (s.recordingFormat == QStringLiteral("wav"))
        m_recordWavRadio->setChecked(true);
    else
        m_recordMp3Radio->setChecked(true);

    // UI
    idx = m_langPackCombo->findText(s.langPack);
    if (idx >= 0) m_langPackCombo->setCurrentIndex(idx);
    m_alwaysOnTopCheck->setChecked(s.alwaysOnTop);
    m_bringToFrontCheck->setChecked(s.bringToFrontOnIncoming);

    // Advanced
    m_handleMediaButtonsCheck->setChecked(s.handleMediaButtons);
    m_multiMonitorCheck->setChecked(s.multiMonitor);
    m_handleIpChangesCheck->setChecked(s.handleIpChanges);
    m_disableMessagingCheck->setChecked(s.disableMessaging);
    m_enableLogCheck->setChecked(s.enableLog);
    m_enableLocalAccountCheck->setChecked(s.enableLocalAccount);
    m_crashReportCheck->setChecked(s.crashReport);
    idx = m_updatesIntervalCombo->findData(s.updatesInterval);
    if (idx >= 0) m_updatesIntervalCombo->setCurrentIndex(idx);
    m_runAtStartupCheck->setChecked(s.runAtStartup);
    m_headsetSupportCheck->setChecked(s.headsetSupport);

    // Video
    m_videoEnabledCheck->setChecked(s.videoEnabled);
    m_videoCodecCombo->setCurrentText(s.videoCodec);
    m_videoBitrateSpin->setValue(s.videoBitrate);
    m_videoH264Check->setChecked(s.videoH264);
    m_videoH263Check->setChecked(s.videoH263);
    m_videoVP8Check->setChecked(s.videoVP8);
    m_videoVP9Check->setChecked(s.videoVP9);
    idx = m_cameraCombo->findText(s.cameraDevice);
    if (idx >= 0) m_cameraCombo->setCurrentIndex(idx);
}

void SettingsDialog::saveSettings(AppSettings &s) const
{
    // Audio
    s.audioInputDevice  = m_audioInputCombo->currentText();
    s.audioOutputDevice = m_audioOutputCombo->currentText();
    s.audioRingDevice   = m_audioRingCombo->currentText();
    s.ringtone          = m_ringtoneEdit->text();
    s.micAmplification  = m_micAmplificationCheck->isChecked();
    s.localDTMF         = m_localDtmfCheck->isChecked();
    s.volumeRing        = m_volumeRingSlider->value();
    s.opusStereo        = m_opusStereoCheck->isChecked();
    s.swLevelAdjustment = m_swLevelAdjustCheck->isChecked();
    s.soundEvents       = m_soundEventsCheck->isChecked();

    // Codecs
    QStringList enabledCodecs;
    for (int i = 0; i < m_codecList->count(); ++i) {
        QListWidgetItem *item = m_codecList->item(i);
        if (item->checkState() == Qt::Checked)
            enabledCodecs.append(item->text());
    }
    s.audioCodecs = enabledCodecs.join(QLatin1Char(' '));
    s.vad        = m_vadCheck->isChecked();
    s.ec         = m_ecCheck->isChecked();
    s.forceCodec = m_forceCodecCheck->isChecked();

    // Network
    s.sourcePort = m_sourcePortSpin->value();
    s.rtpPortMin = m_rtpPortMinSpin->value();
    s.rtpPortMax = m_rtpPortMaxSpin->value();
    s.stun       = m_stunEdit->text();
    s.enableSTUN = m_enableStunCheck->isChecked();
    s.dnsSrvNs   = m_dnsSrvNsEdit->text();
    s.dnsSrv     = m_dnsSrvCheck->isChecked();
    s.rport      = m_rportCheck->isChecked();

    // Features
    s.autoAnswer       = m_autoAnswerCheck->isChecked();
    s.autoAnswerDelay  = m_autoAnswerDelaySpin->value();
    s.autoAnswerMode   = m_autoAnswerModeCombo->currentData().toString();
    s.dnd              = m_dndCheck->isChecked();
    s.callWaiting      = m_callWaitingCheck->isChecked();
    s.forwardingNumber = m_forwardingEdit->text();
    s.forwardingDelay  = m_forwardingDelaySpin->value();
    s.denyIncoming     = m_denyIncomingEdit->text();
    s.directoryOfUsers = m_directoryEdit->text();
    s.defaultListAction = m_defaultActionCombo->currentData().toString();
    s.randomPopupPosition = m_randomPopupCheck->isChecked();
    s.disableNameLookup   = m_disableNameLookupCheck->isChecked();
    s.dtmfMethod          = m_dtmfMethodCombo->currentData().toString();

    // Recording
    s.recordingPath   = m_recordingPathEdit->text();
    s.autoRecording   = m_autoRecordCheck->isChecked();
    s.recordingFormat = m_recordWavRadio->isChecked()
                            ? QStringLiteral("wav")
                            : QStringLiteral("mp3");

    // UI
    s.langPack               = m_langPackCombo->currentText();
    s.alwaysOnTop            = m_alwaysOnTopCheck->isChecked();
    s.bringToFrontOnIncoming = m_bringToFrontCheck->isChecked();

    // Advanced
    s.handleMediaButtons = m_handleMediaButtonsCheck->isChecked();
    s.multiMonitor       = m_multiMonitorCheck->isChecked();
    s.handleIpChanges    = m_handleIpChangesCheck->isChecked();
    s.disableMessaging   = m_disableMessagingCheck->isChecked();
    s.enableLog          = m_enableLogCheck->isChecked();
    s.enableLocalAccount = m_enableLocalAccountCheck->isChecked();
    s.crashReport        = m_crashReportCheck->isChecked();
    s.updatesInterval    = m_updatesIntervalCombo->currentData().toString();
    s.runAtStartup       = m_runAtStartupCheck->isChecked();
    s.headsetSupport     = m_headsetSupportCheck->isChecked();

    // Video
    s.videoEnabled = m_videoEnabledCheck->isChecked();
    s.videoCodec   = m_videoCodecCombo->currentText();
    s.videoBitrate = m_videoBitrateSpin->value();
    s.videoH264    = m_videoH264Check->isChecked();
    s.videoH263    = m_videoH263Check->isChecked();
    s.videoVP8     = m_videoVP8Check->isChecked();
    s.videoVP9     = m_videoVP9Check->isChecked();
    s.cameraDevice = m_cameraCombo->currentText();
}

// ---------------------------------------------------------------------------
// Slots
// ---------------------------------------------------------------------------

void SettingsDialog::onApply()
{
    Q_EMIT applied();
}

void SettingsDialog::onBrowseRecordingPath()
{
    const QString dir = QFileDialog::getExistingDirectory(
        this, tr("Select Recording Directory"), m_recordingPathEdit->text());
    if (!dir.isEmpty())
        m_recordingPathEdit->setText(dir);
}

void SettingsDialog::onCodecMoveUp()
{
    const int row = m_codecList->currentRow();
    if (row <= 0)
        return;
    QListWidgetItem *item = m_codecList->takeItem(row);
    m_codecList->insertItem(row - 1, item);
    m_codecList->setCurrentRow(row - 1);
}

void SettingsDialog::onCodecMoveDown()
{
    const int row = m_codecList->currentRow();
    if (row < 0 || row >= m_codecList->count() - 1)
        return;
    QListWidgetItem *item = m_codecList->takeItem(row);
    m_codecList->insertItem(row + 1, item);
    m_codecList->setCurrentRow(row + 1);
}

// ---------------------------------------------------------------------------
// UI setup
// ---------------------------------------------------------------------------

void SettingsDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    m_tabs = new QTabWidget(this);
    m_tabs->addTab(createAudioTab(),     tr("Audio"));
    m_tabs->addTab(createCodecsTab(),    tr("Codecs"));
    m_tabs->addTab(createNetworkTab(),   tr("Network"));
    m_tabs->addTab(createFeaturesTab(),  tr("Features"));
    m_tabs->addTab(createRecordingTab(), tr("Recording"));
    m_tabs->addTab(createUiTab(),        tr("UI"));
    m_tabs->addTab(createAdvancedTab(),  tr("Advanced"));
    m_tabs->addTab(createVideoTab(),     tr("Video"));
    mainLayout->addWidget(m_tabs);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel |
            QDialogButtonBox::Apply,
        this);
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(m_buttonBox->button(QDialogButtonBox::Apply),
            &QPushButton::clicked, this, &SettingsDialog::onApply);
    mainLayout->addWidget(m_buttonBox);

    resize(560, 520);
}

QWidget *SettingsDialog::createAudioTab()
{
    auto *widget = new QWidget(this);
    auto *form = new QFormLayout(widget);

    m_audioInputCombo = new QComboBox(widget);
    form->addRow(tr("Input Device:"), m_audioInputCombo);

    m_audioOutputCombo = new QComboBox(widget);
    form->addRow(tr("Output Device:"), m_audioOutputCombo);

    m_audioRingCombo = new QComboBox(widget);
    form->addRow(tr("Ring Device:"), m_audioRingCombo);

    auto *ringtoneLayout = new QHBoxLayout;
    m_ringtoneEdit = new QLineEdit(widget);
    ringtoneLayout->addWidget(m_ringtoneEdit);
    auto *browseRingtone = new QPushButton(tr("Browse..."), widget);
    connect(browseRingtone, &QPushButton::clicked, this, [this]() {
        const QString file = QFileDialog::getOpenFileName(
            this, tr("Select Ringtone"), m_ringtoneEdit->text(),
            tr("Audio Files (*.wav *.mp3 *.ogg)"));
        if (!file.isEmpty())
            m_ringtoneEdit->setText(file);
    });
    ringtoneLayout->addWidget(browseRingtone);
    form->addRow(tr("Ringtone:"), ringtoneLayout);

    m_volumeRingSlider = new QSlider(Qt::Horizontal, widget);
    m_volumeRingSlider->setRange(0, 100);
    m_volumeRingSlider->setValue(100);
    form->addRow(tr("Ring Volume:"), m_volumeRingSlider);

    m_micAmplificationCheck = new QCheckBox(tr("Microphone Amplification"), widget);
    form->addRow(m_micAmplificationCheck);

    m_swLevelAdjustCheck = new QCheckBox(tr("Software Level Adjustment"), widget);
    form->addRow(m_swLevelAdjustCheck);

    m_opusStereoCheck = new QCheckBox(tr("Opus Stereo"), widget);
    form->addRow(m_opusStereoCheck);

    m_localDtmfCheck = new QCheckBox(tr("Local DTMF Feedback"), widget);
    form->addRow(m_localDtmfCheck);

    m_soundEventsCheck = new QCheckBox(tr("Sound Events"), widget);
    form->addRow(m_soundEventsCheck);

    return widget;
}

QWidget *SettingsDialog::createCodecsTab()
{
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);

    m_codecList = new QListWidget(widget);
    layout->addWidget(m_codecList);

    auto *btnLayout = new QHBoxLayout;
    auto *upBtn = new QPushButton(tr("Up"), widget);
    connect(upBtn, &QPushButton::clicked, this, &SettingsDialog::onCodecMoveUp);
    btnLayout->addWidget(upBtn);

    auto *downBtn = new QPushButton(tr("Down"), widget);
    connect(downBtn, &QPushButton::clicked, this, &SettingsDialog::onCodecMoveDown);
    btnLayout->addWidget(downBtn);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    m_vadCheck = new QCheckBox(tr("Voice Activity Detection (VAD)"), widget);
    layout->addWidget(m_vadCheck);

    m_ecCheck = new QCheckBox(tr("Echo Cancellation (EC)"), widget);
    layout->addWidget(m_ecCheck);

    m_forceCodecCheck = new QCheckBox(tr("Force Codec"), widget);
    layout->addWidget(m_forceCodecCheck);

    return widget;
}

QWidget *SettingsDialog::createNetworkTab()
{
    auto *widget = new QWidget(this);
    auto *form = new QFormLayout(widget);

    m_sourcePortSpin = new QSpinBox(widget);
    m_sourcePortSpin->setRange(1, 65535);
    m_sourcePortSpin->setValue(5060);
    form->addRow(tr("Source Port:"), m_sourcePortSpin);

    m_rtpPortMinSpin = new QSpinBox(widget);
    m_rtpPortMinSpin->setRange(1, 65535);
    m_rtpPortMinSpin->setValue(5000);
    form->addRow(tr("RTP Port Min:"), m_rtpPortMinSpin);

    m_rtpPortMaxSpin = new QSpinBox(widget);
    m_rtpPortMaxSpin->setRange(1, 65535);
    m_rtpPortMaxSpin->setValue(5100);
    form->addRow(tr("RTP Port Max:"), m_rtpPortMaxSpin);

    m_stunEdit = new QLineEdit(widget);
    m_stunEdit->setPlaceholderText(tr("stun.example.com"));
    form->addRow(tr("STUN Server:"), m_stunEdit);

    m_enableStunCheck = new QCheckBox(tr("Enable STUN"), widget);
    form->addRow(m_enableStunCheck);

    m_dnsSrvNsEdit = new QLineEdit(widget);
    m_dnsSrvNsEdit->setPlaceholderText(tr("8.8.8.8; 8.8.4.4"));
    form->addRow(tr("DNS SRV Nameserver:"), m_dnsSrvNsEdit);

    m_dnsSrvCheck = new QCheckBox(tr("DNS SRV Lookup"), widget);
    form->addRow(m_dnsSrvCheck);

    m_rportCheck = new QCheckBox(tr("Use rport"), widget);
    form->addRow(m_rportCheck);

    return widget;
}

QWidget *SettingsDialog::createFeaturesTab()
{
    auto *widget = new QWidget(this);
    auto *form = new QFormLayout(widget);

    // Auto answer
    auto *aaLayout = new QHBoxLayout;
    m_autoAnswerCheck = new QCheckBox(tr("Auto-Answer"), widget);
    aaLayout->addWidget(m_autoAnswerCheck);
    m_autoAnswerDelaySpin = new QSpinBox(widget);
    m_autoAnswerDelaySpin->setRange(0, 60);
    m_autoAnswerDelaySpin->setSuffix(tr(" s"));
    aaLayout->addWidget(m_autoAnswerDelaySpin);
    form->addRow(aaLayout);

    m_autoAnswerModeCombo = new QComboBox(widget);
    m_autoAnswerModeCombo->addItem(tr("No"), QString());
    m_autoAnswerModeCombo->addItem(tr("Control Button"), QStringLiteral("button"));
    m_autoAnswerModeCombo->addItem(tr("SIP Header"), QStringLiteral("header"));
    m_autoAnswerModeCombo->addItem(tr("All Calls"), QStringLiteral("all"));
    form->addRow(tr("Auto-Answer Mode:"), m_autoAnswerModeCombo);

    // DTMF method
    m_dtmfMethodCombo = new QComboBox(widget);
    m_dtmfMethodCombo->addItem(tr("Auto"), QString());
    m_dtmfMethodCombo->addItem(tr("In-band"), QStringLiteral("inband"));
    m_dtmfMethodCombo->addItem(tr("RFC2833"), QStringLiteral("rfc2833"));
    m_dtmfMethodCombo->addItem(tr("SIP-INFO"), QStringLiteral("sipinfo"));
    form->addRow(tr("DTMF Method:"), m_dtmfMethodCombo);

    m_dndCheck = new QCheckBox(tr("Do Not Disturb"), widget);
    form->addRow(m_dndCheck);

    m_callWaitingCheck = new QCheckBox(tr("Call Waiting"), widget);
    form->addRow(m_callWaitingCheck);

    m_forwardingEdit = new QLineEdit(widget);
    m_forwardingEdit->setPlaceholderText(tr("Forwarding number"));
    form->addRow(tr("Forwarding:"), m_forwardingEdit);

    m_forwardingDelaySpin = new QSpinBox(widget);
    m_forwardingDelaySpin->setRange(0, 120);
    m_forwardingDelaySpin->setSuffix(tr(" s"));
    form->addRow(tr("Forward Delay:"), m_forwardingDelaySpin);

    m_denyIncomingEdit = new QLineEdit(widget);
    m_denyIncomingEdit->setPlaceholderText(tr("Pattern to deny"));
    form->addRow(tr("Deny Incoming:"), m_denyIncomingEdit);

    m_directoryEdit = new QLineEdit(widget);
    m_directoryEdit->setPlaceholderText(tr("URL of users directory"));
    form->addRow(tr("Directory of Users:"), m_directoryEdit);

    m_defaultActionCombo = new QComboBox(widget);
    m_defaultActionCombo->addItem(tr("Default"), QString());
    m_defaultActionCombo->addItem(tr("Call"), QStringLiteral("call"));
    m_defaultActionCombo->addItem(tr("Message"), QStringLiteral("message"));
    form->addRow(tr("Default List Action:"), m_defaultActionCombo);

    m_randomPopupCheck = new QCheckBox(tr("Random Popup Position"), widget);
    form->addRow(m_randomPopupCheck);

    m_disableNameLookupCheck = new QCheckBox(tr("Disable Name Lookup"), widget);
    form->addRow(m_disableNameLookupCheck);

    return widget;
}

QWidget *SettingsDialog::createRecordingTab()
{
    auto *widget = new QWidget(this);
    auto *form = new QFormLayout(widget);

    auto *pathLayout = new QHBoxLayout;
    m_recordingPathEdit = new QLineEdit(widget);
    pathLayout->addWidget(m_recordingPathEdit);
    auto *browseBtn = new QPushButton(tr("Browse..."), widget);
    connect(browseBtn, &QPushButton::clicked,
            this, &SettingsDialog::onBrowseRecordingPath);
    pathLayout->addWidget(browseBtn);
    form->addRow(tr("Recording Path:"), pathLayout);

    m_autoRecordCheck = new QCheckBox(tr("Auto-Record Calls"), widget);
    form->addRow(m_autoRecordCheck);

    // Recording format
    auto *formatGroup = new QGroupBox(tr("Recording Format"), widget);
    auto *formatLayout = new QHBoxLayout(formatGroup);
    m_recordMp3Radio = new QRadioButton(tr("MP3"), formatGroup);
    m_recordWavRadio = new QRadioButton(tr("WAV"), formatGroup);
    m_recordMp3Radio->setChecked(true);
    formatLayout->addWidget(m_recordMp3Radio);
    formatLayout->addWidget(m_recordWavRadio);
    form->addRow(formatGroup);

    return widget;
}

QWidget *SettingsDialog::createUiTab()
{
    auto *widget = new QWidget(this);
    auto *form = new QFormLayout(widget);

    m_langPackCombo = new QComboBox(widget);
    m_langPackCombo->addItem(tr("Default (English)"));
    form->addRow(tr("Language Pack:"), m_langPackCombo);

    m_alwaysOnTopCheck = new QCheckBox(tr("Always on Top"), widget);
    form->addRow(m_alwaysOnTopCheck);

    m_bringToFrontCheck = new QCheckBox(
        tr("Bring to Front on Incoming Call"), widget);
    form->addRow(m_bringToFrontCheck);

    return widget;
}

QWidget *SettingsDialog::createAdvancedTab()
{
    auto *widget = new QWidget(this);
    auto *form = new QFormLayout(widget);

    m_handleMediaButtonsCheck = new QCheckBox(tr("Handle Media Buttons"), widget);
    form->addRow(m_handleMediaButtonsCheck);

    m_multiMonitorCheck = new QCheckBox(tr("Multi-Monitor Support"), widget);
    form->addRow(m_multiMonitorCheck);

    m_handleIpChangesCheck = new QCheckBox(tr("Handle IP Changes"), widget);
    form->addRow(m_handleIpChangesCheck);

    m_disableMessagingCheck = new QCheckBox(tr("Disable Messaging"), widget);
    form->addRow(m_disableMessagingCheck);

    m_enableLogCheck = new QCheckBox(tr("Enable Log File"), widget);
    form->addRow(m_enableLogCheck);

    m_enableLocalAccountCheck = new QCheckBox(tr("Enable Local Account"), widget);
    form->addRow(m_enableLocalAccountCheck);

    m_crashReportCheck = new QCheckBox(tr("Send Crash Report"), widget);
    form->addRow(m_crashReportCheck);

    m_updatesIntervalCombo = new QComboBox(widget);
    m_updatesIntervalCombo->addItem(tr("Weekly"),    QString());
    m_updatesIntervalCombo->addItem(tr("Daily"),     QStringLiteral("daily"));
    m_updatesIntervalCombo->addItem(tr("Monthly"),   QStringLiteral("monthly"));
    m_updatesIntervalCombo->addItem(tr("Quarterly"), QStringLiteral("quarterly"));
    m_updatesIntervalCombo->addItem(tr("Never"),     QStringLiteral("never"));
    form->addRow(tr("Check for Updates:"), m_updatesIntervalCombo);

    m_runAtStartupCheck = new QCheckBox(tr("Run at System Startup"), widget);
    form->addRow(m_runAtStartupCheck);

    m_headsetSupportCheck = new QCheckBox(tr("Headset Support"), widget);
    form->addRow(m_headsetSupportCheck);

    return widget;
}

QWidget *SettingsDialog::createVideoTab()
{
    auto *widget = new QWidget(this);
    auto *form = new QFormLayout(widget);

    auto *noteLabel = new QLabel(
        tr("Video support is a stub — real PJSIP video is not yet implemented."),
        widget);
    noteLabel->setWordWrap(true);
    form->addRow(noteLabel);

    m_videoEnabledCheck = new QCheckBox(tr("Enable Video"), widget);
    form->addRow(m_videoEnabledCheck);

    m_cameraCombo = new QComboBox(widget);
    m_cameraCombo->setEditable(true);
    form->addRow(tr("Camera:"), m_cameraCombo);

    m_videoCodecCombo = new QComboBox(widget);
    m_videoCodecCombo->setEditable(true);
    form->addRow(tr("Video Codec:"), m_videoCodecCombo);

    m_videoBitrateSpin = new QSpinBox(widget);
    m_videoBitrateSpin->setRange(0, 100000);
    m_videoBitrateSpin->setSuffix(tr(" kbps"));
    form->addRow(tr("Video Bitrate:"), m_videoBitrateSpin);

    m_videoH264Check = new QCheckBox(tr("H.264"), widget);
    m_videoH263Check = new QCheckBox(tr("H.263"), widget);
    m_videoVP8Check  = new QCheckBox(tr("VP8"), widget);
    m_videoVP9Check  = new QCheckBox(tr("VP9"), widget);

    auto *codecCheckLayout = new QHBoxLayout;
    codecCheckLayout->addWidget(m_videoH264Check);
    codecCheckLayout->addWidget(m_videoH263Check);
    codecCheckLayout->addWidget(m_videoVP8Check);
    codecCheckLayout->addWidget(m_videoVP9Check);
    form->addRow(tr("Enabled Codecs:"), codecCheckLayout);

    return widget;
}

} // namespace macrosip
