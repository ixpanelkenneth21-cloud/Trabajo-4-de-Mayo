#pragma once
#include "persona.h"
#include <iostream>
#include <mysql.h>
#include "ConexionBD.h"
#include <string>

using namespace std;

class Estudiante : public persona {
private:
	string codigo;
	int id_estudiante = 0;

	// Función auxiliar para escapar texto y prevenir Inyección SQL
	string escaparString(MYSQL* conector, string texto) {
		// Crear un buffer con el doble de tamaño requerido por la API de MySQL
		char* buffer = new char[texto.length() * 2 + 1];
		mysql_real_escape_string(conector, buffer, texto.c_str(), texto.length());
		string resultado(buffer);
		delete[] buffer;
		return resultado;
	}

public:
	Estudiante() {}
	Estudiante(string nom, string ape, string dir, int tel, string fn, int id_ts, string cod, int id_e)
		: persona(nom, ape, dir, tel, fn, id_ts) {
		codigo = cod;
		id_estudiante = id_e;
	}

	// Métodos Get y Set
	void setId_estudiante(int e) { id_estudiante = e; }
	void setCodigo(string c) { codigo = c; }
	void setNombres(string n) { nombres = n; }
	void setApellidos(string a) { apellidos = a; }
	void setDireccion(string d) { direccion = d; }
	void setTelefono(int t) { telefono = t; }
	void setFecha_nacimiento(string fn) { fecha_nacimiento = fn; }
	void setId_tipos_sangre(int ts) { id_tipos_sangre = ts; }

	int getId_estudiante() { return id_estudiante; }
	string getCodigo() { return codigo; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getDireccion() { return direccion; }
	int getTelefono() { return telefono; }
	string getFecha_nacimiento() { return fecha_nacimiento; }
	int getId_tipos_sangre() { return id_tipos_sangre; }

	// Validación: Verificar si el código ya existe en la BD (Evita duplicados)
	bool codigoExiste(string cod, int id_actual = 0) {
		bool existe = false;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			// Si id_actual > 0, excluye al estudiante que se está editando
			string consulta = "SELECT COUNT(*) FROM estudiantes WHERE codigo = '" + cod + "' AND id_estudiantes != " + to_string(id_actual) + ";";
			mysql_query(cn.getConector(), consulta.c_str());
			MYSQL_RES* res = mysql_store_result(cn.getConector());
			MYSQL_ROW fila = mysql_fetch_row(res);
			if (fila && stoi(fila[0]) > 0) {
				existe = true;
			}
			mysql_free_result(res);
		}
		cn.cerrar_conexion();
		return existe;
	}

	// Validación: Verificar si el ID del estudiante existe (Para Modificar/Eliminar)
	bool idExiste(int id) {
		bool existe = false;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "SELECT COUNT(*) FROM estudiantes WHERE id_estudiantes = " + to_string(id) + ";";
			mysql_query(cn.getConector(), consulta.c_str());
			MYSQL_RES* res = mysql_store_result(cn.getConector());
			MYSQL_ROW fila = mysql_fetch_row(res);
			if (fila && stoi(fila[0]) > 0) {
				existe = true;
			}
			mysql_free_result(res);
		}
		cn.cerrar_conexion();
		return existe;
	}

	// Validación: Verificar si el tipo de sangre existe en la BD
	bool tipoSangreExiste(int id_ts) {
		bool existe = false;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "SELECT COUNT(*) FROM tipos_sangre WHERE id_tipos_sangre = " + to_string(id_ts) + ";";
			mysql_query(cn.getConector(), consulta.c_str());
			MYSQL_RES* res = mysql_store_result(cn.getConector());
			MYSQL_ROW fila = mysql_fetch_row(res);
			if (fila && stoi(fila[0]) > 0) {
				existe = true;
			}
			mysql_free_result(res);
		}
		cn.cerrar_conexion();
		return existe;
	}

	// Métodos CRUD con Seguridad Anti-Inyección SQL
	void crear() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			// Sanatización de cadenas de texto contra Inyección SQL
			string codEscapado = escaparString(cn.getConector(), codigo);
			string nomEscapado = escaparString(cn.getConector(), nombres);
			string apeEscapado = escaparString(cn.getConector(), apellidos);
			string dirEscapado = escaparString(cn.getConector(), direccion);
			string fnEscapado = escaparString(cn.getConector(), fecha_nacimiento);

			string consulta = "INSERT INTO estudiantes(codigo,nombres,apellidos,direccion,telefono,fecha_nacimiento,id_tipos_sangre) VALUES ('"
				+ codEscapado + "','" + nomEscapado + "','" + apeEscapado + "','" + dirEscapado + "',"
				+ to_string(telefono) + ",'" + fnEscapado + "'," + to_string(id_tipos_sangre) + ");";

			if (!mysql_query(cn.getConector(), consulta.c_str())) {
				cout << " xxx Ingreso Exitoso de Datos xxx" << endl;
			}
			else {
				cout << " xxx Error al guardar: " << mysql_error(cn.getConector()) << " xxx" << endl;
			}
		}
		else {
			cout << " xxx Fallo la Conexion xxx" << endl;
		}
		cn.cerrar_conexion();
	}

	void leer() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			cout << "\n------------ Datos del Estudiante ------------" << endl;
			string consulta = "SELECT e.id_estudiantes, e.codigo, e.nombres, e.apellidos, e.direccion, e.telefono, e.fecha_nacimiento, ts.sangre FROM estudiantes as e inner join tipos_sangre as ts on e.id_tipos_sangre = ts.id_tipos_sangre;";
			if (!mysql_query(cn.getConector(), consulta.c_str())) {
				MYSQL_RES* resultado = mysql_store_result(cn.getConector());
				MYSQL_ROW fila;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | " << fila[5] << " | " << fila[6] << " | " << fila[7] << endl;
				}
				mysql_free_result(resultado);
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
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string codEscapado = escaparString(cn.getConector(), codigo);
			string nomEscapado = escaparString(cn.getConector(), nombres);
			string apeEscapado = escaparString(cn.getConector(), apellidos);
			string dirEscapado = escaparString(cn.getConector(), direccion);
			string fnEscapado = escaparString(cn.getConector(), fecha_nacimiento);

			string consulta = "UPDATE estudiantes SET codigo = '" + codEscapado + "', nombres = '" + nomEscapado + "', apellidos = '" + apeEscapado + "', direccion = '" + dirEscapado + "', telefono = " + to_string(telefono) + ", fecha_nacimiento = '" + fnEscapado + "', id_tipos_sangre = " + to_string(id_tipos_sangre) + " WHERE id_estudiantes = " + to_string(id_estudiante) + ";";

			if (!mysql_query(cn.getConector(), consulta.c_str())) {
				cout << " xxx Modificacion de Datos Exitoso xxx" << endl;
			}
			else {
				cout << " xxx Error al actualizar: " << mysql_error(cn.getConector()) << " xxx" << endl;
			}
		}
		else {
			cout << " xxx Fallo la Conexion xxx" << endl;
		}
		cn.cerrar_conexion();
	}

	void borrar() {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string consulta = "DELETE FROM estudiantes WHERE id_estudiantes = " + to_string(id_estudiante) + ";";
			if (!mysql_query(cn.getConector(), consulta.c_str())) {
				cout << " xxx Eliminacion de Datos Exitoso xxx" << endl;
			}
			else {
				cout << " xxx Error al eliminar: " << mysql_error(cn.getConector()) << " xxx" << endl;
			}
		}
		else {
			cout << " xxx Fallo la Conexion xxx" << endl;
		}
		cn.cerrar_conexion();
	}
};
