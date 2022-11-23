#include <iostream>
//include fstream for file oprations
#include <fstream>
#include <string>

using namespace std;

typedef struct Pacientes {

	unsigned int dni;
	string nombre;
	string apellido;
	char sexo;
	string natalicio;
	string estado;
	string id_os;
	//Contactos contacto;//tendria que tener 2? uno de emergencia y otra dle mismo paciente
	//Consultas consulta;//consulta asociada, lee la del paciente

}Pacientes;

typedef struct Medicos {

	string matricula;
	string nombre;
	string apellido;
	string telefono;
	string especialidad;
	bool activo;
} Medicos;

typedef struct Consultas {

	string dni_pac;
	string fecha_solicitado;
	string fecha_turno;
	bool presento;
	string matricula_med;
	Medicos medico_consulta;

} Consultas;

typedef struct Contactos {

	string dni_pac;
	string telefono;
	string celular;
	string direccion;
	string mail;

} Contactos;


void agregar_pacientes(Pacientes*& lista_pac, Pacientes paciente, int* tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	Pacientes* aux = new Pacientes[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista_pac[i];
		i++;
	}
	aux[i] = paciente;

	delete[] lista_pac;
	lista_pac = aux;

	return;
}

void agregar_medicos(Medicos*& lista_med, Medicos medico, int* tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	Medicos* aux = new Medicos[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista_med[i];
		i++;
	}
	aux[i] = medico;

	delete[] lista_med;
	lista_med = aux;

	return;
}

void agregar_consultas(Consultas*& lista_cons, Consultas consulta, int* tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	Consultas* aux = new Consultas[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista_cons[i];
		i++;
	}
	aux[i] = consulta;

	delete[] lista_cons;
	lista_cons = aux;

	return;
}

void agregar_contactos(Contactos*& lista_cont, Contactos contacto, int* tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	Contactos* aux = new Contactos[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista_cont[i];
		i++;
	}
	aux[i] = contacto;

	delete[] lista_cont;
	lista_cont = aux;

	return;
}


Pacientes* read_archivo_pacientes(string a1, int* contador) {
	Pacientes* l_pac = new Pacientes[0];
	Pacientes aux;
	fstream fr;
	string dummy;
	char coma;
	int tamact = 0;

	fr.open(a1, ios::in);
	//fr.open(a1, ios::in | ios::app);
	if (!fr.is_open())
		cout << "Error al leer archivo";
	else {
		fr >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy;
		while (fr) {
			fr >> aux.dni >> coma >> aux.apellido >> coma >> aux.nombre >> coma >> aux.sexo >> coma >> aux.natalicio >> coma >> aux.estado >> coma >> aux.id_os;
			//cout << aux.nombre << '\n';
			agregar_pacientes(l_pac, aux, &tamact);
			*contador=*contador+1;
		}


	}


	return l_pac;
}
 
Medicos* read_archivo_medicos(string a1, int* contador) {
	Medicos* l_med = new Medicos[0];
	Medicos aux;
	fstream fr;
	string dummy;
	char coma;
	int tamact = 0;

	fr.open(a1, ios::in);
	//fr.open(a1, ios::in | ios::app);
	if (!fr.is_open())
		cout << "Error al leer archivo";
	else {
		fr >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy;
		while (fr) {
			fr >> aux.matricula >> coma >> aux.nombre >> coma >> aux.apellido >> coma >> aux.telefono >> coma >> aux.especialidad >> coma >> aux.activo;
			//cout << aux.nombre << '\n';
			agregar_medicos(l_med, aux, &tamact);
			*contador = *contador + 1;
		}

	}


	return l_med;
}

