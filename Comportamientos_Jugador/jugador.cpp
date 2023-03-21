#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////
// Métodos privados
//////////////////////////////////////////////////////////

vector<unsigned char> ComportamientoJugador::GetCertainView(state s, vector<vector<unsigned char>> &map){
	// Desplazamiento de filas y columnas cuando nos movemos hacia delante, izq y der
	pair<unsigned int, unsigned int> front, right, left;
	front.first = front.second = right.first = right.second = left.first = left.second = 0;

	switch(st.brujula){
		case norte:
			// Si nos movemos hacia delante mirando al norte, baja una fila y la columna no cambia
			front.first = -1;
			left.second = -1;
			right.second = 1;
			break;
		case sur:
			front.first = 1;
			left.second = 1;
			right.second = -1;
			break;
		case este:
			front.second = 1;
			left.first = -1;
			right.first = 1;
			break;
		case oeste:
			front.second = -1;
			left.first = 1;
			right.first = -1;
			break;
		case noreste:
			front.first = -1;	front.second = 1;
			left.second = -1;
			right.first = 1;
			break;
		case suroeste:
			front.first = 1;	front.second = -1;
			left.second = 1;
			right.first = -1;
			break;
		case noroeste:
			front.first = -1;	front.second = -1;
			left.first = 1;
			right.second = 1;
			break;
		case sureste:
			front.first = 1;	front.second = 1;
			left.first = -1;
			right.second = -1;
			break;
	}

	// Vector para escribir las casillas
	vector<unsigned char> view;
	view.reserve(16);

	// Escritura de casillas
	view[0 ] = map[s.fil][st.col];
	view[1 ] = map[s.fil + front.first + left.first ][s.col + front.second + left.second ];
	view[2 ] = map[s.fil + front.first              ][s.col + front.second               ]; // Ej: La pos 2 se consigue con 1 mov hacia delante
	view[3 ] = map[s.fil + front.first + right.first][s.col + front.second + right.second];

	view[4 ] = map[s.fil + 2*front.first + 2*left.first ][s.col + 2*front.second + 2*left.second ];
	view[5 ] = map[s.fil + 2*front.first + 1*left.first ][s.col + 2*front.second + 1*left.second ];
	view[6 ] = map[s.fil + 2*front.first                ][s.col + 2*front.second                 ];
	view[7 ] = map[s.fil + 2*front.first + 1*right.first][s.col + 2*front.second + 1*right.second];
	view[8 ] = map[s.fil + 2*front.first + 2*right.first][s.col + 2*front.second + 2*right.second];

	view[9 ] = map[s.fil + 3*front.first + 3*left.first ][s.col + 3*front.second + 3*left.second ];
	view[10] = map[s.fil + 3*front.first + 2*left.first ][s.col + 3*front.second + 2*left.second ];
	view[11] = map[s.fil + 3*front.first + 1*left.first ][s.col + 3*front.second + 1*left.second ];
	view[12] = map[s.fil + 3*front.first                ][s.col + 3*front.second                 ];
	view[13] = map[s.fil + 3*front.first + 1*right.first][s.col + 3*front.second + 1*right.second];
	view[14] = map[s.fil + 3*front.first + 2*right.first][s.col + 3*front.second + 2*right.second];
	view[15] = map[s.fil + 3*front.first + 3*right.first][s.col + 3*front.second + 3*right.second];

	return view;
}

