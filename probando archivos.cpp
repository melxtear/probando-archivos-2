#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//include fstream for file oprations
#include <fstream>
#include <string>
#include <ctime>
#include <time.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <iomanip>
using namespace std;

enum class eObras_Sociales { Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA};

string Obras_SocialesToString(eObras_Sociales obras) {

	switch (obras) {
	case eObras_Sociales::Medicus:
		return "Medicus";
		break;
	case eObras_Sociales::OSDE:
		return "OSDE";
		break;
	case eObras_Sociales::Italiano:
		return "Italiano";
		break;
	case eObras_Sociales::Espanyol:
		return "Espanyol";
		break;
	case eObras_Sociales::Aleman:
		return "Aleman";
		break;
	case eObras_Sociales::IOSFA:
		return "IOSFA";
		break;
	}

}

typedef struct Medicos {

	string matricula;
	string nombre;
	string apellido;
	string telefono;
	string especialidad;
	bool activo;

} Medicos;

typedef struct Consultas {

	int dni_pac;
	string fecha_solicitado;
	string fecha_turno;
	bool presento;
	string matricula_med;

} Consultas;

typedef struct Contactos {

	int dni_pac;
	string telefono;
	string celular;
	string direccion;
	string mail;

} Contactos;

typedef struct Pacientes {

	unsigned int dni;
	string nombre;
	string apellido;
	char sexo;
	string natalicio;
	string estado;
	string id_os;
	string archivado;
	//Contactos contacto;//tendria que tener 2? uno de emergencia y otra dle mismo paciente
	//Consultas consulta;//consulta asociada, lee la del paciente

}Pacientes;

/*void resize(Consultas*& lista_cons, int* tamactual, int cantidad_aumentar) {
	*tamactual = *tamactual + cantidad_aumentar;
	int i = 0;
	Consultas* aux = new Consultas[*tamactual];
	while (i < *tamactual - cantidad_aumentar) {
		aux[i] = lista_cons[i];
		i++;
	}

	delete[] lista_cons;
	lista_cons = aux;

	return;
}*/

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

	if (lista_cons == NULL) {
		lista_cons = new Consultas[*tamactual];
	}
	cout << lista_cons << endl;
	cout << "Tamanio actual: " << * tamactual << endl;
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

void agregar_consultas_extra(Consultas consulta, string a1, int* contador) {
	fstream archi;

	archi.open(a1, ios::app); //

	if (archi.is_open()) {
		//dni_pac , fecha_solicitado , fecha_turno , presento , matricula_med
		archi << consulta.dni_pac << " , " << consulta.fecha_solicitado << " , " << consulta.fecha_turno << " , " << consulta.presento << " , " << consulta.matricula_med << endl;
		*contador = *contador + 1;
	}
	else
		cout << "Archivo no encontrado. " << endl;
	archi.close();
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
			fr >> aux.dni_pac >> coma >> aux.fecha_solicitado >> coma >> aux.fecha_turno >> coma >> aux.presento >> coma >> aux.matricula_med;
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
			fr >> aux.dni_pac >> coma >> aux.telefono >> coma >> aux.celular >> coma;
			getline(fr, aux.direccion, ',');
			fr >> aux.mail;
			//cout << aux.nombre << '\n';
			agregar_contactos(l_cont, aux, &tamact);
			*contador4 = *contador4 + 1;
		}


	}


	return l_cont;
}

//no funca
void crear_archivo_consultas_nuevas(string nombre_a1, Consultas*& lista_consultas_nuevas, int* tamactual) {
	fstream archi;

	archi.open(nombre_a1, ios::out);
	//archi2.open(nombre_a2, ios::out);
	int i = 0;

	//&& archi2.is_open()
	if (archi.is_open()) {
		//dni_pac , fecha_solicitado , fecha_turno , presento , matricula_med
		archi << "dni_pac , fecha_solicitado , fecha_turno , presento , matricula_med" << endl;
		while (i < *tamactual) {
			//dni , nombre , apellido , sexo , natalicio , estado , obra_social

			archi << lista_consultas_nuevas[i].dni_pac << " , " << lista_consultas_nuevas[i].fecha_solicitado << " , " << lista_consultas_nuevas[i].fecha_turno << " , " << lista_consultas_nuevas[i].presento << " , " << lista_consultas_nuevas[i].matricula_med << "\n";
			//archi << 10932 << " , " << 6 << " , " << 8 << endl;
			//archi2 << "dni , apellido , nombre" << endl;
			//archi2 << 10932 << " , Maradona , Diego" << endl;
			//archi2 << 1000 << " , Messi , Lionel" << endl;
			i++;
		}

	}

	archi.close();
	//archi2.close();

	return;
}

Consultas* read_archivo_nuevas_consultas(string a1) {
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
			fr >> aux.dni_pac >> coma >> aux.fecha_solicitado >> coma >> aux.fecha_turno >> coma >> aux.presento >> coma >> aux.matricula_med;
			//cout << aux.nombre << '\n';
			agregar_consultas(l_cons, aux, &tamact);

		}


	}


	return l_cons;
}

void agregar_pacientes_archivados(Pacientes*& lista_pac, Pacientes paciente, int* tamactual) {
	*tamactual = *tamactual + 1;
	int i = 0;
	Pacientes* aux = new Pacientes[*tamactual];
	while (i < *tamactual - 1 && *tamactual - 1 != 0) {
		aux[i] = lista_pac[i];
		i++;
	}
	aux[i] = paciente;

	if (&lista_pac[0] != NULL) {
		delete[] lista_pac;
	}
	
	lista_pac = aux;

	return;
}

bool crear_archivo_pacientes_archivados(string nombre_a1, Pacientes*& lista_pac_archivados, int* tamactual) {
	fstream archi, archi2;

	archi.open(nombre_a1, ios::out);
	//archi2.open(nombre_a2, ios::out);
	int i = 0;

	//&& archi2.is_open()
	if (archi.is_open()) {
		archi << "dni , nombre , apellido , sexo , natalicio , estado , obra_social" << endl;
		while (i < *tamactual) {
			//dni , nombre , apellido , sexo , natalicio , estado , obra_social

			archi << lista_pac_archivados[i].dni << " , " << lista_pac_archivados[i].nombre << " , " << lista_pac_archivados[i].apellido << " , " << lista_pac_archivados[i].sexo << " , " << lista_pac_archivados[i].natalicio << " , " << lista_pac_archivados[i].estado << " , " << lista_pac_archivados[i].id_os << "\n";
			//archi << 10932 << " , " << 6 << " , " << 8 << endl;
			//archi2 << "dni , apellido , nombre" << endl;
			//archi2 << 10932 << " , Maradona , Diego" << endl;
			//archi2 << 1000 << " , Messi , Lionel" << endl;
			i++;
		}
		cout << "Se creo con exito el archivo." << endl;
		return true;
	}
	else
		return false;

	archi.close();
	//archi2.close();


}

//viendo ahora
void crear_archivo_lista_pacientes_nueva(string nombre_a1, Pacientes*& lista_pac, int* tamactual) {
	fstream archi, archi2;

	archi.open(nombre_a1, ios::out);
	//archi2.open(nombre_a2, ios::out);
	int i = 0;

	//&& archi2.is_open()
	if (archi.is_open()) {
		archi << "dni , nombre , apellido , sexo , natalicio , estado , obra_social, archivado" << endl;
		while (i < *tamactual) {
			//dni , nombre , apellido , sexo , natalicio , estado , obra_social

			archi << lista_pac[i].dni << " , " << lista_pac[i].nombre << " , " << lista_pac[i].apellido << " , " << lista_pac[i].sexo << " , " << lista_pac[i].natalicio << " , " << lista_pac[i].estado << " , " << lista_pac[i].id_os << " , "<< lista_pac[i].archivado << "\n";
			//archi << 10932 << " , " << 6 << " , " << 8 << endl;
			//archi2 << "dni , apellido , nombre" << endl;
			//archi2 << 10932 << " , Maradona , Diego" << endl;
			//archi2 << 1000 << " , Messi , Lionel" << endl;
			i++;
		}

	}

	archi.close();
	//archi2.close();

	return;
}

//ver si hace falta usar
Pacientes* archivar_pacientes(Pacientes*& lista_pac_a_archivar, int* contador5, Pacientes pac_a_archivar, bool archivar_si) {
	Pacientes* l_pac = new Pacientes[0];
	int tamactual = 0;
	for (int i = 0; i <= 100; i++) {
		if (lista_pac_a_archivar[i].estado == "fallecido" && pac_a_archivar.dni==lista_pac_a_archivar[i].dni) {
			agregar_pacientes_archivados(l_pac, lista_pac_a_archivar[i], &tamactual);
		}
		else if (archivar_si == true && pac_a_archivar.dni == lista_pac_a_archivar[i].dni) {
			agregar_pacientes_archivados(l_pac, lista_pac_a_archivar[i], &tamactual);
		}
	}
	*contador5 = tamactual;
	return l_pac;
}
 
Pacientes* read_archivo_pacientes_archivados(string a1) {
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
			
		}


	}


	return l_pac;
}

//ya visto, funciona
Pacientes* read_archivo_lista_pacientes_nueva(string a1) {
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
		fr >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy >> coma >> dummy;
		while (fr) {
			fr >> aux.dni >> coma >> aux.apellido >> coma >> aux.nombre >> coma >> aux.sexo >> coma >> aux.natalicio >> coma >> aux.estado >> coma >> aux.id_os >> coma >> aux.archivado;
			//cout << aux.nombre << '\n';
			agregar_pacientes(l_pac, aux, &tamact);
		}


	}


	return l_pac;
}

//fue la primer idea para pasar de string a int, retornaba la fecha como int (ver si puede llegar a servir)
int string_a_int(string fecha) {
	int i = 0;
	int n = 0;
	//char cadena[strlen(pac.natalicio)] = pac.natalicio;
	//string aux = consulta.fecha_solicitado;
	string aux = fecha;
	int aux1 = fecha.length();

	char* cadena=new char[aux1];

	while(i<aux1) {
		if (aux[i] != '\0') {
			cadena[i] = aux[i];
		}
		i++;
	}

	for (int indice = 0; indice < strlen(cadena); indice++)
	{
		char actual = cadena[indice];
		if (actual != '\0') {
			if (actual != '/') {
				if (actual == '1' || actual == '2' || actual == '3' || actual == '4' || actual == '5' || actual == '6' || actual == '7' || actual == '8' || actual == '9' || actual == '0') {
					n = 10 * n + (actual - '0');
				}
				
			}
		}
		
		//printf("Tenemos el caracter '%c'\n", actual);
	}
	
	return n;
	//int aux = 0;
	//for (int i = 0; i < 3; i++) {
		//aux = stoi(paciente.natalicio);
	//}
	//return aux;
} 

/*void toInt(string cadena) {

	time_t curr_time;
	//char* tm = ctime(&curr_time);
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	curr_time = time(NULL);
	int i = 0;
	int j = 0;
	//int dia,mes,anio;
	string dia, mes, anio = "";
	while (i < cadena.length()) {
		char aux = cadena[i];
		if (aux != '/') {
			if (j == 0)
				dia = dia + aux;
			if (j == 1)
				mes = mes + aux;
			if (j == 2)
				anio = anio + aux;
		}
		else {
			j++;
		}
		i++;


	}
	now->tm_mday = dia;
	now->tm_mon = mes;
	now->tm_year = anio;

	cout << "dia : " << now->tm_mday << endl;
	cout << "mes : " << now->tm_mon << endl;
	cout << "anio : " << now->tm_year << endl;



}*/

//convierte un string de fecha en una fecha ctime
tm* toInt(string cadena) {
	time_t t = time(0);   // get time now
	//tm* ltm = localtime(&t);;
	tm* ltm = (tm*)malloc(sizeof(tm));

	int i = 0;
	int j = 0;
	//int dia,mes,anio;
	string dia, mes, anio = "";
	while (i < cadena.length()) {
		char aux = cadena[i];
		if (aux != '/') {
			if (j == 0)
				dia = dia + aux;
			if (j == 1)
				mes = mes + aux;
			if (j == 2)
				anio = anio + aux;
		}
		else {
			j++;
		}
		i++;


	}
	ltm->tm_year = stoi(anio);
	ltm->tm_mday = stoi(dia);
	ltm->tm_mon = stoi(mes);
	//cout << "dia : " << ltm->tm_mday << endl;
	//cout << "mes : " << ltm->tm_mon << endl;
	//cout << "anio : " << ltm->tm_year << endl;

	return ltm;

}

