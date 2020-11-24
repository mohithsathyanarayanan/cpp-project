#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<algorithm>
#include <fstream>
#include "Base.cpp"
#include <vector>
using namespace  std;
#include<string>
#include "ply.cpp"
#include<utility>
#include<bits/stdc++.h>

double polygonArea(double X[], double Y[], int n) 
{ 
    // Initialze area 
    double area = 0.0; 
  
    // Calculate value of shoelace formula 
    int j = n - 1; 
    for (int i = 0; i < n; i++) 
    { 
        area += (X[j] + X[i]) * (Y[j] - Y[i]); 
        j = i;  // j is previous vertex to i 
    } 
  
    // Return absolute value 
    return abs(area / 2.0); 
}


vector <int> mid_vertex(vector <int> &v, int facelines)
{
    vector <int> middle ;
    for(int i =1 ; i<facelines-1;i++)
    {
        middle.push_back(v[i]) ;
    }

    return middle ;

}



int main()
{
    string myply ;
    ifstream MyReadFile("cube.txt");

    string vertex = "vertex" ;
    int vertex_num ;
    string face = "face" ;
    int face_num ;
    while(getline(MyReadFile,myply))
    {
        size_t found_2 = myply.find(face) ; 
        size_t found = myply.find(vertex) ;
        if(found!=std::string::npos)
        {
            vertex_num = int(myply[found+7])-48 ;
            cout<< vertex_num << endl ;
            
            
        }

        if(found_2 != std::string:: npos )
        {
            face_num = int(myply[found_2+5])-48 ;
            cout<<face_num << endl ;
            break ;
        }
    }
    vector <float> v2 ;
    vector <vertices> v ;
    int counter ;
    bool flag = false ;
    while(getline(MyReadFile,myply))
    {
        string end = "end_header" ;
        size_t found_3 =  myply.find(end) ;
        
        if(found_3!=std::string::npos)
        {
            flag = true ;
            continue ;
        }
        int len = myply.length() ;
        string num_str="" ;
        int num,num2 ;
        
        while(flag)
        {
            counter = counter+1 ;
            float x,y,z ;
            vector <float> temp ;
            for(int i = 0 ; i<len ; i++)
            {
                string element = string(1,myply[i]) ;
                if(element.compare(" ")!=0)
                {
                    num_str=num_str+element ;
                }

                if(element.compare(" ")==0)
                {
                    num = stof(num_str) ;
                    num_str ="" ;
                    temp.push_back(num) ; 
                    v2.push_back(num) ;  
                }

            }
            if(counter<vertex_num+1)
            {
                v.push_back({temp[0],temp[1],temp[2]}) ;
            }
            if(counter == vertex_num+face_num)
            {
                flag=false ;
            }
            break;
        }

        
    }

    for(int i = 0 ; i<vertex_num ; i++)
    {
        cout<< v[i].x << " " << v[i].y << " " << v[i].z << endl ;
    }
    vector <int> facelist ;
    for(int i = vertex_num*3 ; i<v2.size();i++)
    {
        facelist.push_back(v2[i]) ;
    }

    int face_lines = facelist.size()/face_num ;
    int counter2=0 ;
    vector <int> sublist ;
    vector <int> mid_list ;
    for(int x : facelist)
    {
        cout<< x<<" " ;
        sublist.push_back(x) ;
        counter2 = counter2+1 ;
        if(counter2==face_lines)
        {
            vector <int> result ;
            cout<<endl ;
            counter2=0 ;
            for(int z : sublist)
            {
                cout<<z ;
            }
            cout<<endl ;
            result = mid_vertex(sublist,face_lines);
            for(int r : result)
            {
                mid_list.push_back(r) ;
            }
            result.clear() ;
            sublist.clear() ;
        }
    }

    for(int m : mid_list)
    {
        cout<<m ;
    }
    ply p(v,facelist,vertex_num,face_num) ;   

    vector <float> list ;
    list = p.face_area(face_lines) ;


    vector< pair <float,int> > vect; //first is area and second is index of sublist vertex
    
    for(int i = 0 ; i<list.size();i++)
    {
        vect.push_back(make_pair(list[i],mid_list[i]));
    }

    sort(vect.rbegin(), vect.rend()) ;
    reverse(vect.begin(),vect.end());

    int bottom = floor(list.size()/10) ;

    vector <int> ejector ;

    for(int i = 0 ; i<bottom;i++)
    {
        ejector.push_back(vect[i].second) ;
    }

    for(int x : ejector)
    {
        v.erase(v.begin()+x) ;
    }

    ofstream file ;
    file.open("output.txt");
    file<<"ply"<<endl ;
    file<<"format ascii 1.0"<<endl ;
    file<<"element vertex "<< vertex_num-bottom<<endl ;
    file<<"property float32 x"<<endl ;
    file<<"property float32 y"<<endl ;
    file<<"property float32 z"<<endl ;
    file<<"element face "<< face_num-bottom<<endl ;
    file<<"property list uint8 int32 vertex_indices"<<endl ;
    file<<"end_header"<<endl ;
    int c = 0 ;
    for(vertices s : v)
    {
        c=c+1 ;
        file<< s.x <<" "<< s.y<<" " << s.z<<endl ;
        if(c==vertex_num-ejector.size())
        {
            break ;
        }
    }
    int c2 = 0 ;
    for( int f : facelist)
    {
        c2=c2+1 ;
        file<<f<<" " ;

        if(c2==face_lines)
        {
            file<<endl ;
            c2=0 ;
        }

    }



          
}