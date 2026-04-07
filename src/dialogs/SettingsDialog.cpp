#include "SettingsDialog.h"
#include "models/Settings.h"

#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace macrosip {

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Settings"));
    setupUi();
}

void SettingsDialog::loadSettings(const AppSettings &s)
{
    // Audio
    m_ringtoneEdit->setText(s.ringtone);
    m_micAmplificationCheck->setChecked(s.micAmplification);
    m_localDtmfCheck->setChecked(s.localDTMF);

    // Select devices by text if present
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
    m_dnsSrvCheck->setChecked(s.dnsSrv);
    m_rportCheck->setChecked(s.rport);

    // Features
    m_autoAnswerCheck->setChecked(s.autoAnswer);
    m_autoAnswerDelaySpin->setValue(s.autoAnswerDelay);
    m_dndCheck->setChecked(s.dnd);
    m_callWaitingCheck->setChecked(s.callWaiting);
    m_forwardingEdit->setText(s.forwardingNumber);
    m_forwardingDelaySpin->setValue(s.forwardingDelay);
    m_denyIncomingEdit->setText(s.denyIncoming);

    // Recording
    m_recordingPathEdit->setText(s.recordingPath);
    m_autoRecordCheck->setChecked(s.autoRecording);

    // UI
    idx = m_langPackCombo->findText(s.langPack);
    if (idx >= 0) m_langPackCombo->setCurrentIndex(idx);
    m_alwaysOnTopCheck->setChecked(s.alwaysOnTop);
    m_bringToFrontCheck->setChecked(s.bringToFrontOnIncoming);
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
    s.dnsSrv     = m_dnsSrvCheck->isChecked();
    s.rport      = m_rportCheck->isChecked();

    // Features
    s.autoAnswer      = m_autoAnswerCheck->isChecked();
    s.autoAnswerDelay = m_autoAnswerDelaySpin->value();
    s.dnd             = m_dndCheck->isChecked();
    s.callWaiting     = m_callWaitingCheck->isChecked();
    s.forwardingNumber = m_forwardingEdit->text();
    s.forwardingDelay  = m_forwardingDelaySpin->value();
    s.denyIncoming     = m_denyIncomingEdit->text();

    // Recording
    s.recordingPath = m_recordingPathEdit->text();
    s.autoRecording = m_autoRecordCheck->isChecked();

    // UI
    s.langPack              = m_langPackCombo->currentText();
    s.alwaysOnTop           = m_alwaysOnTopCheck->isChecked();
    s.bringToFrontOnIncoming = m_bringToFrontCheck->isChecked();
}

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

void SettingsDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    m_tabs = new QTabWidget(this);
    m_tabs->addTab(createAudioTab(), tr("Audio"));
    m_tabs->addTab(createCodecsTab(), tr("Codecs"));
    m_tabs->addTab(createNetworkTab(), tr("Network"));
    m_tabs->addTab(createFeaturesTab(), tr("Features"));
    m_tabs->addTab(createRecordingTab(), tr("Recording"));
    m_tabs->addTab(createUiTab(), tr("UI"));
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

    resize(520, 480);
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

    m_micAmplificationCheck = new QCheckBox(tr("Microphone Amplification"),
                                             widget);
    form->addRow(m_micAmplificationCheck);

    m_localDtmfCheck = new QCheckBox(tr("Local DTMF Feedback"), widget);
    form->addRow(m_localDtmfCheck);

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
    connect(upBtn, &QPushButton::clicked,
            this, &SettingsDialog::onCodecMoveUp);
    btnLayout->addWidget(upBtn);

    auto *downBtn = new QPushButton(tr("Down"), widget);
    connect(downBtn, &QPushButton::clicked,
            this, &SettingsDialog::onCodecMoveDown);
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

    auto *aaLayout = new QHBoxLayout;
    m_autoAnswerCheck = new QCheckBox(tr("Auto-Answer"), widget);
    aaLayout->addWidget(m_autoAnswerCheck);
    m_autoAnswerDelaySpin = new QSpinBox(widget);
    m_autoAnswerDelaySpin->setRange(0, 60);
    m_autoAnswerDelaySpin->setSuffix(tr(" s"));
    aaLayout->addWidget(m_autoAnswerDelaySpin);
    form->addRow(aaLayout);

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

} // namespace macrosip
