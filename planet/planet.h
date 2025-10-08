#ifndef _PLANET_H_
#define _PLANET_H_

#include "../vec2/vec2.h"
#include "../gfx/gfx.h"

#define R_ECRAN 4.948240e12

#define G 6.67e-11

#define M_SOLEIL 1.9891e30
#define R_SOLEIL 2.5e7

#define M_MERCURE 3.3011e23
#define MERCURE_AXE_A 5.790905e10
#define E_MERCURE 0.2056
#define P_MERCURE 4.60012e10
#define R_MERCURE 2.439e6

#define M_VENUS 4.8675e24
#define VENUS_AXE_A 1.082095e11
#define E_VENUS 0.00678
#define P_VENUS 1.07476e11
#define R_VENUS 6.051e6

#define M_TERRE 5.972e24
#define TERRE_AXE_A 1.496e11
#define E_TERRE 0.01671022
#define P_TERRE 1.47e11
#define R_TERRE 6.371e6

#define M_MARS 6.4185e23
#define MARS_AXE_A 2.27944e11
#define E_MARS 0.09339
#define P_MARS 2.06655e11
#define R_MARS 3.389e6

#define M_RND2 2.5732e23
#define RND2_AXE_A 3.9617e11
#define E_RND2 0.185755
#define P_RND2 3.79350e11
#define R_RND2  8e6

#define M_JUPITER 1.8986e27
#define JUPITER_AXE_A 7.7834e11
#define E_JUPITER 0.04839
#define P_JUPITER 7.4068e11
#define R_JUPITER   6.9911e7//25

#define M_SATURNE 5.6846e26
#define SATURNE_AXE_A 1.4267e12
#define E_SATURNE 0.0539
#define P_SATURNE 1.3498e12
#define R_SATURNE   5.8232e7  //20

#define M_URANUS 8.681e26
#define URANUS_AXE_A 2.8707e11
#define E_URANUS 0.04726
#define P_URANUS 2.735e12
#define R_URANUS  2.5362e7 //10

#define M_RND1 3.471e26
#define RND1_AXE_A 3.568400e12
#define E_RND1 0.0157576
#define P_RND1 5.542300e12
#define R_RND1  6e6 //10

#define M_NEPTUNE 1.024e26
#define NEPTUNE_AXE_A 4.498400e12
#define E_NEPTUNE 0.00858587
#define P_NEPTUNE 4.459800e12
#define R_NEPTUNE  2.4622e7 //10

typedef enum _sys_sol{
    SOLEIL,
    MERCURE,
    VENUS,
    TERRE,
    MARS,
    JUPITER,
    SATURNE,
    URANUS,
    NEPTUNE
} sys_sol;

typedef struct _planet
{
    double mass;
    double e; // exentricité
    double axe_a;
    double r; //rayon
    uint32_t color;
    vec2 a;
    vec2 pos;      // x(t)
    vec2 prec_pos; // x(t - dt)
    
} planet_t;

typedef struct _system
{
    planet_t star;       // ex. The sun
    uint32_t nb_planets; // The number of orbiting planets
    planet_t *planets;   // An array of orbiting planets
} system_t;

vec2 f_gravitation(double m1, double m2, vec2 p1_p2);
vec2 dist_p1_p2(planet_t p1, planet_t p2);
vec2 f_res(planet_t p, system_t sys);
vec2 accel(planet_t p, system_t sys);
vec2 To_Vec(vec2 pos_metre, double r_ecran);
vec2 return_vec(vec2 vec);
void init_planet_pos(planet_t *p, system_t sys, double delta_t);
uint32_t r_pixel(double r_meters, double screen_m);
// Those function are not mandatory to implement,
// it's rather a hint of what you should have.
planet_t create_planet(double mass, double e, double axe_a, double r, uint32_t color, vec2 pos);
system_t create_system(double delta_t);
void show_system(struct gfx_context_t *ctxt, system_t *system, double r_ecran, sys_sol center);
void update_system(system_t *system, double delta_t);
void free_system(system_t *system);

#endif