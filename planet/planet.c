#include "planet.h"
#include "../vec2/vec2.h"
#include <stdlib.h>
#include <assert.h>



// verifier la fonction vec2_norm --> on veut une distance en mềtre --> faire une fonction vec_norm + vec_to_meters

vec2 f_gravitation(double m1, double m2, vec2 p1_p2){
    vec2 fgrav = vec2_mul(G*m1*m2 / pow(vec2_norm(p1_p2),3), p1_p2); 
    return fgrav;
}

vec2 dist_p1_p2(planet_t p1, planet_t p2){
    vec2 p1_p2 = vec2_create_zero();
    p1_p2.x = p2.prec_pos.x - p1.prec_pos.x;
    p1_p2.y = p2.prec_pos.y - p1.prec_pos.y;
    return p1_p2;
}

vec2 f_res(planet_t p, system_t sys){
    vec2 fres = f_gravitation(p.mass,sys.star.mass,dist_p1_p2(p,sys.star));
    for (uint32_t i=0; i<sys.nb_planets; i++){
        if (p.mass != sys.planets[i].mass){
            fres = vec2_add(fres, f_gravitation(p.mass,sys.planets[i].mass,dist_p1_p2(p, sys.planets[i])));
        }
    }
    return fres;
}

vec2 accel(planet_t p, system_t sys){
    vec2 fres = f_res(p, sys);
    return vec2_mul(1.0/p.mass, fres);
}

vec2 To_Vec(vec2 pos_metre, double r_ecran)
{
    vec2 pos_vec = vec2_create(pos_metre.x/r_ecran, pos_metre.y/r_ecran);
    return pos_vec;
}

vec2 return_vec(vec2 vec)
{
    double temp = vec.x;
    vec.x = (-1) * vec.y;
    vec.y = temp;
    return vec;
}

void init_planet_pos(planet_t *p, system_t sys, double delta_t){
    vec2 vec_perp = return_vec(p->prec_pos);
    vec2 v0 = vec2_mul(sqrt((G*M_SOLEIL*(1.0+p->e)) / (p->axe_a*(1.0-p->e))), vec2_mul(1/vec2_norm(vec_perp), vec_perp));
    vec2 accel_p = accel(*p, sys);
    p->pos = vec2_add(p->prec_pos, vec2_add(vec2_mul(delta_t, v0) , vec2_mul(pow(delta_t, 2.0)/2.0, accel_p)));
    vec2_print(accel_p);
}

uint32_t r_pixel(double r_meters, double screen_m){
    double res = 500000 * r_meters / screen_m;
    if (res<1.0){
        res = 1.0;
    }
    else if (res - floor(res) > 0.5){
        res = ceil(res);
    }
    else{
        res = floor(res);
    }
    return (uint32_t)res;
}

planet_t create_planet(double mass,double e, double axe_a, double r, uint32_t color, vec2 pos)
{
    planet_t planet;
    planet.mass = mass;
    planet.e = e;
    planet.axe_a = axe_a;
    planet.prec_pos = pos;
    planet.r =r;
    planet.color = color;
    //planet.a = vec2_create_zero();
    return planet;
}


