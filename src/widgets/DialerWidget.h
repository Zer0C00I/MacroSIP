#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>

namespace macrosip {

class DialerWidget : public QWidget {
    Q_OBJECT

public:
    explicit DialerWidget(QWidget *parent = nullptr);
    ~DialerWidget() override = default;

    QString currentNumber() const;
    void setNumber(const QString &number);
    void setStatusText(const QString &text);
    void clear();

Q_SIGNALS:
    void callRequested(const QString &number);
    void hangupRequested();
    void dtmfPressed(const QString &digit);

private Q_SLOTS:
    void onDigitClicked();
    void onCallClicked();
    void onHangupClicked();

private:
    void setupUi();
    QPushButton *createDigitButton(const QString &digit, const QString &letters);

    QLineEdit *m_numberInput = nullptr;
    QLabel *m_statusLabel = nullptr;
    QPushButton *m_callButton = nullptr;
    QPushButton *m_hangupButton = nullptr;
    QGridLayout *m_dialpadLayout = nullptr;
};

} // namespace macrosip
