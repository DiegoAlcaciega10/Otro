#include <iostream>
#include <stdlib.h> 
#include <string>
using namespace std;

class Dron{
    private:
    int *ndrones;
    int *energia;
    public:
    Dron(int n){
        ndrones= new int[n];
        energia= new int[n];
    }
    void asignarenergia(int n){
        for(int i=0; i<n; i++){
            cout<<"Ingrese la energia del dron "<<i+1<<": ";
            cin>>energia[i];
        }
    }
    void mostrardrones(int n){
        cout <<"Drones y  energia "<<endl;
        for(int i=0;i<n;i++){
           cout<<"Dron "<<i+1<<": Energia = "<<energia[i]<<endl;  
        }
    }

};


int main(){
    cout<<"Programa de misiones de drones"<<endl;
    cout<<"----------------------------"<<endl;
    int n=0,m=0;

    cout <<"Ingrese el numero de drones"<<endl;
    cin >> n;
    cout <<"Ingrese el numero de misiones"<<endl;
    cin >> m;
    Dron drones(n);
    drones.asignarenergia(n);
    drones.mostrardrones(n);
    return 0;
}