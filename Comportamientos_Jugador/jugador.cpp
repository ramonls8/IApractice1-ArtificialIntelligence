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
	cout << "Fil: " << st.fil << ", Col: " << st.col << ", ";
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

	cout << "Colisión: " << sensores.colision << "    ";
	cout << "Reset: " << sensores.reset << "    ";
	cout << "Vida: " << sensores.vida << "    ";
	cout << "Última acción: " << last_action << endl;

	cout << "Terreno:    ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << endl;
}

void ComportamientoJugador::UpdateState(const Sensores &sensores){
	// Comprobamos si hemos perdido o conseguido objetos
	if (sensores.reset) {wearingBikini = false; wearingShoes = false;}
	else if (sensores.terreno[0] == 'K')		wearingBikini = true;
	else if (sensores.terreno[0] == 'D')		wearingShoes = true;

	// Sabemos la posición gracias a los sensores
	if (SensorIsWorking(sensores)){
		// Acabamos de llegar a una casilla de posicionamiento tras estar desubicados
		if (wellLocated == false){
			wellLocated = true;

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
			// Pasamos el mapa auxiliar a mapa resultado y actualizamos posición en este
			TransferMap(sensores);
			/*
			// Reconstruimos los objetos localizados con los nuevos valores de mapaResultado
			UpdateLocatedObjects(1);
			*/
		}
		/*
		// Seguimos ubicados
		else
			// Actualizamos los objetos localizados con la vista actual
			UpdateLocatedObjects(0);
		*/

		// Actualizamos el estado
		st.fil = sensores.posF;
		st.col = sensores.posC;
		st.brujula = sensores.sentido;
	}
	
	// Hay reset y no estamos ubicados
	else if (sensores.reset){
		wellLocated = false;

		// Como no sabemos donde estamos, reiniciamos el mapa auxiliar y el estado
		ResetCharMatrix(mapaAuxiliar);
		ResetState(mapaResultado.size());
	}

	// No hay reset y no estamos ubicados, por lo que tenemos en cuenta last_action
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

/*
bool ComportamientoJugador::CanMoveForward(const Sensores &sensores){
	bool canMoveForward = true;

	if (sensores.terreno[2] == 'P' || sensores.terreno[2] == 'M' ||
		sensores.superficie[2] != NO_ENTITY)
		canMoveForward = false;

	return canMoveForward;
}
*/

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

unsigned int ComportamientoJugador::DintaceInViewFromPlace(unsigned int p){
	unsigned int distance;

	if (p==0)				distance = 0;
	else if (1<=p && p<=3)	distance = 1;
	else if (4<=p && p<=8)	distance = 2;
	else if (9<=p && p<=15)	distance = 3;
	else					distance = FAR;

	return distance;
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

int ComportamientoJugador::CostOfPassingBy(unsigned char terrain, unsigned char surface){
	int cost = 1;

	// Si hay una entidad no puede pasar
	if (surface != NO_ENTITY)
		return FAR;

	// Calcula cuanta batería perdería debido al terreno
	switch (terrain){
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
		case 'M': case 'P':
			cost = FAR;
			break;
		default:
			cost = 1;
			break;
	}

	return cost;
}

int ComportamientoJugador::CostOfAction(const Sensores &sensores, Action action){
	int cost = 1;

	// Calcula cuanta batería perdería debido a la siguiente casilla
	if (action == actFORWARD){
		cost = CostOfPassingBy(sensores.terreno[2], sensores.superficie[2]);
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
	const unsigned int C = 3;

	if (sensores.terreno[0] == 'X')
		if (sensores.bateria < sensores.vida * C && sensores.bateria < MAX_BATTERY-10)
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
			if (CostOfAction(sensores, actFORWARD) < LOW_COST)
				action = actFORWARD;
			distanceFromWolves++;
		}
	}
	else
		distanceFromWolves = FAR;

	return action;
}

unsigned int ComportamientoJugador::PriorityOf(const Sensores & sensores, unsigned char c){
	const unsigned int C = 2;
	// Devuelve la prioridad para conseguir un objeto, sin tener en cuenta la distancia
	unsigned int priority;

	switch (c){
		case 'G':	// Posicionamiento
			priority = (wellLocated) ? FAR : 0;
			break;
		case 'K':	// Bikini
			priority = (wearingBikini) ? FAR : 2;
			break;
		case 'D':	// Zapatillas
			priority = (wearingShoes) ? FAR : 2;
			break;
		case 'X':	// Recarga
			priority = (sensores.bateria<LOW_BATTERY && sensores.bateria<C*sensores.vida) ? 2 : FAR;
			break;
		default:	// Otros
			priority = FAR;
			break;
	}

	return priority;
}

int ComportamientoJugador::PriotityObjectInView(const Sensores &sensores){
	int bestObj, bestObjPriotity = FAR;

	// Busca el objeto con menor prioridad
	for (unsigned int i=1; i<16; i++){
		// Suma la prioridad del objeto y la distancia
		int objPriotity = PriorityOf(sensores, sensores.terreno[i]) + DintaceInViewFromPlace(i);

		// Se queda el objeto más prioritario hasta ahora
		if (objPriotity < bestObjPriotity){
			bestObj = i;
			bestObjPriotity = objPriotity;
		}
	}

	// Solo devuelve el objeto si tiene una prioridad aceptable
	if (bestObjPriotity >= FAR)
		bestObj = INVALID_POS;
	
	return bestObj;
}

pair<int,int> ComportamientoJugador::PriotityObjectInMap(const Sensores &sensores){
	pair<int,int> bestObj;
	int bestObjPriotity = FAR;
	unsigned int size = mapaResultado.size();

	// Busca el objeto con menor prioridad
	for (unsigned int i=0; i<size; i++)
		for (unsigned int j=0; j<size; j++){
			// Suma la prioridad del objeto y la distancia
			int objPriotity = PriorityOf(sensores, mapaResultado[i][j]) + DintaceInMapFromPlace(i,j);

			// Se queda el objeto más prioritario hasta ahora
			if (objPriotity < bestObjPriotity){
				bestObj = {i,j};
				bestObjPriotity = objPriotity;
			}
		}

	// Solo devuelve el objeto si tiene una prioridad aceptable
	if (bestObjPriotity >= FAR)
		bestObj = INVALID_PLACE;
	
	return bestObj;
}

Action ComportamientoJugador::MoveToBestObjectInView(const Sensores &sensores){
	int obj = PriotityObjectInView(sensores);
	Action action = actIDLE;

	// Comprueba que hay un objeto al que ir
	if (obj == INVALID_POS || obj == 0)
		return actIDLE;
	
	// Comprueba donde está el objeto
	switch (obj){
		// Parte izquierda
		case 1: case 4: case 9:
			action = actTURN_SL;
			break;
		// Parte derecha
		case 3: case 8: case 15:
			action = actTURN_SR;
			break;
		// Frente
		default:
			action = actFORWARD;
			break;
	}

	// Si no puede girar, intenta avanzar
	if (action==actTURN_SL)
		if (!(CostOfAction(sensores, action) < LOW_COST && CostOfPassingBy(sensores.terreno[1],NO_ENTITY) < LOW_COST))
			action = actFORWARD;
	
	if (action==actTURN_SR)
		if (!(CostOfAction(sensores, action) < LOW_COST && CostOfPassingBy(sensores.terreno[3],NO_ENTITY) < LOW_COST))
			action = actFORWARD;
	
	// Comprueba si puede avanzar
	if (!(CostOfAction(sensores, action) < LOW_COST))
		action = actIDLE;

	return action;
}

Action ComportamientoJugador::MoveToBestObjectInMap(const Sensores &sensores){
	pair<int,int> obj = PriotityObjectInMap(sensores);

	// Comprueba que hay un objeto al que ir
	if (obj == INVALID_PLACE)
		return actIDLE;

	// Gira si obj está en otro lado o avanza si está lejos y enfrente. Debe comprobar
	// que puede ir hasta él en la línea recta aproximada que los conecta por el mapa

	// ------ Método sin implementar, puede que no sea necesario ------

	return actIDLE;
}


bool ComportamientoJugador::IsTrapped(const Sensores &sensores){
	return CostOfPassingBy(sensores.terreno[2], NO_ENTITY) > LOW_COST;
}

Action ComportamientoJugador::EscapeFromZone(const Sensores &sensores){
	// Tiempo que lleva en la misma posición
	static pair<int, int> place = INVALID_PLACE;
	static int timeInSamePlace = 1;


	// Actualiza la posición y el tiempo que lleva en ella
	pair<int, int> newPlace = {st.fil, st.col};
	if (place == newPlace)
		timeInSamePlace++;
	else{
		place = newPlace;
		timeInSamePlace = 1;
	}

	// Rotaciones y máximo de veces que lo hará
	Action rotate = (rand()%2) ? actTURN_BL : actTURN_BR;
	const unsigned int MAXTIME = 3;

/*
	// Intenta pasar por la izq o la der
	if (CostOfPassingBy(sensores.terreno[1],NO_ENTITY) < LOW_COST)
		return actTURN_SL;
	if (CostOfPassingBy(sensores.terreno[3],NO_ENTITY) < LOW_COST)
		return actTURN_SR;
*/
	// Si ha pasado el límite de rotaciones en la misma casilla, intenta avanzar aunque tenga coste alto
	if (timeInSamePlace > MAXTIME && CostOfAction(sensores, actFORWARD) < FAR)
		return actFORWARD;

	// Si no ha pasado el límite de rotaciones, intenta rotar con coste bajo
	if (CostOfAction(sensores, rotate) < LOW_COST && timeInSamePlace < MAXTIME)
		return rotate;
	
	// Intenta salir si hay salida tras atravesar una zona con alto coste
	if (CostOfPassingBy(sensores.terreno[5], NO_ENTITY) < LOW_COST ||
		CostOfPassingBy(sensores.terreno[6], NO_ENTITY) < LOW_COST ||
		CostOfPassingBy(sensores.terreno[7], NO_ENTITY) < LOW_COST)
		return actFORWARD;
	
	// Intenta salir si hay salida tras atravesar dos zonas con alto coste
	if ((CostOfPassingBy(sensores.terreno[11], NO_ENTITY) < LOW_COST ||
		CostOfPassingBy(sensores.terreno[12], NO_ENTITY) < LOW_COST ||
		CostOfPassingBy(sensores.terreno[13], NO_ENTITY) < LOW_COST) &&
		CostOfPassingBy(sensores.terreno[6], NO_ENTITY) < FAR)
		return actFORWARD;
	
	// En otro caso, intenta rotar aunque tenga coste alto
	return rotate;
}

bool ComportamientoJugador::IsWall(unsigned char c){
	if (isPrecipiceConsideredAsWall)
		return c == 'M' || c == 'P';
	else
		return c == 'M';
}

void ComportamientoJugador::ConsiderPrecipiceAsWall(const Sensores &sensores){
	const unsigned int CERTAIN_LIFE = 2500;

	if (sensores.vida < CERTAIN_LIFE)
		if (sensores.terreno[2]=='P' && sensores.terreno[3]=='P' && sensores.terreno[4]=='P'
			&& (sensores.terreno[5]!='P' || sensores.terreno[6]!='P' || sensores.terreno[7]!='P'))
			isPrecipiceConsideredAsWall = true;
}

Action ComportamientoJugador::Wall(const Sensores &sensores){
	// El muro está a la izq o a la der
	static bool left = true;

	// Pasos para atravesar muro
	const unsigned int STEPS_NUMBER = 3;

	// Entra en el espacio abierto del muro
	if (nextToWall > 0 && nextToWall < STEPS_NUMBER && CostOfPassingBy(sensores.terreno[2],NO_ENTITY)<LOW_COST){
		nextToWall--;
		return actFORWARD;
	}

	// Comprueba si no hay muro
	else if (nextToWall==0 && !IsWall(sensores.terreno[1]) && !IsWall(sensores.terreno[2]) && !IsWall(sensores.terreno[3]))
		return actIDLE;
	
	// Si el muro está delante, gira hacia donde se puede pasar,
	// si no gira al lado contrario del muro que estaba recorriendo
	else if (IsWall(sensores.terreno[2])){
		if (CostOfPassingBy(sensores.terreno[1],NO_ENTITY) < LOW_COST)
			return actTURN_SL;
		else if (CostOfPassingBy(sensores.terreno[3],NO_ENTITY) < LOW_COST)
			return actTURN_SR;
		else if (left)
			return (rand()%2) ? actTURN_BR : actTURN_SR;
		else
			return (rand()%2) ? actTURN_BL : actTURN_SL;
	}

	// Si tiene muro a la izq y puede avanzar
	else if (IsWall(sensores.terreno[1]) && CostOfPassingBy(sensores.terreno[2],NO_ENTITY) < LOW_COST){
		nextToWall = STEPS_NUMBER;
		left = true;
		return actFORWARD;
	}

	// Si tiene muro a la der y puede avanzar
	else if (IsWall(sensores.terreno[3]) && CostOfPassingBy(sensores.terreno[2],NO_ENTITY) < LOW_COST){
		nextToWall = STEPS_NUMBER;
		left = false;
		return actFORWARD;
	}

	// Gira para entrar en el espacio abierto del muro
	else if (nextToWall == STEPS_NUMBER){
		nextToWall--;
		return (left) ? actTURN_SL : actTURN_SR;
	}
	
	// No puede avanzar por alguna razón, gira 135º aleatoreamente
	return (rand()%2) ? actTURN_BL : actTURN_BR;
}

//////////////////////////////////////////////////////////
// Métodos públicos
//////////////////////////////////////////////////////////

Action ComportamientoJugador::think(Sensores sensores){
	////// ACTUALIZACIÓN //////

	// Crea la acción
	Action action = actIDLE;
	bool actionDetermined = false;

	// Actualizar estado
	UpdateState(sensores);

	// Info debug
	ShowInfo(sensores);

	// Elegimos mapa
	vector<vector<unsigned char>> * map;
	if (wellLocated)		map = & mapaResultado;
	else					map = & mapaAuxiliar;

	// Guardamos la vista en el mapa
	SaveActualView(sensores.terreno, *map);



	////// NUEVA ACCIÓN //////

	// Escapa de los lobos
	action = EscapeFromWolves(sensores);
	if (action != actIDLE && CostOfAction(sensores, action) < LOW_COST)
		actionDetermined = true;
	
	// Espera en casilla de recarga
	if (!actionDetermined)
		if (Recharge(sensores)){
			action = actIDLE;
			actionDetermined = true;
		}
			

	// Busca el objeto más prioritario en la vista, y si no ve nada, en el mapa
	if (!actionDetermined){
		action = MoveToBestObjectInView(sensores);
		//if (wellLocated && action==actIDLE)
		//	action = MoveToBestObjectInMap(sensores);
		if (action != actIDLE)
			actionDetermined = true;
	}

	// Comprueba si debería considerar los precipicios como muros
	//ConsiderPrecipiceAsWall(sensores);
	// Muros
	if (!actionDetermined){
		action = Wall(sensores);
		if (action != actIDLE)
			actionDetermined = true;
	}
	else
		nextToWall = 0;

	// Si está atrapado en bosque o agua sin objetos, intenta salir
	if (!actionDetermined && IsTrapped(sensores)){
		action = EscapeFromZone(sensores);
		actionDetermined = true;
	}

	// Busca lugares del mapa sin descubrir
	if (!actionDetermined){

	}
	

	// Decisión aleatoria
	if (!actionDetermined){
		if (CostOfAction(sensores, actFORWARD) < LOW_COST)
			action = actFORWARD;
		else{
			int n = rand()%4;
			switch (n){
				case 0:		action = actTURN_SR;	break;
				case 1:		action = actTURN_SL;	break;
				case 2:		action = actTURN_BL;	break;
				case 3:		action = actTURN_BR;	break;
			}
		}
		actionDetermined = true;
	}
	


	////// FILANIZACIÓN //////

	// Si hay una entidad delante y quiere avanzar, no podrá
	if (action==actFORWARD && CostOfPassingBy(sensores.terreno[2],sensores.superficie[2]) == FAR)
		action = (rand()%2) ? actTURN_BL : actTURN_BR;

	// Recordar la última acción
	last_action = action;
	return action;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

