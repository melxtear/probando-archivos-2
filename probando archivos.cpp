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
	Contactos contacto;//tendria que tener 2? uno de emergencia y otra dle mismo paciente
	//Consultas consulta;//consulta asociada, lee la del paciente

}Pacientes;


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


void agregar_pacientes_archivados(Pacientes*& lista_pac, Pacientes paciente, int* tamactual) {
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

void crear_archivo_pacientes_archivados(string nombre_a1, Pacientes*& lista_pac_archivados, int* tamactual) {
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
		
	}

	archi.close();
	//archi2.close();

	return;
}

Pacientes* archivar_pacientes(Pacientes*& lista_pac_a_archivar, int* contador5) {
	Pacientes* l_pac = new Pacientes[0];
	int tamactual = 0;
	for (int i = 0; i <= 100; i++) {
		if (lista_pac_a_archivar[i].estado == "fallecido") {
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

	aux1 = toInt(lista_consultas_filtradas[0].fecha_solicitado);

	for (int i = 0; i < *tamactual; i++) {

          aux2 = toInt(lista_consultas_filtradas[i].fecha_solicitado);
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

	aux1 = toInt(lista_consultas_filtradas[0].fecha_solicitado);

	for (int i = 0; i < *tamactual; i++) {

		aux2 = toInt(lista_consultas_filtradas[i].fecha_solicitado);
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

//Consultas* lista_consultas_filtradas, int* tamactual

bool Verificar_Anio_Ultima_Consulta(tm* fecha_ultima_consulta) {
	
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
	cout << aux2->tm_mday << ", " << aux2->tm_mon << ", " << aux2->tm_year << endl;

	time_t t = time(0);
	tm* nuevo= localtime(&t);
	nuevo->tm_year = (aux2->tm_year) - (fecha_ultima_consulta->tm_year);

	cout << nuevo->tm_year << endl;

	if (nuevo->tm_year < 10) {
		return true;
		//ok, la diferencia de año es menor a 10 o sea es un paciente recuperable, podemos llamar
	}
	else if (nuevo->tm_year == 10) { //la diferencia de año es 10, está al limite
		if (fecha_ultima_consulta->tm_mon > aux2->tm_mon) { //vemos si el mes de la ultima consulta es mayor
			return true;
			//ok, el mes de la consulta es mayor, ej 11/2022-12/2012, significa que todavia no llegaron a ser 10 años 
			//justos de su ultima consulta, por eso es un paciente recuperable, podemos llamarlo
		}
		else if (fecha_ultima_consulta->tm_mon == aux2->tm_mon) { //el mes es igua, está al limit
			if (fecha_ultima_consulta->tm_mday >= aux2->tm_mday) { 
				return true;
				//todavia no se cumplieron los 10 años o se cumplieron los 10 años justo ese dia
				//pero es un paciente recuperable, podemos llamarlo
			}
			else//el dia de la ultima consulta es mas chico, se supero el limite
				return false;
			//ya se cumplieron los 10 años, es un paciente irrecuperable, procedemos a archivarlo

		}
		else if (fecha_ultima_consulta->tm_mon < aux2->tm_mon) {////el mes de ultima consulta es mas chico, supero limite
			//ya se cumplieron los 10 años, es un paciente irrecuperable, procedemos a archivarlo
			return false;
		}
	}
	else//la diferencia de años es mayor a los 10, se supero el limite
		return false;
		//ya se cumplieron los 10 años, es un paciente irrecuperable, procedemos a archivarlo

	//cout << "dia : " << ltm->tm_mday << endl;
	//cout << "mes : " << ltm->tm_mon << endl;
	//cout << "anio : " << ltm->tm_year << endl;

}

void Verificar_Datos_Paciente(Pacientes paciente_datos_verificar) {
	int respuesta1 = rand() % 2; 

	cout << "El paciente ha cambiado sus datos de obra social? " << endl;
	if (respuesta1 == 1) {
		cout << "El paciente ha cambiado de obra social, preguntamos por cual y modificamos sus datos en el archivo. " << endl;
		
		if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Medicus)) {
			int respuesta2 = rand() % 5+1;
			//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
			if (respuesta2 == 1) {
				cout << "El paciente se cambio a Osde, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::OSDE;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 2) {
				cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Italiano;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 3) {
				cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Espanyol;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 4) {
				cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Aleman;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 5) {
				cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::IOSFA;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}

		}
		else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::OSDE)) {
			int respuesta2 = rand() % 5+1; 

			//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
			if (respuesta2 == 1) {
				cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Medicus;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 2) {
				cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Italiano;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 3) {
				cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Espanyol;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 4) {
				cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Aleman;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 5) {
				cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::IOSFA;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}

		}
		else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Italiano)) {
			int respuesta2 = rand() % 5 + 1;

			//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
			if (respuesta2 == 1) {
				cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Medicus;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 2) {
				cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::OSDE;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 3) {
				cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Espanyol;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 4) {
				cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Aleman;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 5) {
				cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::IOSFA;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}

		}
		else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Espanyol)) {
			int respuesta2 = rand() % 5 + 1;

			//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
			if (respuesta2 == 1) {
				cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Medicus;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 2) {
				cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Italiano;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 3) {
				cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::OSDE;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 4) {
				cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Aleman;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 5) {
				cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::IOSFA;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}

		}
		else if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::Aleman)) {
			int respuesta2 = rand() % 5 + 1;

			//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
			if (respuesta2 == 1) {
				cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Medicus;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 2) {
				cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Italiano;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 3) {
				cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Espanyol;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 4) {
				cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::OSDE;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 5) {
				cout << "El paciente se cambio a IOSFA, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::IOSFA;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}

		}
		else {
			//if (paciente_datos_verificar.id_os == Obras_SocialesToString(eObras_Sociales::IOSFA)) 
			int respuesta2 = rand() % 5 + 1;
			
			//Medicus, OSDE, Italiano, Espanyol, Aleman, IOSFA
			if (respuesta2 == 1) {
				cout << "El paciente se cambio a Medicus, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Medicus;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 2) {
				cout << "El paciente se cambio a Italiano, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Italiano;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			else if (respuesta2 == 3) {
				cout << "El paciente se cambio a Espanyol, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Espanyol;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 4) {
				cout << "El paciente se cambio a Aleman, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::Aleman;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}
			if (respuesta2 == 5) {
				cout << "El paciente se cambio a OSDE, guardamos nueva obra social." << endl;
				eObras_Sociales nuevo = eObras_Sociales::OSDE;
				paciente_datos_verificar.id_os == Obras_SocialesToString(nuevo);
			}

		}

	}
	else
		cout << "El paciente no se cambio de obra social." << endl;
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
	int contador5 = 0;
	int contador6 = 0;

	Pacientes* lista;
	lista=read_archivo_pacientes("Pacientes.csv", &contador);//con & transformo la variable en un puntero

	Consultas* lista1;
	lista1 = read_archivo_consultas("Consultas.csv", &contador2);

	Medicos* lista2;
	lista2 = read_archivo_medicos("Medicos.csv", &contador3);

	Contactos* lista3;
	lista3 = read_archivo_contactos("Contactos.csv", &contador4);
	
	Pacientes* lista4;
	lista4 = archivar_pacientes(lista, &contador5);
		
	crear_archivo_pacientes_archivados("Pacientes_Archivados.csv", lista4, &contador5);

	Pacientes* lista5;
	lista5 = read_archivo_pacientes_archivados("Pacientes_Archivados.csv");

	Consultas* lista_cons;
	Medicos* medico_nueva_consulta;
	Medicos* medico_nueva_consulta_nuevo;

	//los contador restan 1 porque sino imprime el ultimo 2 veces, ver si es solucion optima o no
	for (int i = 0; i < contador-1; i++) {
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
		
		bool verificacion=Verificar_Anio_Ultima_Consulta(aux3);

		if (verificacion) {
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
			cout << "Paciente irrecuperable, no se puede volver a asignar turno. Procedemos a archivar" << endl;
			
		contador6 = 0;

		//int aux3 = Encontrar_Consulta(lista_cons, lista[i], &contador6);
		//cout << "La consulta mas actual es: " << aux3 << endl;*/
		//contador6 = 0;
	}

	
	//int aux = string_a_int(lista[1]);
	for (int i = 0; i < contador2-1; i++) {
		cout << lista1[i].dni_pac << "," << lista1[i].fecha_solicitado << "," << lista1[i].fecha_turno << "," << lista1[i].presento << "," << lista1[i].matricula_med << endl;
	}
	
	for (int i = 0; i < contador3-1; i++) {
		cout << lista2[i].matricula << "," << lista2[i].nombre << "," << lista2[i].apellido << "," << lista2[i].telefono << "," << lista2[i].especialidad << "," << lista2[i].activo  << endl;
	}

	for (int i = 0; i < contador4-1; i++) {
		cout << lista3[i].dni_pac << "," << lista3[i].telefono << "," << lista3[i].celular << "," << lista3[i].direccion << "," << lista3[i].mail << endl;
	}
	
	cout << "Leyendo pacientes archivados:" << endl;
	for (int i = 0; i < contador5; i++) {
	   cout << lista5[i].dni << "," << lista5[i].nombre << "," << lista5[i].apellido << "," << lista5[i].sexo << "," << lista5[i].natalicio << "," << lista5[i].estado << "," << lista5[i].id_os << endl;
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