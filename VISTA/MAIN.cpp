#include <iostream>
#include <string>
#include <regex>
#include "Estudiante.h"

using namespace std;

// --- FUNCIONES DE VALIDACIÓN POR CAMPO ---

string leerCodigo(Estudiante& e, int id_actual = 0) {
	string valor;
	regex formato("^E[0-9]{3}$"); // Formato E001, E002, etc. (Exactamente 4 caracteres)
	while (true) {
		cout << "Ingrese Codigo (Formato E001, max 4 caract.): ";
		getline(cin, valor);
		if (valor.empty()) {
			cout << ">> Error: El campo codigo es obligatorio.\n";
		}
		else if (valor.length() > 4 || !regex_match(valor, formato)) {
			cout << ">> Error: Debe seguir el formato exacto (E seguido de 3 numeros).\n";
		}
		else if (e.codigoExiste(valor, id_actual)) {
			cout << ">> Error: El codigo ingresado ya se encuentra registrado (Duplicado).\n";
		}
		else {
			return valor;
		}
	}
}

string leerTextoObligatorio(string nombreCampo, int max_longitud) {
	string valor;
	regex formato("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$"); // Solo letras y espacios
	while (true) {
		cout << "Ingrese " << nombreCampo << ": ";
		getline(cin, valor);
		if (valor.empty()) {
			cout << ">> Error: El campo " << nombreCampo << " es obligatorio.\n";
		}
		else if (valor.length() > max_longitud) {
			cout << ">> Error: Supera la longitud maxima de " << max_longitud << " caracteres.\n";
		}
		else if (!regex_match(valor, formato)) {
			cout << ">> Error: No se permiten numeros ni caracteres especiales.\n";
		}
		else {
			return valor;
		}
	}
}

string leerDireccion() {
	string valor;
	while (true) {
		cout << "Ingrese Direccion: ";
		getline(cin, valor);
		if (valor.empty()) {
			cout << ">> Error: La direccion no puede estar vacia.\n";
		}
		else if (valor.length() > 100) {
			cout << ">> Error: La direccion supera los 100 caracteres.\n";
		}
		else {
			return valor;
		}
	}
}

int leerTelefono() {
	string entrada;
	regex formato("^[0-9]{8}$"); // Exactamente 8 dígitos numéricos
	while (true) {
		cout << "Ingrese Telefono (8 digitos numéricos): ";
		getline(cin, entrada);
		if (entrada.empty()) {
			cout << ">> Error: El telefono es obligatorio.\n";
		}
		else if (!regex_match(entrada, formato)) {
			cout << ">> Error: Debe contener exactamente 8 numeros (sin letras ni espacios).\n";
		}
		else {
			return stoi(entrada);
		}
	}
}

string leerFechaNacimiento() {
	string valor;
	regex formato("^[0-9]{4}-[0-9]{2}-[0-9]{2}$"); // Formato AAAA-MM-DD
	while (true) {
		cout << "Ingrese Fecha Nacimiento (AAAA-MM-DD): ";
		getline(cin, valor);
		if (valor.empty()) {
			cout << ">> Error: La fecha de nacimiento es obligatoria.\n";
		}
		else if (!regex_match(valor, formato)) {
			cout << ">> Error: Formato invalido. Use estrictamente AAAA-MM-DD.\n";
		}
		else {
			// Validación básica de coherencia de fecha (Año no futuro razonable)
			int anio = stoi(valor.substr(0, 4));
			int mes = stoi(valor.substr(5, 2));
			int dia = stoi(valor.substr(8, 2));
			if (anio > 2026 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
				cout << ">> Error: Ingrese una fecha real y que no sea futura.\n";
			}
			else {
				return valor;
			}
		}
	}
}