void ComportamientoJugador::SaveActualView(const vector<unsigned char> &view, vector<vector<unsigned char>> &map){
	// Desplazamiento de filas y columnas cuando nos movemos hacia delante, izq y der
	pair<unsigned int, unsigned int> front, right, left;
	front.first = front.second = right.first = right.second = left.first = left.second = 0;

	switch(st.brujula){
		case norte:
			// Si nos movemos hacia delante mirando al norte, baja una fila y la columna no cambia
			front.first = -1;
			left.second = -1;
			right.second = 1;
			break;
		case sur:
			front.first = 1;
			left.second = 1;
			right.second = -1;
			break;
		case este:
			front.second = 1;
			left.first = -1;
			right.first = 1;
			break;
		case oeste:
			front.second = -1;
			left.first = 1;
			right.first = -1;
			break;
		case noreste:
			front.first = -1;	front.second = 1;
			left.second = -1;
			right.first = 1;
			break;
		case suroeste:
			front.first = 1;	front.second = -1;
			left.second = 1;
			right.first = -1;
			break;
		case noroeste:
			front.first = -1;	front.second = -1;
			left.first = 1;
			right.second = 1;
			break;
		case sureste:
			front.first = 1;	front.second = 1;
			left.first = -1;
			right.second = -1;
			break;
	}

	// Escritura de casillas
	map[st.fil][st.col] = view[0];
	map[st.fil + front.first + left.first ][st.col + front.second + left.second ] = view[1];
	map[st.fil + front.first              ][st.col + front.second               ] = view[2]; // Ej: La pos 2 se consigue con 1 mov hacia delante
	map[st.fil + front.first + right.first][st.col + front.second + right.second] = view[3];

	map[st.fil + 2*front.first + 2*left.first ][st.col + 2*front.second + 2*left.second ] = view[4 ];
	map[st.fil + 2*front.first + 1*left.first ][st.col + 2*front.second + 1*left.second ] = view[5 ];
	map[st.fil + 2*front.first                ][st.col + 2*front.second                 ] = view[6 ];
	map[st.fil + 2*front.first + 1*right.first][st.col + 2*front.second + 1*right.second] = view[7 ];
	map[st.fil + 2*front.first + 2*right.first][st.col + 2*front.second + 2*right.second] = view[8 ];

	map[st.fil + 3*front.first + 3*left.first ][st.col + 3*front.second + 3*left.second ] = view[9 ];
	map[st.fil + 3*front.first + 2*left.first ][st.col + 3*front.second + 2*left.second ] = view[10];
	map[st.fil + 3*front.first + 1*left.first ][st.col + 3*front.second + 1*left.second ] = view[11];
	map[st.fil + 3*front.first                ][st.col + 3*front.second                 ] = view[12];
	map[st.fil + 3*front.first + 1*right.first][st.col + 3*front.second + 1*right.second] = view[13];
	map[st.fil + 3*front.first + 2*right.first][st.col + 3*front.second + 2*right.second] = view[14];
	map[st.fil + 3*front.first + 3*right.first][st.col + 3*front.second + 3*right.second] = view[15];
}

void ComportamientoJugador::ResetCharMatrix(vector<vector<unsigned char>> &matrix, char c = '?'){
	int rows = matrix.size();

	for (int i=0; i<rows; i++){
		int cols = matrix[i].size();

		for (int j=0; j<cols; j++)
			matrix[i][j] = c;
	}
}

