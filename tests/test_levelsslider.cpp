#include <QtTest>
#include <QSignalSpy>
#include "widgets/LevelsSlider.h"

using namespace macrosip;

class TestLevelsSlider : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testSetVolume();
    void testSetMuted();
    void testIsMuted();
    void testSetLevel();
    void testVolumeChangedSignal();
};

void TestLevelsSlider::testDefaultState()
{
    LevelsSlider slider;
    QVERIFY(!slider.isMuted());
    // Default volume should be reasonable (0-100)
    QVERIFY(slider.volume() >= 0);
    QVERIFY(slider.volume() <= 100);
}

void TestLevelsSlider::testSetVolume()
{
    LevelsSlider slider;
    slider.setVolume(75);
    QCOMPARE(slider.volume(), 75);

    slider.setVolume(0);
    QCOMPARE(slider.volume(), 0);

    slider.setVolume(100);
    QCOMPARE(slider.volume(), 100);
}

void TestLevelsSlider::testSetMuted()
{
    LevelsSlider slider;
    QVERIFY(!slider.isMuted());

    slider.setMuted(true);
    QVERIFY(slider.isMuted());

    slider.setMuted(false);
    QVERIFY(!slider.isMuted());
}

void TestLevelsSlider::testIsMuted()
{
    LevelsSlider slider;
    slider.setMuted(true);
    QVERIFY(slider.isMuted());
    slider.setMuted(false);
    QVERIFY(!slider.isMuted());
}

void TestLevelsSlider::testSetLevel()
{
    LevelsSlider slider;
    // setLevel updates the VU meter, should not crash
    slider.setLevel(0);
    slider.setLevel(50);
    slider.setLevel(100);
}

void TestLevelsSlider::testVolumeChangedSignal()
{
    LevelsSlider slider;
    QSignalSpy spy(&slider, &LevelsSlider::volumeChanged);
    QVERIFY(spy.isValid());

    slider.setVolume(60);
    // setVolume triggers the slider which emits volumeChanged
    QVERIFY(spy.count() >= 1);
    QCOMPARE(spy.last().at(0).toInt(), 60);
}

QTEST_MAIN(TestLevelsSlider)
#include "test_levelsslider.moc"
