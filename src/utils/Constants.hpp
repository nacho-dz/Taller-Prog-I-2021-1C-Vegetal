#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MIN_PLAYERS 1
#define MAX_PLAYERS 4

// estadoNivel
#define MAX_PLATFORMS 12
#define MAX_ENEMIES 3
#define MAX_BARRELS 8
#define MAX_HAMMERS 2

// Dimensiones
#define ANCHO_NIVEL 224
#define ALTO_NIVEL 256

#define ANCHO_TILE 16
#define ALTO_TILE 16

#define ANCHO_BARRIL 12
#define ALTO_BARRIL 10

#define ANCHO_ENEMIGO_FUEGO 15
#define ALTO_ENEMIGO_FUEGO 16

#define ANCHO_FUEGO 16
#define ALTO_FUEGO 16

#define ANCHO_PLATAFORMA 16
#define ALTO_PLATAFORMA 8

#define ANCHO_POLEA 11
#define ALTO_POLEA 10

#define ANCHO_MARIO 16
#define ALTO_MARIO 16

#define DONKEYKONG_ANCHO 48
#define DONKEYKONG_ALTO 32

#define PAULINE_POS_X 88
#define PAULINE_POS_Y 34

// Nivel 1
#define N1_POS_X_FUEGO1 48
#define N1_POS_X_FUEGO2 88
#define N1_POS_X_FUEGO3 128
#define N1_POS_X_FUEGO4 168

#define N1_POS_Y_FUEGO 240

#define N1_POS_X1_POLEA 10
#define N1_POS_X2_POLEA 203

#define N1_POS_Y1_POLEA 128
#define N1_POS_Y2_POLEA 168

// Nivel 2
#define N2_POS_X_FUEGO 16
#define N2_POS_Y_FUEGO 216

#define N2_POS_X_BARRIL 20
#define N2_POS_Y_BARRIL 74

// Common
#define MARIO_START_X 0
#define MARIO_START_Y 232

#define DONKEYKONG_POS_X 20
#define DONKEYKONG_POS_Y 52

#define PAULINE_ANCHO 16
#define PAULINE_ALTO 22

#define DEFAULT_CONFIG_X 56
#define DEFAULT_CONFIG_Y 20

#define MARIO_LIVES 3
#define TOP_LEVEL 40.5f

// Login
enum class Login {
  OK,
  ABORTED,
  INVALID_USER_PASS,
  USER_ALREADY_CONNECTED,
  MAX_USERS_CONNECTED,
  INVALID_USER
};

// Config
const char CONFIG_FILE[] = "archivo.json";

#endif// CONSTANTS_H
