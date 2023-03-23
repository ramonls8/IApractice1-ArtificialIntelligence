#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <set>
using namespace std;

struct state{
  int fil, col;
  Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      
      ResetState(size);
      last_action = actIDLE;

      // Crea el mapa auxiliar con suficientes casillas para no salirse
      // nunca de él, aunque no sepamos nuestra posición en el mapa
      unsigned int auxSize = size*2-1;
      vector<unsigned char> aux(auxSize, '?');
      for (unsigned int i=0; i<auxSize; i++)
        mapaAuxiliar.push_back(aux);
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
    // Variables de estado
    state st;
    Action last_action;
    bool wellLocated = false;
    vector<vector<unsigned char>> mapaAuxiliar;
    bool wearingBikini = false;
    bool wearingShoes = false;
    unsigned int distanceFromWolves = FAR;
    unsigned int nextToWall = 0;
    bool isPrecipiceConsideredAsWall = false;

    // Constantes
    const unsigned int LOW_COST = 20;
    const unsigned int MAX_BATTERY = 5000;
    const unsigned int LOW_BATTERY = 1000;
    const unsigned int FAR = 99999;
    const int INVALID_POS = -1;
    const pair<int,int> INVALID_PLACE = {-1,-1};
    const unsigned char NO_ENTITY = '_';


    // Calcula y devuelve una vista del mapa para un estado concreto
    // que no tiene por qué ser el actual
    vector<unsigned char> GetCertainView(state certainSt, vector<vector<unsigned char>> &map);

    // Guarda la vista actual en el mapa
    void SaveActualView(const vector<unsigned char> &view, vector<vector<unsigned char>> &map);

    // Rellena todos los valores de una matriz con el carácter c
    void ResetCharMatrix(vector<vector<unsigned char>> &matrix, char c);

    // Devuelve el estado a los valores por defecto
    void ResetState(unsigned int size);

    // Devuelve si el sensor funciona y puede conocer la posición
    bool SensorIsWorking(const Sensores &sensores);

    // Informa de la posición actual
    void ShowInfo(const Sensores &sensores);

    // Actualiza state tras la última acción
    void UpdateState(const Sensores &sensores);

    // Pasa los datos del mapa temporal al mapa resultado cuando
    // el personaje se ubica
    void TransferMap(const Sensores &sensores);

    // Desvuelve true si un carácter es correspondiente a un personaje y no a una casilla,
    // es decir, aparecería en sensores.superficie y no en sensores.terreno
    bool IsCharacter(unsigned char c);

    // Calcula la distancia a un elemento c en las casillas de la vista actual
    unsigned int DintaceInViewFromObject(const Sensores &sensores, unsigned char c);

    // Calcula la distancia a un elemento en posición p de la vista actual
    unsigned int DintaceInViewFromPlace(unsigned int p);

    // Calcula la distancia del personaje a una posición r,c del mapa
    unsigned int DintaceInMapFromPlace(unsigned int row, unsigned int col);

    /*
    // Devuelve true si puede avanzar hacia delante
    bool CanMoveForward(const Sensores &sensores);
    */

    // Calcula el coste de pasar por una casilla teniendo en cuenta el terreno y la superficie
    // Devuelve FAR si no se puede hacer
    int CostOfPassingBy(unsigned char terrain, unsigned char surface);

    // Calcula el coste que tendrá una acción en el futuro o en este turno,
    // es decir, si se mueve, el coste de la casilla donde llegue, si gira,
    // el coste de girar en la casilla en la que lo hace
    // Devuelve FAR si no se puede hacer
    int CostOfAction(const Sensores &sensores, Action action);

    // Espera en la casilla de recarga para conseguir batería
    bool Recharge(const Sensores &sensores);

    // Devuelve true si tenemos objetos, por lo que no debemos morir
    bool WorthLiving(const Sensores &sensores);

    // Intenta escapar de los lobos. Si devuelve actIDLE, es porque
    // no hay que escapar
    Action EscapeFromWolves(const Sensores &sensores);


    // Devuelve la prioridad para conseguir un objeto, sin tener en cuenta la distancia
    unsigned int PriorityOf(const Sensores & sensores, unsigned char c);

    // Decide el objeto más prioritario en ese momento en la vista
    int PriotityObjectInView(const Sensores &sensores);

    // Decide el objeto más prioritario en ese momento en el mapa
    pair<int,int> PriotityObjectInMap(const Sensores &sensores);

    // Devuelve una acción para ir al objeto más prioritario en la vista.
    // actIDLE si no hay un lugar necesario al que ir.
    Action MoveToBestObjectInView(const Sensores &sensores);

    // Devuelve una acción para ir al objeto más prioritario en el mapa.
    // actIDLE si no hay un lugar necesario al que ir.
    Action MoveToBestObjectInMap(const Sensores &sensores);


    // Devuelve si está atrapado en una zona de agua o bosque.
    bool IsTrapped(const Sensores &sensores);

    // Devuelve una acción para escapar de una zona de agua o bosque.
    // Llamar a la función solo si está atrapado.
    Action EscapeFromZone(const Sensores &sensores);

    // Devuelve si una casilla se considera un muro
    bool IsWall(unsigned char c);

    // Comprueba si debería considerar los precipicios como muros
    void ConsiderPrecipiceAsWall(const Sensores &sensores);

    // Devuelve una acción para recorrer y atravesar un muro
    Action Wall(const Sensores &sensores);

    // Devuelve actFORWARD si puede pasar y si no un giro aleatorio
    Action RandomAction(const Sensores &sensores);
};

#endif