int leerTipoSangre(Estudiante& e) {
	string entrada;
	while (true) {
		cout << "Ingrese ID Tipo Sangre: ";
		getline(cin, entrada);
		if (entrada.empty()) {
			cout << ">> Error: El tipo de sangre es obligatorio.\n";
		}
		else {
			try {
				int id_ts = stoi(entrada);
				if (e.tipoSangreExiste(id_ts)) {
					return id_ts;
				}
				else {
					cout << ">> Error: El ID tipo de sangre ingresado no existe en la tabla tipos_sangre.\n";
				}
			}
			catch (...) {
				cout << ">> Error: Ingrese un valor exclusivamente numerico.\n";
			}
		}
	}
}

// --- FUNCIÓN PRINCIPAL ---

int main() {
	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	int telefono = 0, id_tipos_sangre = 0, id_estudiante = 0;
	Estudiante e = Estudiante();

	// --- 1. INGRESO DE DATOS (CREATE) ---
	cout << "\n======= REGISTRO DE NUEVO ESTUDIANTE =======" << endl;
	codigo = leerCodigo(e); // Pasa validación de formato y duplicado
	nombres = leerTextoObligatorio("Nombres", 60);
	apellidos = leerTextoObligatorio("Apellidos", 60);
	direccion = leerDireccion();
	telefono = leerTelefono();
	fecha_nacimiento = leerFechaNacimiento();
	id_tipos_sangre = leerTipoSangre(e); // Valida que exista en la tabla relacional

	// Guardamos los datos validados
	e.setCodigo(codigo);
	e.setNombres(nombres);
	e.setApellidos(apellidos);
	e.setDireccion(direccion);
	e.setTelefono(telefono);
	e.setFecha_nacimiento(fecha_nacimiento);
	e.setId_tipos_sangre(id_tipos_sangre);

	e.crear();
	e.leer();

	// --- 2. ACTUALIZACION DE DATOS (UPDATE) ---
	cout << "\n======= MODIFICAR ESTUDIANTE =======" << endl;
	while (true) {
		cout << "Ingrese el ID a modificar: ";
		string entradaId;
		getline(cin, entradaId);
		try {
			id_estudiante = stoi(entradaId);
			if (e.idExiste(id_estudiante)) {
				break;
			}
			else {
				cout << ">> Error: El ID del estudiante no existe en el sistema.\n";
			}
		}
		catch (...) {
			cout << ">> Error: Ingrese un numero valido.\n";
		}
	}

	// Al actualizar pasamos el 'id_estudiante' actual para permitir conservar su propio código original si no cambia
	codigo = leerCodigo(e, id_estudiante);
	nombres = leerTextoObligatorio("Nombres", 60);
	apellidos = leerTextoObligatorio("Apellidos", 60);
	direccion = leerDireccion();
	telefono = leerTelefono();
	fecha_nacimiento = leerFechaNacimiento();
	id_tipos_sangre = leerTipoSangre(e);

	e.setId_estudiante(id_estudiante);
	e.setCodigo(codigo);
	e.setNombres(nombres);
	e.setApellidos(apellidos);
	e.setDireccion(direccion);
	e.setTelefono(telefono);
	e.setFecha_nacimiento(fecha_nacimiento);
	e.setId_tipos_sangre(id_tipos_sangre);

	e.actualizar();
	e.leer();

	// --- 3. ELIMINACION DE DATOS (DELETE) ---
	cout << "\n======= ELIMINAR ESTUDIANTE =======" << endl;
	while (true) {
		cout << "Ingrese el ID a eliminar: ";
		string entradaId;
		getline(cin, entradaId);
		try {
			id_estudiante = stoi(entradaId);
			if (e.idExiste(id_estudiante)) {
				break;
			}
			else {
				cout << ">> Error: El ID del estudiante no existe.\n";
			}
		}
		catch (...) {
			cout << ">> Error: Ingrese un numero valido.\n";
		}
	}

	e.setId_estudiante(id_estudiante);
	e.borrar();
	e.leer();

	return 0;
}
