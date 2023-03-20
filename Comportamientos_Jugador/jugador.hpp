#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
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

    const unsigned int LOW_COST = 20;


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

    // Devuelve true si puede avanzar hacia delante
    bool CanMoveForward(const Sensores &sensores);

    // Calcula el coste que tendrá una acción en el futuro o en este turno,
    // es decir, si se mueve, el coste de la casilla donde llegue, si gira,
    // el coste de girar en la casilla en la que lo hace
    int CostOfAction(const Sensores &sensores, Action action);
};

#endif
