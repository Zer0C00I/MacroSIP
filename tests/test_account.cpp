#include <QtTest>
#include "models/Account.h"

using namespace macrosip;

class TestAccount : public QObject {
    Q_OBJECT
private slots:
    void testDefaultValues();
    void testIsValid();
    void testSipUri();
    void testSipUriFallbackToServer();
    void testClear();
};

void TestAccount::testDefaultValues()
{
    Account acc;
    QCOMPARE(acc.port, 5060);
    QCOMPARE(acc.registerRefresh, 300);
    QCOMPARE(acc.keepAlive, 15);
    QVERIFY(acc.server.isEmpty());
    QVERIFY(acc.username.isEmpty());
    QVERIFY(acc.domain.isEmpty());
    QVERIFY(acc.password.isEmpty());
    QVERIFY(!acc.publish);
    QVERIFY(!acc.ice);
    QVERIFY(!acc.allowRewrite);
    QVERIFY(!acc.hideCID);
}

void TestAccount::testIsValid()
{
    Account acc;
    QVERIFY(!acc.isValid());

    acc.server = QStringLiteral("sip.example.com");
    QVERIFY(!acc.isValid());

    acc.username = QStringLiteral("user1");
    QVERIFY(acc.isValid());

    // Both fields required
    acc.server.clear();
    QVERIFY(!acc.isValid());
}

void TestAccount::testSipUri()
{
    Account acc;
    acc.username = QStringLiteral("user1");
    acc.domain = QStringLiteral("example.com");
    QCOMPARE(acc.sipUri(), QStringLiteral("sip:user1@example.com"));
}

void TestAccount::testSipUriFallbackToServer()
{
    Account acc;
    acc.username = QStringLiteral("user1");
    acc.server = QStringLiteral("sip.example.com");
    // domain is empty, should fall back to server
    QCOMPARE(acc.sipUri(), QStringLiteral("sip:user1@sip.example.com"));
}

void TestAccount::testClear()
{
    Account acc;
    acc.server = QStringLiteral("sip.example.com");
    acc.username = QStringLiteral("user1");
    acc.domain = QStringLiteral("example.com");
    acc.password = QStringLiteral("secret");
    acc.port = 5080;
    acc.publish = true;
    acc.ice = true;

    acc.clear();

    QVERIFY(acc.server.isEmpty());
    QVERIFY(acc.username.isEmpty());
    QVERIFY(acc.domain.isEmpty());
    QVERIFY(acc.password.isEmpty());
    QCOMPARE(acc.port, 5060);
    QCOMPARE(acc.registerRefresh, 300);
    QCOMPARE(acc.keepAlive, 15);
    QVERIFY(!acc.publish);
    QVERIFY(!acc.ice);
}

QTEST_MAIN(TestAccount)
#include "test_account.moc"
