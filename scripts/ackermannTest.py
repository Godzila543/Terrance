import math

height = 10
width = 10

while True:
    print("Enter the angle in degrees: ")
    angle = float(input())
    angle = math.radians(angle)
    if angle == 0:
        angle = 0.00001
    x = height / math.tan(angle)
    x1 = x + width/2
    x2 = x - width/2
    r1 = math.sqrt(x1**2 + height**2)
    r2 = math.sqrt(x2**2 + height**2)

    theta1 = math.atan(height/x1)
    theta2 = math.atan(height/x2)

    print(f"x: {x}")
    print(f"x1: {x1}")
    print(f"x2: {x2}")
    print(f"r1: {r1}")
    print(f"r2: {r2}")
    print(f"theta1: {math.degrees(theta1)}")
    print(f"theta2: {math.degrees(theta2)}")