/*Contactos* filtrar_lista_por_dni_contactos(Contactos* lista_contactos, Pacientes pac, int* tamactual, int* tam) {
	Contactos* l_cont = new Contactos[0];
	int tamact = 0;

	for (int i = 0; i < *tamactual; i++) {
		if (pac.dni == lista_contactos[i].dni_pac) {
			agregar_contactos(l_cont, lista_contactos[i], &tamact);
			*tam = *tam + 1;
		}
	}
	return l_cont;

}*/

Consultas* filtrar_lista_por_dni(Consultas* lista_consultas, Pacientes pac, int* tamactual, int* tam) {
	Consultas* l_cons = new Consultas[0];
	int tamact = 0;

	for (int i = 0; i < *tamactual; i++) {
		if (pac.dni == lista_consultas[i].dni_pac) {
			agregar_consultas(l_cons, lista_consultas[i], &tamact);
			*tam = *tam + 1;
		}
	}
	return l_cons;

}

//retorna fecha ctime de ultima consulta
tm* Encontrar_Consulta_Fecha(Consultas* lista_consultas_filtradas, int* tamactual) {
	Consultas* l_cons = new Consultas[*tamactual];
	tm* aux1=0;
	tm* aux2=0;

	//l_cons = filtrar_lista_por_dni(lista_consultas, pac, tamactual);

	aux1 = toInt(lista_consultas_filtradas[0].fecha_turno);

	for (int i = 0; i < *tamactual; i++) {

          aux2 = toInt(lista_consultas_filtradas[i].fecha_turno);
		  //aux1.año=1980 aux1.mes= 7 aux1.dia=20
		  //aux2.año=1982 aux2.mes=8  aux1.dia=24

		  if (aux1->tm_year < aux2->tm_year)
			  aux1 = aux2;
		  else if (aux1->tm_year < aux2->tm_year && aux1->tm_mon < aux2->tm_mon) 
			  aux1 = aux2;
		  else if (aux1->tm_year < aux2->tm_year && aux1->tm_mon < aux2->tm_mon && aux1->tm_mday < aux2->tm_mday)
			  aux1 = aux2;
	}

	return aux1;
}

//retorna struct de ultima consulta
Consultas encontrar_ultima_consulta(Consultas* lista_consultas_filtradas, int* tamactual) {
	Consultas aux;
	tm* aux1;
	tm* aux2;

	aux1 = toInt(lista_consultas_filtradas[0].fecha_turno);

	for (int i = 0; i < *tamactual; i++) {

		aux2 = toInt(lista_consultas_filtradas[i].fecha_turno);
		//aux1.año=1980 aux1.mes= 7 aux1.dia=20
		//aux2.año=1982 aux2.mes=8  aux1.dia=24

		if (aux1->tm_year < aux2->tm_year) {
			aux1 = aux2;
			aux = lista_consultas_filtradas[i];
		}
		else if (aux1->tm_year < aux2->tm_year && aux1->tm_mon < aux2->tm_mon) {
			aux1 = aux2;
			aux = lista_consultas_filtradas[i];
		}
		else if (aux1->tm_year < aux2->tm_year && aux1->tm_mon < aux2->tm_mon && aux1->tm_mday < aux2->tm_mday) {
			aux1 = aux2;
			aux = lista_consultas_filtradas[i];
		}
	}

	return aux;

}

Medicos* Buscar_Medico_Viejo(Medicos* Lista_Medicos, Consultas* lista_consultas, int* contador6, int*tam) {

	Consultas ultima_consulta = encontrar_ultima_consulta(lista_consultas, contador6);
	Medicos* aux=NULL;

	for (int i = 0; i < *tam; i++) {
		if (ultima_consulta.matricula_med == Lista_Medicos[i].matricula && Lista_Medicos[i].activo == true) { //chequeamos solo si encuentra ==matricula, hay que ver del boolean agenda_llena
			//si encuentra al medico que lo habia atendido antes y este se encuentra disponible, misma especialidad???
			aux = &Lista_Medicos[i]; //encontramos al medico
			return aux;
		}
	}
	return aux;//retornamos el struct del medico, significa que se puede asignar turno con el medico 
}

Medicos* Buscar_Medico_Nuevo(Medicos* Lista_Medicos, Consultas* lista_consultas, int* contador6, int* tam) {

	Consultas ultima_consulta = encontrar_ultima_consulta(lista_consultas, contador6);
	Medicos* aux = NULL;

	Medicos* medico_ultima_consulta = Buscar_Medico_Viejo(Lista_Medicos, lista_consultas, contador6, tam);
	for (int i = 0; i < *tam; i++) {
		int respuesta_agenda_llena = rand() % 2;
		if (medico_ultima_consulta != NULL) {
			if (ultima_consulta.matricula_med != Lista_Medicos[i].matricula && Lista_Medicos[i].activo == true && medico_ultima_consulta->especialidad == Lista_Medicos[i].especialidad) { //chequeamos solo si encuentra ==matricula, hay que ver del boolean agenda_llena
				//si encuentra al medico que lo habia atendido antes y este se encuentra disponible, misma especialidad???
				aux = &Lista_Medicos[i]; //encontramos al medico
				return aux;
			}
		}
		else
			if (ultima_consulta.matricula_med != Lista_Medicos[i].matricula && Lista_Medicos[i].activo == true && respuesta_agenda_llena==0) { //chequeamos solo si encuentra ==matricula, hay que ver del boolean agenda_llena
				//si encuentra al medico que lo habia atendido antes y este se encuentra disponible, misma especialidad???
				aux = &Lista_Medicos[i]; //encontramos al medico
				return aux;
			}

	}
	return aux;//retornamos el struct del medico, significa que se puede asignar turno con el medico 
}

Pacientes* Buscar_Pacientes_Archivados(Pacientes* lista_pac, Pacientes pac_archivado_a_buscar, int* tam) {

	Pacientes* aux = NULL;
	for (int i = 0; i < *tam; i++) {
		if (lista_pac[i].dni == pac_archivado_a_buscar.dni) {
			aux = &lista_pac[i];
			return aux;
		}
			
	}
	return aux;
}
//Consultas* lista_consultas_filtradas, int* tamactual

int Verificar_Anio_Ultima_Consulta(tm* fecha_ultima_consulta) {
	
	//time_t curr_time;
	//curr_time = time(NULL);

	//char* tm = ctime(&curr_time);
	//cout << "Today is : " << tm;
	
	//auto now = chrono::system_clock::now();
	//auto time = chrono::system_clock::to_time_t(now);

	//cout << put_time(localtime(&time), "%Y");

	/*time_t p = time(0);   // get time now
	tm* now = localtime(&p);
	cout << now->tm_mday << ", " << now->tm_mon << ", " << now->tm_year << endl;*/

	char s[100];
	int rc;
	time_t temp;
	struct tm* timeptr;

	temp = time(NULL);
	timeptr = localtime(&temp);

	//"Today is %A, %b %d %Y.\nTime:  %r"
	rc = strftime(s, sizeof(s), "%d/%m/%Y", timeptr);
	//printf("%d characters written.\n%s\n", rc, s);
	//cout << "Separacion: " << endl;
	//cout << s << endl;
	//tm* now2 = localtime(&t);
	//int aux1 = string_a_int(s);
	tm* aux2 = toInt(s);

	//cout << aux1 << endl;
	//cout << aux2->tm_mday << ", " << aux2->tm_mon << ", " << aux2->tm_year << endl;

	time_t t = time(0);
	tm* nuevo= localtime(&t);
	nuevo->tm_year = (aux2->tm_year) - (fecha_ultima_consulta->tm_year);

	//cout << "Diferencia de años: " << nuevo->tm_year << endl;

	if (nuevo->tm_year < 10 && nuevo->tm_year>0) {
		return 1;
		//ok, la diferencia de año es menor a 10 o sea es un paciente recuperable, podemos llamar
	}
	else if (nuevo->tm_year == 10) { //la diferencia de año es 10, está al limite
		if (fecha_ultima_consulta->tm_mon > aux2->tm_mon) { //vemos si el mes de la ultima consulta es mayor
			return 1;
			//ok, el mes de la consulta es mayor, ej 11/2022-12/2012, significa que todavia no llegaron a ser 10 años 
			//justos de su ultima consulta, por eso es un paciente recuperable, podemos llamarlo
		}
		else if (fecha_ultima_consulta->tm_mon == aux2->tm_mon) { //el mes es igua, está al limit
			if (fecha_ultima_consulta->tm_mday >= aux2->tm_mday) {
				return 1;
				//todavia no se cumplieron los 10 años o se cumplieron los 10 años justo ese dia
				//pero es un paciente recuperable, podemos llamarlo
			}
			else//el dia de la ultima consulta es mas chico, se supero el limite
				return 0;
			//ya se cumplieron los 10 años, es un paciente irrecuperable, procedemos a archivarlo

		}
		else if (fecha_ultima_consulta->tm_mon < aux2->tm_mon) {////el mes de ultima consulta es mas chico, supero limite
			//ya se cumplieron los 10 años, es un paciente irrecuperable, procedemos a archivarlo
			return 0;
		}
	}
	else if (nuevo->tm_year > 10)//la diferencia de años es mayor a los 10, se supero el limite
		return 0;//ya se cumplieron los 10 años, es un paciente irrecuperable, procedemos a archivarlo
	else if (nuevo->tm_year < 0)
		return 2;
	else if (nuevo->tm_year == 0) {
		if (fecha_ultima_consulta->tm_mon > aux2->tm_mon)
			return 2;
		else if (fecha_ultima_consulta->tm_mon == aux2->tm_mon) {
			if (fecha_ultima_consulta->tm_mday >= aux2->tm_mday) {
				return 2;
				//todavia no se cumplieron los 10 años o se cumplieron los 10 años justo ese dia
				//pero es un paciente recuperable, podemos llamarlo
			}
			else//el dia de la ultima consulta es mas chico, se supero el limite
				return 1;
		}
		else if (fecha_ultima_consulta->tm_mon < aux2->tm_mon)
			return 1;
	}
		

	//cout << "dia : " << ltm->tm_mday << endl;
	//cout << "mes : " << ltm->tm_mon << endl;
	//cout << "anio : " << ltm->tm_year << endl;

}

string Verificar_Datos_Paciente(Pacientes paciente_datos_verificar) {


	if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Medicus)) {
		int respuesta2 = rand() % 5 + 1;
		//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
		if (respuesta2 == 1) {
			cout << "El paciente se cambio a Osde, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::OSDE;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}
		else if (respuesta2 == 2) {
			cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Italiano;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}
		else if (respuesta2 == 3) {
			cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Espanyol;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}
		if (respuesta2 == 4) {
			cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Aleman;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}
		if (respuesta2 == 5) {
			cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::IOSFA;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}

	}
	else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::OSDE)) {
		int respuesta2 = rand() % 5 + 1;

		//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
		if (respuesta2 == 1) {
			cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Medicus;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 2) {
			cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Italiano;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 3) {
			cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Espanyol;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}
		if (respuesta2 == 4) {
			cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Aleman;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}
		if (respuesta2 == 5) {
			cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::IOSFA;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);

		}

	}
	else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Italiano)) {
		int respuesta2 = rand() % 5 + 1;

		//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
		if (respuesta2 == 1) {
			cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Medicus;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 2) {
			cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::OSDE;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 3) {
			cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Espanyol;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 4) {
			cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Aleman;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 5) {
			cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::IOSFA;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}

	}
	else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Espanyol)) {
		int respuesta2 = rand() % 5 + 1;

		//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
		if (respuesta2 == 1) {
			cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Medicus;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 2) {
			cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Italiano;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 3) {
			cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::OSDE;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 4) {
			cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Aleman;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 5) {
			cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::IOSFA;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}

	}
	else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Aleman)) {
		int respuesta2 = rand() % 5 + 1;

		//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
		if (respuesta2 == 1) {
			cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Medicus;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 2) {
			cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Italiano;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 3) {
			cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Espanyol;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 4) {
			cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::OSDE;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 5) {
			cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::IOSFA;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}

	}
	else {
		//if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::IOSFA)) 
		int respuesta2 = rand() % 5 + 1;

		//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
		if (respuesta2 == 1) {
			cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Medicus;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 2) {
			cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Italiano;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		else if (respuesta2 == 3) {
			cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Espanyol;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 4) {
			cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::Aleman;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}
		if (respuesta2 == 5) {
			cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
			eObras_Sociales nuevo = eObras_Sociales::OSDE;
			paciente_datos_verificar.id_os = Obras_SocialesToString(nuevo);
		}

	}

	return paciente_datos_verificar.id_os;
}