system_t create_system(double delta_t)
{
    vec2 Vec_Sol = vec2_create(0, 0);
    planet_t Soleil = create_planet(M_SOLEIL, 0.0, 0.0,R_SOLEIL,COLOR_YELLOW,Vec_Sol);
    
    vec2 Vec_Mercure = vec2_create(P_MERCURE, 0.0);
    planet_t Mercure = create_planet(M_MERCURE, E_MERCURE, MERCURE_AXE_A,R_MERCURE, COLOR_KAKI, Vec_Mercure);

    vec2 Vec_Venus = vec2_create(P_VENUS, 0.0);
    planet_t Venus = create_planet(M_VENUS, E_VENUS, VENUS_AXE_A, R_VENUS, COLOR_BRAUN, Vec_Venus);
    
    vec2 Vec_Terre = vec2_create(P_TERRE, 0.0);
    planet_t Terre = create_planet(M_TERRE, E_TERRE, TERRE_AXE_A,R_TERRE, COLOR_BLUE, Vec_Terre);

    vec2 Vec_Mars = vec2_create(P_MARS, 0.0);
    planet_t Mars = create_planet(M_MARS, E_MARS, MARS_AXE_A, R_MARS, COLOR_RED, Vec_Mars);

    vec2 Vec_Rnd2 = vec2_create(P_RND2, 0.0);
    planet_t Rnd2 = create_planet(M_RND2, E_RND2, RND2_AXE_A, R_RND2, COLOR_GREEN, Vec_Rnd2);

    vec2 Vec_Jupiter = vec2_create(P_JUPITER, 0);
    planet_t Jupiter = create_planet(M_JUPITER, E_JUPITER, JUPITER_AXE_A, R_JUPITER, COLOR_BRAUN, Vec_Jupiter);
    
    vec2 Vec_Saturne = vec2_create(P_SATURNE, 0);
    planet_t Saturne = create_planet(M_SATURNE, E_SATURNE, SATURNE_AXE_A, R_SATURNE, COLOR_GREY, Vec_Saturne);

    vec2 Vec_Uranus = vec2_create(P_URANUS, 0);
    planet_t Uranus = create_planet(M_URANUS, E_URANUS, URANUS_AXE_A, R_URANUS, COLOR_LIGHTBLUE, Vec_Uranus);

    vec2 Vec_Rnd1 = vec2_create(P_RND1, 0);
    planet_t Rnd1 = create_planet(M_RND1, E_RND1, RND1_AXE_A,R_RND1, COLOR_GREEN, Vec_Rnd1);
    
    vec2 Vec_Neptune = vec2_create(P_NEPTUNE, 0);
    planet_t Neptune = create_planet(M_NEPTUNE, E_NEPTUNE, NEPTUNE_AXE_A,R_NEPTUNE, COLOR_BLUE, Vec_Neptune);
    
    
    
    system_t system;
    uint32_t nb_planets = 10;

    system.star = Soleil;
    system.nb_planets = nb_planets;
    system.planets = malloc(nb_planets * sizeof(planet_t)); 
    assert(system.planets != NULL);
    system.planets[0] = Mercure;
    system.planets[1] = Venus;
    system.planets[2] = Terre;
    system.planets[3] = Mars;
    system.planets[4] = Rnd2;
    system.planets[5] = Jupiter;
    system.planets[6] = Saturne;
    system.planets[7] = Uranus;
    system.planets[8] = Rnd1;
    system.planets[9] = Neptune;
    
    for (uint32_t i=0; i<system.nb_planets; i++){
        init_planet_pos(&system.planets[i], system, delta_t);
    }
    
    return system;
    
}
void show_system(struct gfx_context_t *ctxt, system_t *system, double r_ecran, sys_sol center)
{
    uint32_t shift_x = 0;
    uint32_t shift_y = 0;
    if(center > 0)
    {
        coordinates coord_0 = vec2_to_coordinates(vec2_create_zero(),  ctxt->width, ctxt->height);
        coordinates coord_center = vec2_to_coordinates(To_Vec(system->planets[center-1].pos, r_ecran), ctxt->width, ctxt->height);
        shift_x = coord_center.column - coord_0.column;
        shift_y = coord_center.row - coord_0.row;
    }
    coordinates coord_sol = vec2_to_coordinates(To_Vec(system->star.pos, r_ecran ), ctxt->width, ctxt->height);
    coord_sol.column -= shift_x;
    coord_sol.row -= shift_y;
    draw_full_circle(ctxt, coord_sol.column, coord_sol.row, r_pixel(system->star.r, r_ecran), COLOR_YELLOW);
    for( uint32_t i=0; i<system->nb_planets; i++){
        coordinates coord_p = vec2_to_coordinates(To_Vec(system->planets[i].pos, r_ecran), ctxt->width, ctxt->height);
        coord_p.column -= shift_x;
        coord_p.row -= shift_y;
        draw_full_circle(ctxt, coord_p.column, coord_p.row, r_pixel(system->planets[i].r, r_ecran), system->planets[i].color);
    }
    
}
void update_system(system_t *system, double delta_t)
{
    for(uint32_t i=0; i<system->nb_planets; i++){
        system->planets[i].a = accel(system->planets[i], *system);  
    }
    for(uint32_t i=0; i<system->nb_planets; i++){
        vec2 temp = system->planets[i].pos;
        system->planets[i].pos = vec2_add(vec2_sub(vec2_mul(2, temp), system->planets[i].prec_pos), vec2_mul(pow(delta_t,2.0), system->planets[i].a));
        system->planets[i].prec_pos = temp;
    }
}




void free_system(system_t *system)
{
    free(system->planets);
    system->planets = NULL;
    
}


