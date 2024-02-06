#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "tgaimage.h"
using namespace std;

// dimenzije slike
const int width  = 512;
const int height = 512;

const TGAColor green = TGAColor(0, 255, 0, 1);
const TGAColor red   = TGAColor(255, 0, 0, 1);
const TGAColor blue  = TGAColor(0, 0, 255, 1);
const TGAColor purple = TGAColor(225, 0, 225, 1);
               

//baricentricne kooridnate
float bar_coord(float x_a,float y_a,float x_c,float y_c,float x,float y){
    return((y_a - y_c) * x + (x_c - x_a) * y + x_a * y_c - x_c * y_a);
}

void set_color(int x, int y, TGAImage &image, TGAColor color, bool invert = false){
    image.set(y, x, color);
}

//zadatak 1
void draw_triangle_2d(float x0, float y0, float x1, float y1, float x2, float y2 ,TGAImage &image,TGAColor color){   
    float min_x = floor(min((min(x0,x1)), x2));
    float max_x = ceil(max((max(x0, x1)), x2));
    float min_y = floor(min((min(y0,y1)), y2));
    float max_y = ceil(max((max(y0, y1)), y2));

    for(float y = min_y; y <= max_y; y++){
        for(float x = min_x; x <= max_x; x++){
            float alpha = bar_coord(x1, y1, x2, y2, x, y) / bar_coord(x1, y1, x2, y2, x0, y0);
            float beta = bar_coord(x2, y2, x0, y0, x, y) / bar_coord(x2, y2, x0, y0, x1, y1);
            float gamma = bar_coord(x0, y0, x1, y1, x, y) / bar_coord(x0, y0, x1, y1, x2, y2);

            if((alpha >= 0 && beta >= 0 && gamma >= 0) && (alpha <= 1 && beta <= 1 && gamma <= 1)){
                if((alpha > 0 || (bar_coord(x1, y1, x2, y2, x0, y0) * bar_coord(x1, y1, x2, y2, -1, -1)) >= 0) &&
                (beta > 0 || (bar_coord(x2, y2, x0, y0, x1, y1) * bar_coord(x2, y2, x0, y0, -1, -1)) >= 0) &&
                (gamma > 0 || (bar_coord(x0, y0, x1, y1, x2, y2) * bar_coord(x0, y0, x1, y1, -1, -1)) >= 0)){
                    set_color(x, y, image, color);
                }
            }
        }
    }
}


//zadatak 2
void draw_triangle_2d_gouraurd (float x0, float y0, float x1, float y1, float x2, float y2 ,TGAImage &image,TGAColor c0,TGAColor c1,TGAColor c2){
    float min_x = floor(min((min(x0,x1)), x2));
    float max_x = ceil(max((max(x0, x1)), x2));
    float min_y = floor(min((min(y0,y1)), y2));
    float max_y = ceil(max((max(y0, y1)), y2));

    for(float y = min_y; y <= max_y; y++){
        for(float x = min_x; x <= max_x; x++){
            float alpha = bar_coord(x1, y1, x2, y2, x, y) / bar_coord(x1, y1, x2, y2, x0, y0);
            float beta = bar_coord(x2, y2, x0, y0, x, y) / bar_coord(x2, y2, x0, y0, x1, y1);
            float gamma = bar_coord(x0, y0, x1, y1, x, y) / bar_coord(x0, y0, x1, y1, x2, y2);

            if((alpha >= 0 && beta >= 0 && gamma >= 0) && (alpha <= 1 && beta <= 1 && gamma <= 1)){
                if((alpha > 0 || (bar_coord(x1, y1, x2, y2, x0, y0) * bar_coord(x1, y1, x2, y2, -1, -1)) >= 0) &&
                (beta > 0 || (bar_coord(x2, y2, x0, y0, x1, y1) * bar_coord(x2, y2, x0, y0, -1, -1)) >= 0) &&
                (gamma > 0 || (bar_coord(x0, y0, x1, y1, x2, y2) * bar_coord(x0, y0, x1, y1, -1, -1)) >= 0)){
                    TGAColor c;
                    c.r = alpha*c0.r + beta*c1.r + gamma*c2.r;
                    c.g = alpha*c0.g + beta*c1.g + gamma*c2.g;
                    c.b = alpha*c0.b + beta*c1.b + gamma*c2.b;

                    set_color(x,y,image,c);
                }
            }
        }
    }
}