tm* fecha_nuevo_turno_random() {
	time_t t = time(0);   // get time now
	//tm* ltm = localtime(&t);;
	tm* ltm = (tm*)malloc(sizeof(tm));

	ltm->tm_year = 2023;
	ltm->tm_mon = rand() % 11+1;
	ltm->tm_mday = 0;

	//auto t = time(nullptr);
	//auto tm = *localtime(&t);

	//ostringstream oss;
	//cout << put_time(&tm, "%d-%m-%Y %H-%M-%S");
	//auto str = oss.str();

	if (ltm->tm_mon == 4 || ltm->tm_mon == 6 || ltm->tm_mon == 9 || ltm->tm_mon == 11)
		ltm->tm_mday = rand() % 30 + 1; //abril, junio, septiembre y noviembre
	else if (ltm->tm_mon == 1 || ltm->tm_mon == 3 || ltm->tm_mon == 5 || ltm->tm_mon == 7 || ltm->tm_mon == 8 || ltm->tm_mon == 10 || ltm->tm_mon == 12)
		ltm->tm_mday = rand() % 31 + 1; //enero, marzo, mayo, julio, agosto, octubre y diciembre
	else if (ltm->tm_mon==2)//febrero
		ltm->tm_mday = rand() % 28 + 1;

	int A = (14 - ltm->tm_mon) / 12;
	int Y = ltm->tm_year - A;
	int M = ltm->tm_mon + (12 * A) - 2;
	int diaSemana;

	if (ltm->tm_year >= 1582)       /// Inicio del calendario Gregoriano
		diaSemana = (ltm->tm_mday + Y + Y / 4 - Y / 100 + Y / 400 + (31 * M) / 12) % 7;

	else        /// calendario Juliano
		diaSemana = (5 + ltm->tm_mday + Y + Y / 4 + (31 * M) / 12) % 7;

	if (diaSemana > 0)
		diaSemana--;
	else
		diaSemana = 6;

	ltm->tm_wday = diaSemana;
	/*cout << "La fecha de su nuevo turno es: " << endl;
	cout << dia_semana << endl;
	cout << "Dia: " << ltm->tm_mday << endl;
	cout << "Mes: " << ltm->tm_mon << endl;
	cout << "Anio: " << ltm->tm_year << endl;*/
	return ltm;
}

//ver si sirve
string convertir_dia_a_string_dia(tm* ltm) {

	string dia_semana;

	switch (ltm->tm_wday) {

	case 0: dia_semana = "Lunes"; break;
	case 1: dia_semana = "Martes"; break;
	case 2: dia_semana = "Miercoles"; break;
	case 3: dia_semana = "Jueves"; break;
	case 4: dia_semana = "Viernes"; break;
	case 5: dia_semana = "Sabado"; break;
	case 6: dia_semana = "Domingo"; break;
	}

	return dia_semana;

}

//nueva, funciona
void Agregar_Archivado(Pacientes* lista_pac_antigua, Pacientes* lista_archivados, int* tam_ant, int* tam_arch) {
	
	for (int i = 0; i < *tam_ant; i++) {
		Pacientes* paciente_encontrado = Buscar_Pacientes_Archivados(lista_archivados, lista_pac_antigua[i], tam_arch);
		
		if (paciente_encontrado != NULL) { //lo encontro en la lista de archivados
			lista_pac_antigua[i].archivado = "Archivado";
		}
		else { //no lo encontro en la lista de archivados
			lista_pac_antigua[i].archivado = "No_Archivado";
		}
	}
}

//nueva
Medicos* Asignar_Medico(Medicos* Lista_Medicos, Consultas* lista_cons, int* contador6, int* contador3) {

	Medicos* medico_nueva_consulta=NULL;
	Medicos* medico_nueva_consulta_nuevo=NULL;

	cout << "Desea un turno con el medico de su ultima consulta?" << endl;
	int respuesta1 = rand() % 2;
	if (respuesta1 == 1) {
		medico_nueva_consulta = Buscar_Medico_Viejo(Lista_Medicos, lista_cons, contador6, contador3);

		if (medico_nueva_consulta != NULL) {
			cout << "Encontramos al medico de su ultima consulta, sus datos son: " << endl;
			cout << "Matricula: " << medico_nueva_consulta->matricula << " Apellido: " << medico_nueva_consulta->apellido << " Nombre: " << medico_nueva_consulta->nombre << " Especialidad: " << medico_nueva_consulta->especialidad << endl;
			return medico_nueva_consulta;// se asignó con exito
		}
		else {
			cout << "No se ha encontrado al medico de su ultima consulta en el hospital." << endl;
			cout << "Desea buscar otro medico? " << endl;

			int respuesta2 = rand() % 2;

			if (respuesta2 == 1) {
				cout << "Ha decidido buscar otro medico: " << endl;
				medico_nueva_consulta_nuevo = Buscar_Medico_Nuevo(Lista_Medicos, lista_cons, contador6, contador3);

				if (medico_nueva_consulta_nuevo != NULL) {
					cout << "Encontramos un nuevo medico, sus datos son: " << endl;
					cout << "Matricula: " << medico_nueva_consulta_nuevo->matricula << " Apellido: " << medico_nueva_consulta_nuevo->apellido << " Nombre: " << medico_nueva_consulta_nuevo->nombre << " Especialidad: " << medico_nueva_consulta_nuevo->especialidad << endl;
					return medico_nueva_consulta_nuevo;
				}
				else {
					cout << "No se ha encontrado un medico nuevo disponible. Archivamos al paciente." << endl;
					return medico_nueva_consulta_nuevo; 
				}
					
			}
			else {
				cout << "El paciente ha decidido no buscar otro medico. Archivamos al paciente." << endl;
				return medico_nueva_consulta;
			}
				
		}
	}
	else {
		cout << "Ha decidido no asignar turno con su ultimo medico, procedemos a buscar un nuevo. " << endl;

		medico_nueva_consulta_nuevo = Buscar_Medico_Nuevo(Lista_Medicos, lista_cons, contador6, contador3);

		if (medico_nueva_consulta_nuevo != NULL) {
			cout << "Encontramos un nuevo medico, sus datos son: " << endl;
			cout << "Matricula: " << medico_nueva_consulta_nuevo->matricula << " Apellido: " << medico_nueva_consulta_nuevo->apellido << " Nombre: " << medico_nueva_consulta_nuevo->nombre << " Especialidad: " << medico_nueva_consulta_nuevo->especialidad << endl;
			return medico_nueva_consulta_nuevo;
		}
		else {
			cout << "No se ha encontrado al medico nuevo. Archivamos al paciente." << endl;
			return medico_nueva_consulta_nuevo;
		}
			
	}
}

bool cambio_obra_social() {
	int respuesta1 = rand() % 2;

	cout << "El paciente ha cambiado sus datos de obra social? " << endl;
	if (respuesta1 == 1) {
		cout << "El paciente ha cambiado de obra social, preguntamos por cual y modificamos sus datos en el archivo. " << endl;
		return true;
	}
	else {
		cout << "El paciente no se cambio de obra social." << endl;
		return false;
	}


}
//nueva, revisar porque asi corre bien pero no me deja agregar datos de nueva consulta a lista, se rompe
//se rompe con el tema de la funcion toint, recibe vacio a partir del paciente 3, creo arrastra basura
//ver el tema de 2023, sino lo pongo fijo imprime 3000 y pico, lo del mes creo que es 0 a 11 y 0 es enero, etc

string fecha_de_hoy() {
	time_t curr_time;
	tm* curr_tm;
	char date_string1[100];
	

	time(&curr_time);
	curr_tm = localtime(&curr_time);

	strftime(date_string1, 50, "%d/%m/%Y", curr_tm);
	return date_string1;
}

string fecha_turno(tm* fecha_turno) {
	time_t curr_time2;
	tm* curr_tm2;
	time(&curr_time2);
	curr_tm2 = localtime(&curr_time2);

	char date_string2[100];

	curr_tm2->tm_year = 2023;
	curr_tm2->tm_mon = fecha_turno->tm_mon;
	curr_tm2->tm_mday = fecha_turno->tm_mday;

	strftime(date_string2, 50, "%d/%m/2023", curr_tm2); //ver
	return date_string2;
}

Contactos* buscar_contacto_emergencia(Contactos* lista_contactos, int* tam_contactos, Pacientes pac_a_llamar, Contactos* contacto_pac) {
	Contactos* contacto_aux1 = NULL;
	for (int i = 0; i < *tam_contactos; i++) {
		if (lista_contactos[i].dni_pac == pac_a_llamar.dni && lista_contactos[i].telefono != contacto_pac->telefono) {
			contacto_aux1 = &lista_contactos[i];
			return contacto_aux1;
		}
	}
	return contacto_aux1;
}


/*Contactos* buscar_contacto_emergencia(Contactos* lista_contactos, int* tam_contactos, Pacientes pac_a_llamar, Contactos contacto_pac) {

	Contactos* contacto_aux = NULL;
	for (int i = 0, i < tam_contactos; i++) {
		if (lista_contactos[i].dni_pac == pac_a_llamar.dni && lista_contactos[i].telefono != contacto_pac.telefono) {
			contacto_aux = &lista_contactos[i];
			return contacto_aux;
		}
	};
	return contacto_aux;
}*/
Contactos* buscar_contacto_pac(Contactos* lista_contactos, int* tam_contactos, Pacientes pac_a_llamar) {
	Contactos* contacto_aux = NULL;

	for (int i = 0; i < *tam_contactos; i++) {
		if (lista_contactos[i].dni_pac == pac_a_llamar.dni) {
			contacto_aux = &lista_contactos[i];
			return contacto_aux;
		}
	}
	return contacto_aux;
}
/*Contactos* buscar_contactos(Contactos* lista_contactos, int* tam_contactos, Pacientes pac_a_llamar) {

	Contactos* contacto_aux = NULL;
	for (int l = 0, l < tam_contactos; l++) {
		if (lista_contactos[l].dni_pac == pac_a_llamar.dni) {
			contacto_aux = &lista_contactos[l];
			return contacto_aux;
		}
	}
	return contacto_aux;
}*/
//ver si funca y si la necesitamos
void fecha_de_hoy_y_nuevo_turno(Consultas consulta_nueva, tm* fecha_nuevo_turno) {
	time_t curr_time;
	tm* curr_tm;
	char date_string1[100];
	char date_string2[100];

	time(&curr_time);
	curr_tm = localtime(&curr_time);

	strftime(date_string1, 50, "%d/%m/%Y", curr_tm);
	consulta_nueva.fecha_solicitado = date_string1;

	time_t curr_time2;
	tm* curr_tm2;
	time(&curr_time2);
	curr_tm2 = localtime(&curr_time2);

	curr_tm2->tm_year = 2023;
	curr_tm2->tm_mon = fecha_nuevo_turno->tm_mon;
	curr_tm2->tm_mday = fecha_nuevo_turno->tm_mday;

	strftime(date_string2, 50, "%d/%m/2023", curr_tm2);//ver
	consulta_nueva.fecha_turno = date_string2;
}


