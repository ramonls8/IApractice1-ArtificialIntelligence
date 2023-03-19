#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////
// Funciones
//////////////////////////////////////////////////////////

// Guarda la vista actual en el mapa
void SaveView(vector<unsigned char> &view, const state &st, vector<vector<unsigned char>> &map){
	map[st.fil][st.col] = view[0];
}

// Rellena todos los valores de una matriz con el carácter c
void ResetCharMatrix(vector<vector<unsigned char>> &matrix, char c = '?'){
	int rows = matrix.size();

	for (int i=0; i<rows; i++){
		int cols = matrix[i].size();

		for (int j=0; j<cols; j++)
			matrix[i][j] = c;
	}
}

//////////////////////////////////////////////////////////
// Métodos privados
//////////////////////////////////////////////////////////

bool ComportamientoJugador::ResetState(unsigned int size){
	// La fila y columna serán las últimas para poder rellenar el mapa
    // auxiliar sin salir de él en caso de no poder ubicarnos
	st.fil = st.col = size-1;
    st.brujula = norte;
}

bool ComportamientoJugador::SensorIsWorking(const Sensores &sensores){
	return sensores.posF != -1;
}

void ComportamientoJugador::ShowInfo(const Sensores &sensores){
	cout << "Fil " << sensores.posF << ", Col " << sensores.posC << ", ";
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
	cout << "Terreno:    ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión:   " << sensores.colision << endl;
	cout << "Reset:      " << sensores.reset << endl;
	cout << "Vida:       " << sensores.vida << endl;
	cout << endl;
}

void ComportamientoJugador::UpdateState(const Sensores &sensores){
	// Sabemos la posición gracias a los sensores
	if (SensorIsWorking(sensores)){
		// Comprobamos si acabamos de llegar a una casilla de posicionamiento tras estar
		// desubicados, donde pasaremos los datos que hemos descubierto en
		// el mapa auxiliar al mapa resultado
		if (wellLocated = false){
			// Actualizamos nuestra posición en mapa auxiliar
			if (last_action == actFORWARD)
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
			// Pasamos el mapa auxiliar con nuestra posición en este al mapa resultado
			// con la nueva posición

			// corregir: TransferMap(mapaAuxiliar, st.fil, st.col, mapaResultado, sensores.posF, sensores.posC)
		}
		
		// Actualizamos el estado
		st.fil = sensores.posF;
		st.col = sensores.posC;
		st.brujula = sensores.sentido;
		wellLocated = true;
	}
	
	// Hay reset y no sabemos la nueva ubicación
	else if (sensores.reset){
		wellLocated = false;

		// Como no sabemos donde estamos, reiniciamos el mapa auxiliar y el estado
		ResetCharMatrix(mapaAuxiliar);
		ResetState(mapaResultado.size());
	}

	// No hay reset y no valen los sensores, por lo que tenemos en cuenta last_action
	else {
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
	}

	/*
	// Si no conocía la posición y pisa una casilla G, a partir de ahora sí la conocerá
	if (SensorIsWorking(sensores) && !wellLocated){
		st.fil = sensores.posF;
		st.col = sensores.posC;
		st.brujula = sensores.sentido;
		wellLocated = true;
	}
	*/
}




//////////////////////////////////////////////////////////
// Métodos públicos
//////////////////////////////////////////////////////////

Action ComportamientoJugador::think(Sensores sensores){
	// Crea la acción
	Action accion = actIDLE;

	// Actualizar estado
	UpdateState(sensores);

	// Info debug
	ShowInfo(sensores);

	// Guarda la vista en el mapa
	if (wellLocated)
		SaveView(sensores.terreno, st, mapaResultado);
	else
		SaveView(sensores.terreno, st, mapaAuxiliar);

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

