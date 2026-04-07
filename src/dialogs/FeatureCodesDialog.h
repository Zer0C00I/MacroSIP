#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>

namespace macrosip {

class FeatureCodesDialog : public QDialog {
    Q_OBJECT

public:
    explicit FeatureCodesDialog(QWidget *parent = nullptr);
    ~FeatureCodesDialog() override = default;

    // Call parking
    void setCallParkCode(const QString &code);
    QString callParkCode() const;
    void setCallParkEnabled(bool enabled);
    bool callParkEnabled() const;

    // Blind transfer
    void setBlindTransferCode(const QString &code);
    QString blindTransferCode() const;
    void setBlindTransferEnabled(bool enabled);
    bool blindTransferEnabled() const;

    // Attended transfer
    void setAttendedTransferCode(const QString &code);
    QString attendedTransferCode() const;
    void setAttendedTransferEnabled(bool enabled);
    bool attendedTransferEnabled() const;

private Q_SLOTS:
    void onAccepted();

private:
    void setupUi();

    QLineEdit *m_callParkEdit = nullptr;
    QCheckBox *m_callParkCheck = nullptr;

    QLineEdit *m_blindTransferEdit = nullptr;
    QCheckBox *m_blindTransferCheck = nullptr;

    QLineEdit *m_attendedTransferEdit = nullptr;
    QCheckBox *m_attendedTransferCheck = nullptr;

    QDialogButtonBox *m_buttonBox = nullptr;
};

} // namespace macrosip
