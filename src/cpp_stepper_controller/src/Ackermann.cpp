#include "Ackermann.hpp"

AckermannSteering::AckermannSteering(double wheelSeperationHeight, double wheelSeperationWidth, double wheelRadius, double maxSteeringAngle) {
    this->wheelSeperationHeigh = wheelSeperationHeight;
    this->wheelSeperationWidth = wheelSeperationWidth;
    this->maxSteeringAngle = maxSteeringAngle;
    this->speed = 0;
    this->angle = 0;
    this->wheelRadius = wheelRadius;
    this->steeringAngles = {0, 0, 0, 0};
    this->rpms = {0, 0, 0, 0};
}

void AckermannSteering::setSteeringAngle(double angle_) {
    // first convert angle to radius
    angle = angle_ * M_PI / 180;
    if angle == 0:
        angle = 0.00001;
    if angle > maxSteeringAngle:
        angle = maxSteeringAngle;

    if angle < -maxSteeringAngle:
        angle = -maxSteeringAngle;

    update();
}

void AckermannSteering::setSteering(double angle, double speed) {
    setSpeed(speed);
    setSteeringAngle(angle);
}

void AckermannSteering::setSpeed(double speed) {
    this->speed = speed;
    update();
}

void AckermannSteering::update()
{
    double x = wheelSeperationHeight / tan(angle)
    double x1 = x + width/2
    double x2 = x - width/2
    double r1 = math.sqrt(x1**2 + height**2)
    double r2 = math.sqrt(x2**2 + height**2)

    double theta1 = math.atan(height/x1)
    double theta2 = math.atan(height/x2)

    double rpm1 = speed * r1 / wheelRadius
    double rpm2 = speed * r2 / wheelRadius

    this->steeringAngles = {theta1, theta2, -theta1, -theta2};
    this->rpms = {rpm1, rpm2, rpm1, rpm2};
}

SteeringAngles AckermannSteering::getSteeringAngles() {
    return steeringAngles;
}

RPMs AckermannSteering::getRPMs() {
    return rpms;
}