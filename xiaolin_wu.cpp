#include <iostream>
#include <cmath>
#include <vector>
#include "display.h"

using namespace std;

float x_1, x_2, y_1, y_2, dx, dy, current_steps = 0, gradient;
vector<float> coordinates;

float fractional_part(float x) {
    return x - floor(x);
}

void xiaolin_wu_line_drawing_algorithm() {
    bool steep = abs(dy) > abs(dx);

    if (steep) {
        swap(x_1, y_1);
        swap(x_2, y_2);
    }

    if (x_1 > x_2) {
        swap(x_1, x_2);
        swap(y_1, y_2);
    }

    dx = x_2 - x_1;
    dy = y_2 - y_1;

    float scaling_factor_x = max(x_1, x_2) + 5;
    float scaling_factor_y = max(y_1, y_2) + 5;

    gradient = dy / dx;

    int x = x_1;
    while (x <= x_2) {
        float t = (x - x_1) / dx;

        float y = y_1 * (1 - t) + y_2 * t;
        float ypxl = floor(y);
        float alpha = y - ypxl;

        coordinates.push_back((steep ? ypxl : x)/ scaling_factor_x);
        coordinates.push_back((steep ? x : ypxl)/ scaling_factor_y);

        coordinates.push_back(steep ? 1.0 - alpha : 1.0 - alpha);
        coordinates.push_back(steep ? alpha : alpha);

        x++;
        current_steps += 1;
    }
}

void input() {
    cout << "Enter value of X1: ";
    cin >> x_1;
    cout << "Enter value of y1: ";
    cin >> y_1;
    cout << "Enter value of X2: ";
    cin >> x_2;
    cout << "Enter value of Y2: ";
    cin >> y_2;
}

int main() {
    input();
    xiaolin_wu_line_drawing_algorithm();

    for (float i : coordinates) {
        cout << "element: " << i << endl;
    }

    Display display_board = Display(coordinates,1);
    display_board.draw();

    return 0;
}
