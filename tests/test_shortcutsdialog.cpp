#include <QtTest>
#include "dialogs/ShortcutsDialog.h"
#include "models/Settings.h"

using namespace macrosip;

class TestShortcutsDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testSetShortcutsGetShortcuts();
    void testEmptyShortcuts();
    void testMaxShortcuts();
};

void TestShortcutsDialog::testConstruction()
{
    ShortcutsDialog dlg;
    QList<Shortcut> shortcuts = dlg.shortcuts();
    // Default should have RowCount empty entries
    QCOMPARE(shortcuts.size(), 8);
}

void TestShortcutsDialog::testSetShortcutsGetShortcuts()
{
    ShortcutsDialog dlg;

    QList<Shortcut> input;
    Shortcut s1;
    s1.label = QStringLiteral("Speed 1");
    s1.number = QStringLiteral("100");
    s1.type = 0;
    input.append(s1);

    Shortcut s2;
    s2.label = QStringLiteral("Speed 2");
    s2.number = QStringLiteral("200");
    s2.type = 1;
    input.append(s2);

    dlg.setShortcuts(input);
    QList<Shortcut> result = dlg.shortcuts();

    // Should have at least the entries we set
    QVERIFY(result.size() >= 2);
    QCOMPARE(result[0].label, QStringLiteral("Speed 1"));
    QCOMPARE(result[0].number, QStringLiteral("100"));
    QCOMPARE(result[0].type, 0);
    QCOMPARE(result[1].label, QStringLiteral("Speed 2"));
    QCOMPARE(result[1].number, QStringLiteral("200"));
    QCOMPARE(result[1].type, 1);
}

void TestShortcutsDialog::testEmptyShortcuts()
{
    ShortcutsDialog dlg;
    QList<Shortcut> empty;
    dlg.setShortcuts(empty);

    QList<Shortcut> result = dlg.shortcuts();
    // Should have RowCount entries (all empty)
    QCOMPARE(result.size(), 8);
    for (const Shortcut &s : result) {
        QVERIFY(s.label.isEmpty());
        QVERIFY(s.number.isEmpty());
    }
}

void TestShortcutsDialog::testMaxShortcuts()
{
    ShortcutsDialog dlg;

    QList<Shortcut> input;
    for (int i = 0; i < 8; ++i) {
        Shortcut s;
        s.label = QStringLiteral("Key %1").arg(i + 1);
        s.number = QStringLiteral("%1").arg((i + 1) * 100);
        s.type = i % 2;
        input.append(s);
    }

    dlg.setShortcuts(input);
    QList<Shortcut> result = dlg.shortcuts();

    QCOMPARE(result.size(), 8);
    for (int i = 0; i < 8; ++i) {
        QCOMPARE(result[i].label, QStringLiteral("Key %1").arg(i + 1));
        QCOMPARE(result[i].number, QStringLiteral("%1").arg((i + 1) * 100));
    }
}

QTEST_MAIN(TestShortcutsDialog)
#include "test_shortcutsdialog.moc"
