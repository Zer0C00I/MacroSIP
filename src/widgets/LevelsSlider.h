#pragma once

#include <QWidget>
#include <QSlider>
#include <QProgressBar>
#include <QHBoxLayout>

namespace macrosip {

class LevelsSlider : public QWidget {
    Q_OBJECT

public:
    explicit LevelsSlider(QWidget *parent = nullptr);
    ~LevelsSlider() override = default;

    void setVolume(int vol);
    int volume() const;
    void setLevel(int level);
    void setMuted(bool muted);
    bool isMuted() const;

Q_SIGNALS:
    void volumeChanged(int value);

private Q_SLOTS:
    void onSliderValueChanged(int value);

private:
    void setupUi();
    void updateMutedAppearance();

    QSlider *m_slider = nullptr;
    QProgressBar *m_vuMeter = nullptr;
    bool m_muted = false;
};

} // namespace macrosip
