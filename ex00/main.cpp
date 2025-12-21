#include "Engine.hpp"
#include "car.hpp"
#include "CompositeDrivingStateCalculator.hpp"
#include "SteerWheel.hpp"
#include "TestContext.hpp"
#include "Brake.hpp"
#include "Gear.hpp"
#include "Transmission.hpp"
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
void testGear();
void testTransmission();
void testCar();

void test()
{
    testDrivingState();
    testEngine();
    testBrake();
    testSteerWheel();
    testCompositeDrivingStateCalculator();
    testGear();
    testTransmission();
    testCar();
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

    engine.power(true);
    engine.speed(10);
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

    Engine engine;
    Brake brake;
    CompositeDrivingStateCalculator compositeDrivingStateCalculator;
    DrivingState state;
    DrivingState res;

    engine.power(true);
    engine.speed(3);
    brake.force(2);
    compositeDrivingStateCalculator.addFormula(engine);
    compositeDrivingStateCalculator.addFormula(brake);
    res = compositeDrivingStateCalculator.calculate(state, 1);
    TestEqual("複数数式 speed", res.speed(), 1);
    TestEqual("複数数式 angle", res.angle(), 0);
}

void testGear()
{
    std::cerr << " === Gear" << std::endl;

    DrivingState state(3, 0);
    Gear gear(2);

    state = gear.calculate(state, 1);
    TestEqual("ギアの力 speed", state.speed(), 6);
    TestEqual("ギアの力 angle", state.angle(), 0);
}

void testTransmission()
{
    std::cerr << " === Transmission" << std::endl;

    DrivingState state(3, 0);
    DrivingState res;
    Gear gear1(1);          // スピード変わらない
    Gear gear2(2);          // スピード2倍
    Gear gearReverse(-1.0); // スピード逆
    Transmission transmission;

    transmission.addGear(gear1);
    transmission.addGear(gear2);
    transmission.setReverse(gearReverse);
    res = transmission.calculate(state, 1);
    TestEqual("ギア1の力 speed", res.speed(), 3);
    TestEqual("ギア1の力 angle", res.angle(), 0);

    transmission.shiftup(); // エラー処理チェックのため２回行う
    transmission.shiftup();
    res = transmission.calculate(state, 1);
    TestEqual("ギア2の力 speed", res.speed(), 6);
    TestEqual("ギア2の力 angle", res.angle(), 0);

    transmission.shiftdown(); // エラー処理チェックのため２回行う
    transmission.shiftdown();
    res = transmission.calculate(state, 1);
    TestEqual("ギア1の力 speed", res.speed(), 3);
    TestEqual("ギア1の力 angle", res.angle(), 0);

    transmission.shiftReverse();
    res = transmission.calculate(state, 1);
    TestEqual("逆ギアの力 speed", res.speed(), -3);
    TestEqual("逆ギアの力 angle", res.angle(), 0);

    transmission.shiftReverse();
    res = transmission.calculate(state, 1);
    TestEqual("ギア1の力 speed", res.speed(), 3);
    TestEqual("ギア1の力 angle", res.angle(), 0);
}

void testCar()
{
    std::cerr << " === Car" << std::endl;

    Engine engine;
    Brake brake;
    SteerWheel steerWheel;
    Transmission transmission;
    Gear gear1(1);
    Gear gear2(2);
    Gear gearReverse(-1);

    transmission.addGear(gear1);
    transmission.addGear(gear2);
    transmission.setReverse(gearReverse);

    DrivingState res;
    Car car(engine, brake, steerWheel, transmission);
    res = car.calculate();
    TestEqual("初期状態 speed", res.speed(), 0);
    TestEqual("初期状態 angle", res.angle(), 0);

    car.start();
    car.accelerate(50);

    {
        res = car.calculate();
        TestEqual("started accelerate speed", res.speed(), 50);
        TestEqual("started accelerate angle", res.angle(), 0);
    }

    {
        car.stop();
        res = car.calculate();
        TestEqual("stopped accelerate speed", res.speed(), 0);
        TestEqual("stopped accelerate angle", res.angle(), 0);
        car.start();
    }

    {
        car.shift_gears_up();
        res = car.calculate();
        TestEqual("shift_gears_up speed", res.speed(), 100);
        TestEqual("shift_gears_up angle", res.angle(), 0);
        car.shift_gears_down();
    }

    {
        car.shift_gears_up();
        car.shift_gears_down();
        res = car.calculate();
        TestEqual("shift_gears_down speed", res.speed(), 50);
        TestEqual("shift_gears_down angle", res.angle(), 0);
    }

    {
        car.reverse();
        res = car.calculate();
        TestEqual("reverse speed", res.speed(), -50);
        TestEqual("reverse angle", res.angle(), 0);
        car.reverse();
    }

    {
        car.turn_wheel(10);
        res = car.calculate();
        TestEqual("turn_wheel speed", res.speed(), 50);
        TestEqual("turn_wheel angle", res.angle(), 10);
        car.turn_wheel(0);
    }

    {
        car.turn_wheel(100);
        car.straighten_wheels();
        res = car.calculate();
        TestEqual("straighten_wheels speed", res.speed(), 50);
        TestEqual("straighten_wheels angle", res.angle(), 0);
    }

    {
        car.apply_force_on_brakes(2);
        res = car.calculate();
        TestEqual("apply_force_on_brakes speed", res.speed(), 48);
        TestEqual("apply_force_on_brakes angle", res.angle(), 0);
        car.apply_force_on_brakes(0);
    }

    {
        car.apply_emergency_brakes();
        res = car.calculate();
        TestEqual("apply_emergency_brakes speed", res.speed(), 0);
        TestEqual("apply_emergency_brakes angle", res.angle(), 0);
        car.apply_force_on_brakes(0);
    }
}
