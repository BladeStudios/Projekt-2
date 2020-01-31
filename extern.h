#pragma once
//DEFINITIONS
//corners
#define ctopleft (char)201
#define ctopright (char)187
#define cbottomleft (char)200
#define cbottomright (char)188

//lines
#define cvertical (char)186
#define chorizontal (char)205

//T-shape corners
#define ctop (char)203
#define cleft (char)204
#define cmiddle (char)206
#define cright (char)185
#define cbottom (char)202

//other symbols
#define square 'X'
#define solid '*'
#define nothing ' '
#define deleted '#'
#define title '@'
//(char)254

//character limit
#define windowWidth 23
#define windowHeight 18

//GLOBAL VARIABLES
extern char tab[windowWidth][windowHeight];
extern char prevtab[windowWidth][windowHeight];
extern bool fin;

//global objects
//extern Block bl;