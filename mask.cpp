#include "mask.h"
#include <stdexcept>

Mask::Mask() :
    norm_k(1),
    r_shift(0), g_shift(0), b_shift(0)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->matrix[i][j] = 0;
        }
    }
    this->matrix[1][1] = 1;
}

double Mask::at(int x, int y)
{
    return this->matrix[x+1][y+1];
}

double Mask::set(int x, int y, double val)
{
    this->matrix[x+1][y+1] = val;
}

double Mask::norm()
{
    return this->norm_k;
}

double Mask::red_shift()
{
    return this->r_shift;
}

double Mask::green_shift()
{
    return this->g_shift;
}

double Mask::blue_shift()
{
    return this->b_shift;
}

void Mask::setNorm(double val)
{
    if (val == 0)
    {
        throw new std::runtime_error("Mask::setNorm(): norm must not be 0");
    }
    this->norm_k = val;
}

void Mask::setRedShift(int val)
{
    this->r_shift = val;
}

void Mask::setGreenShift(int val)
{
    this->g_shift = val;
}

void Mask::setBlueShift(int val)
{
    this->b_shift = val;
}
