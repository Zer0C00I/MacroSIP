#include <QtTest>
#include <QSignalSpy>
#include "widgets/LevelsSlider.h"

using namespace macrosip;

class TestLevelsSlider : public QObject {
    Q_OBJECT
private slots:
    void testDefaultState();
    void testSetVolume();
    void testSetVolumeEmitsSignal();
    void testSetMuted();
    void testMutedDoesNotChangeVolume();
    void testSetLevel();
};

void TestLevelsSlider::testDefaultState()
{
    LevelsSlider slider;
    QVERIFY(!slider.isMuted());
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

void TestLevelsSlider::testSetVolumeEmitsSignal()
{
    LevelsSlider slider;
    QSignalSpy spy(&slider, &LevelsSlider::volumeChanged);

    slider.setVolume(60);

    QVERIFY(spy.count() >= 1);
    QCOMPARE(spy.last().at(0).toInt(), 60);
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

void TestLevelsSlider::testMutedDoesNotChangeVolume()
{
    LevelsSlider slider;
    slider.setVolume(50);
    QCOMPARE(slider.volume(), 50);

    slider.setMuted(true);
    QCOMPARE(slider.volume(), 50);  // volume value preserved

    slider.setMuted(false);
    QCOMPARE(slider.volume(), 50);
}

void TestLevelsSlider::testSetLevel()
{
    LevelsSlider slider;
    // setLevel updates the VU meter — we just verify no crash with bounds
    slider.setLevel(0);
    slider.setLevel(50);
    slider.setLevel(100);
    // Volume should not change from setLevel
    int origVol = slider.volume();
    slider.setLevel(80);
    QCOMPARE(slider.volume(), origVol);
}

QTEST_MAIN(TestLevelsSlider)
#include "test_levelsslider.moc"
