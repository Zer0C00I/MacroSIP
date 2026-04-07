#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>

namespace macrosip {

struct Contact;

class AddContactDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddContactDialog(QWidget *parent = nullptr);
    ~AddContactDialog() override = default;

    void setContact(const Contact &contact);
    Contact contact() const;

private Q_SLOTS:
    void onAccepted();

private:
    void setupUi();

    QLineEdit *m_nameEdit = nullptr;
    QLineEdit *m_numberEdit = nullptr;
    QLineEdit *m_firstnameEdit = nullptr;
    QLineEdit *m_lastnameEdit = nullptr;
    QLineEdit *m_phoneEdit = nullptr;
    QLineEdit *m_mobileEdit = nullptr;
    QLineEdit *m_emailEdit = nullptr;
    QLineEdit *m_addressEdit = nullptr;
    QLineEdit *m_cityEdit = nullptr;
    QLineEdit *m_stateEdit = nullptr;
    QLineEdit *m_zipEdit = nullptr;
    QLineEdit *m_commentEdit = nullptr;
    QCheckBox *m_presenceCheck = nullptr;
    QCheckBox *m_starredCheck = nullptr;
    QDialogButtonBox *m_buttonBox = nullptr;
};

} // namespace macrosip
