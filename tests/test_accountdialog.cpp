#include <QtTest>
#include "dialogs/AccountDialog.h"
#include "models/Account.h"

using namespace macrosip;

class TestAccountDialog : public QObject {
    Q_OBJECT
private slots:
    void testConstruction();
    void testSetAccountGetAccount();
    void testRoundTrip();
};

void TestAccountDialog::testConstruction()
{
    AccountDialog dlg;
    Account acc = dlg.account();
    // Default should be empty
    QVERIFY(acc.server.isEmpty());
    QVERIFY(acc.username.isEmpty());
}

void TestAccountDialog::testSetAccountGetAccount()
{
    AccountDialog dlg;
    Account acc;
    acc.server = QStringLiteral("sip.example.com");
    acc.username = QStringLiteral("user1");
    acc.domain = QStringLiteral("example.com");
    acc.password = QStringLiteral("secret");
    acc.port = 5080;
    acc.publish = true;
    acc.ice = true;

    dlg.setAccount(acc);
    Account result = dlg.account();

    QCOMPARE(result.server, QStringLiteral("sip.example.com"));
    QCOMPARE(result.username, QStringLiteral("user1"));
    QCOMPARE(result.domain, QStringLiteral("example.com"));
    QCOMPARE(result.password, QStringLiteral("secret"));
    QCOMPARE(result.port, 5080);
    QCOMPARE(result.publish, true);
    QCOMPARE(result.ice, true);
}

void TestAccountDialog::testRoundTrip()
{
    AccountDialog dlg;
    Account acc;
    acc.label = QStringLiteral("Work");
    acc.server = QStringLiteral("pbx.corp.com");
    acc.proxy = QStringLiteral("proxy.corp.com");
    acc.username = QStringLiteral("ext100");
    acc.domain = QStringLiteral("corp.com");
    acc.authID = QStringLiteral("auth100");
    acc.displayName = QStringLiteral("John Doe");
    acc.dialingPrefix = QStringLiteral("9");
    acc.port = 5070;
    acc.registerRefresh = 600;
    acc.keepAlive = 30;
    acc.allowRewrite = true;
    acc.hideCID = true;

    dlg.setAccount(acc);
    Account result = dlg.account();

    QCOMPARE(result.label, acc.label);
    QCOMPARE(result.server, acc.server);
    QCOMPARE(result.proxy, acc.proxy);
    QCOMPARE(result.username, acc.username);
    QCOMPARE(result.domain, acc.domain);
    QCOMPARE(result.authID, acc.authID);
    QCOMPARE(result.displayName, acc.displayName);
    QCOMPARE(result.dialingPrefix, acc.dialingPrefix);
    QCOMPARE(result.port, acc.port);
    QCOMPARE(result.registerRefresh, acc.registerRefresh);
    QCOMPARE(result.keepAlive, acc.keepAlive);
    QCOMPARE(result.allowRewrite, acc.allowRewrite);
    QCOMPARE(result.hideCID, acc.hideCID);
}

QTEST_MAIN(TestAccountDialog)
#include "test_accountdialog.moc"
