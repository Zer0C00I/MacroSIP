#pragma once

#include <QDialog>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QList>

namespace macrosip {

struct Shortcut;

class ShortcutsDialog : public QDialog {
    Q_OBJECT

public:
    explicit ShortcutsDialog(QWidget *parent = nullptr);
    ~ShortcutsDialog() override = default;

    void setShortcuts(const QList<Shortcut> &shortcuts);
    QList<Shortcut> shortcuts() const;

private Q_SLOTS:
    void onAccepted();

private:
    void setupUi();

    static constexpr int RowCount = 8;
    static constexpr int ColLabel  = 0;
    static constexpr int ColNumber = 1;
    static constexpr int ColType   = 2;

    QTableWidget *m_table = nullptr;
    QDialogButtonBox *m_buttonBox = nullptr;
};

} // namespace macrosip
