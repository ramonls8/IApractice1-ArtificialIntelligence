#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;



// Guarda la vista actual en el mapa
void SaveView(const vector<unsigned char> &view, const state &st, vector<vector<unsigned char>> &map){
	map[st.fil][st.col] = view[0];
}

//////////////////////////////////////////////////////////

void ComportamientoJugador::ShowInfo(const Sensores &sensores){
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl;	break;
		case 1: cout << "Noreste" << endl;	break;
		case 2: cout << "Este" << endl;		break;
		case 3: cout << "Sureste" << endl;	break;
		case 4: cout << "Sur " << endl;		break;
		case 5: cout << "Suroeste" << endl;	break;
		case 6: cout << "Oeste" << endl;	break;
		case 7: cout << "Noroeste" << endl;	break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;
}






//////////////////////////////////////////////////////////

Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;

	// Actualizar con la última acción
	switch (last_action){
		case actFORWARD:	// Da un paso si no hay colisión
			if (!sensores.colision){
				switch (st.brujula){
					case norte:		st.fil--; 			break;
					case noreste:	st.fil--; st.col++;	break;
					case este:		st.col++;			break;
					case sureste:	st.fil++; st.col++;	break;
					case sur:		st.fil++;			break;
					case suroeste:	st.fil++; st.col--;	break;
					case oeste:		st.col--;			break;
					case noroeste:	st.fil--; st.col--;	break;
				}
			}
			break;
		
		case actTURN_SL:
			st.brujula =
				static_cast<Orientacion>( (st.brujula+7) % 8 );
			break;
		case actTURN_SR:
			st.brujula =
				static_cast<Orientacion>( (st.brujula+1) % 8 );
			break;
		case actTURN_BL:
			st.brujula =
				static_cast<Orientacion>( (st.brujula+5) % 8 );
			break;
		case actTURN_BR:
			st.brujula =
				static_cast<Orientacion>( (st.brujula+3) % 8 );
			break;
	}

	// Info debug
	ShowInfo(sensores);



	// Si no conocía la posición y pisa una casilla G, a partir de ahora sí la conocerá
	if (sensores.posF!=-1 and !bien_situado){
		st.fil = sensores.posF;
		st.col = sensores.posC;
		st.brujula = sensores.sentido;
		bien_situado = true;
	}

	// Guarda lo que ve en el mapa temporal o en el mapa resultado
	if (bien_situado)
		SaveView(sensores.terreno, st, mapaResultado);

	// Decidir la nueva acción
	if ((sensores.terreno[2]=='T' or sensores.terreno[2]=='S') or
		sensores.terreno[2]=='G' and sensores.superficie[2]=='_'){
		accion = actFORWARD;
	} else{
		if (rand()%2==0)	accion = actTURN_SR;
		else				accion = actTURN_SL;
	}
	
	// Recorda la última acción
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