/*
void Secretaria(Pacientes* lista_pac, Consultas* lista_consultas, Contactos* lista_contactos, Medicos* lista_medicos, int* tam_pacientes, int* tam_consultas, int* tam_contactos, int* tam_medicos) {

	int tam_lista_filtrada_consultas = 0;
	Consultas* lista_cons;
	Medicos* medico_nueva_consulta;
	Medicos* medico_nueva_consulta_nuevo;
	Consultas nueva_consulta;
	Contactos* contacto_paciente_a_llamar=NULL;
	Contactos* contacto_paciente_a_llamar_emergencia=NULL;
	tm* fecha_nuevo_turno;

	Consultas* nueva_lista_auxiliar_consultas=NULL;
	int tam_lista_consultas_auxiliar;

	int tam_lista_archivados = 0;
	Pacientes* lista_pac_archivados=NULL;
	for (int i = 0; i < *tam_pacientes - 1; i++) { //recorre lista pacientes-1
		cout << "Paciente nro: " << i + 1 << endl;
		cout << "Dni: " << lista_pac[i].dni << ", " << "Nombre: " << lista_pac[i].nombre << ", " << "Apellido: " << lista_pac[i].apellido << ", "
			<< "Sexo: " << lista_pac[i].sexo << ", " << "Fecha de nacimiento: " << lista_pac[i].natalicio << ", " << "Estado paciente: " << lista_pac[i].estado
			<< ", " << "Obra social: " << lista_pac[i].id_os << endl;
		//int aux2 = string_a_int(lista[i]);
		//cout << "Es: " << aux2 << endl;

		lista_cons = filtrar_lista_por_dni(lista_consultas, lista_pac[i], tam_consultas, &tam_lista_filtrada_consultas);
		for (int j = 0; j < tam_lista_filtrada_consultas; j++) {
			cout << "Dni: " << lista_cons[j].dni_pac << endl;
			cout << "Fecha solicitado del turno: " << lista_cons[j].fecha_solicitado << endl;
			cout << "Fecha del turno: " << lista_cons[j].fecha_turno << endl;
			cout << "Matricula del medico: " << lista_cons[j].matricula_med << endl;
			if (lista_cons[j].presento == true) {
				cout << "Presento:" << "Se presento al ultimo turno." << endl;
			}
			else
				cout <<"Presento:" << "No se presento al ultimo turno." << endl;
					
				
			
			tm* aux8;
			aux8 = toInt(lista_cons[j].fecha_solicitado);
			//cout << "Dia: " << aux8->tm_mday << " Mes: " << aux8->tm_mon << " Anio: " << aux8->tm_year << endl;
		}
		tm* aux3 = Encontrar_Consulta_Fecha(lista_cons, &tam_lista_filtrada_consultas);
		cout << "La consulta mas actual es: " << aux3->tm_mday << ", " << aux3->tm_mon << ", " << aux3->tm_year << endl;
		Consultas aux_ult_consulta = encontrar_ultima_consulta(lista_cons, &tam_lista_filtrada_consultas);

		int verificacion = Verificar_Anio_Ultima_Consulta(aux3);
		//ultima_consulta = encontrar_ultima_consulta(lista_cons, &tam_lista_filtrada);

		if (verificacion==1 && aux_ult_consulta.presento==false) { //paciente relativamente nuevo
			cout << "Paciente recuperable, procedemos a buscar algun contacto telefonico y llamar. " << endl;

			contacto_paciente_a_llamar = buscar_contacto_pac(lista_contactos, tam_contactos, lista_pac[i]);

			if (contacto_paciente_a_llamar != NULL) {
				cout << "Encontramos contacto del paciente, los datos son los siguientes: " << endl;

				cout << "Dni del paciente: " << contacto_paciente_a_llamar->dni_pac << ", " << "Telefono: " << contacto_paciente_a_llamar->telefono << ", "
					<< "Celular: " << contacto_paciente_a_llamar->celular << ", " << "Direccion: " << contacto_paciente_a_llamar->direccion
					<< ", " << "E-Mail: " << contacto_paciente_a_llamar->mail << endl;

				cout << "Llamando al paciente.." << endl;

				int respuesta_llamado_paciente = rand() % 2;

				if (respuesta_llamado_paciente) {
					cout << "El paciente ha respondido al llamado. Procedemos a consultar sobre la posibilidad de tener un nuevo turno en nuestro centro medico" << endl;

					int respuesta_pac_nuevo_turno = rand() % 2;

					if (respuesta_pac_nuevo_turno) {
						cout << "El paciente quiere un nuevo turno en nuestro centro medico." << endl;
						medico_nueva_consulta = Asignar_Medico(lista_medicos, lista_cons, &tam_lista_filtrada_consultas, tam_medicos);

						if (medico_nueva_consulta != NULL) {
							cout << "Ya asignamos con exito al medico de su proxima consulta, procedemos a dar una fecha del turno. " << endl;
							fecha_nuevo_turno = fecha_nuevo_turno_random();

							nueva_consulta.dni_pac = lista_pac[i].dni;
							time_t curr_time;
							tm* curr_tm;
							char date_string1[100];
							char date_string2[100];

							time(&curr_time);
							curr_tm = localtime(&curr_time);

							strftime(date_string1, 50, "%d/%m/%Y", curr_tm);
							nueva_consulta.fecha_solicitado = date_string1;

							time_t curr_time2;
							tm* curr_tm2;
							time(&curr_time2);
							curr_tm2 = localtime(&curr_time2);

							curr_tm2->tm_year = 2023;
							curr_tm2->tm_mon = fecha_nuevo_turno->tm_mon;
							curr_tm2->tm_mday = fecha_nuevo_turno->tm_mday;

							strftime(date_string2, 50, "%d/%m/2023", curr_tm2); //ver
							nueva_consulta.fecha_turno = date_string2;
							nueva_consulta.matricula_med = medico_nueva_consulta->matricula;
							nueva_consulta.presento = false;

							cout << "Datos de la nueva consulta: " << endl;
							cout << "DNI del paciente: " << nueva_consulta.dni_pac << endl;
							cout << "Fecha en la cual se solicito el turno: " << nueva_consulta.fecha_solicitado << endl;
							cout << "Fecha del turno: " << nueva_consulta.fecha_turno << endl;
							cout << "Matricula del medico del proximo turno: " << nueva_consulta.matricula_med << endl;
							cout << "Se presento el paciente?: " << nueva_consulta.presento << endl;
							string nueva_obra=Verificar_Datos_Paciente(lista_pac[i]);
							cout << "Obra social nueva: " << nueva_obra << endl;
						

						}
						//else
							//cout << "Hubo problemas para asignar un medico con disponibilidad, volveremos a llamar al paciente en unos dias. " << endl;
					}
					else {
						cout << "El paciente no está interesado en obtener un nuevo turno en nuestro centro medico, archivamos su historial. " << endl;
						agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
						//aca habria que llamar a la funcion de archivar
					}

				}
				else {
					cout << "El paciente no ha respondido al llamado, procedemos a llamar a su contacto de emergencia con el fin de dar con el paciente. " << endl;
					contacto_paciente_a_llamar_emergencia = buscar_contacto_emergencia(lista_contactos, tam_contactos, lista_pac[i], contacto_paciente_a_llamar);

					if (contacto_paciente_a_llamar_emergencia != NULL) {
						cout << "Encontramos al contacto de emergencia, sus datos son: " << endl;

						cout << "Dni del paciente: " << contacto_paciente_a_llamar_emergencia->dni_pac << ", " << "Telefono del contacto: " << contacto_paciente_a_llamar_emergencia->telefono << ", "
							<< "Celular del contacto: " << contacto_paciente_a_llamar->celular << ", " << "Direccion del contacto: " << contacto_paciente_a_llamar->direccion
							<< ", " << "E-Mail del contacto: " << contacto_paciente_a_llamar->mail << endl;

						cout << "Llamando al contacto de emergencia.. " << endl;

						int respuesta_contacto_emergencia = rand() % 2;
						if (respuesta_contacto_emergencia) {
							cout << "El contacto ha respondido al llamado, procedemos a consultar sobre como se encuentra el paciente y porque no atendio, con el fin de asignar un nuevo turno" << endl;

							int respuesta_estado_pac = rand() % 3;//0 esta vivo, no atendio porque estaba ocupado, procedemos a llamarlo y ya directo asignar turnp
							//1 fallecio, procedemos a archivar y modificar su estado a fallecido
							//2 internado, procedemos a dejar en standby y llamar cuando se encuentre mejor, modificamos estado

							if (respuesta_estado_pac == 0) {
								cout << "El paciente se encuentra bien, procedemos a llamarlo y ver la posibilidad de que agende un nuevo turno. " << endl;
								int respuesta_pac_nuevo_turno2 = rand() % 2;

								if (respuesta_pac_nuevo_turno2) {
									cout << "El paciente quiere un nuevo turno en nuestro centro medico." << endl;
									medico_nueva_consulta = Asignar_Medico(lista_medicos, lista_cons, &tam_lista_filtrada_consultas, tam_medicos);

									if (medico_nueva_consulta != NULL) {
										cout << "Ya asignamos con exito al medico de su proxima consulta, procedemos a dar una fecha del turno. " << endl;
										fecha_nuevo_turno = fecha_nuevo_turno_random();

										nueva_consulta.dni_pac = lista_pac[i].dni;
										time_t curr_time;
										tm* curr_tm;
										char date_string1[100];
										char date_string2[100];

										time(&curr_time);
										curr_tm = localtime(&curr_time);

										strftime(date_string1, 50, "%d/%m/%Y", curr_tm);
										nueva_consulta.fecha_solicitado = date_string1;

										time_t curr_time2;
										tm* curr_tm2;
										time(&curr_time2);
										curr_tm2 = localtime(&curr_time2);

										curr_tm2->tm_year = 2023;
										curr_tm2->tm_mon = fecha_nuevo_turno->tm_mon;
										curr_tm2->tm_mday = fecha_nuevo_turno->tm_mday;

										strftime(date_string2, 50, "%d/%m/2023", curr_tm2);//ver
										nueva_consulta.fecha_turno = date_string2;

										nueva_consulta.matricula_med = medico_nueva_consulta->matricula;
										nueva_consulta.presento = false;

										cout << "Datos de la nueva consulta: " << endl;
										cout << "DNI del paciente: " << nueva_consulta.dni_pac << endl;
										cout << "Fecha en la cual se solicito el turno: " << nueva_consulta.fecha_solicitado << endl;
										cout << "Fecha del turno: " << nueva_consulta.fecha_turno << endl;
										cout << "Matricula del medico del proximo turno: " << nueva_consulta.matricula_med << endl;
										cout << "Se presento el paciente?: " << nueva_consulta.presento << endl;
										//guardamos la info en la lista de consultas
										//VER
										Verificar_Datos_Paciente(lista_pac[i]);
										//agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, &tam_lista_consultas_auxiliar);
										cout << "Obra social nueva: " << lista_pac[i].id_os << endl;
									}
									//else
									//	cout << "Hubo problemas para asignar un medico con disponibilidad, volveremos a llamar al paciente en unos dias. " << endl;
								}
								else {
									cout << "El paciente no está interesado en obtener un nuevo turno en nuestro centro medico, archivamos su historial. " << endl;
									agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
									//aca habria que llamar a la funcion de archivar
								}
							}
							else if (respuesta_estado_pac == 1) {
								lista_pac[i].estado = "fallecido";
								cout << "El paciente ha fallecido, archivamos su historial." << endl;
								agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
								//funcion de archivar

							}
							else {
								cout << "El contacto nos informa que el paciente se encuentra internado, modificamos el archivo y procedemos a llamar mas adelante" << endl;
								lista_pac[i].estado = "internado";
							}

						}
						else {
							cout << "El contacto de emergencia no ha respondido al llamado. Enviamos un email a ambos contactos con el fin de recibir respuesta, de igual forma en unos dias llamamos al paciente otra vez. " << endl;
							//dejamos en standby
							cout << "Enviando email al paciente,  su correo es:" << contacto_paciente_a_llamar->mail << endl;
							cout << "Enviando email al contacto de emergencia, su correo es: " << contacto_paciente_a_llamar_emergencia->mail << endl;
						}
					}
					else {
						cout << "No se encontró un contacto de emergencia, procedemos a enviar un email al paciente e intentar llamar en unos dias otra vez. " << endl;
						cout << "Enviando email al paciente,  su correo es:" << contacto_paciente_a_llamar->mail << endl;
						//dejamos en standby

					}
				}

			}
			else
				cout << "Ha ocurrido un error y no se ha podido encontrar información de contacto del paciente. " << endl;
		}
		else if(verificacion==0) {
			cout << "El paciente se atendio hace mas de 10 años, es un paciente irrecuperable. Archivamos su historial. " << endl;
			agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
			//archivamos
		}
		else if(verificacion==2)
			cout << "El paciente ya tiene un turno proximo. No hace falta llamar." << endl;
		else if (lista_pac[i].estado == "fallecido") {
			cout << "El paciente se encuentra fallecido, archivamos su historial. " << endl;
			agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
			//archivamos
		}
		else if (lista_pac[i].estado == "internado") {
			cout << "El paciente se encuentra internado en nuestro centro medico, llamamos mas adelante. " << endl;
		}
		else if (aux_ult_consulta.presento == true) {
			cout << "El paciente se presento a su ultimo turno, el cual fue hace menos de 10 años. No hace falta llamarlo." << endl;
		}


		//Asignar_Turno(lista[i], verificacion, lista2, lista1, &contador2, &contador3);

		tam_lista_filtrada_consultas = 0;

		//int aux3 = Encontrar_Consulta(lista_cons, lista[i], &contador6);
		//cout << "La consulta mas actual es: " << aux3 << endl;
		//contador6 = 0;
	}
	

	//crear_archivo_consultas_nuevas("Consultas_Nuevas.csv", nueva_lista_auxiliar_consultas, &tam_lista_consultas_auxiliar);

	//Consultas* lista_aux_cons = NULL;
	//lista_aux_cons = read_archivo_nuevas_consultas("Consultas_Nuevas.csv");
	//cout << "Leyendo nuevas consultas. " << endl;
	//for (int i = 0; i < tam_lista_consultas_auxiliar-1; i++) {
		//cout << "Dni paciente: " << lista_aux_cons[i].dni_pac << endl;
		//cout << "Fecha en la cual se solicito el nuevo turno: " << lista_aux_cons[i].fecha_solicitado << endl;
		//cout << "Fecha del turno: " << lista_aux_cons[i].fecha_turno << endl;
		//cout << "Matricula del medico: " << lista_aux_cons[i].matricula_med << endl;
		//cout << "Presento: " << lista_aux_cons[i].presento << endl;
	//}

	crear_archivo_pacientes_archivados("Pacientes_Archivados.csv", lista_pac_archivados, &tam_lista_archivados);

	Pacientes* lista_archivados;
	lista_archivados = read_archivo_pacientes_archivados("Pacientes_Archivados.csv");

	cout << "Leyendo pacientes archivados:" << endl;
	for (int i = 0; i < tam_lista_archivados; i++) {
		cout << lista_archivados[i].dni << "," << lista_archivados[i].nombre << "," << lista_archivados[i].apellido << "," << lista_archivados[i].sexo << "," << lista_archivados[i].natalicio << "," << lista_archivados[i].estado << "," << lista_archivados[i].id_os << endl;
	}

	Agregar_Archivado(lista_pac, lista_archivados, tam_pacientes, &tam_lista_archivados);

	crear_archivo_lista_pacientes_nueva("Pacientes_Nueva_Lista.csv", lista_pac, tam_pacientes);

	Pacientes* lista_nueva_pac1;
	lista_nueva_pac1 = read_archivo_lista_pacientes_nueva("Pacientes_Nueva_Lista.csv");

	cout << "Imprimiendo nueva lista con columna de archivado. " << endl;
	for (int i = 0; i < *tam_pacientes - 1; i++) {
		cout << lista_nueva_pac1[i].dni << "," << lista_nueva_pac1[i].nombre << "," << lista_nueva_pac1[i].apellido << " , " << lista_nueva_pac1[i].sexo << " , " << lista_nueva_pac1[i].natalicio << " , " << lista_nueva_pac1[i].estado << " , " << lista_nueva_pac1[i].id_os << " , " << lista_nueva_pac1[i].archivado << endl;
	}
}
*/


