#include "LevelsSlider.h"

namespace macrosip {

LevelsSlider::LevelsSlider(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void LevelsSlider::setVolume(int vol)
{
    m_slider->setValue(vol);
}

int LevelsSlider::volume() const
{
    return m_slider->value();
}

void LevelsSlider::setLevel(int level)
{
    m_vuMeter->setValue(level);
}

void LevelsSlider::setMuted(bool muted)
{
    m_muted = muted;
    updateMutedAppearance();
}

bool LevelsSlider::isMuted() const
{
    return m_muted;
}

void LevelsSlider::onSliderValueChanged(int value)
{
    Q_EMIT volumeChanged(value);
}

void LevelsSlider::setupUi()
{
    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, 100);
    m_slider->setValue(80);
    connect(m_slider, &QSlider::valueChanged,
            this, &LevelsSlider::onSliderValueChanged);
    layout->addWidget(m_slider, 3);

    m_vuMeter = new QProgressBar(this);
    m_vuMeter->setRange(0, 100);
    m_vuMeter->setValue(0);
    m_vuMeter->setTextVisible(false);
    m_vuMeter->setFixedHeight(16);
    layout->addWidget(m_vuMeter, 1);
}

void LevelsSlider::updateMutedAppearance()
{
    m_slider->setEnabled(!m_muted);
    if (m_muted) {
        m_slider->setStyleSheet(
            QStringLiteral("QSlider::groove:horizontal { background: #ccc; }"));
        m_vuMeter->setStyleSheet(
            QStringLiteral("QProgressBar::chunk { background: #999; }"));
    } else {
        m_slider->setStyleSheet(QString());
        m_vuMeter->setStyleSheet(QString());
    }
}

} // namespace macrosip
