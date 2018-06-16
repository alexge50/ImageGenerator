#include <iostream>
#include <FreeImagePlus.h>

#include "PerlinNoise.h"

const int WIDTH = 1024;
const int HEIGHT = 1024;

const int SCALE = 1;

BYTE imagedata[WIDTH][HEIGHT][3];

double noiseData[3][SCALE * WIDTH][SCALE * HEIGHT];

void SaveImage(const char *name)
{
    int width = WIDTH;
    int height = HEIGHT;

    fipImage img(FIT_BITMAP, width, height);
    img = FreeImage_ConvertFromRawBits(&imagedata[0][0][0], width, height, 3 * height, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
    img.save("test.jpg");
}

int main()
{
    int seed;
    printf("seed: ");
    scanf("%d", &seed);
    srand(static_cast<unsigned int>(seed));

    Noise::noise(&noiseData[0][0][0], SCALE * WIDTH, SCALE * HEIGHT);
    Noise::noise(&noiseData[1][0][0], SCALE * WIDTH, SCALE * HEIGHT);
    Noise::noise(&noiseData[2][0][0], SCALE * WIDTH, SCALE * HEIGHT);

    for(int x = 0; x < WIDTH; x++)
        for(int y = 0; y < HEIGHT; y++) {
            double sample_r = PerlinNoise::perlinNoise(&noiseData[0][0][0], SCALE  * WIDTH, SCALE  * HEIGHT, x, y, 6, 0.4, 1000.0);
            double sample_g = PerlinNoise::perlinNoise(&noiseData[1][0][0], SCALE  * WIDTH, SCALE  * HEIGHT, x, y, 6, 0.4, 1000.0);
            double sample_b = PerlinNoise::perlinNoise(&noiseData[2][0][0], SCALE  * WIDTH, SCALE  * HEIGHT, x, y, 6, 0.4, 1000.0);

            double sample_blocky_r = Blocky::blocky(&noiseData[0][0][0], SCALE  * WIDTH, SCALE  * HEIGHT, x, y, 6, 0.4, 100.0);
            double sample_blocky_g = Blocky::blocky(&noiseData[1][0][0], SCALE  * WIDTH, SCALE  * HEIGHT, x, y, 6, 0.4, 100.0);
            double sample_blocky_b = Blocky::blocky(&noiseData[2][0][0], SCALE  * WIDTH, SCALE  * HEIGHT, x, y, 6, 0.4, 100.0);

            /*imagedata[x][y][0] = 0xFF & static_cast<int>((sample_r) * 256.0);
            imagedata[x][y][1] = 0xFF & static_cast<int>((sample_g) * 256.0);
            imagedata[x][y][2] = 0xFF & static_cast<int>((sample_blocky_b + sample_b) * 128.0);*/

            imagedata[x][y][0] = 0xFF & static_cast<int>((sample_blocky_r + sample_r) * 128.0);
            imagedata[x][y][1] = 0xFF & static_cast<int>((sample_blocky_g + sample_g) * 128.0);
            imagedata[x][y][2] = 0xFF & static_cast<int>((sample_blocky_b + sample_b) * 128.0);
        }

    SaveImage("noise.bmp");

    return 0;
}