Consultas* read_archivo_consultas(string a1, int* contador2) {
	Consultas* l_cons = new Consultas[0];
	Consultas aux;
	fstream fr;
	string dummy;
	char coma;
	int tamact = 0;

	fr.open(a1, ios::in);
	//fr.open(a1, ios::in | ios::app);
	if (!fr.is_open())
		cout << "Error al leer archivo";
	else {
		fr >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy;
		while (fr) {
			//dni_pac , fecha_solicitado , fecha_turno , presento , matricula_med
			
			//cout << aux.nombre << '\n';
			agregar_consultas(l_cons, aux, &tamact);
			*contador2 = *contador2 + 1;
		}

	}


	return l_cons;
}

Contactos* read_archivo_contactos(string a1, int* contador4) {
	Contactos* l_cont = new Contactos[0];
	Contactos aux;
	fstream fr;
	string dummy;
	char coma;
	int tamact = 0;

	fr.open(a1, ios::in);
	//fr.open(a1, ios::in | ios::app);
	if (!fr.is_open())
		cout << "Error al leer archivo";
	else {
		fr >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy;
		while (fr) {
			fr >> aux.dni_pac >> coma >> aux.telefono >> coma >> aux.celular >> coma >> aux.direccion >> coma >> aux.mail;
			//cout << aux.nombre << '\n';
			agregar_contactos(l_cont, aux, &tamact);
			*contador4 = *contador4 + 1;
		}


	}


	return l_cont;
}

void crear_archivo(string nombre_a1, string nombre_a2) {
	fstream archi, archi2;

	archi.open(nombre_a1, ios::out);
	archi2.open(nombre_a2, ios::out);

	if (archi.is_open() && archi2.is_open()) {
		archi << "dni , nota1 , nota2" << endl;
		archi << 1000 << " , " << 8 << " , " << 7 << endl;
		archi << 10932 << " , " << 6 << " , " << 8 << endl;
		archi2 << "dni , apellido , nombre" << endl;
		archi2 << 10932 << " , Maradona , Diego" << endl;
		archi2 << 1000 << " , Messi , Lionel" << endl;
	}

	archi.close();
	archi2.close();

	return;
}


int main()
{
    fstream file; //object of fstream class

    //open file "test.txt" in out(write) mode
    // ios::out Open for output operations.
    file.open("test.txt", ios::out);
	
	int contador = 0; 
	int* p = &contador;
	int contador2 = 0;
	int contador3 = 0;
	int contador4 = 0;

	Pacientes* lista;
	lista=read_archivo_pacientes("Pacientes.csv", &contador);//con & transformo la variable en un puntero

	Consultas* lista1;
	lista1 = read_archivo_consultas("Consultas.csv", &contador2);

	Medicos* lista2;
	lista2 = read_archivo_medicos("Medicos.csv", &contador3);

	Contactos* lista3;
	lista3 = read_archivo_contactos("Contactos.csv", &contador4);

	for (int i = 0; i < contador; i++) {
		cout << lista[i].dni << "," << lista[i].nombre << "," << lista[i].apellido << "," << lista[i].sexo << "," << lista[i].natalicio << "," << lista[i].estado << "," << lista[i].id_os << endl;
	}

	for (int i = 0; i < contador2; i++) {
		cout << lista1[i].dni_pac << "," << lista1[i].fecha_solicitado << "," << lista1[i].fecha_turno << "," << lista1[i].presento << "," << lista1[i].matricula_med << endl;
	}

	for (int i = 0; i < contador3; i++) {
		cout << lista2[i].matricula << "," << lista2[i].nombre << "," << lista2[i].apellido << "," << lista2[i].telefono << "," << lista2[i].especialidad << "," << lista2[i].activo  << endl;
	}

	for (int i = 0; i < contador4; i++) {
		cout << lista3[i].dni_pac << "," << lista3[i].telefono << "," << lista3[i].celular << "," << lista3[i].direccion << "," << lista3[i].mail << endl;
	}
    //If file is not created, return error
    if (!file) {
        cout << "Error in file creation!";
        return 0;
    }
    else { //File is created
        cout << "File Creation successfull.";
    }
    //closing the file
    file.close();
}