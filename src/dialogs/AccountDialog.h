#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDialogButtonBox>

namespace macrosip {

struct Account;

class AccountDialog : public QDialog {
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = nullptr);
    ~AccountDialog() override = default;

    void setAccount(const Account &account);
    Account account() const;

private Q_SLOTS:
    void onAccepted();

private:
    void setupUi();

    // Text fields
    QLineEdit *m_labelEdit = nullptr;
    QLineEdit *m_serverEdit = nullptr;
    QLineEdit *m_proxyEdit = nullptr;
    QLineEdit *m_usernameEdit = nullptr;
    QLineEdit *m_domainEdit = nullptr;
    QLineEdit *m_authIdEdit = nullptr;
    QLineEdit *m_passwordEdit = nullptr;
    QLineEdit *m_displayNameEdit = nullptr;
    QLineEdit *m_dialingPrefixEdit = nullptr;
    QLineEdit *m_dialPlanEdit = nullptr;
    QLineEdit *m_publicAddrEdit = nullptr;

    // Numeric fields
    QSpinBox *m_portSpin = nullptr;
    QSpinBox *m_refreshSpin = nullptr;
    QSpinBox *m_keepAliveSpin = nullptr;

    // Combo boxes
    QComboBox *m_transportCombo = nullptr;
    QComboBox *m_srtpCombo = nullptr;

    // Check boxes
    QCheckBox *m_publishCheck = nullptr;
    QCheckBox *m_iceCheck = nullptr;
    QCheckBox *m_allowRewriteCheck = nullptr;
    QCheckBox *m_hideCidCheck = nullptr;

    QDialogButtonBox *m_buttonBox = nullptr;
};

} // namespace macrosip
