#pragma once
#include <iostream>
using namespace std;
class persona{
	//Atributos
protected: string nombres, apellidos, direccion, fecha_nacimiento;
		 int telefono = 0, id_tipos_sangre = 0;
		 //Constructores
		 persona(){}
		 persona(string nom, string ape,string dir, int tel,string fn,int id_st) {
			 nombres = nom;
			 apellidos = ape;
			 direccion = dir;
			 telefono = tel;
			 fecha_nacimiento = fn;
			 id_tipos_sangre = id_st;
		 }
};