Pacientes* filtrar_lista_verificacion(Pacientes*& lista_pac, Consultas* lista_consultas, Pacientes*& lista_pac_archivados, int* tam_pac_archivados, int* tam_pacientes, int* tam_consultas, int* tam_nueva_lista) {
	Pacientes* lista_aux=NULL;
	Consultas* lista_cons_filtradas = NULL;
	int tam_lista_filtrada_consultas = 0;
	int verificacion = 0;

	for (int i = 0; i < *tam_pacientes - 1; i++) {

		lista_cons_filtradas = filtrar_lista_por_dni(lista_consultas, lista_pac[i], tam_consultas, &tam_lista_filtrada_consultas);
		tm* aux3 = Encontrar_Consulta_Fecha(lista_cons_filtradas, &tam_lista_filtrada_consultas);
		//cout << "La consulta mas actual es: " << aux3->tm_mday << ", " << aux3->tm_mon << ", " << aux3->tm_year << endl;
		Consultas aux_ult_consulta = encontrar_ultima_consulta(lista_cons_filtradas, &tam_lista_filtrada_consultas);

		verificacion = Verificar_Anio_Ultima_Consulta(aux3);

		if (verificacion == 0) {
			cout << "El paciente " << lista_pac[i].dni << " se atendio hace mas de 10 años, es un paciente irrecuperable.Archivamos su historial. " << endl;
			agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], tam_pac_archivados);
		}
		else if (verificacion == 1) {
			//cumple el tema de que es menor a los 10 años
			agregar_pacientes(lista_aux, lista_pac[i], tam_nueva_lista);
			/*cout << "Imprimiendo consultas del paciente" << endl;
			for(int j = 0; j < tam_lista_filtrada_consultas; j++) {
				cout << "Dni: " << lista_cons[j].dni_pac << endl;
				cout << "Fecha solicitado del turno: " << lista_cons[j].fecha_solicitado << endl;
				cout << "Fecha del turno: " << lista_cons[j].fecha_turno << endl;
				cout << "Matricula del medico: " << lista_cons[j].matricula_med << endl;
				if (lista_cons[j].presento == true) {
					cout << "Presento:" << "Se presento al ultimo turno." << endl;
				}
				else
					cout << "Presento:" << "No se presento al ultimo turno." << endl;

				//tm* aux8;
				//aux8 = toInt(lista_cons[j].fecha_solicitado);
				//cout << "Dia: " << aux8->tm_mday << " Mes: " << aux8->tm_mon << " Anio: " << aux8->tm_year << endl;
			}	*/
		}
		else if (verificacion == 2) {
			cout << "El paciente ya tiene un turno proximo. No hace falta llamar." << endl;
		}
		tam_lista_filtrada_consultas = 0;
	}

	return lista_aux;
}

Pacientes* filtrar_lista_archivados(Pacientes* lista_pac, Consultas* lista_consultas, Pacientes* lista_pac_archivados, int* tam_pac_archivados, int* tam_pacientes, int* tam_consultas, int* tam_nueva_lista) {
	Pacientes* lista_aux = NULL;
	Consultas* lista_cons_filtradas = NULL;
	int tam_lista_filtrada_consultas = 0;
	int verificacion = 0;

	for (int i = 0; i < *tam_pacientes - 1; i++) {

		lista_cons_filtradas = filtrar_lista_por_dni(lista_consultas, lista_pac[i], tam_consultas, &tam_lista_filtrada_consultas);
		tm* aux3 = Encontrar_Consulta_Fecha(lista_cons_filtradas, &tam_lista_filtrada_consultas);
		//cout << "La consulta mas actual es: " << aux3->tm_mday << ", " << aux3->tm_mon << ", " << aux3->tm_year << endl;
		Consultas aux_ult_consulta = encontrar_ultima_consulta(lista_cons_filtradas, &tam_lista_filtrada_consultas);

		verificacion = Verificar_Anio_Ultima_Consulta(aux3);

		if (verificacion == 0) {
			//cout << "El paciente " << lista_pac[i].dni << " se atendio hace mas de 10 años, es un paciente irrecuperable.Archivamos su historial. " << endl;
			agregar_pacientes_archivados(lista_aux, lista_pac[i], tam_pac_archivados);
		}
		tam_lista_filtrada_consultas = 0;
	}
	return lista_aux;

}

void Imprimir_Datos_Consulta(Consultas nueva_consulta, Pacientes lista_pac) {
	if (cambio_obra_social() == true) {
		string nueva_obra = Verificar_Datos_Paciente(lista_pac);
		cout << "Datos de la nueva consulta: " << endl;
		cout << "DNI del paciente: " << nueva_consulta.dni_pac << endl;
		cout << "Fecha en la cual se solicito el turno: " << nueva_consulta.fecha_solicitado << endl;
		cout << "Fecha del turno: " << nueva_consulta.fecha_turno << endl;
		cout << "Matricula del medico del proximo turno: " << nueva_consulta.matricula_med << endl;
		cout << "Se presento el paciente?: " << nueva_consulta.presento << endl;
		cout << "Obra social nueva: " << nueva_obra << endl;
		//agregar_consultas_extra(nueva_consulta, "Consultas.csv", tam_consultas);
		//agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, &tam_lista_consultas_auxiliar);
	}
	else {
		cout << "Datos de la nueva consulta: " << endl;
		cout << "DNI del paciente: " << nueva_consulta.dni_pac << endl;
		cout << "Fecha en la cual se solicito el turno: " << nueva_consulta.fecha_solicitado << endl;
		cout << "Fecha del turno: " << nueva_consulta.fecha_turno << endl;
		cout << "Matricula del medico del proximo turno: " << nueva_consulta.matricula_med << endl;
		cout << "Se presento el paciente?: " << nueva_consulta.presento << endl;
		cout << "Obra social:" << lista_pac.id_os << endl;
		//agregar_consultas_extra(nueva_consulta, "Consultas.csv", tam_consultas);
		//agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, &tam_lista_consultas_auxiliar);
	}
}



