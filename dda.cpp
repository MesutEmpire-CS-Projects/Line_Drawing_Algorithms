#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "display.h"
using namespace std;

float x_1,x_2,y_1,y_2,m;
float dx,dy;
int current_steps = 0;
int steps;
vector<float> coordinates;

void dda_algorithm(){
    float scaling_factor_x = max(x_1, x_2) + 5;  // Adjust as needed
    float scaling_factor_y = max(y_1, y_2) + 5;  // Adjust as needed

    if (abs(dx) > abs(dy)){
        steps = abs(dx);
    }else{
        steps = abs(dy);
    }
    cout << x_1 << y_1 << endl;



    coordinates.resize(2 * (steps+1));
    coordinates[2*current_steps] = round(x_1)/scaling_factor_x;
    coordinates[2*current_steps + 1] = round(y_1)/scaling_factor_y;

    current_steps = 1;

    while(current_steps<=steps+1 && x_1<=x_2 && y_1<=y_2){
        if ( m < 1 ){
            x_1 = 1+x_1;
            y_1 = m+y_1;
        } else if ( m > 1 ){
            x_1 = (1/m)+x_1;
            y_1 = 1+y_1;
        }
        else {
            x_1 = 1+x_1;
            y_1 = 1+y_1;
        }

        coordinates[2*current_steps] = round(x_1)/scaling_factor_x;
        coordinates[2*current_steps + 1] = round(y_1)/scaling_factor_y;
        current_steps +=1;
    }

    for(float i:coordinates){
        cout << "element: " << i << endl;
    }
}
void input(){
    printf("Enter value of X1 :");
    cin >> x_1;
    printf("Enter value of y1 :");
    cin >> y_1;
    printf("Enter value of X2 :");
    cin >> x_2;
    printf("Enter value of Y2 :");
    cin >> y_2;
    dx=x_2-x_1;
    dy=y_2-y_1;
    m=dy/dx;
    dda_algorithm();
}


int main() {
    input();
    Display display_board = Display(coordinates);
    display_board.draw();
}


