//
// Created by alex on 5/1/18.
//

#ifndef NOISE_GENERATOR_PERLINNOISE_H
#define NOISE_GENERATOR_PERLINNOISE_H

#include <math.h>

namespace PerlinNoise {
    /*inline double dotGrindGradient(int ix, int iy, double x, double y, double sample)
    {
        double rand_angle = (rand() % 360) * (M_PI / 180.);
        double grad_x = cos(rand_angle);
        double grad_y = sin(rand_angle);

        double dx = x - (double)ix;
        double dy = y - (double)iy;

        return (dx * grad_x + dy * grad_y);
    }*/

    inline double interpolate(double a, double b, double x) {
        double ft = x * M_PI;
        double f = (1.0 - cos(ft)) * 0.5;

        return a * (1.0 - f) + b * f;
    }

    double noise(double *data, int width, int height, double x, double y) {
        double fx = x - int(x);
        double fy = y - int(y);
        //wrap around
        int x0 = (int(x) + width) % width;
        int y0 = (int(y) + height) % height;

        //neighbor values
        int x1 = (x0 + width - 1) % width;
        int y1 = (y0 + height - 1) % height;


        double s, t, u, v;
        double value = 0;
        /*s = dotGrindGradient(x0, y0, x, y);
        t = dotGrindGradient(x1, y0, x, y);
        u = dotGrindGradient(x0, y1, x, y);
        v = dotGrindGradient(x1, y1, x, y);*/
        /*s = data[x0 + y0 * width];
        t = data[x0 + y1 * width];
        u = data[x1 + y0 * width];
        v = data[x1 + y1 * width];*/

        value += fx * fy * data[x0 + y0 * width];
        value += (1 - fx) * fy * data[x1 + y0 * width];
        value += fx * (1 - fy) * data[x0 + y1 * width];
        value += (1 - fx) * (1 - fy) * data[x1 + y1 * width];

        return value;
        /*double i1 = interpolate(s, t, x - x0);
        double i2 = interpolate(u, v, x - x0);

        return interpolate(i1, i2, y - y0);*/
    }

    double perlinNoise(double *data, int width, int height, double x, double y, int octaves, double roughness, double zoom)
    {
        double n = 0;
        double frequency = 0.5;
        double amplitude = 1.1;

        for(int i = 0; i < octaves; i++)
        {
            frequency *= 2;
            amplitude *= roughness;

            n += noise(data, width, height, x * frequency / zoom, y * frequency / zoom) * amplitude;
        }

        return n;
    }
};

namespace Noise
{
    void noise(double *m, int width, int height)
    {
        for(int i = 0; i < width; i++)
            for(int j = 0; j < height; j++)
                m[i + j * width] = (rand() % 32678) / 32678.0;
    }
};

namespace Blocky
{

    double noise(double *data, int width, int height, double x, double y) {
        double fx = x - int(x);
        double fy = y - int(y);
        //wrap around
        int x0 = (int(x) + width) % width;
        int y0 = (int(y) + height) % height;

        //neighbor values
        int x1 = (x0 + width - 1) % width;
        int y1 = (y0 + height - 1) % height;


        double s, t, u, v;
        double value = 0;
        /*s = dotGrindGradient(x0, y0, x, y);
        t = dotGrindGradient(x1, y0, x, y);
        u = dotGrindGradient(x0, y1, x, y);
        v = dotGrindGradient(x1, y1, x, y);*/
        /*s = data[x0 + y0 * width];
        t = data[x0 + y1 * width];
        u = data[x1 + y0 * width];
        v = data[x1 + y1 * width];*/

        value += data[x0 + y0 * width];
        value += data[x1 + y0 * width];
        value += data[x0 + y1 * width];
        value += data[x1 + y1 * width];

        return value;
    }

    double blocky(double *data, int width, int height, double x, double y, int octaves, double roughness, double zoom)
    {
        double n = 0;
        double frequency = 0.5;
        double amplitude = 0.5;

        for(int i = 0; i < octaves; i++)
        {
            frequency *= 2;
            amplitude *= roughness;

            n += noise(data, width, height, x * frequency / zoom, y * frequency / zoom) * amplitude;
        }

        return n;
    }
};
#endif //NOISE_GENERATOR_PERLINNOISE_H