void Imprimir_Resto(Consultas*& nueva_lista_auxiliar_consultas, Medicos* lista_medicos, Consultas* lista_cons, int *tam_lista_filtrada_consultas, Contactos* lista_contactos, int* tam_contactos, Pacientes lista_pac, int* tam_lista_consultas_auxiliar, int* tam_medicos, Pacientes*& lista_pac_archivados, int *tam_lista_archivados) {

	//int tam_lista_filtrada_consultas = 0;
	//Consultas* lista_cons;
	Medicos* medico_nueva_consulta;
	Medicos* medico_nueva_consulta_nuevo;
	Consultas nueva_consulta;
	Contactos* contacto_paciente_a_llamar = NULL;
	Contactos* contacto_paciente_a_llamar_emergencia = NULL;
	tm* fecha_nuevo_turno;

	//Consultas* nueva_lista_auxiliar_consultas = NULL;
	//int tam_lista_archivados = 0;

	//Pacientes* lista_pac_archivados = NULL;
	//tm* aux3 = Encontrar_Consulta_Fecha(lista_cons, tam_lista_filtrada_consultas);
	//cout << "La consulta mas actual es: " << aux3->tm_mday << ", " << aux3->tm_mon << ", " << aux3->tm_year << endl;
	Consultas aux_ult_consulta;
	aux_ult_consulta=encontrar_ultima_consulta(lista_cons, tam_lista_filtrada_consultas);

	//int verificacion = Verificar_Anio_Ultima_Consulta(aux3);
	//ultima_consulta = encontrar_ultima_consulta(lista_cons, &tam_lista_filtrada);

		if (aux_ult_consulta.presento == false) { //paciente relativamente nuevo
			cout << "Paciente recuperable, procedemos a buscar algun contacto telefonico y llamar. " << endl;

			contacto_paciente_a_llamar = buscar_contacto_pac(lista_contactos, tam_contactos, lista_pac);

			if (contacto_paciente_a_llamar != NULL) {
				cout << "Encontramos contacto del paciente, los datos son los siguientes: " << endl;

				cout << "Dni del paciente: " << contacto_paciente_a_llamar->dni_pac << ", " << "Telefono: " << contacto_paciente_a_llamar->telefono << ", "
					<< "Celular: " << contacto_paciente_a_llamar->celular << ", " << "Direccion: " << contacto_paciente_a_llamar->direccion
					<< ", " << "E-Mail: " << contacto_paciente_a_llamar->mail << endl;

				cout << "Llamando al paciente.." << endl;

				int respuesta_llamado_paciente = rand() % 2;

				if (respuesta_llamado_paciente) {
					cout << "El paciente ha respondido al llamado. Procedemos a consultar sobre la posibilidad de tener un nuevo turno en nuestro centro medico" << endl;

					int respuesta_pac_nuevo_turno = rand() % 2;

					if (respuesta_pac_nuevo_turno) {
						cout << "El paciente quiere un nuevo turno en nuestro centro medico." << endl;
						medico_nueva_consulta = Asignar_Medico(lista_medicos, lista_cons, tam_lista_filtrada_consultas, tam_medicos);

						if (medico_nueva_consulta != NULL) {
							cout << "Ya asignamos con exito al medico de su proxima consulta, procedemos a dar una fecha del turno. " << endl;
							fecha_nuevo_turno = fecha_nuevo_turno_random();
							string aux_fecha_turno = fecha_turno(fecha_nuevo_turno);
							nueva_consulta.fecha_turno = aux_fecha_turno;

							string aux_fecha_de_hoy = fecha_de_hoy();
							nueva_consulta.fecha_solicitado = aux_fecha_de_hoy;

							nueva_consulta.matricula_med = medico_nueva_consulta->matricula;
							nueva_consulta.presento = false;
							nueva_consulta.dni_pac = lista_pac.dni;

							Imprimir_Datos_Consulta(nueva_consulta, lista_pac);

							agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, tam_lista_consultas_auxiliar);
							//agregar_consultas_extra(nueva_consulta, "Consultas.csv", tam_consultas);
							//agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, &tam_lista_consultas_auxiliar);
						}
						//else
							//cout << "Hubo problemas para asignar un medico con disponibilidad, volveremos a llamar al paciente en unos dias. " << endl;
					}
					else {
						cout << "El paciente no está interesado en obtener un nuevo turno en nuestro centro medico, archivamos su historial. " << endl;
						agregar_pacientes_archivados(lista_pac_archivados, lista_pac, tam_lista_archivados);
						//aca habria que llamar a la funcion de archivar
					}

				}
				else {
					cout << "El paciente no ha respondido al llamado, procedemos a llamar a su contacto de emergencia con el fin de dar con el paciente. " << endl;
					contacto_paciente_a_llamar_emergencia = buscar_contacto_emergencia(lista_contactos, tam_contactos, lista_pac, contacto_paciente_a_llamar);

					if (contacto_paciente_a_llamar_emergencia != NULL) {
						cout << "Encontramos al contacto de emergencia, sus datos son: " << endl;

						cout << "Dni del paciente: " << contacto_paciente_a_llamar_emergencia->dni_pac << ", " << "Telefono del contacto: " << contacto_paciente_a_llamar_emergencia->telefono << ", "
							<< "Celular del contacto: " << contacto_paciente_a_llamar->celular << ", " << "Direccion del contacto: " << contacto_paciente_a_llamar->direccion
							<< ", " << "E-Mail del contacto: " << contacto_paciente_a_llamar->mail << endl;

						cout << "Llamando al contacto de emergencia.. " << endl;

						int respuesta_contacto_emergencia = rand() % 2;
						if (respuesta_contacto_emergencia) {
							cout << "El contacto ha respondido al llamado, procedemos a consultar sobre como se encuentra el paciente y porque no atendio, con el fin de asignar un nuevo turno" << endl;

							int respuesta_estado_pac = rand() % 3;//0 esta vivo, no atendio porque estaba ocupado, procedemos a llamarlo y ya directo asignar turnp
							//1 fallecio, procedemos a archivar y modificar su estado a fallecido
							//2 internado, procedemos a dejar en standby y llamar cuando se encuentre mejor, modificamos estado

							if (respuesta_estado_pac == 0) {
								cout << "El paciente se encuentra bien, procedemos a llamarlo y ver la posibilidad de que agende un nuevo turno. " << endl;
								int respuesta_pac_nuevo_turno2 = rand() % 2;

								if (respuesta_pac_nuevo_turno2) {
									cout << "El paciente quiere un nuevo turno en nuestro centro medico." << endl;
									medico_nueva_consulta = Asignar_Medico(lista_medicos, lista_cons, tam_lista_filtrada_consultas, tam_medicos);

									if (medico_nueva_consulta != NULL) {
										cout << "Ya asignamos con exito al medico de su proxima consulta, procedemos a dar una fecha del turno. " << endl;
										/*fecha_nuevo_turno = fecha_nuevo_turno_random();
										nueva_consulta.dni_pac = lista_pac[i].dni;
										string aux_fecha_de_hoy = fecha_de_hoy();
										nueva_consulta.fecha_solicitado = aux_fecha_de_hoy;

										string aux_fecha_turno = fecha_turno(fecha_nuevo_turno);
										nueva_consulta.fecha_turno = aux_fecha_turno;
										nueva_consulta.matricula_med = medico_nueva_consulta->matricula;
										nueva_consulta.presento = false;*/

										fecha_nuevo_turno = fecha_nuevo_turno_random();
										string aux_fecha_turno = fecha_turno(fecha_nuevo_turno);
										nueva_consulta.fecha_turno = aux_fecha_turno;

										string aux_fecha_de_hoy = fecha_de_hoy();
										nueva_consulta.fecha_solicitado = aux_fecha_de_hoy;

										nueva_consulta.matricula_med = medico_nueva_consulta->matricula;
										nueva_consulta.presento = false;
										nueva_consulta.dni_pac = lista_pac.dni;

										Imprimir_Datos_Consulta(nueva_consulta, lista_pac);

										agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, tam_lista_consultas_auxiliar);

									}
									//else
									//	cout << "Hubo problemas para asignar un medico con disponibilidad, volveremos a llamar al paciente en unos dias. " << endl;
								}
								else {
									cout << "El paciente no está interesado en obtener un nuevo turno en nuestro centro medico, archivamos su historial. " << endl;
									agregar_pacientes_archivados(lista_pac_archivados, lista_pac, tam_lista_archivados);
									//aca habria que llamar a la funcion de archivar
								}
							}
							else if (respuesta_estado_pac == 1) {
								lista_pac.estado = "fallecido";
								cout << "El paciente ha fallecido, archivamos su historial." << endl;
								agregar_pacientes_archivados(lista_pac_archivados, lista_pac, tam_lista_archivados);
								//funcion de archivar

							}
							else {
								cout << "El contacto nos informa que el paciente se encuentra internado, modificamos el archivo y procedemos a llamar mas adelante" << endl;
								lista_pac.estado = "internado";
							}

						}
						else {
							cout << "El contacto de emergencia no ha respondido al llamado. Enviamos un email a ambos contactos con el fin de recibir respuesta, de igual forma en unos dias llamamos al paciente otra vez. " << endl;
							//dejamos en standby
							cout << "Enviando email al paciente,  su correo es:" << contacto_paciente_a_llamar->mail << endl;
							cout << "Enviando email al contacto de emergencia, su correo es: " << contacto_paciente_a_llamar_emergencia->mail << endl;
						}
					}
					else {
						cout << "No se encontró un contacto de emergencia, procedemos a enviar un email al paciente e intentar llamar en unos dias otra vez. " << endl;
						cout << "Enviando email al paciente,  su correo es:" << contacto_paciente_a_llamar->mail << endl;
						//dejamos en standby

					}
				}

			}
			else
				cout << "Ha ocurrido un error y no se ha podido encontrar información de contacto del paciente. " << endl;
		}
		else if (aux_ult_consulta.presento == true) {
			cout << "El paciente se presento a su ultimo turno, el cual fue hace menos de 10 años. No hace falta llamarlo." << endl;
	    }

	//Asignar_Turno(lista[i], verificacion, lista2, lista1, &contador2, &contador3);

	//tam_lista_filtrada_consultas = 0;

	//int aux3 = Encontrar_Consulta(lista_cons, lista[i], &contador6);
	//cout << "La consulta mas actual es: " << aux3 << endl;
	//contador6 = 0;

	//	else if (verificacion == 0) {
	//		cout << "El paciente se atendio hace mas de 10 años, es un paciente irrecuperable. Archivamos su historial. " << endl;
	//		agregar_pacientes_archivados(lista_pac_archivados, lista_pac, &tam_lista_archivados);
	//		//archivamos
	//	}
	//	else if (verificacion == 2)
//   	cout << "El paciente ya tiene un turno proximo. No hace falta llamar." << endl;
}


