/*******************************************************
 * Homework 1: Rasterization                           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method decribed in the handout.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <cmath>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int radius;
bool **image;

void renderPixel(int x, int y, int r ){
    assert(x >= 0 && y >= 0 && x <= radius && y <= radius);
    if (r == radius){
        //Q1
        image[x][y] = 1;
        image[y][x] = 1;
        //Q2
        image[x][r - y] = 1;
        image[y][r - x] = 1;
    }
    else{//inner
        int r2 = (radius - r)/2;
        //Q1
        image[x + r2][y + r2] = 1;
        image[y + r2][x + r2] = 1;
        //Q4
        image[r - x + r2][y + r2] = 1;
        image[r - y + r2][x + r2] = 1;
    }
    //inner circle







    // TODO:  light up the pixel's symmetric counterpart
}

void rasterizeArc(int r) {
    // TODO:  rasterint;
    for(int i = 0; i < 2; i++){
        if (i == 1){r = r * .67;}
            int y = r;
            int x = r/2;
            int d = 1 - r/2;
            int deltaE = 3;
            int deltaSE = -2 * r/2 + 5;
            renderPixel(x, y, r);

            while(y > x){
                if (d < 0){
                    d += deltaE;
                    deltaE += 2;
                    deltaSE += 2;
                }
                else{
                    d += deltaSE;
                    deltaE += 2;
                    deltaSE += 4;
                    y--;
                }
                x++;
                //cout << x << " " << y << endl;
                renderPixel(x, y, r);
            }

    }

}

// You shouldn't need to change anything below this point.

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " circleSize\n";
        return 0;
    }

#ifdef _WIN32
    sscanf_s(argv[1], "%d", &radius);
#else
    sscanf(argv[1], "%d", &radius);
#endif
    if (radius <= 0) {
        cout << "Image must be of positive size.\n";
        return 0;
    }

    // reserve image as 2d array
    image = new bool*[radius+1];
    for (int i = 0; i <= radius; i++) image[i] = new bool[radius+1];

    rasterizeArc(radius);

    char filename[50];
#ifdef _WIN32
    sprintf_s(filename, 50, "circle%d.ppm", radius);
#else
    sprintf(filename, "circle%d.ppm", radius);
#endif

    ofstream outfile(filename);
    outfile << "P3\n# " << filename << "\n";
    outfile << radius+1 << ' ' << radius+1 << ' ' << 1 << endl;

    for (int i = 0; i <= radius; i++)
    for (int j = 0; j <= radius; j++)
        outfile << image[radius-i][j] << " 0 0\n";

    // delete image data
    for (int i = 0; i <= radius; i++) delete [] image[i];
    delete [] image;

    return 0;
}
