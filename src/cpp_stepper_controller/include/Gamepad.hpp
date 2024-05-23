struct Stick
{
    int x;
    int y;
};

struct Triggers
{
    int left;
    int right;
};

struct Buttons
{
    int up;
    int down;
    int left;
    int right;
    int a;
    int b;
    int x;
    int y;
    int l1;
    int r1;
    int select;
    int start;
    int l_stick;
    int r_stick;
};

struct Gamepad
{
    Stick left_stick;
    Stick right_stick;
    Stick d_pad;
    Triggers triggers;
    Buttons buttons;
};