Consultas* Imprimir_Secretaria(Pacientes* lista_pac, Consultas* lista_consultas, Contactos* lista_contactos, Medicos* lista_medicos, int* tam_pacientes, int* tam_consultas, int* tam_contactos, int* tam_medicos, int *tam_lista_consultas_auxiliar) {

	int tam_lista_filtrada_consultas = 0;
	Consultas* lista_cons;
	Medicos* medico_nueva_consulta;
	Medicos* medico_nueva_consulta_nuevo;
	Consultas nueva_consulta;
	Contactos* contacto_paciente_a_llamar = NULL;
	Contactos* contacto_paciente_a_llamar_emergencia = NULL;
	tm* fecha_nuevo_turno;

	Consultas* nueva_lista_auxiliar_consultas = NULL;
	
	Pacientes* lista_pac_activos = NULL;

	int tam_lista_archivados = 0;
	Pacientes* lista_pac_archivados = NULL;
	//filtrar_lista_verificacion(Pacientes* lista_pac, Consultas* lista_consultas, Pacientes* lista_pac_archivados, int* tam_pac_archivados, int* tam_pacientes, int* tam_consultas, int* tam_nueva_lista)
	int tam_nueva_lista = 0;

	int tam_pac_archivados = 0;
	lista_pac_activos = filtrar_lista_verificacion(lista_pac, lista_consultas, lista_pac_archivados, &tam_lista_archivados, tam_pacientes, tam_consultas, &tam_nueva_lista);
	//filtrar_lista_verificacion(lista_pac, lista_consultas, lista_pac_archivados, pac, int* tam_pac_archivados, int* tam_pacientes, int* tam_consultas, int* tam_nueva_lista)
	//Pacientes* lista_aux=filtrar_lista_archivados(lista_pac, lista_consultas, lista_pac_archivados, &tam_pac_archivados, tam_pacientes, tam_consultas, &tam_nueva_lista);

	if (lista_pac_activos != NULL) {
		for (int i = 0; i < tam_nueva_lista; i++) { //recorre lista pacientes-1
			if (lista_pac[i].estado == "n/c") {
				cout << "Paciente nro: " << i + 1 << endl;
				cout << "Dni: " << lista_pac_activos[i].dni << ", " << "Nombre: " << lista_pac_activos[i].nombre << ", " << "Apellido: " << lista_pac_activos[i].apellido << ", "
					<< "Sexo: " << lista_pac_activos[i].sexo << ", " << "Fecha de nacimiento: " << lista_pac_activos[i].natalicio << ", " << "Estado paciente: " << lista_pac_activos[i].estado
					<< ", " << "Obra social: " << lista_pac_activos[i].id_os << endl;
				//int aux2 = string_a_int(lista[i]);
				//cout << "Es: " << aux2 << endl;

				lista_cons = filtrar_lista_por_dni(lista_consultas, lista_pac_activos[i], tam_consultas, &tam_lista_filtrada_consultas);
				//for (int j = 0; j < tam_lista_filtrada_consultas; j++) {
					//cout << "Dni: " << lista_cons[j].dni_pac << endl;
					//cout << "Fecha solicitado del turno: " << lista_cons[j].fecha_solicitado << endl;
					//cout << "Fecha del turno: " << lista_cons[j].fecha_turno << endl;
					//cout << "Matricula del medico: " << lista_cons[j].matricula_med << endl;
					//if (lista_cons[j].presento == true) {
						//cout << "Presento:" << "Se presento al ultimo turno." << endl;
					//}
					//else
					//	cout << "Presento:" << "No se presento al ultimo turno." << endl;
					//tm* aux8;
					//aux8 = toInt(lista_cons[j].fecha_solicitado);
					//cout << "Dia: " << aux8->tm_mday << " Mes: " << aux8->tm_mon << " Anio: " << aux8->tm_year << endl;

// 				}
				//tm* aux3 = Encontrar_Consulta_Fecha(lista_cons, &tam_lista_filtrada_consultas);
				//cout << "La consulta mas actual es: " << aux3->tm_mday << ", " << aux3->tm_mon << ", " << aux3->tm_year << endl;
				//Consultas aux_ult_consulta = encontrar_ultima_consulta(lista_cons, &tam_lista_filtrada_consultas);
				

				Imprimir_Resto(nueva_lista_auxiliar_consultas, lista_medicos, lista_cons, &tam_lista_filtrada_consultas, lista_contactos, tam_contactos, lista_pac[i], tam_lista_consultas_auxiliar, tam_medicos, lista_pac_archivados, &tam_pac_archivados);
				tam_lista_filtrada_consultas = 0;
			}
			else if (lista_pac[i].estado == "fallecido") {
				cout << "El paciente se encuentra fallecido, archivamos su historial. " << endl;
				agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_pac_archivados);
			}
			else if (lista_pac[i].estado == "internado") {
				cout << "El paciente se encuentra internado en nuestro centro medico, llamamos mas adelante. " << endl;
			}
		}

		bool resp_pac_archivados = crear_archivo_pacientes_archivados("Pacientes_Archivados.csv", lista_pac_archivados, &tam_pac_archivados);

		Pacientes* lista_archivados;
		lista_archivados = read_archivo_pacientes_archivados("Pacientes_Archivados.csv");

		if (resp_pac_archivados) {
			cout << "Leyendo pacientes archivados:" << endl;
			for (int i = 0; i < tam_pac_archivados; i++) {
				cout << lista_archivados[i].dni << "," << lista_archivados[i].nombre << "," << lista_archivados[i].apellido << "," << lista_archivados[i].sexo << "," << lista_archivados[i].natalicio << "," << lista_archivados[i].estado << "," << lista_archivados[i].id_os << endl;
			}
			Agregar_Archivado(lista_pac, lista_archivados, tam_pacientes, &tam_pac_archivados);

			crear_archivo_lista_pacientes_nueva("Pacientes_Nueva_Lista.csv", lista_pac, tam_pacientes);
		}
		else
			cout << "Error al crear lista de pacientes archivado. " << endl;

		Pacientes* lista_nueva_pac1;
		lista_nueva_pac1 = read_archivo_lista_pacientes_nueva("Pacientes_Nueva_Lista.csv");

		cout << "Imprimiendo nueva lista con columna de archivado. " << endl;
		for (int i = 0; i < *tam_pacientes - 1; i++) {
			cout << lista_nueva_pac1[i].dni << "," << lista_nueva_pac1[i].nombre << "," << lista_nueva_pac1[i].apellido << " , " << lista_nueva_pac1[i].sexo << " , " << lista_nueva_pac1[i].natalicio << " , " << lista_nueva_pac1[i].estado << " , " << lista_nueva_pac1[i].id_os << " , " << lista_nueva_pac1[i].archivado << endl;
		}

		return nueva_lista_auxiliar_consultas;
	}
	else
		cout << "Ha ocurrido un error al hacer la verificacion. " << endl;
	
	return nueva_lista_auxiliar_consultas;//null
	//crear_archivo_consultas_nuevas("Consultas_Nuevas.csv", nueva_lista_auxiliar_consultas, &tam_lista_consultas_auxiliar);

	//Consultas* lista_aux_cons = NULL;
	//lista_aux_cons = read_archivo_nuevas_consultas("Consultas_Nuevas.csv");
	//cout << "Leyendo nuevas consultas. " << endl;
	//for (int i = 0; i < tam_lista_consultas_auxiliar-1; i++) {
		//cout << "Dni paciente: " << lista_aux_cons[i].dni_pac << endl;
		//cout << "Fecha en la cual se solicito el nuevo turno: " << lista_aux_cons[i].fecha_solicitado << endl;
		//cout << "Fecha del turno: " << lista_aux_cons[i].fecha_turno << endl;
		//cout << "Matricula del medico: " << lista_aux_cons[i].matricula_med << endl;
		//cout << "Presento: " << lista_aux_cons[i].presento << endl;
	//}

	/*
	tm* aux3 = Encontrar_Consulta_Fecha(lista_cons, &tam_lista_filtrada_consultas);
		cout << "La consulta mas actual es: " << aux3->tm_mday << ", " << aux3->tm_mon << ", " << aux3->tm_year << endl;
		Consultas aux_ult_consulta = encontrar_ultima_consulta(lista_cons, &tam_lista_filtrada_consultas);

		int verificacion = Verificar_Anio_Ultima_Consulta(aux3);
		//ultima_consulta = encontrar_ultima_consulta(lista_cons, &tam_lista_filtrada);

		if (verificacion == 1 && aux_ult_consulta.presento == false) { //paciente relativamente nuevo
			cout << "Paciente recuperable, procedemos a buscar algun contacto telefonico y llamar. " << endl;

			contacto_paciente_a_llamar = buscar_contacto_pac(lista_contactos, tam_contactos, lista_pac[i]);

			if (contacto_paciente_a_llamar != NULL) {
				cout << "Encontramos contacto del paciente, los datos son los siguientes: " << endl;

				cout << "Dni del paciente: " << contacto_paciente_a_llamar->dni_pac << ", " << "Telefono: " << contacto_paciente_a_llamar->telefono << ", "
					<< "Celular: " << contacto_paciente_a_llamar->celular << ", " << "Direccion: " << contacto_paciente_a_llamar->direccion
					<< ", " << "E-Mail: " << contacto_paciente_a_llamar->mail << endl;

				cout << "Llamando al paciente.." << endl;

				int respuesta_llamado_paciente = rand() % 2;

				if (respuesta_llamado_paciente) {
					cout << "El paciente ha respondido al llamado. Procedemos a consultar sobre la posibilidad de tener un nuevo turno en nuestro centro medico" << endl;

					int respuesta_pac_nuevo_turno = rand() % 2;

					if (respuesta_pac_nuevo_turno) {
						cout << "El paciente quiere un nuevo turno en nuestro centro medico." << endl;
						medico_nueva_consulta = Asignar_Medico(lista_medicos, lista_cons, &tam_lista_filtrada_consultas, tam_medicos);

						if (medico_nueva_consulta != NULL) {
							cout << "Ya asignamos con exito al medico de su proxima consulta, procedemos a dar una fecha del turno. " << endl;
							fecha_nuevo_turno = fecha_nuevo_turno_random();

							nueva_consulta.dni_pac = lista_pac[i].dni;
							string aux_fecha_de_hoy = fecha_de_hoy();
							nueva_consulta.fecha_solicitado = aux_fecha_de_hoy;

							string aux_fecha_turno = fecha_turno(fecha_nuevo_turno);
							nueva_consulta.fecha_turno = aux_fecha_turno;
							nueva_consulta.matricula_med = medico_nueva_consulta->matricula;
							nueva_consulta.presento = false;

							Imprimir_Datos_Consulta(nueva_consulta, lista_pac[i]);






						}
						//else
							//cout << "Hubo problemas para asignar un medico con disponibilidad, volveremos a llamar al paciente en unos dias. " << endl;
					}
					else {
						cout << "El paciente no está interesado en obtener un nuevo turno en nuestro centro medico, archivamos su historial. " << endl;
						agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
						//aca habria que llamar a la funcion de archivar
					}

				}
				else {
					cout << "El paciente no ha respondido al llamado, procedemos a llamar a su contacto de emergencia con el fin de dar con el paciente. " << endl;
					contacto_paciente_a_llamar_emergencia = buscar_contacto_emergencia(lista_contactos, tam_contactos, lista_pac[i], contacto_paciente_a_llamar);

					if (contacto_paciente_a_llamar_emergencia != NULL) {
						cout << "Encontramos al contacto de emergencia, sus datos son: " << endl;

						cout << "Dni del paciente: " << contacto_paciente_a_llamar_emergencia->dni_pac << ", " << "Telefono del contacto: " << contacto_paciente_a_llamar_emergencia->telefono << ", "
							<< "Celular del contacto: " << contacto_paciente_a_llamar->celular << ", " << "Direccion del contacto: " << contacto_paciente_a_llamar->direccion
							<< ", " << "E-Mail del contacto: " << contacto_paciente_a_llamar->mail << endl;

						cout << "Llamando al contacto de emergencia.. " << endl;

						int respuesta_contacto_emergencia = rand() % 2;
						if (respuesta_contacto_emergencia) {
							cout << "El contacto ha respondido al llamado, procedemos a consultar sobre como se encuentra el paciente y porque no atendio, con el fin de asignar un nuevo turno" << endl;

							int respuesta_estado_pac = rand() % 3;//0 esta vivo, no atendio porque estaba ocupado, procedemos a llamarlo y ya directo asignar turnp
							//1 fallecio, procedemos a archivar y modificar su estado a fallecido
							//2 internado, procedemos a dejar en standby y llamar cuando se encuentre mejor, modificamos estado

							if (respuesta_estado_pac == 0) {
								cout << "El paciente se encuentra bien, procedemos a llamarlo y ver la posibilidad de que agende un nuevo turno. " << endl;
								int respuesta_pac_nuevo_turno2 = rand() % 2;

								if (respuesta_pac_nuevo_turno2) {
									cout << "El paciente quiere un nuevo turno en nuestro centro medico." << endl;
									medico_nueva_consulta = Asignar_Medico(lista_medicos, lista_cons, &tam_lista_filtrada_consultas, tam_medicos);

									if (medico_nueva_consulta != NULL) {
										cout << "Ya asignamos con exito al medico de su proxima consulta, procedemos a dar una fecha del turno. " << endl;
										fecha_nuevo_turno = fecha_nuevo_turno_random();
										nueva_consulta.dni_pac = lista_pac[i].dni;
										string aux_fecha_de_hoy = fecha_de_hoy();
										nueva_consulta.fecha_solicitado = aux_fecha_de_hoy;

										string aux_fecha_turno = fecha_turno(fecha_nuevo_turno);
										nueva_consulta.fecha_turno = aux_fecha_turno;
										nueva_consulta.matricula_med = medico_nueva_consulta->matricula;
										nueva_consulta.presento = false;

										if (cambio_obra_social() == true) {
											string nueva_obra = Verificar_Datos_Paciente(lista_pac[i]);
											cout << "Datos de la nueva consulta: " << endl;
											cout << "DNI del paciente: " << nueva_consulta.dni_pac << endl;
											cout << "Fecha en la cual se solicito el turno: " << nueva_consulta.fecha_solicitado << endl;
											cout << "Fecha del turno: " << nueva_consulta.fecha_turno << endl;
											cout << "Matricula del medico del proximo turno: " << nueva_consulta.matricula_med << endl;
											cout << "Se presento el paciente?: " << nueva_consulta.presento << endl;
											cout << "Obra social nueva: " << nueva_obra << endl;

											agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, tam_lista_consultas_auxiliar);
											//agregar_consultas_extra(nueva_consulta, "Consultas.csv", tam_consultas);
											//agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, &tam_lista_consultas_auxiliar);
										}
										else {
											cout << "Datos de la nueva consulta: " << endl;
											cout << "DNI del paciente: " << nueva_consulta.dni_pac << endl;
											cout << "Fecha en la cual se solicito el turno: " << nueva_consulta.fecha_solicitado << endl;
											cout << "Fecha del turno: " << nueva_consulta.fecha_turno << endl;
											cout << "Matricula del medico del proximo turno: " << nueva_consulta.matricula_med << endl;
											cout << "Se presento el paciente?: " << nueva_consulta.presento << endl;
											cout << "Obra social" << lista_pac[i].id_os << endl;

											agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, tam_lista_consultas_auxiliar);
											//agregar_consultas_extra(nueva_consulta, "Consultas.csv", tam_consultas);
											//agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, &tam_lista_consultas_auxiliar);
										}
										//agregar_consultas(nueva_lista_auxiliar_consultas, nueva_consulta, &tam_lista_consultas_auxiliar);

									}
									//else
									//	cout << "Hubo problemas para asignar un medico con disponibilidad, volveremos a llamar al paciente en unos dias. " << endl;
								}
								else {
									cout << "El paciente no está interesado en obtener un nuevo turno en nuestro centro medico, archivamos su historial. " << endl;
									agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
									//aca habria que llamar a la funcion de archivar
								}
							}
							else if (respuesta_estado_pac == 1) {
								lista_pac[i].estado = "fallecido";
								cout << "El paciente ha fallecido, archivamos su historial." << endl;
								agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
								//funcion de archivar

							}
							else {
								cout << "El contacto nos informa que el paciente se encuentra internado, modificamos el archivo y procedemos a llamar mas adelante" << endl;
								lista_pac[i].estado = "internado";
							}

						}
						else {
							cout << "El contacto de emergencia no ha respondido al llamado. Enviamos un email a ambos contactos con el fin de recibir respuesta, de igual forma en unos dias llamamos al paciente otra vez. " << endl;
							//dejamos en standby
							cout << "Enviando email al paciente,  su correo es:" << contacto_paciente_a_llamar->mail << endl;
							cout << "Enviando email al contacto de emergencia, su correo es: " << contacto_paciente_a_llamar_emergencia->mail << endl;
						}
					}
					else {
						cout << "No se encontró un contacto de emergencia, procedemos a enviar un email al paciente e intentar llamar en unos dias otra vez. " << endl;
						cout << "Enviando email al paciente,  su correo es:" << contacto_paciente_a_llamar->mail << endl;
						//dejamos en standby

					}
				}

			}
			else
				cout << "Ha ocurrido un error y no se ha podido encontrar información de contacto del paciente. " << endl;
		}
		else if (verificacion == 0) {
			cout << "El paciente se atendio hace mas de 10 años, es un paciente irrecuperable. Archivamos su historial. " << endl;
			agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
			//archivamos
		}
		else if (verificacion == 2)
			cout << "El paciente ya tiene un turno proximo. No hace falta llamar." << endl;
		else if (lista_pac[i].estado == "fallecido") {
			cout << "El paciente se encuentra fallecido, archivamos su historial. " << endl;
			agregar_pacientes_archivados(lista_pac_archivados, lista_pac[i], &tam_lista_archivados);
			//archivamos
		}
		else if (lista_pac[i].estado == "internado") {
			cout << "El paciente se encuentra internado en nuestro centro medico, llamamos mas adelante. " << endl;
		}
		else if (aux_ult_consulta.presento == true) {
			cout << "El paciente se presento a su ultimo turno, el cual fue hace menos de 10 años. No hace falta llamarlo." << endl;
		}


		//Asignar_Turno(lista[i], verificacion, lista2, lista1, &contador2, &contador3);

		tam_lista_filtrada_consultas = 0;

		//int aux3 = Encontrar_Consulta(lista_cons, lista[i], &contador6);
		//cout << "La consulta mas actual es: " << aux3 << endl;
		//contador6 = 0;
	*/
}
//terminar funcion, habria que ver del struct de paciente que tenga contacto y acceda a los de emergencia y eso


//impresiones


