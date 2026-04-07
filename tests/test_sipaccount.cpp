#include <QtTest>
#include <QSignalSpy>
#include "sip/SipAccount.h"

using namespace macrosip;

class TestSipAccount : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testConfigureValid();
    void testConfigureInvalid();
    void testRegisterStub();
    void testUnregister();
    void testIsRegistered();
    void testHandleRegistrationState();
    void testRegistrationStateSignal();
    void testDoubleUnregister();
};

void TestSipAccount::testDefaultState()
{
    SipAccount acc;
    QCOMPARE(acc.accountId(), -1);
    QCOMPARE(acc.registrationState(), RegistrationState::Unregistered);
    QVERIFY(!acc.isRegistered());
}

void TestSipAccount::testConfigureValid()
{
    SipAccount acc;
    Account cfg;
    cfg.server = QStringLiteral("sip.example.com");
    cfg.username = QStringLiteral("user1");

    QVERIFY(acc.configure(cfg));
}

void TestSipAccount::testConfigureInvalid()
{
    SipAccount acc;
    Account cfg;  // empty, invalid
    QVERIFY(!acc.configure(cfg));
}

void TestSipAccount::testRegisterStub()
{
    SipAccount acc;
    Account cfg;
    cfg.server = QStringLiteral("sip.example.com");
    cfg.username = QStringLiteral("user1");

    QVERIFY(acc.configure(cfg));

    QSignalSpy spy(&acc, &SipAccount::registrationStateChanged);
    QVERIFY(acc.registerAccount());

    // In stub mode, registerAccount() immediately sets Registered
    QCOMPARE(acc.registrationState(), RegistrationState::Registered);
    QVERIFY(acc.isRegistered());
    QCOMPARE(acc.accountId(), 1);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<RegistrationState>(),
             RegistrationState::Registered);
}

void TestSipAccount::testUnregister()
{
    SipAccount acc;
    Account cfg;
    cfg.server = QStringLiteral("sip.example.com");
    cfg.username = QStringLiteral("user1");

    acc.configure(cfg);
    acc.registerAccount();

    QSignalSpy spy(&acc, &SipAccount::registrationStateChanged);
    acc.unregisterAccount();

    QCOMPARE(acc.registrationState(), RegistrationState::Unregistered);
    QCOMPARE(acc.accountId(), -1);
    QVERIFY(!acc.isRegistered());
    QCOMPARE(spy.count(), 1);
}

void TestSipAccount::testIsRegistered()
{
    SipAccount acc;
    QVERIFY(!acc.isRegistered());

    acc.handleRegistrationState(RegistrationState::Registered, 200,
                                QStringLiteral("OK"));
    QVERIFY(acc.isRegistered());

    acc.handleRegistrationState(RegistrationState::Error, 403,
                                QStringLiteral("Forbidden"));
    QVERIFY(!acc.isRegistered());
}

void TestSipAccount::testHandleRegistrationState()
{
    SipAccount acc;
    QSignalSpy spy(&acc, &SipAccount::registrationStateChanged);

    acc.handleRegistrationState(RegistrationState::Registering, 100,
                                QStringLiteral("Trying"));
    QCOMPARE(acc.registrationState(), RegistrationState::Registering);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(1).toInt(), 100);
    QCOMPARE(spy.at(0).at(2).toString(), QStringLiteral("Trying"));
}

void TestSipAccount::testRegistrationStateSignal()
{
    SipAccount acc;
    QSignalSpy spy(&acc, &SipAccount::registrationStateChanged);

    acc.handleRegistrationState(RegistrationState::Registering, 100, QStringLiteral("Trying"));
    acc.handleRegistrationState(RegistrationState::Registered, 200, QStringLiteral("OK"));
    acc.handleRegistrationState(RegistrationState::Error, 403, QStringLiteral("Forbidden"));

    QCOMPARE(spy.count(), 3);
}

void TestSipAccount::testDoubleUnregister()
{
    SipAccount acc;
    QSignalSpy spy(&acc, &SipAccount::registrationStateChanged);

    // Unregistering without registering should be a no-op
    acc.unregisterAccount();
    QCOMPARE(spy.count(), 0);
}

QTEST_GUILESS_MAIN(TestSipAccount)
#include "test_sipaccount.moc"
