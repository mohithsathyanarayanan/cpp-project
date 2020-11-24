#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include <fstream>
#include <vector>
using namespace  std;
#include<string>

struct vertices
{
    float x,y,z ;
};



class ply 
{
    public:
    vector <int> face_list;
    int faces_num ;
    int vertices_num ;
    vector <vertices> vertices_list ;
    ply(vector <vertices> &v,vector <int> &f,int ver , int fac)
    {
        face_list = f ;
        vertices_num = ver ;
        faces_num = fac ;
        vertices_list = v ;
    }

    
    
    float area(vertices v1,vertices v2, vertices v3) //its always going to be 3X3 matrix
    {
        float det ;
        det = v1.x * ((v2.y * v3.z) - (v2.z * v3.y)) - v1.y * ((v2.x * v3.z)-(v2.z * v3.x)) + v1.z*((v2.x * v3.y) - (v2.y*v3.x)) ;
        float area = det*0.5 ;
        return area ;
    }

    
    float triangle(vector <int> temp)
    {
        float tri_area = area(vertices_list[temp[0]],vertices_list[temp[1]],vertices_list[temp[2]]) ;
        return abs(tri_area) ;
    }


    vector <float> face(vector <int> &temp,int facelines)
    {
        vector <float> sublist ;
        int count = 0 ;
        bool flag = true ;
        int area ;
        while(flag)
        {
            count = count + 1 ;
            int x = temp[0] ;
            int y = temp[1] ;
            int z = temp[2] ;
            vector <int> :: iterator it ;
            it = temp.begin() ;
            it++ ;
            area= triangle(temp) ;
            sublist.push_back(area) ;
            temp.erase(it) ;
            if(count == facelines-2)
            {
                flag =false ;
            }
        }

        return sublist ;
    }
    
        
    vector <float> face_area(int face_lines)
    {
        int count = 0 ;
        vector <int> temp ;
        vector <float> list ;
        vector <float> sublist ; 
        for(int x : face_list)
        {
            count=count+1 ;
            temp.push_back(x) ;

            if(count==face_lines)
            {
                count=0 ;
                sublist=face(temp,face_lines) ;
                for(float x : sublist)
                {
                    list.push_back(x) ;
                }
                temp.clear() ;

            }
        }
        return list ;
    }    
    
    
    
    


};