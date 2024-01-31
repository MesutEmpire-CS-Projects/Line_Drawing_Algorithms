#include <iostream>
#include <vector>
#include <cmath>
#include "display.h"
using namespace std;

float x_1, x_2, y_1, y_2, m, p_k,start_x,start_y,end_x,end_y;
float dx, dy, d, length, a, b, current_steps;
int thickness;
vector<float> coordinates;
vector<float> result_coordinates;

void IntensifyPixels(float x, float y, float r) {
    float scaling_factor_x = max(x_1, x_2) + 5;
    float scaling_factor_y = max(y_1, y_2) + 5;

    float intensity = max(0.0f, r);
    intensity = max(0.0f, min(1.0f, intensity));

    if ((start_x == x && start_y == y) || (end_x == x && end_y == y)) {
        intensity = 1.0f;
        cout << "Stop ::: " << intensity << endl;
    }

    result_coordinates.push_back(round(x)/scaling_factor_x );
    result_coordinates.push_back(round(y)/scaling_factor_y );
    result_coordinates.push_back(intensity);
}

vector<float> gupta_sproull_algorithm() {
    int p_k = 2 * dy - dx;
    d = 0;
    length = sqrt(dx * dx + dy + dy);

    a = dx / length;
    b = dy / length;

    while (x_1 <= x_2) {
//        IntensifyPixels(x_1, y_1 - 1, d + b);
        IntensifyPixels(x_1, y_1, d);
//        IntensifyPixels(x_1, y_1 + 1, d - b);

        if (p_k < 0) {
            p_k += 2 * dy;
            x_1 += 1;
            d += a;
        } else {
            p_k += (2 * dy - 2 * dx);
            x_1 += 1;
            y_1 += 1;
            d += (a - b);
        }

        current_steps += 1;
    }

    return result_coordinates;
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
    current_steps = 0;  // Initialize current_steps

    start_x = x_1;
    start_y = y_1;
    end_x = x_2;
    end_y = x_2;
    coordinates = gupta_sproull_algorithm();
}

int main() {
    input();

    // Display the result
    for (float i : coordinates) {
        cout << "element: " << i << endl;
    }
    Display display_board = Display(coordinates,1);
    display_board.draw();

    return 0;
}
