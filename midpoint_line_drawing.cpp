#include <iostream>
#include <cmath>
#include <vector>
#include "display.h"

using namespace std;


float x_1, x_2, y_1, y_2, m, d_initial;
float dx, dy,dd;
int current_steps=0;
vector<float> coordinates;

void midpoint_line_drawing_algorithm() {
    d_initial = 2*dy - dx;
    dd = 2*(dy-dx);

    while (x_1 <= x_2 && y_1 <= y_2) {
        coordinates.resize(2 * current_steps+2);
        coordinates[2 * current_steps] = round(x_1)/35;
        coordinates[2 * current_steps + 1] = round(y_1)/20;

        if (d_initial < 0) {
            d_initial += 2 * dy;
            x_1 = x_1 + 1;
        } else if (d_initial >= 0) {
            d_initial += dd;
            x_1 = x_1 + 1;
            y_1 = y_1 + 1;
        }
        current_steps += 1;
    }

    for (float i: coordinates) {
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
    m = dy / dx;
    midpoint_line_drawing_algorithm();
}


int main() {
    input();
    Display display_board = Display(coordinates);
    display_board.draw();
}