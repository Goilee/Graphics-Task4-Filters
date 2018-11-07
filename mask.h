#ifndef MASK_H
#define MASK_H


class Mask
{
public /*fields*/:
    double matrix[3][3];
    double norm_k;
    int r_shift;
    int g_shift;
    int b_shift;

public /*methods*/:
    Mask();
    double at(int x, int y);
    double set(int x, int y, double val);
    double norm();
    double red_shift();
    double green_shift();
    double blue_shift();
    void setNorm(double val);
    void setRedShift(int val);
    void setGreenShift(int val);
    void setBlueShift(int val);
};

#endif // MASK_H