//zadatak 3
void draw_triangle(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2,TGAImage &image,TGAColor color){
    // pretvorba homogenih u normalne
    x0 = x0 / z0;
    y0 = y0 / z0;
    x1 = x1 / z1;
    y1 = y1 / z1;
    x2 = x2 / z2;
    y2 = y2 / z2;

    //transformacija
    x0 = (1 + x0) * width * 0.5;
    x1 = (1 + x1) * width * 0.5;
    x2 = (1 + x2) * width * 0.5;

    y0 = (1 + y0) * height * 0.5;
    y1 = (1 + y1) * height * 0.5;
    y2 = (1 + y2) * height * 0.5;

    float min_x = floor(min((min(x0,x1)), x2));
    float max_x = ceil(max((max(x0, x1)), x2));
    float min_y = floor(min((min(y0,y1)), y2));
    float max_y = ceil(max((max(y0, y1)), y2));

    for(float y = min_y; y <= max_y; y++){
        for(float x = min_x; x <= max_x; x++){
            float alpha = bar_coord(x1, y1, x2, y2, x, y) / bar_coord(x1, y1, x2, y2, x0, y0);
            float beta = bar_coord(x2, y2, x0, y0, x, y) / bar_coord(x2, y2, x0, y0, x1, y1);
            float gamma = bar_coord(x0, y0, x1, y1, x, y) / bar_coord(x0, y0, x1, y1, x2, y2);

            if((alpha >= 0 && beta >= 0 && gamma >= 0) && (alpha <= 1 && beta <= 1 && gamma <= 1)){
                if((alpha > 0 || (bar_coord(x1, y1, x2, y2, x0, y0) * bar_coord(x1, y1, x2, y2, -1, -1)) >= 0) &&
                (beta > 0 || (bar_coord(x2, y2, x0, y0, x1, y1) * bar_coord(x2, y2, x0, y0, -1, -1)) >= 0) &&
                (gamma > 0 || (bar_coord(x0, y0, x1, y1, x2, y2) * bar_coord(x0, y0, x1, y1, -1, -1)) >= 0)){
                    set_color(x, y, image, color);
                }
            }
        }
    }
}

//zadatak 4
void draw_triangle_tex(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float u0, float v0, float u1, float v1, float u2, float v2, TGAImage &image, const char* path){
    x0 = x0 / z0;
    y0 = y0 / z0;
    x1 = x1 / z1;
    y1 = y1 / z1;
    x2 = x2 / z2;
    y2 = y2 / z2;

    x0 = (1 + x0) * width * 0.5;
    x1 = (1 + x1) * width * 0.5;
    x2 = (1 + x2) * width * 0.5;

    y0 = (1 + y0) * height * 0.5;
    y1 = (1 + y1) * height * 0.5;
    y2 = (1 + y2) * height * 0.5;

    float min_x = floor(min((min(x0,x1)), x2));
    float max_x = ceil(max((max(x0, x1)), x2));
    float min_y = floor(min((min(y0,y1)), y2));
    float max_y = ceil(max((max(y0, y1)), y2));

    TGAImage texture;
    texture.read_tga_file(path);

    for(float y = min_y; y <= max_y; y++){
        for(float x = min_x; x <= max_x; x++){
            float alpha = bar_coord(x1, y1, x2, y2, x, y) / bar_coord(x1, y1, x2, y2, x0, y0);
            float beta = bar_coord(x2, y2, x0, y0, x, y) / bar_coord(x2, y2, x0, y0, x1, y1);
            float gamma = bar_coord(x0, y0, x1, y1, x, y) / bar_coord(x0, y0, x1, y1, x2, y2);

            if((alpha >= 0 && beta >= 0 && gamma >= 0) && (alpha <= 1 && beta <= 1 && gamma <= 1)){
                if((alpha > 0 || (bar_coord(x1, y1, x2, y2, x0, y0) * bar_coord(x1, y1, x2, y2, -1, -1)) >= 0) &&
                (beta > 0 || (bar_coord(x2, y2, x0, y0, x1, y1) * bar_coord(x2, y2, x0, y0, -1, -1)) >= 0) &&
                (gamma > 0 || (bar_coord(x0, y0, x1, y1, x2, y2) * bar_coord(x0, y0, x1, y1, -1, -1)) >= 0)){
                    float u = round(texture.get_width() * (alpha * u0 + beta * u1 + gamma * u2));
                    float v = round(texture.get_height() * (alpha * v0 + beta * v1 + gamma * v2));
                    TGAColor textrue_color = texture.get(u, v);
                    set_color(x, y, image, textrue_color);
                }
            }
        }
    }
}

