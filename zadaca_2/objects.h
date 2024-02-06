#pragma once
#include <cmath>
#include "geometry.h"
#include "ray.h"
#include "material.h"

class Object 
{
  public:
    Material material;
    virtual bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const = 0;  
};

class Sphere : public Object
{
    float r;
    Vec3f c;
      
  public:
    Sphere(const Vec3f &c, const float &r) : c(c), r(r) { }
    Sphere(const Vec3f &c, const float &r, const Material &mat) : c(c), r(r)
    { 
        Object::material = mat;
    }

    bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const
    {
        Vec3f e_minus_c = ray.origin - c;
        float d2 = ray.direction * ray.direction;
        
        float disc = pow(ray.direction * e_minus_c, 2) - d2 * (e_minus_c * e_minus_c - r * r);
        
        if (disc < 0)
        {
            return false;
        }
        else
        {
            bool ray_inside_sphere = e_minus_c * e_minus_c <= r * r;
            if (ray_inside_sphere)
            {
                float t1 = (-ray.direction * e_minus_c + sqrt(disc)) / d2;
                t = t1;
            }
            else
            {
                float t2 = (-ray.direction * e_minus_c - sqrt(disc)) / d2;
                t = t2;
            }
            
            Vec3f hit_point = ray.origin + ray.direction * t;
            normal = (hit_point - c).normalize();
            return true;
        }
    }
};
	
class Cuboid : public Object
{
    Vec3f c1;
    Vec3f c2;

public:

    Cuboid(const Vec3f &c1, const Vec3f &c2, const Material &mat): c1(c1), c2(c2) {
        Object::material = mat;
    }

    bool ray_intersect(const Ray &ray, float &t, Vec3f &normal) const{
        float t_near = numeric_limits<float>::min(); 
        float t_far = numeric_limits<float>::max(); 

        
        float x_min = min(c1.x, c2.x);
        float x_max = max(c1.x, c2.x);

        float y_min = min(c1.y, c2.y);
        float y_max = max(c1.y, c2.y);

        float z_min = min(c1.z, c2.z);
        float z_max = max(c1.z, c2.z);
        
        
        if(ray.direction.x == 0){
            if(ray.origin.x < x_min || ray.origin.x > x_max)
                return false; 
            
        }
		else
		{
            float t1 = (x_min - ray.origin.x) / ray.direction.x;
            float t2 = (x_max - ray.origin.x) / ray.direction.x;

            if(t1 > t2)
                swap(t1, t2);
            

            t_near = max(t_near, t1);
            t_far = min(t_far, t2); 

            if(t_near > t_far || t_far < 0)
                return false;
            
        }

        t = t_near;

        
        if(ray.direction.y == 0){
            if(ray.origin.y < y_min || ray.origin.y > y_max)
                return false;
        }
		else
		{
            float t1 = (y_min - ray.origin.y) / ray.direction.y;
            float t2 = (y_max - ray.origin.y) / ray.direction.y;

            if(t1 > t2)
                swap(t1,t2);
            

            t_near = max(t_near, t1);
            t_far = min(t_far, t2); 

            if(t_near > t_far || t_far < 0)
                return false;
            
        }

        t = t_near;

        
        if(ray.direction.z == 0){
            if(ray.origin.z < z_min || ray.origin.z > z_max)
                return false;
            
        }
		else
		{
            float t1 = (z_min - ray.origin.z) / ray.direction.z;
            float t2 = (z_max - ray.origin.z) / ray.direction.z;

            if(t1 > t2)
                swap(t1, t2);
            

            t_near = max(t_near, t1);
            t_far = min(t_far, t2); 

            if(t_near > t_far || t_far < 0)
                return false;
            
        }

        t = t_near;


        
        if (abs(ray.origin.x - c1.x) < 0.01)
            normal = Vec3f(1, 0, 0);
        
		else if (abs(ray.origin.x - c2.x) < 0.01)
            normal = Vec3f(-1, 0, 0);
			
        else if(abs(ray.origin.y - c1.y) < 0.01)
            normal = Vec3f(0, 1, 0);
		
        else if(abs(ray.origin.y - c2.y) < 0.01)
            normal = Vec3f(0, -1, 0);
		
        else if(abs(ray.origin.z - c1.z) < 0.01)
            normal = Vec3f(0, 0, 1);
		
        else if(abs(ray.origin.z - c2.z) < 0.01)
            normal = Vec3f(0, 0, -1);
        


        return true;
    }
};