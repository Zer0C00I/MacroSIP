#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDialogButtonBox>

namespace macrosip {

class AAOptionsDialog : public QDialog {
    Q_OBJECT

public:
    explicit AAOptionsDialog(QWidget *parent = nullptr);
    ~AAOptionsDialog() override = default;

    void setAutoAnswerEnabled(bool enabled);
    bool autoAnswerEnabled() const;

    void setAutoAnswerDelay(int seconds);
    int autoAnswerDelay() const;

    void setNumberFilter(const QString &filter);
    QString numberFilter() const;

private Q_SLOTS:
    void onAccepted();

private:
    void setupUi();

    QCheckBox *m_enableCheck = nullptr;
    QSpinBox *m_delaySpin = nullptr;
    QLineEdit *m_filterEdit = nullptr;
    QDialogButtonBox *m_buttonBox = nullptr;
};

} // namespace macrosip