void draw_triangle_tex_corrected(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float u0, float v0, float u1, float v1, float u2, float v2, TGAImage &image, const char* path){
    x0 = x0 / z0;
    y0 = y0 / z0;
    x1 = x1 / z1;
    y1 = y1 / z1;
    x2 = x2 / z2;
    y2 = y2 / z2;

    u0 = u0 / z0;
    u1 = u1 / z1;
    u2 = u2 / z2;    
    v0 = v0 / z0;
    v1 = v1 / z1;
    v2 = v2 / z2;

    z0 = 1 / z0;
    z1 = 1 / z1;
    z2 = 1 / z2;

    x0 = (1 + x0) * width * 0.5;
    x1 = (1 + x1) * width * 0.5;
    x2 = (1 + x2) * width * 0.5;

    y0 = (1 + y0) * height * 0.5;
    y1 = (1 + y1) * height * 0.5;
    y2 = (1 + y2) * height * 0.5;

    float min_x = floor(min((min(x0,x1)), x2));
    float max_x = ceil(max((max(x0, x1)), x2));
    float min_y = floor(min((min(y0,y1)), y2));
    float max_y = ceil(max((max(y0, y1)), y2));

    TGAImage texture;
    texture.read_tga_file(path);

    for(float y = min_y; y <= max_y; y++){
        for(float x = min_x; x <= max_x; x++){
            float alpha = bar_coord(x1, y1, x2, y2, x, y) / bar_coord(x1, y1, x2, y2, x0, y0);
            float beta = bar_coord(x2, y2, x0, y0, x, y) / bar_coord(x2, y2, x0, y0, x1, y1);
            float gamma = bar_coord(x0, y0, x1, y1, x, y) / bar_coord(x0, y0, x1, y1, x2, y2);

            if((alpha >= 0 && beta >= 0 && gamma >= 0) && (alpha <= 1 && beta <= 1 && gamma <= 1)){
                if((alpha > 0 || (bar_coord(x1, y1, x2, y2, x0, y0) * bar_coord(x1, y1, x2, y2, -1, -1)) >= 0) &&
                (beta > 0 || (bar_coord(x2, y2, x0, y0, x1, y1) * bar_coord(x2, y2, x0, y0, -1, -1)) >= 0) &&
                (gamma > 0 || (bar_coord(x0, y0, x1, y1, x2, y2) * bar_coord(x0, y0, x1, y1, -1, -1)) >= 0)){
                    float u = round(texture.get_width() * (alpha * u0 + beta * u1 + gamma * u2));
                    float v = round(texture.get_height() * (alpha * v0 + beta * v1 + gamma * v2));

                    float z = 1 / (alpha * z0 + beta * z1 + gamma * z2);

                    u = u * z;
                    v = v * z;


                    TGAColor textrue_color = texture.get(u, v);
                    set_color(x, y, image, textrue_color);
                }
            }
        }
    }
}


int main()
{
    // definiraj sliku
    TGAImage image(width, height, TGAImage::RGB);
    
    // nacrtaj trokut 
    draw_triangle_2d(120, 230, 200, 230, 100, 120,image, purple);
    draw_triangle_2d(400, 300, 400, 150, 350,240,image, red);
    draw_triangle_2d_gouraurd(350, 350, 320, 100, 220,150,image, red,green,blue);
    
    // spremi sliku 
    image.flip_vertically();
    image.write_tga_file("zad1&2.tga");
    //-------------------------------------------------------------------------------------//

    TGAImage image2(width, height, TGAImage::RGB);

    draw_triangle(-48, -10, 82, 29, -15, 44, 13, 34, 114, image2, blue);

    image2.flip_vertically();
    image2.write_tga_file("zad3.tga");
    //-------------------------------------------------------------------------------------//

    TGAImage image3(width, height, TGAImage::RGB);

    draw_triangle_tex(-48, -10, 82, 29, -15, 44, 13, 34, 114, 0, 0, 0, 1, 1, 0, image3, "rocks.tga");

    image3.flip_vertically();
    image3.write_tga_file("zad4_a.tga");
    //-------------------------------------------------------------------------------------//

    TGAImage image4(width, height, TGAImage::RGB);

    draw_triangle_tex_corrected(-48, -10, 82, 29, -15, 44, 13, 34, 114, 0, 0, 0, 1, 1, 0, image4, "rocks.tga");

    image4.flip_vertically();
    image4.write_tga_file("zad4_b.tga");


}