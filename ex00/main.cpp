#include "Engine.hpp"
#include "CompositeDrivingStateCalculator.hpp"
#include "SteerWheel.hpp"
#include "TestContext.hpp"
#include "Brake.hpp"
#include "test.hpp"
#include <string>
#include <iostream>

void test();

int main()
{
    test();
    return (0);
}

void testDrivingState();
void testEngine();
void testBrake();
void testSteerWheel();
void testCompositeDrivingStateCalculator();

void test()
{
    testDrivingState();
    testEngine();
    testBrake();
    testSteerWheel();
    testCompositeDrivingStateCalculator();
}

void testDrivingState()
{
    std::cerr << " === DrivingState " << std::endl;
    DrivingState state;

    TestTrue("初期値 speed", state.speed() == 0);
    TestTrue("初期値 angle", state.angle() == 0);
    state = DrivingState(3, 4);
    TestEqual("変更後 speed", state.speed(), 3.0);
    TestEqual("変更後 angle", state.angle(), 4.0);
}

void testEngine()
{
    std::cerr << " === Engine " << std::endl;

    Engine engine;
    DrivingState state;

    engine.instanceSpeed(10);
    state = engine.calculate(state, 1);
    TestEqual("加速後の速度チェック", state.speed(), 10.0);
}

void testBrake()
{
    std::cerr << " === Brake" << std::endl;

    Brake brake;
    DrivingState state(16, 0);

    brake.force(5);
    state = brake.calculate(state, 2);
    // v = v0 - (動摩擦係数 * force) * 時間 = 6
    TestEqual("v == 16 - (1 * 5) * 2 = 6", state.speed(), 6);
}

void testSteerWheel()
{
    std::cerr << " === SteerWheel" << std::endl;

    SteerWheel steerWheel;
    DrivingState state;

    steerWheel.angle(5);
    state = steerWheel.calculate(state, 1);
    TestEqual("車の向きを設定", state.angle(), 5);
}

void testCompositeDrivingStateCalculator()
{
    std::cerr << " === CompositeDrivingStateCalculator" << std::endl;

    Engine engine1;
    Engine engine2;
    CompositeDrivingStateCalculator compositeDrivingStateCalculator;
    DrivingState state;

    engine1.instanceSpeed(3);
    engine2.instanceSpeed(3);
    compositeDrivingStateCalculator.addFormula(engine1);
    compositeDrivingStateCalculator.addFormula(engine2);
    state = compositeDrivingStateCalculator.calculate(state, 1);
    TestEqual("複数数式", state.speed(), 6);
}