void ComportamientoJugador::ResetState(unsigned int size){
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
	// Comprobamos si hemos perdido o conseguido objetos
	if (sensores.reset) {wearingBikini = false; wearingShoes = false;}
	else if (sensores.terreno[0] == 'K')		wearingBikini = true;
	else if (sensores.terreno[0] == 'D')		wearingShoes = true;

	// Sabemos la posición gracias a los sensores
	if (SensorIsWorking(sensores)){
		// Comprobamos si acabamos de llegar a una casilla de posicionamiento tras estar
		// desubicados, donde pasaremos los datos que hemos descubierto en
		// el mapa auxiliar al mapa resultado
		if (wellLocated == false){
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
			TransferMap(sensores);
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

void ComportamientoJugador::TransferMap(const Sensores &sensores){
	// Pasamos el mapa auxiliar con nuestra posición y orientación
	// en este al mapa resultado con la nueva posición
	unsigned int size = mapaResultado.size();
	unsigned int i,j;

	// Mista orientación
	if (st.brujula == sensores.sentido)
		for (i=0; i<size; i++)
			for (j=0; j<size; j++)
				// Si conocemos la casilla, la guardamos en mapa resultado
				if (mapaAuxiliar[i+st.fil-sensores.posF][j+st.col-sensores.posC] != '?')
					mapaResultado[i][j] = mapaAuxiliar[i+st.fil-sensores.posF][j+st.col-sensores.posC];
	
	// No es necesario implementarlo para una orientaciones diferentes
	// ya que cuando reaparece o cuando aparece por primera vez en un nivel
	// en el que está desubicado, siempre lo hace mirando al norte, que
	// es la orientación por defecto de la brújula
}

bool ComportamientoJugador::CanMoveForward(const Sensores &sensores){
	bool canMoveForward = true;

	if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M' ||
		sensores.superficie[2] != '_')
		canMoveForward = false;

	return canMoveForward;
}

bool ComportamientoJugador::IsCharacter(unsigned char c){
	// Comprueba si la letra es minúscula
	return 'a' <= c || c <= 'z';
}

unsigned int ComportamientoJugador::DintaceInViewFromObject(const Sensores &sensores, unsigned char c){
	vector<unsigned char> view;

	if (IsCharacter(c))	view = sensores.superficie;
	else				view = sensores.terreno;

	if (view[0]==c)
		return 0;
	else if (view[1]==c || view[2]==c || view[3]==c)
		return 1;
	else if (view[4]==c || view[5]==c || view[6]==c || view[7]==c || view[8]==c)
		return 2;
	else if (view[9]==c || view[10]==c || view[11]==c || view[12]==c
			|| view[13]==c || view[14]==c || view[15]==c)
		return 3;
	
	return FAR;
}

unsigned int ComportamientoJugador::DintaceInMapFromPlace(unsigned int row, unsigned int col){
	// Distancia en filas y columnas
	int rowDistance = st.fil - row;
	int colDistance = st.col - col;

	// Valor absoluto de la distancia
	if (rowDistance < 0)	rowDistance = -rowDistance;
	if (colDistance < 0)	colDistance = -colDistance;

	// Como podemos movernos en diagonal, el nº de pasos será la mayor distancia entre filas y columnas
	unsigned int distance = rowDistance;
	if (rowDistance < colDistance)	distance = colDistance;

	return distance;
}

int ComportamientoJugador::CostOfAction(const Sensores &sensores, Action action){
	int cost;

	// Calcula cuanta batería perdería debido a la siguiente casilla
	if (action == actFORWARD){
		switch (sensores.terreno[2]){
			case 'A':
				if (wearingBikini)	cost = 10;
				else				cost = 200;
				break;
			case 'B':
				if (wearingShoes)	cost = 15;
				else				cost = 100;
				break;
			case 'T':
				cost = 2;
				break;
			default:
				cost = 1;
				break;
		}
	}
	// Calcula cuanta batería perdería con un giro de 45 º
	else if (action==actTURN_SL || action==actTURN_SR) {
		switch (sensores.terreno[0]){
			case 'A':
				if (wearingBikini)	cost = 5;
				else				cost = 500;
				break;
			case 'B':
				if (wearingShoes)	cost = 1;
				else				cost = 3;
				break;
			case 'T':
				cost = 2;
				break;
			default:
				cost = 1;
				break;
		}
	}
	// Calcula cuanta batería perdería con un giro de 135 º
	else if (action==actTURN_BL || action==actTURN_BR) {
		switch (sensores.terreno[0]){
			case 'A':
				if (wearingBikini)	cost = 5;
				else				cost = 50;
				break;
			case 'B':
				if (wearingShoes)	cost = 1;
				else				cost = 3;
				break;
			case 'T':
				cost = 2;
				break;
			default:
				cost = 1;
				break;
		}
	}
	else
		cost = 0;
	
	return cost;
}

bool ComportamientoJugador::WorthLiving(const Sensores &sensores){
	return wearingBikini || wearingShoes;
}

bool ComportamientoJugador::Recharge(const Sensores &sensores){
	// Nº de veces que la vida batería debe ser mayor que la vida para dejar
	// de esperar en esta casilla
	unsigned int c = 3;

	if (sensores.terreno[0] == 'X')
		if (sensores.bateria < sensores.vida * c && sensores.bateria < MAX_BATTERY)
			return true;
	
	return false;
}

Action ComportamientoJugador::EscapeFromWolves(const Sensores &sensores){
	const unsigned int DANGEROUS_DISTANCE = 3;

	// Si devuelve actIDLE, es porque no hay que escapar
	Action action = actIDLE;

	if (WorthLiving(sensores)){
		unsigned int newDistance = DintaceInViewFromObject(sensores, 'l');

		// Si hay un lobo delante, se gira
		if (newDistance < DANGEROUS_DISTANCE){
			if (rand()%2==0)	action = actTURN_BR;
			else				action = actTURN_BL;

			distanceFromWolves = newDistance;
		}
		// Si en el turno anterior había un lobo detrás, intenta avanzar
		else if (distanceFromWolves < DANGEROUS_DISTANCE){
			if (CanMoveForward(sensores))
				action = actFORWARD;
			distanceFromWolves++;
		}
	}
	else
		distanceFromWolves = FAR;

	return action;
}

//////////////////////////////////////////////////////////
// Métodos públicos
//////////////////////////////////////////////////////////

Action ComportamientoJugador::think(Sensores sensores){
	// ACTUALIZACIÓN

	// Crea la acción
	Action action = actIDLE;

	// Actualizar estado
	UpdateState(sensores);

	// Info debug
	ShowInfo(sensores);

	// Elegimos mapa
	vector<vector<unsigned char>> * map;
	if (wellLocated)	map = & mapaResultado;
	else				map = & mapaAuxiliar;

	// Guardamos la vista en el mapa
	SaveActualView(sensores.terreno, *map);




	// NUEVA ACCIÓN

	// Escapar de los lobos
	action = EscapeFromWolves(sensores);
	if (action != actIDLE && CostOfAction(sensores, action) < LOW_COST)
		return action;
	

	// Esperar en casilla de recarga
	if (Recharge(sensores))
		return actIDLE;

	// Decisión sencilla temporal
	if (CanMoveForward(sensores) && CostOfAction(sensores, actFORWARD) < LOW_COST){
		action = actFORWARD;
	} else{
		if (rand()%2==0)	action = actTURN_BR;
		else				action = actTURN_BL;
	}
	


	// FILANIZACIÓN

	// Recordar la última acción
	last_action = action;
	return action;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

