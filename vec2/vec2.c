#include "vec2.h"
#include <math.h>
#include <stdio.h>

/// Create a 2d vector.
/// @param x_ The first component.
/// @param y_ The second component.
/// @return The newly created vector.
vec2 vec2_create(double x_, double y_) 
{
    vec2 V;
    V.x = x_;
    V.y = y_;
    return V;
}

/// Create a zero 2d vector.
/// @return The newly created zero vector.
vec2 vec2_create_zero() 
{
    vec2 V;
    V = vec2_create(0.0, 0.0);
    return V;
}

/// Add two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The sum in a new vector.
vec2 vec2_add(vec2 lhs, vec2 rhs) 
{
    vec2 res;
    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    return res;
}

/// Substract two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The difference in a new vector.
vec2 vec2_sub(vec2 lhs, vec2 rhs) 
{
    vec2 res;
    res.x = lhs.x - rhs.x;
    res.y = lhs.y - rhs.y;
    return res;
}

/// Multiply a vector by a scalar.
/// @param scalar The left operand, a scalar.
/// @param rhs The right operand, a vector.
/// @return The product in a new vector.
vec2 vec2_mul(double scalar, vec2 rhs) 
{
    vec2 res;
    res.x = rhs.x * scalar;
    res.y = rhs.y * scalar;
    return res;
}

/// Compute the dot product (scalar product) between two vectors.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @return The dot product.
double vec2_dot(vec2 lhs, vec2 rhs) 
{
    double res;
    res = (lhs.x * rhs.x) + (lhs.y * rhs.y);
    return res;
}

/// Compute the square of the euclidean norm of a given vector.
/// @param v The vector.
/// @return The square of the norm.
double vec2_norm_sqr(vec2 v) 
{
    double res;
    res = pow(vec2_norm(v), 2);
    return res;
}

/// Compute the euclidean norm of a given vector.
/// @param v The vector.
/// @return The norm.
double vec2_norm(vec2 v) 
{
    double res;
    res = sqrt(pow(v.x, 2)+pow(v.y, 2));
    return res;
}

/// Compute the normalization of a given vector.
/// @param v The vector.
/// @return The new normalized vector.
vec2 vec2_normalize(vec2 v) 
{
    vec2 res;
    res.x = v.x / vec2_norm(v);
    res.y = v.y / vec2_norm(v);
    return res;
}

/// Check whether two vectors are approximately equals within a given tolerance.
/// @param lhs The left operand.
/// @param rhs The right operand.
/// @param eps The tolerance.
/// @return true if vector are approximately equal, false otherwise.
bool vec2_is_approx_equal(vec2 lhs, vec2 rhs, double eps) 
{
    bool res = false;

    if(rhs.x - lhs.x < eps)
    {
        res = true;
    }
    else if(rhs.y - lhs.y < eps)
    {
        res = true;
    }
    
    return res;
}

/// Compute the coordinates of a 2d vector (with components between 0 and 1)
/// in a given screen matrix.
/// @param v The 2d vector.
/// @param width The screen width.
/// @param height The screen height.
/// @return The coordinates (rwo, column).
coordinates vec2_to_coordinates(vec2 v, uint32_t width, uint32_t height){
    int32_t zero_x = width / 2;
    int32_t zero_y = height / 2;
    coordinates res;
    if (v.x == 0.0){
        res.column = zero_x;
    }
    else{
        double col = zero_x * v.x;
        double reste_x = (col*(col>0) + (-1)*col*(col<0));
        while(reste_x >= 1.0){
            reste_x = reste_x - 1.0;
        }
        if(reste_x == 0.0){
            col = zero_x + col-1; 
        }
        else{
            col = zero_x + floor(col);
        }
        res.column = (int32_t)col;
    }
    if(v.y == 0){
        res.row = zero_y;
    }
    else{
        double row = zero_y * v.y;
        double reste_y = (row*(row>0) + (-1)*row*(row<0));
    
        while(reste_y >= 1.0){
            reste_y = reste_y - 1.0;
        }
        if(reste_y == 0.0){
            row = row + zero_y-1; 
        }
        else{
            row = zero_y + ceil(row);
        }
        res.row = (int32_t)row;
    }
    
    return res;
}


/// Print a vector in the standard output.
/// @param v The vector.
void vec2_print(vec2 v) 
{
    printf("x = %g, y = %g\n", v.x, v.y);
}

