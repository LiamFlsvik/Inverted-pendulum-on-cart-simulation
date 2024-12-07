//
// Created by liamf on 12/4/2024.
//

#ifndef PID_HPP
#define PID_HPP
#include <threepp/math/Vector3.hpp>
#include <threepp/core/Clock.hpp>


class PID {


public:

    PID(float Kp, float Ki, float Kd, const threepp::Vector3 setPoint) : Kp(1), Ki(0.1), Kd(5), setPoint(setPoint) {}

    threepp::Vector3 getForceVector() {
        dt = clock.getDelta();
        if (dt < 1e-6) {
            dt = 1e-6;
        }
        calculatePID();
        return forceVector;


    }

    void calculatePID() {
        //TODO: Implement nichols zieger autotuner
        error = setPoint.x - input;
        P = Kp * error;
        I += Ki * error*dt;
        D = Kd * (error-prevError)/dt;
        forceVector.x = P + I + D;
        prevError = error;
    }

    void oscillate() {
        //TODO: Sine wave oscillations if the pendulums orientation is in the interval [PI,2*PI]
    }

    void setInput (const float &input_) {
        input = input_;
    }

private:
    float input;
    threepp::Vector3 forceVector;
    threepp::Vector3 setPoint;
    float angle = 0;
    float Kp;
    float Ki;
    float Kd;
    float P = 0;
    float I = 0;
    float D = 0;

    float error = 0;
    float prevError = 0;

    float dt = 1;
    threepp::Clock clock;

};



#endif //PID_HPP
