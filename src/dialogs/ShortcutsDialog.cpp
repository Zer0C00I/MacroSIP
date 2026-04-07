#include "ShortcutsDialog.h"
#include "models/Settings.h"

#include <QComboBox>
#include <QHeaderView>
#include <QLineEdit>
#include <QVBoxLayout>

namespace macrosip {

ShortcutsDialog::ShortcutsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Shortcuts"));
    setupUi();
}

void ShortcutsDialog::setShortcuts(const QList<Shortcut> &shortcuts)
{
    for (int row = 0; row < RowCount; ++row) {
        const bool hasData = row < static_cast<int>(shortcuts.size());

        auto *labelEdit = qobject_cast<QLineEdit *>(
            m_table->cellWidget(row, ColLabel));
        auto *numberEdit = qobject_cast<QLineEdit *>(
            m_table->cellWidget(row, ColNumber));
        auto *typeCombo = qobject_cast<QComboBox *>(
            m_table->cellWidget(row, ColType));

        if (labelEdit)
            labelEdit->setText(hasData ? shortcuts[row].label : QString());
        if (numberEdit)
            numberEdit->setText(hasData ? shortcuts[row].number : QString());
        if (typeCombo && hasData)
            typeCombo->setCurrentIndex(shortcuts[row].type);
    }
}

QList<Shortcut> ShortcutsDialog::shortcuts() const
{
    QList<Shortcut> result;
    result.reserve(RowCount);

    for (int row = 0; row < RowCount; ++row) {
        Shortcut s;

        auto *labelEdit = qobject_cast<QLineEdit *>(
            m_table->cellWidget(row, ColLabel));
        auto *numberEdit = qobject_cast<QLineEdit *>(
            m_table->cellWidget(row, ColNumber));
        auto *typeCombo = qobject_cast<QComboBox *>(
            m_table->cellWidget(row, ColType));

        if (labelEdit)  s.label  = labelEdit->text();
        if (numberEdit) s.number = numberEdit->text();
        if (typeCombo)  s.type   = typeCombo->currentIndex();

        result.append(s);
    }
    return result;
}

void ShortcutsDialog::onAccepted()
{
    accept();
}

void ShortcutsDialog::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    m_table = new QTableWidget(RowCount, 3, this);
    m_table->setHorizontalHeaderLabels(
        {tr("Label"), tr("Number"), tr("Type")});
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->verticalHeader()->setVisible(true);

    for (int row = 0; row < RowCount; ++row) {
        auto *labelEdit = new QLineEdit(m_table);
        m_table->setCellWidget(row, ColLabel, labelEdit);

        auto *numberEdit = new QLineEdit(m_table);
        m_table->setCellWidget(row, ColNumber, numberEdit);

        auto *typeCombo = new QComboBox(m_table);
        typeCombo->addItem(tr("Speed Dial"));
        typeCombo->addItem(tr("BLF"));
        typeCombo->addItem(tr("Presence"));
        m_table->setCellWidget(row, ColType, typeCombo);
    }

    mainLayout->addWidget(m_table);

    m_buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &ShortcutsDialog::onAccepted);
    connect(m_buttonBox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    mainLayout->addWidget(m_buttonBox);

    resize(500, 360);
}

} // namespace macrosip