/*void Llamar_Paciente(Pacientes* lista_pac, Contactos* lista_contacto, int* tam_contactos, int* tam2) {
	
	for (int i = 0; i < ) {
		Contactos* lista_filtrada = filtrar_lista_por_dni_contactos(lista_contacto, lista_pac[i], tam_contactos, tam2);
	    //imprimimos datos de contacto
		if (lista_pac[i].dni == lista_contacto.dni_pac) {
			cout << "Contactando paciente.." << endl;
			int respuesta = rand() % 2;

			if (respuesta) {
				cout << "Paciente respondio, procedemos a preguntar sobre posibilidad de nuevo turno en nuestro centro medico." << endl;
			}
			else {
				cout << "Paciente no respondio, buscamos contacto de emergencia de paciente" << endl;

			}
	}
	
			
	}
}*/
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
	int contador5 = 0;
	int contador6 = 0;
	int contador7 = 0;

	Pacientes* lista;
	lista=read_archivo_pacientes("Pacientes.csv", &contador);//con & transformo la variable en un puntero

	Consultas* lista1;
	lista1 = read_archivo_consultas("Consultas.csv", &contador2);

	Medicos* lista2;
	lista2 = read_archivo_medicos("Medicos.csv", &contador3);

	Contactos* lista3;
	lista3 = read_archivo_contactos("Contactos.csv", &contador4);
	
	

	
	Consultas* lista_cons;
	Contactos* lista_filtrada_contactos;
	Medicos* medico_nueva_consulta;
	Medicos* medico_nueva_consulta_nuevo;

	int tam_lista_consultas_auxiliar = 0;
	/*
	for (int i = 0; i < contador2-1; i++) {
		cout << lista1[i].dni_pac << "," << lista1[i].fecha_solicitado << "," << lista1[i].fecha_turno << "," << lista1[i].presento << "," << lista1[i].matricula_med << endl;
	}*/
	//los contador restan 1 porque sino imprime el ultimo 2 veces, ver si es solucion optima o no
	Consultas* lista5=Imprimir_Secretaria(lista, lista1, lista3, lista2, &contador, &contador2, &contador4, &contador3, &tam_lista_consultas_auxiliar);

	if (lista5 != NULL) {
		for (int i = 0; i < tam_lista_consultas_auxiliar; i++) {
			agregar_consultas_extra(lista5[i], "Consultas.csv", &contador2);
		}
	}
	else
	{
		for (int i = 0; i < contador2-1; i++) {
			cout << i << ", " << contador2 << endl;
			cout << lista1[i].dni_pac << "," << lista1[i].fecha_solicitado << "," << lista1[i].fecha_turno << "," << lista1[i].presento << "," << lista1[i].matricula_med << endl;
		}
	}
	/*for int i = 0; i < contador - 1; i++) {
		cout << "Paciente nro: " << i << endl;
		cout << lista[i].dni << "," << lista[i].nombre << "," << lista[i].apellido << "," << lista[i].sexo << "," << lista[i].natalicio << "," << lista[i].estado << "," << lista[i].id_os << endl;
		//int aux2 = string_a_int(lista[i]);
		//cout << "Es: " << aux2 << endl;

		lista_cons = filtrar_lista_por_dni(lista1, lista[i], &contador2, &contador6);
		for (int j = 0; j < contador6; j++) {
			cout << lista_cons[j].dni_pac << " , " << lista_cons[j].fecha_solicitado << ", " << lista_cons[j].fecha_turno << ", " << lista_cons[j].presento << endl;
			tm* aux8;
			aux8 = toInt(lista_cons[j].fecha_solicitado);
			//cout << "Dia: " << aux8->tm_mday << " Mes: " << aux8->tm_mon << " Anio: " << aux8->tm_year << endl;
		}
		tm* aux3 = Encontrar_Consulta_Fecha(lista_cons, &contador6);
		cout << "La consulta mas actual es: " << aux3->tm_mday << ", " << aux3->tm_mon << ", " << aux3->tm_year << endl;

		
		//Asignar_Turno(lista[i], verificacion, lista2, lista1, &contador2, &contador3);
			
		contador6 = 0;

		//int aux3 = Encontrar_Consulta(lista_cons, lista[i], &contador6);
		//cout << "La consulta mas actual es: " << aux3 << endl;
		//contador6 = 0;
	}*/

	
	//lista1 = read_archivo_consultas("Consultas.csv", &contador5);
	
	//int aux = string_a_int(lista[1]);
	/*
	*/
	
	for (int i = 0; i < contador3-1; i++) {
		cout << lista2[i].matricula << "," << lista2[i].nombre << "," << lista2[i].apellido << "," << lista2[i].telefono << "," << lista2[i].especialidad << "," << lista2[i].activo  << endl;
	}

	for (int i = 0; i < contador4-1; i++) {
		cout << lista3[i].dni_pac << "," << lista3[i].telefono << "," << lista3[i].celular << "," << lista3[i].direccion << "," << lista3[i].mail << endl;
	}
	
	

	for (int j = 0; j < 5; j++) {
		fecha_nuevo_turno_random();
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
/*
if (verificacion) {
			lista_filtrada_contactos = filtrar_lista_por_dni_contactos(lista3, lista[i], &contador4, &contador7);

			for (int k = 0; k < contador7; k++) {
				//dni_paciente , telefono , celular , direccion , mail
				cout << lista_filtrada_contactos[k].dni_pac << ", " << lista_filtrada_contactos[k].telefono << ", " << lista_filtrada_contactos[k].celular << ", " << lista_filtrada_contactos[k].direccion << ", " << lista_filtrada_contactos[k].mail << endl;
				cout << "Llamando al contacto.." << endl;

				int respuesta_contacto = rand() % 2;
				if (respuesta_contacto) {
					cout << "El paciente ha respondido, procedemos a consultar sobre la posibilidad de agendar un nuevo turno." << endl;
					Medicos* medico_nueva_consulta;
					Medicos* medico_nueva_consulta_nuevo;
					tm* ltm;
					string dia_de_semana;
					Consultas consulta_nueva;

					int verificacion_respuesta = rand() % 2;

					if (verificacion_respuesta) {
						cout << "Paciente recuperable, procedemos a asignar turno." << endl;
						Medicos* medico_asignado = Asignar_Medico(lista2, lista_cons, &contador2, &contador3);
						if (medico_asignado != NULL) {
							cout << "Se asignó con exito al medico. Procedemos a asignar fecha de proximo turno con dicho medico." << endl;
							ltm = fecha_nuevo_turno_random();


							consulta_nueva.dni_pac = lista[i].dni;
							consulta_nueva.matricula_med = medico_asignado->matricula;
							consulta_nueva.presento = false;

							time_t curr_time;
							tm* curr_tm;
							char date_string1[100];
							char date_string2[100];

							time(&curr_time);
							curr_tm = localtime(&curr_time);

							strftime(date_string1, 50, "%d/%m/%Y", curr_tm);
							consulta_nueva.fecha_solicitado = date_string1;

							time_t curr_time2;
							tm* curr_tm2;
							time(&curr_time2);
							curr_tm2 = localtime(&curr_time2);

							curr_tm2->tm_mon = ltm->tm_mon;
							curr_tm2->tm_mday = ltm->tm_mday;

							strftime(date_string2, 50, "%d/%m/2023", curr_tm2);//ver
							consulta_nueva.fecha_turno = date_string2;

							cout << "La fecha en la cual se solicito el turno es: " << date_string1 << endl;
							cout << "Fecha de turno " << date_string2 << endl;
						}
					}
					else {
						cout << "Paciente irrecuperable, no se puede volver a asignar turno. Procedemos a archivar" << endl;
					}
				}
			}
*/
/*if (verificacion) {
			cout << "Paciente recuperable, procedemos a asignar turno." << endl;

			cout << "Desea un turno con el medico de su ultima consulta?" << endl;
			int respuesta1 = rand() % 2;
			if (respuesta1 == 1) {
				medico_nueva_consulta = Buscar_Medico_Viejo(lista2, lista_cons, &contador6, &contador3);

				if (medico_nueva_consulta != NULL) {
					cout << "Encontramos al medico de su ultima consulta, sus datos son: " << endl;
					cout << "Matricula: " << medico_nueva_consulta->matricula << " Apellido: " << medico_nueva_consulta->apellido << " Nombre: " << medico_nueva_consulta->nombre << " Especialidad: " << medico_nueva_consulta->especialidad << endl;
					Verificar_Datos_Paciente(lista[i]);
				}
				else {
					cout << "No se ha encontrado al medico." << endl;
					cout << "Desea buscar otro medico? " << endl;

					int respuesta2 = rand() % 2;

					if (respuesta2 == 1) {
						cout << "Ha decidido buscar otro medico: " << endl;
						medico_nueva_consulta_nuevo = Buscar_Medico_Nuevo(lista2, lista_cons, &contador6, &contador3);

						if (medico_nueva_consulta_nuevo != NULL) {
							cout << "Encontramos un nuevo medico, sus datos son: " << endl;
							cout << "Matricula: " << medico_nueva_consulta_nuevo->matricula << " Apellido: " << medico_nueva_consulta_nuevo->apellido << " Nombre: " << medico_nueva_consulta_nuevo->nombre << " Especialidad: " << medico_nueva_consulta_nuevo->especialidad << endl;
							Verificar_Datos_Paciente(lista[i]);
						}
						else
							cout << "No se ha encontrado al medico nuevo." << endl;
					}
					else
						cout << "El paciente ha decidido no buscar otro medido" << endl;
				}
			}
			else {
				cout << "Ha decidido no asignar turno con su ultimo medico, procedemos a buscar un nuevo. " << endl;
				
				medico_nueva_consulta_nuevo = Buscar_Medico_Nuevo(lista2, lista_cons, &contador6, &contador3);

					if (medico_nueva_consulta_nuevo != NULL) {
						cout << "Encontramos un nuevo medico, sus datos son: " << endl;
						cout << "Matricula: " << medico_nueva_consulta_nuevo->matricula << " Apellido: " << medico_nueva_consulta_nuevo->apellido << " Nombre: " << medico_nueva_consulta_nuevo->nombre << " Especialidad: " << medico_nueva_consulta_nuevo->especialidad << endl;
						Verificar_Datos_Paciente(lista[i]);
					}
					else
						cout << "No se ha encontrado al medico nuevo." << endl;
			}
			
		}
		else
			cout << "Paciente irrecuperable, no se puede volver a asignar turno. Procedemos a archivar" << endl;*/

			/*void Asignar_Turno(Pacientes pac, bool verificacion_respuesta, Medicos* lista2, Consultas* lista_cons, int* contador2, int* contador3) {
				Medicos* medico_nueva_consulta;
				Medicos* medico_nueva_consulta_nuevo;
				tm* ltm;
				string dia_de_semana;
				Consultas consulta_nueva;

				if (verificacion_respuesta) {
					cout << "Paciente recuperable, procedemos a asignar turno." << endl;
					Medicos* medico_asignado = Asignar_Medico(lista2, lista_cons, contador2, contador3);
					if (medico_asignado != NULL) {
						cout << "Se asignó con exito al medico. Procedemos a asignar fecha de proximo turno con dicho medico." << endl;
						ltm = fecha_nuevo_turno_random();

						//cout << "La fecha de su nuevo turno es: " << endl;
						//cout << dia_de_semana << endl;
						//cout << "Dia: " << ltm->tm_mday << endl;
						//cout << "Mes: " << ltm->tm_mon << endl;
						//cout << "Anio: " << ltm->tm_year << endl;
						consulta_nueva.dni_pac = pac.dni;
						consulta_nueva.matricula_med = medico_asignado->matricula;
						consulta_nueva.presento = false;

						time_t curr_time;
						tm* curr_tm;
						char date_string1[100];
						char date_string2[100];

						time(&curr_time);
						curr_tm = localtime(&curr_time);

						strftime(date_string1, 50, "%d/%m/%Y", curr_tm);
						consulta_nueva.fecha_solicitado = date_string1;

						time_t curr_time2;
						tm* curr_tm2;
						time(&curr_time2);
						curr_tm2 = localtime(&curr_time2);

						//curr_tm2->tm_year = 2023;
						curr_tm2->tm_mon = ltm->tm_mon;
						curr_tm2->tm_mday = ltm->tm_mday;

						strftime(date_string2, 50, "%d/%m/2023", curr_tm2);//ver
						consulta_nueva.fecha_turno = date_string2;

						cout << "La fecha en la cual se solicito el turno es: " << date_string1 << endl;
						cout << "Fecha de turno " << date_string2 << endl;
						//fechas a string
						//auto t2 = time(nullptr);
						//auto tm = *localtime(&t2);
						/*if (ltm->tm_mday == 6) {
							ltm = fecha_nuevo_turno_random();
							dia_de_semana = convertir_dia_a_string_dia(ltm);
						}
						else {
							dia_de_semana = convertir_dia_a_string_dia(ltm);
						}


						//agregar_consultas(lista_cons, consulta_nueva, contador2);
					}
				}
				else {
					cout << "Paciente irrecuperable, no se puede volver a asignar turno. Procedemos a archivar" << endl;
				}

			}*/