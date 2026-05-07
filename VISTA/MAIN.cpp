#include <iostream>
#include "Estudiante.h"
using namespace std;

int main() {
	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	int telefono = 0, id_tipos_sangre = 0, id_estudiante = 0;

	// --- 1. INGRESO DE DATOS ---
	cout << "Ingrese Codigo: ";
	getline(cin, codigo); // Usamos getline por si el codigo tiene letras
	cout << "Ingrese Nombres: ";
	getline(cin, nombres);
	cout << "Ingrese Apellidos: ";
	getline(cin, apellidos);
	cout << "Ingrese Direccion: ";
	getline(cin, direccion);
	cout << "Ingrese Telefono: ";
	cin >> telefono;
	cin.ignore();
	cout << "Ingrese Fecha Nacimiento: ";
	getline(cin, fecha_nacimiento);
	cout << "Ingrese Tipo Sangre: ";
	cin >> id_tipos_sangre;
	cin.ignore();

	Estudiante e = Estudiante(nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipos_sangre, codigo, id_estudiante);
	e.crear();
	e.leer();

	// --- 2. ACTUALIZACION DE DATOS ---
	cout << "Ingrese el ID a modificar: "; // Cambiamos a ID para que coincida con tu imagen 1/2
	cin >> id_estudiante;
	cin.ignore();

	cout << "Ingrese Codigo: ";
	getline(cin, codigo);
	cout << "Ingrese Nombres: ";
	getline(cin, nombres);
	cout << "Ingrese Apellidos: ";
	getline(cin, apellidos);
	cout << "Ingrese Direccion: ";
	getline(cin, direccion);
	cout << "Ingrese Telefono: ";
	cin >> telefono;
	cin.ignore();
	cout << "Ingrese Fecha Nacimiento: ";
	getline(cin, fecha_nacimiento);
	cout << "Ingrese Tipo Sangre: ";
	cin >> id_tipos_sangre;
	cin.ignore();

	// Pasamos los nuevos valores al objeto
	e.setId_estudiante(id_estudiante); // Importante para saber a quién actualizar
	e.setCodigo(codigo);
	e.setCodigo(codigo);
	e.setNombres(nombres);
	e.setApellidos(apellidos);
	e.setDireccion(direccion);
	e.setTelefono(telefono);
	e.setFecha_nacimiento(fecha_nacimiento);
	e.setId_tipos_sangre(id_tipos_sangre);

	e.actualizar();
	e.leer();

	// --- 3. ELIMINACION DE DATOS ---
	cout << "Ingrese el ID a eliminar: ";
	cin >> id_estudiante;
	cin.ignore(); // Agregamos este para limpiar la ultima entrada

	e.setId_estudiante(id_estudiante);
	e.borrar();
	e.leer();
}



























//COMO PUEDO VER SI SE HIZO CONEXION 
/*
	ConexionBD cn = ConexionBD();
	cn.abrir_conexion();
	if (cn.getConector()) {
		cout << "Conexion exitosa" << endl;
	}
	else{
		cout << "Conexion fallida" << endl;
	}
	cn.cerrar_conexion();
	*/