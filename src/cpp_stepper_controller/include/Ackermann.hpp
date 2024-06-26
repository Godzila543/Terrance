struct SteeringAngles {
    double frontLeft;
    double frontRight;
    double rearLeft;
    double rearRight;
};

struct RPMs {
    double frontLeft;
    double frontRight;
    double rearLeft;
    double rearRight;
};

class AckermannSteering {
public:
    AckermannSteering(double wheelSeperationHeight, double wheelSeperationWidth, double wheelRadius, double maxSteeringAngle);
    void setSteeringAngle(double angle);
    void setSteering(double angle, double speed);
    void setSpeed(double speed);
    void update();

    SteeringAngles getSteeringAngles();
    RPMs getRPMs();

private:
    double wheelSeperationHeight;
    double wheelSeperationWidth;
    double maxSteeringAngle;
    double speed;
    double wheelRadius;
    double angle;
    SteeringAngles steeringAngles;
    RPMs rpms;
};