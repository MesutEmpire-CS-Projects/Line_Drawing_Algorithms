#include <iostream>
#include <cmath>
#include <vector>
#include "display.h"

using namespace std;

float x_1, x_2, y_1, y_2, dx, dy, p_k,x,y;
vector<float> coordinates;

void bresenham_algorithm() {
    float scaling_factor_x = max(x_1, x_2) + 5;
    float scaling_factor_y = max(y_1, y_2) + 5;
    int step,incx, incy;
    dx = abs(dx);
    dy = abs(dy);
    incx = 1;
    if (x_2 < x_1) incx = -1;
    incy = 1;
    if (y_2 < y_1) incy = -1;

    if (dx > dy) {
        step = dx;
    } else {
        step = dy;
    }

    x = x_1;
    y = y_1;

    coordinates.push_back(round(x)/scaling_factor_x);
    coordinates.push_back(round(y)/scaling_factor_y);

    p_k = 2 * dy - dx;

    for (int i = 0; i < step; i++) {
        if (p_k < 0) {
            x += incx;
            p_k += 2 * dy;
        } else {
            x += incx;
            y += incy;
            p_k += 2 * (dy - dx);
        }

        coordinates.push_back(round(x)/scaling_factor_x);
        coordinates.push_back(round(y)/scaling_factor_y);
    }

    for (float i : coordinates) {
        cout << "element: " << i << endl;
    }
}

void input() {
    printf("Enter value of X1 :");
    cin >> x_1;
    printf("Enter value of y1 :");
    cin >> y_1;
    printf("Enter value of X2 :");
    cin >> x_2;
    printf("Enter value of Y2 :");
    cin >> y_2;

    dx = x_2 - x_1;
    dy = y_2 - y_1;

    p_k = 2 * abs(dy) - abs(dx);

    bresenham_algorithm();
}

int main() {
    input();
    Display display_board = Display(coordinates);
    display_board.draw();
    return 0;
}

