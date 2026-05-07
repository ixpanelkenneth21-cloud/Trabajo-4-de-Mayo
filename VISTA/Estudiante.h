#pragma once
#include "persona.h"
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>

using namespace std;
class Estudiante : persona{
	//Atributos
private: string codigo;
	   int id_estudiante = 0;
	   //Constructor
public :
	   Estudiante(){}
	   Estudiante(string nom, string ape, string dir, int tel, string fn, int id_ts, string cod, int id_e) : persona(nom, ape, dir, tel, fn, id_ts) {
		   codigo = cod;
		   id_estudiante = id_e;
	   }
	   //Metodos Get y Set
	   // Set(modificar un atributo)
	   void setId_estudiante(int e) { id_estudiante = e; }
	   void setCodigo(string c) { codigo = c; }
	   void setNombres(string n) { nombres = n; }
	   void setApellidos(string a) { apellidos = a; }
	   void setDireccion(string d) { direccion = d; }
	   void setTelefono(int t) { telefono = t; }
	   void setFecha_nacimiento(string fn) { fecha_nacimiento = fn; }
	   void setId_tipos_sangre(int ts) { id_tipos_sangre = ts; }

	   // Get(obtener el valor de un atributo)
	   int getId_estudiante() { return id_estudiante; }
	   string getCodigo() { return codigo; }
	   string getNombres() { return nombres; }
	   string getApellidos() { return apellidos; }
	   string getDireccion() { return direccion; }
	   int getTelefono() { return telefono; }
	   string getFecha_nacimiento() { return fecha_nacimiento; }
	   int getId_tipos_sangre() { return id_tipos_sangre; }

	   //Metodos
	   void crear(){
		   int q_estado = 0;
		   ConexionBD cn = ConexionBD();
		   cn.abrir_conexion();
		   if (cn.getConector()) {
			   //Convierte un entero a un string
			   string t = to_string(telefono);
			   string id_ts = to_string(id_tipos_sangre);
			   string consulta = "INSERT INTO estudiantes(codigo,nombres,apellidos,direccion,telefono,fecha_nacimiento,id_tipos_sangre) VALUES ('"+codigo+"','"+nombres+"','" +apellidos+ "','" +direccion+ "',"+t+",'"+fecha_nacimiento+"',"+id_ts+");";
			   const char* c = consulta.c_str();
			   q_estado = mysql_query(cn.getConector(), c);
			   if (!q_estado) {
				   cout << " xxx Ingreso Exitoso de Datosxxx" << endl;
			   }
			   else {
				   cout << " xxx Consulta Fallida: " << mysql_error(cn.getConector()) << " xxx" << endl;
			   }

		   }
		   else {
			   cout << " xxx Fallo la Conexion xxx" << endl;
		   }
		   cn.cerrar_conexion();
	   }
	   void leer() {
		   int q_estado = 0;
		   ConexionBD cn = ConexionBD();
		   MYSQL_ROW fila;
		   MYSQL_RES* resultado;
		   cn.abrir_conexion();
		   if (cn.getConector()) {
			   cout << "------------Datos del Estudiante------------" << endl;
			   string consulta = "SELECT e.id_estudiantes, e.codigo, e.nombres, e.apellidos, e.direccion, e.telefono, e.fecha_nacimiento, ts.sangre FROM estudiantes as e inner join tipos_sangre as ts on e.id_tipos_sangre = ts.id_tipos_sangre;";
			   const char* c = consulta.c_str();
			   q_estado = mysql_query(cn.getConector(), c);
			   if (!q_estado) {
				   resultado = mysql_store_result(cn.getConector());
				   while (fila = mysql_fetch_row(resultado)) {
					   cout << fila[0] << "," << fila[1] << "," << fila[2] << "," << fila[3] << "," << fila[4] << "," << fila[5] << "," << fila[6] << "," << fila[7] << endl;
				   }
			   }
			   else {
				   cout << " xxx Error al Consultar: " << mysql_error(cn.getConector()) << " xxx" << endl;
			   }

		   }
		   else {
			   cout << " xxx Fallo la Conexion xxx" << endl;
		   }
		   cn.cerrar_conexion();
	   }
	   void actualizar() {
		   int q_estado = 0;
		   ConexionBD cn = ConexionBD();
		   cn.abrir_conexion();
		   if (cn.getConector()) {
			   //Convierte un entero a un string

			   string t = to_string(telefono);
			   string id_ts = to_string(id_tipos_sangre);
			   string id_e = to_string(id_estudiante);
			   string consulta = "update estudiantes set codigo = '" + codigo + "', nombres = '" + nombres + "', apellidos = '" + apellidos + "', direccion = '" + direccion + "', telefono = " + t + ", fecha_nacimiento = '" + fecha_nacimiento + "', id_tipos_sangre =" + id_ts + " where codigo = '" + id_e + "";
			   const char* c = consulta.c_str();
			   q_estado = mysql_query(cn.getConector(), c);
			   if (!q_estado) {
				   cout << " xxx Modificacion de Datos Exitoso xxx" << endl;
			   }
			   else {
				   cout << " xxx Consulta Fallida: " << mysql_error(cn.getConector()) << " xxx" << endl;
			   }
		   }
		   else {
			   cout << " xxx Fallo la Conexion xxx" << endl;
		   }
		   cn.cerrar_conexion();
	   }
	   void borrar() {
		   int q_estado = 0;
		   ConexionBD cn = ConexionBD();
		   cn.abrir_conexion();
		   if (cn.getConector()) {
			   //Convierte un entero a un string
			   string t = to_string(telefono);
			   string id_ts = to_string(id_tipos_sangre);
			   string id_e = to_string(id_estudiante);
			   string consulta = "delete from estudiantes where codigo = '" + id_e + "";
			   const char* c = consulta.c_str();
			   q_estado = mysql_query(cn.getConector(), c);
			   if (!q_estado) {
				   cout << " xxx Eliminacion de Datos Exitoso xxx" << endl;
			   }
			   else {
				   cout << " xxx Consulta Fallida: " << mysql_error(cn.getConector()) << " xxx" << endl;
			   }
		   }
		   else {
			   cout << " xxx Fallo la Conexion xxx" << endl;
		   }
		   cn.cerrar_conexion();
	   }
};

