

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


									//NEW// Keyframes
									//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0, rotBrIzq = 0, rotBrDer = 0, rotRodDer = 0;
float giroMonito = 0;

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;
int juego;
int juego1 = 0;
int mundo;

float arriba = 0.0;
float  arribaInc = 0;
float horizontal = 0;
float vertical = 0;
float profundidad = 0;
float giro = 0;
float giroInc = 0;
float giro2 = 0;
float horizontal2 = 0;
float vertical2 = 1.24;
float descenso = -25;
float sigue = 0;

bool rot_rueda = true;


typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float rotBrIzq;
	float rotInc2;
	float rotBrDer;
	float rotRodDer;
	float rotInc4;
	float rotInc3;

	float giroMonito;
	float giroMonitoInc;

	//montaña rusa
	float arriba = 0;
	float horizontal = 0;
	float vertical = 1.24;
	float profundidad = -25;
	float giro = 0;
	float giro2 = 0;
	float horizontal2 = 0;
	float vertical2 = 1.24;
	float descenso = -25;
	float sigue = 0;

	float arribaInc = 0.0;
	float horizontalInc = 0;
	float verticalInc = 0;
	float profundidadInc = 0;
	float giroInc = 0;
	float giro2Inc = 0;
	float horizontal2Inc = 0;
	float vertical2Inc = 0;
	float descensoInc = 0;
	float sigueInc = 0;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 20;			//introducir datos
bool play = false;
int playIndex = 0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 1, 1, 1, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Piso
CTexture text6;	//Casa01
CTexture text7;//torre roja
CTexture text8;//torre blanca
CTexture text9;//torre azul
CTexture text10;//torre azul
CTexture text11;// estrellas
CTexture text12;//cadenas
CTexture text13;//silla amarilla

CTexture text14;
CTexture text15;
CTexture text16;
CTexture text17;
CTexture text18;
CTexture text19;
CTexture text20;
CTexture text21;
CTexture text22;
CTexture text23;
CTexture text24;
CTexture text25;
CTexture text26;

//NEW///////////////////////////7


float abrirPuerta = 0;
//END NEW//////////////////////////////////////////

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Piso
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito
CFiguras fig8;//torre roja
CFiguras fig9;//torre blanca
CFiguras fig10;//torre azul
CFiguras fig11;//estrellas
CFiguras fig12;//cadenas
CFiguras fig13;//silla amarilla

CFiguras fig14;
CFiguras fig15;
CFiguras fig16;
CFiguras fig17;
CFiguras fig18;
CFiguras fig19;
CFiguras fig20;
CFiguras fig21;
CFiguras fig22;
CFiguras fig23;
CFiguras fig24;
CFiguras fig25;
void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].rotBrIzq = rotBrIzq;
	KeyFrame[FrameIndex].rotBrDer = rotBrDer;
	KeyFrame[FrameIndex].rotRodDer = rotBrDer;
	KeyFrame[FrameIndex].giroMonito = giroMonito;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotBrIzq = KeyFrame[0].rotBrIzq;
	rotBrDer = KeyFrame[0].rotBrDer;
	rotRodDer = KeyFrame[0].rotRodDer;
	giroMonito = KeyFrame[0].giroMonito;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotBrIzq - KeyFrame[playIndex].rotBrIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBrDer - KeyFrame[playIndex].rotBrDer) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}

void montana(void) {

	glPushMatrix();

	//rieles horizontales
	glPushMatrix();
	glTranslatef(-25, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-22, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-21, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-18, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-17, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-12, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-11, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-10, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-9, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-8, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-7, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-6, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-5, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-4, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-3, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-2, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(2, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(3, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(4, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(6, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(7, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(8, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(9, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(10, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(11, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(12, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(13, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(19, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(21, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(22, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, 1, 0);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();
	//hacia atras

	glPushMatrix();
	glTranslatef(26.3, 1, -2);
	glRotatef(0, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -3);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -4);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -5);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -6);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -7);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -8);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -9);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -10);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -11);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -12);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -13);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -14);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.3, 1, -15);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	//hacia atras recto izquierda
	glPushMatrix();
	glTranslatef(25, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(24, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(22, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(21, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(19, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(18, 1, -17.56);
	glRotatef(90, 0, 1, 0);

	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	//rieles largos
	glPushMatrix();
	glTranslatef(0, 1, .4);
	glScalef(50, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, -.4);
	glScalef(50, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.86, 1, -8.8);
	glRotatef(90, 0, 1, 0);
	glScalef(15, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.7, 1, -8.8);
	glRotatef(90, 0, 1, 0);
	glScalef(15, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	//rieles de atras
	glPushMatrix();
	glTranslatef(21.5, 1, -18);
	glScalef(7, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(21.5, 1, -17.15);
	glScalef(7, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	//rieles de atras hacia arriba
	glPushMatrix();

	glPushMatrix();
	glTranslatef(17.6, 1.3, -18);
	glRotatef(-40, 0, 0, 1);
	glScalef(1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17.6, 1.3, -17.15);
	glRotatef(-40, 0, 0, 1);
	glScalef(1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12.98, 8.96, -18);
	glRotatef(-60, 0, 0, 1);
	glScalef(17, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12.98, 8.96, -17.15);
	glRotatef(-60, 0, 0, 1);
	glScalef(17, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17, 2, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 3.7, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14.9, 5.7, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13, 8.9, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 10.7, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11, 12.4, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 14.1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9, 15.8, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPopMatrix();//hacia arriba fin
				  //descenso

	glPushMatrix();

	glPushMatrix();
	glTranslatef(2, 8.96, -18);
	glRotatef(60, 0, 0, 1);
	glScalef(17, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 8.96, -17.15);
	glRotatef(60, 0, 0, 1);
	glScalef(17, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.67, 16.6, -17.15);
	glRotatef(35, 0, 0, 1);
	glScalef(1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.67, 16.6, -18);
	glRotatef(35, 0, 0, 1);
	glScalef(1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.46, 16.9, -17.15);
	glScalef(.8, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.46, 16.9, -18);
	glScalef(.8, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-35, 0, 0, 1);
	glTranslatef(-2.75, 18.4, -17.15);
	glScalef(1.1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-35, 0, 0, 1);
	glTranslatef(-2.75, 18.4, -18);
	glScalef(1.1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 16.8, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, 16.8, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 15.8, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 14.2, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 12.4, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, 10.6, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, 8.9, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 7.3, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5.56, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 3.8, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, 2, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-4, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-5, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-6, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-7, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-8, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-9, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-10, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-11, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-12, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-13, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-14, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-15, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-17, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-18, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-19, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-20, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-21, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-22, 1, -17.56);
	glRotatef(90, 0, 1, 0);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -1);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -2);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -3);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -4);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -5);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -6);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -7);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -8);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -9);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -10);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -11);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -12);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -13);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -14);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -15);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23.3, 1, -16);
	glScalef(.9, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPopMatrix();//aqui termina el descenso

				  //rieles atras despues del descenso
	glPushMatrix();

	glPushMatrix();
	glTranslatef(-2.63, 1.3, -18);
	glRotatef(40, 0, 0, 1);
	glScalef(1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.63, 1.3, -17.15);
	glRotatef(40, 0, 0, 1);
	glScalef(1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12.5, 1, -18);
	glScalef(19, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12.5, 1, -17.15);
	glScalef(19, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();
	glPopMatrix();//recta despues del descenso

	glPushMatrix();//giro despues del descenso
	glTranslatef(3, 0, -17.58);
	glRotatef(180, 0, 1, 0);


	glPushMatrix();
	glTranslatef(25.26, 1, .31);
	glRotatef(20, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.2, 1, -.5);
	glRotatef(20, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.65, 1, .1);
	glRotatef(35, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.6, 1, -.75);
	glRotatef(45, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26, 1, -.2);
	glRotatef(50, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.8, 1, -1.11);
	glRotatef(75, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.45, 1, -.86);
	glRotatef(60, 0, 1, 0);
	glScalef(1.1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();



	glPopMatrix();

	//aqui termine el giro

	//hacia atras despues del giro de descenso

	//rieles de atras

	glPushMatrix();
	glTranslatef(-23.7, 1, -8.4);
	glRotatef(90, 0, 1, 0);
	glScalef(16, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-22.85, 1, -8.4);
	glRotatef(90, 0, 1, 0);
	glScalef(16, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();


	glPushMatrix();//giro
	glPushMatrix();
	glTranslatef(25.26, 1, .31);
	glRotatef(20, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.2, 1, -.5);
	glRotatef(20, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.65, 1, .1);
	glRotatef(35, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.6, 1, -.75);
	glRotatef(45, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26, 1, -.2);
	glRotatef(50, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.8, 1, -1.11);
	glRotatef(75, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.45, 1, -.86);
	glRotatef(60, 0, 1, 0);
	glScalef(1.1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();



	glPopMatrix();

	//aqui termine el giro

	glPushMatrix();//giro
	glTranslatef(26.3, 0, 8.7);
	glRotatef(90, 0, 1, 0);


	glPushMatrix();
	glTranslatef(25.26, 1, .31);
	glRotatef(20, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.2, 1, -.5);
	glRotatef(20, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.65, 1, .1);
	glRotatef(35, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.6, 1, -.75);
	glRotatef(45, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26, 1, -.2);
	glRotatef(50, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25.8, 1, -1.11);
	glRotatef(75, 0, 1, 0);
	glScalef(.5, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.45, 1, -.86);
	glRotatef(60, 0, 1, 0);
	glScalef(1.1, .1, .1);
	fig11.prisma3(text9.GLindex, text9.GLindex);
	glPopMatrix();



	glPopMatrix();

	//aqui termine el giro





	//soportes
	glPushMatrix();
	glTranslatef(0, 0, -.4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, .4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, -.4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, .4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, -.4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, 0, .4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(23, 0, -.4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23, 0, .4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23, 0, -.4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-23, 0, .4);
	fig10.cilindro(.1, 1, 100, text8.GLindex);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.6, 0, -2);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26, 0, -2);
	fig10.cilindro(.1, 1, 100, text8.GLindex);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(26.6, 0, -11);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(26, 0, -11);
	fig10.cilindro(.1, 1, 100, text8.GLindex);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(16, 0, -18);
	fig10.cilindro(.1, 3.7, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0, -17.2);
	fig10.cilindro(.1, 3.7, 100, text8.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(14, 0, -18);
	fig10.cilindro(.1, 7, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, 0, -17.2);
	fig10.cilindro(.1, 7, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 0, -18);
	fig10.cilindro(.1, 17, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 0, -17.2);
	fig10.cilindro(.1, 17, 100, text8.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(4, 0, -18);
	fig10.cilindro(.1, 12, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 0, -17.2);
	fig10.cilindro(.1, 12, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 0, -18);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 0, -17.2);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7, 0, -18);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7, 0, -17.2);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, -18);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-15, 0, -17.2);
	fig10.cilindro(.1, 1, 100, text8.GLindex);
	glPopMatrix();

	glPopMatrix();
}

void carrito(void) {

	glPushMatrix();


	glPopMatrix();
	glPushMatrix();
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	fig8.prisma2(text25.GLindex, text7.GLindex);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();





	glPopMatrix();

}

void parque()
{

	glPushMatrix(); //Camino1
	glTranslatef(0, 0.0, 0.0);
	glScalef(200, 0.1, 200);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//INICIA
	//camino 1

	glPushMatrix();
	glTranslatef(0, 0.1, -20);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 0.0);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, -4);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, -8);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, -12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, -16);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 4);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 8);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//camino 2 i<quierda 

	glPushMatrix();
	glTranslatef(4, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//camino 2 derecha 

	glPushMatrix();
	glTranslatef(-4, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 12);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Camino paralelo derecho 

	glPushMatrix();
	glTranslatef(-16, 0.1, 16);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 20);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 24);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 28);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 32);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 36);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 40);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 44);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//camino lateral izquierdo 
	glPushMatrix();
	glTranslatef(16, 0.1, 16);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 20);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 24);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 28);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 32);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 36);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 40);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 44);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//UNION DE CARRILES PARALELOS 

	glPushMatrix();
	glTranslatef(12, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4, 0.1, 48);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//CAMINO SKY SCREAMER JUEGO 3

	glPushMatrix();
	glTranslatef(0, 0.1, 52);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 56);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 60);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.1, 64);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//CAMINO DIVISORIO JUEGO 1 Y 2

	glPushMatrix();
	glTranslatef(-20, 0.1, 24);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24, 0.1, 24);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, 0.1, 24);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-32, 0.1, 24);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-20, 0.1, 24);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//AREA PARA LA MONTAÑA RUSA 
	glPushMatrix();
	glTranslatef(-34, 0.1, 40);
	glScalef(25, 0.1, 25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//AREA PARA JUEGO 1


//CAMINO DIVISORIO JUEGO 4 Y 5

	glPushMatrix();
	glTranslatef(24, 0.1, 30);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(28, 0.1, 30);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(32, 0.1, 30);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(36, 0.1, 30);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 0.1, 30);
	glScalef(4, 0.1, 4);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//AREA JUEGO 4

	glPushMatrix();
	glTranslatef(24, 0.1, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();




}

void tienda1(void)
{
	//piso 
	glPushMatrix();
	glTranslatef(8, 0.1, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig19.prisma3(text18.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared atras
	glPushMatrix();
	glTranslatef(3, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig17.prisma2(text19.GLindex, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//fachada
	glPushMatrix();
	glTranslatef(13, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig17.prisma2(text20.GLindex, text20.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral 
	glPushMatrix();
	glTranslatef(8, 2.5, 25);
	glRotatef(90, 0, 0, 1);
	glScalef(5, 10, 0.1);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral
	glPushMatrix();
	glTranslatef(8, 2.5, 15);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 5, 10);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//techo
	glPushMatrix();
	glTranslatef(8, 5, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig20.prisma3(text21.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void tienda2(void)
{
	glTranslatef(0, 0.1, 20);
	glPushMatrix();
	//piso 
	glPushMatrix();
	glTranslatef(8, 0.1, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig19.prisma3(text18.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared atras
	glPushMatrix();
	glTranslatef(3, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig17.prisma2(text19.GLindex, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//fachada
	glPushMatrix();
	glTranslatef(13, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig21.prisma2(text22.GLindex, text22.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral 
	glPushMatrix();
	glTranslatef(8, 2.5, 25);
	glRotatef(90, 0, 0, 1);
	glScalef(5, 10, 0.1);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral
	glPushMatrix();
	glTranslatef(8, 2.5, 15);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 5, 10);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//techo
	glPushMatrix();
	glTranslatef(8, 5, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig20.prisma3(text21.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPopMatrix();
}

void baños(void)
{
	glTranslatef(0, 0.1, 20);
	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	//piso 
	glPushMatrix();
	glTranslatef(8, 0.1, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig19.prisma3(text18.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared atras
	glPushMatrix();
	glTranslatef(3, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig17.prisma2(text19.GLindex, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//fachada
	glPushMatrix();
	glTranslatef(13, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig22.prisma2(text23.GLindex, text23.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral 
	glPushMatrix();
	glTranslatef(8, 2.5, 25);
	glRotatef(90, 0, 0, 1);
	glScalef(5, 10, 0.1);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral
	glPushMatrix();
	glTranslatef(8, 2.5, 15);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 5, 10);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//techo
	glPushMatrix();
	glTranslatef(8, 5, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig20.prisma3(text21.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPopMatrix();
}

void tienda3(void)
{
	glTranslatef(0, 0.1, -20);
	glRotatef(360, 0, 1, 0);
	glPushMatrix();
	//piso 
	glPushMatrix();
	glTranslatef(8, 0.1, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig19.prisma3(text18.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared atras
	glPushMatrix();
	glTranslatef(3, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig17.prisma2(text19.GLindex, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//fachada
	glPushMatrix();
	glTranslatef(13, 2.5, 20);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glScalef(10, 0.1, 5);
	glDisable(GL_LIGHTING);
	fig23.prisma3(text24.GLindex, text24.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral 
	glPushMatrix();
	glTranslatef(8, 2.5, 25);
	glRotatef(90, 0, 0, 1);
	glScalef(5, 10, 0.1);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//pared lateral
	glPushMatrix();
	glTranslatef(8, 2.5, 15);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 5, 10);
	glDisable(GL_LIGHTING);
	fig18.prisma3(0, text19.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//techo
	glPushMatrix();
	glTranslatef(8, 5, 20);
	glScalef(10, 0.1, 10);
	glDisable(GL_LIGHTING);
	fig20.prisma3(text21.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPopMatrix();
}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	fig7.prisma(2.0, 2.0, 1, text2.GLindex);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	fig7.cilindro(0.25, 0.25, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	fig7.esfera(0.75, 15, 15, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho-->
	glTranslatef(1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(-45, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <--
	glTranslatef(-1.25, 0.65, 0);
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(45, 0, 1, 0);
	glRotatef(25, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glTranslatef(-0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(0, -1.5, 0);
	fig7.prisma(1, 2, 1, 0);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + rotRodIzq, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}



GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	parque();

	//monito();
	// endList
	glEndList();

	return(ciudadDL);
}

void rueda_fortuna(void) {
	glPushMatrix();//rueda
	glScalef(2,2,2);
	glTranslatef(0.0,0.0,35);
	glPushMatrix();//centro_rueda
			glTranslatef(0.0, 7.0,1.5);
			glRotatef(90,0,1,0);
			if (rot_rueda)
			{
				glRotatef(juego, 1, 0, 0);
			}
			glScalef(3, .5, .5);
			fig3.prisma2(text7.GLindex, text7.GLindex);
			glScalef(.333,2,2);
			glRotatef(-90, 0, 1, 0);
			glTranslatef(0.0, -7.0, -1.5);
			glPushMatrix();//rueda1
				glPushMatrix();
					glTranslatef(0.0,3.0, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(115, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();//POSTE_UNION_RUEDAS
					glTranslatef(4.5, 7.0, 1.5);
					glRotatef(90, 0, 1, 0);
					glScalef(3, .5, .5);
					if (rot_rueda)
					{
						glRotatef(-juego, 1, 0, 0);
					}
					
					fig3.prisma2(text7.GLindex, text7.GLindex);
					glScalef(.333, 2, 2);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0.0,-0.5,0.0);
					glScalef(.1, 1, .1);
					fig3.prisma2(text7.GLindex, text12.GLindex);
					glScalef(10, 1, 10);
					glTranslatef(0.0,-1.0,0.0);
					glScalef(1.5, 1, 1);
					fig8.prisma2(text25.GLindex, text13.GLindex);


				glPopMatrix();//fIN_POSTE_UNION_RUEDAS

				glPushMatrix();
					glTranslatef(3.5, 5.0, 0.0);
					glRotatef(60,0.0,0.0,1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(115, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);

				glPopMatrix();

				glPushMatrix();//POSTE_UNION_RUEDAS
					glTranslatef(2.3, 11.0, 1.5);
					glRotatef(90, 0, 1, 0);
					glScalef(3, .5, .5);
					if (rot_rueda)
					{
						glRotatef(-juego, 1, 0, 0);
					}
					fig3.prisma2(text7.GLindex, text7.GLindex);
					glScalef(.333, 2, 2);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0.0, -0.5, 0.0);
					glScalef(.1, 1, .1);
					fig3.prisma2(text7.GLindex, text12.GLindex);
					glScalef(10, 1, 10);
					glTranslatef(0.0, -1.0, 0.0);
					glScalef(1.5, 1, 1);
					fig8.prisma2(text25.GLindex, text13.GLindex);
				glPopMatrix();//fIN_POSTE_UNION_RUEDAS

				glPushMatrix();
					glTranslatef(3.5, 9.0, 0.0);
					glRotatef(120, 0.0, 0.0, 1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(115, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();//POSTE_UNION_RUEDAS
					glTranslatef(-2.3, 11.0, 1.5);
					glRotatef(90, 0, 1, 0);
					glScalef(3, .5, .5);
					if (rot_rueda)
					{
						glRotatef(-juego, 1, 0, 0);
					}
					fig3.prisma2(text7.GLindex, text7.GLindex);
					glScalef(.333, 2, 2);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0.0, -0.5, 0.0);
					glScalef(.1, 1, .1);
					fig3.prisma2(text7.GLindex, text12.GLindex);
					glScalef(10, 1, 10);
					glTranslatef(0.0, -1.0, 0.0);
					glScalef(1.5, 1, 1);
					fig8.prisma2(text25.GLindex, text13.GLindex);
				glPopMatrix();//fIN_POSTE_UNION_RUEDAS

				glPushMatrix();
					glTranslatef(0.0, 11.0, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(-65, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();//POSTE_UNION_RUEDAS
					glTranslatef(-4.5, 7.0, 1.5);
					glRotatef(90, 0, 1, 0);
					glScalef(3, .5, .5);
					if (rot_rueda)
					{
						glRotatef(-juego, 1, 0, 0);
					}
					fig3.prisma2(text7.GLindex, text7.GLindex);
					glScalef(.333, 2, 2);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0.0, -0.5, 0.0);
					glScalef(.1, 1, .1);
					fig3.prisma2(text7.GLindex, text12.GLindex);
					glScalef(10, 1, 10);
					glTranslatef(0.0, -1.0, 0.0);
					glScalef(1.5, 1, 1);
					fig8.prisma2(text25.GLindex, text13.GLindex);
				glPopMatrix();//fIN_POSTE_UNION_RUEDAS

				glPushMatrix();
					glTranslatef(-3.5, 9.0, 0.0);
					glRotatef(60, 0.0, 0.0, 1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(-65, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();//POSTE_UNION_RUEDAS
					glTranslatef(-2.3, 3.0, 1.5);
					glRotatef(90, 0, 1, 0);
					glScalef(3, .5, .5);
					if (rot_rueda)
					{
						glRotatef(-juego, 1, 0, 0);
					}
					fig3.prisma2(text7.GLindex, text7.GLindex);
					glScalef(.333, 2, 2);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0.0, -0.5, 0.0);
					glScalef(.1, 1, .1);
					fig3.prisma2(text7.GLindex, text12.GLindex);
					glScalef(10, 1, 10);
					glTranslatef(0.0, -1.0, 0.0);
					glScalef(1.5, 1, 1);
					fig8.prisma2(text25.GLindex, text13.GLindex);
				glPopMatrix();//fIN_POSTE_UNION_RUEDAS

				glPushMatrix();
					glTranslatef(-3.5, 5.0, 0.0);
					glRotatef(120, 0.0, 0.0, 1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(-65, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();//POSTE_UNION_RUEDAS
					glTranslatef(2.3, 3.0, 1.5);
					glRotatef(90, 0, 1, 0);
					glScalef(3, .5, .5);
					if (rot_rueda)
					{
						glRotatef(-juego, 1, 0, 0);
					}
					fig3.prisma2(text7.GLindex, text7.GLindex);
					glScalef(.333, 2, 2);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0.0, -0.5, 0.0);
					glScalef(.1, 1, .1);
					fig3.prisma2(text7.GLindex, text12.GLindex);
					glScalef(10, 1, 10);
					glTranslatef(0.0, -1.0, 0.0);
					glScalef(1.5, 1, 1);
					fig8.prisma2(text25.GLindex, text13.GLindex);
				glPopMatrix();//fIN_POSTE_UNION_RUEDAS

			glPopMatrix();//Rueda1
	
			glPushMatrix();//rueda2
				glTranslatef(0.0,0.0,3.0);
				glPushMatrix();
					glTranslatef(0.0, 3.0, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(115, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(3.5, 5.0, 0.0);
					glRotatef(60, 0.0, 0.0, 1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(115, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(3.5, 9.0, 0.0);
					glRotatef(120, 0.0, 0.0, 1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(115, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(0.0, 11.0, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(-65, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-3.5, 9.0, 0.0);
					glRotatef(60, 0.0, 0.0, 1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(-65, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();

				glPushMatrix();
					glTranslatef(-3.5, 5.0, 0.0);
					glRotatef(120, 0.0, 0.0, 1.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
					//DIAGONAL
					glScalef(.25, 2, 10);
					glRotatef(-65, 0.0, 0.0, 1.0);
					glTranslatef(1.6, -1.7, 0.0);
					glScalef(5, .5, .1);
					fig3.prisma2(text7.GLindex, text7.GLindex);
				glPopMatrix();
			glPopMatrix();//Rueda2
	glPopMatrix();//centro_rueda
		glTranslatef(0, 0.0, 1.5);
		glScalef(.5, 14, .5);
		fig3.prisma2(text7.GLindex, text7.GLindex);
	glPopMatrix();//fin_rueda
}
void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);


	text1.LoadBMP("sky.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();



	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("piedras.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	text7.LoadTGA("texturas/skyscreamer/fondorojo.tga");
	text7.BuildGLTexture();
	text7.ReleaseImage();

	text8.LoadTGA("texturas/skyscreamer/metalblanco.tga");
	text8.BuildGLTexture();
	text8.ReleaseImage();

	text9.LoadTGA("texturas/skyscreamer/metalazul.tga");
	text9.BuildGLTexture();
	text9.ReleaseImage();

	text10.LoadTGA("mundo.tga");
	text10.BuildGLTexture();
	text10.ReleaseImage();

	text11.LoadTGA("texturas/skyscreamer/estrellas.tga");
	text11.BuildGLTexture();
	text11.ReleaseImage();

	text12.LoadTGA("texturas/skyscreamer/cadena.tga");
	text12.BuildGLTexture();
	text12.ReleaseImage();

	text13.LoadTGA("texturas/skyscreamer/plasticoamarillo.tga");
	text13.BuildGLTexture();
	text13.ReleaseImage();

	text18.LoadTGA("ladrillo.tga");
	text18.BuildGLTexture();
	text18.ReleaseImage();


	text19.LoadTGA("ladrillo.tga");
	text19.BuildGLTexture();
	text19.ReleaseImage();

	text20.LoadTGA("facha.tga");
	text20.BuildGLTexture();
	text20.ReleaseImage();

	text21.LoadTGA("techo.tga");
	text21.BuildGLTexture();
	text21.ReleaseImage();

	text22.LoadTGA("tienda2.tga");
	text22.BuildGLTexture();
	text22.ReleaseImage();

	text23.LoadTGA("wc.tga");
	text23.BuildGLTexture();
	text23.ReleaseImage();

	text24.LoadTGA("tienda3.tga");
	text24.BuildGLTexture();
	text24.ReleaseImage();

	text25.LoadTGA("trans.tga");
	text25.BuildGLTexture();
	text25.ReleaseImage();

	//NEW////////////////////////////////////////////

	//ida
	KeyFrame[0].arriba = 0;
	KeyFrame[0].horizontal = 0;
	KeyFrame[0].vertical = 1.4;
	KeyFrame[0].profundidad = -25;
	KeyFrame[0].giro = 0;
	KeyFrame[0].sigue = 0;
	KeyFrame[0].horizontal2 = 0;
	KeyFrame[0].vertical2 = 0;
	KeyFrame[0].descenso = 0;
	KeyFrame[0].giro2 = 0;

	//regreso
	KeyFrame[1].arriba = 0;
	KeyFrame[1].horizontal = 26.2;
	KeyFrame[1].vertical = 1.4;
	KeyFrame[1].profundidad = -25;
	KeyFrame[1].giro = 0;


	KeyFrame[2].arriba = 0;
	KeyFrame[2].horizontal = 26.2;
	KeyFrame[2].vertical = 1.4;
	KeyFrame[2].profundidad = -42;
	KeyFrame[2].giro = 0;


	//antes de subir
	KeyFrame[3].arriba = 0;
	KeyFrame[3].horizontal = 18;
	KeyFrame[3].vertical = 1.4;
	KeyFrame[3].profundidad = -42;
	KeyFrame[3].giro = 0;


	//sube
	KeyFrame[4].arriba = 0;
	KeyFrame[4].horizontal = 9;
	KeyFrame[4].vertical = 17;
	KeyFrame[4].profundidad = -42;
	KeyFrame[4].giro = 0;


	//prepara caerse
	KeyFrame[5].arriba = 0;
	KeyFrame[5].horizontal = 7;
	KeyFrame[5].vertical = 17;
	KeyFrame[5].profundidad = -42;
	KeyFrame[5].giro = 0;


	//baja
	KeyFrame[6].arriba = 0;
	KeyFrame[6].horizontal = -3;
	KeyFrame[6].vertical = 1.4;
	KeyFrame[6].profundidad = -42;
	KeyFrame[6].giro = 0;


	//sigue despues de bajar
	KeyFrame[7].arriba = 0;
	KeyFrame[7].horizontal = -26.2;
	KeyFrame[7].vertical = 1.4;
	KeyFrame[7].profundidad = -42;
	KeyFrame[7].giro = 0;

	//regreso izquierda
	KeyFrame[8].arriba = 0;
	KeyFrame[8].horizontal = -26.2;
	KeyFrame[8].vertical = 1.4;
	KeyFrame[8].profundidad = -25;
	KeyFrame[8].giro = 0;

	//va a punto inicial
	KeyFrame[9].arriba = 0;
	KeyFrame[9].horizontal = 0;
	KeyFrame[9].vertical = 1.4;
	KeyFrame[9].profundidad = -25;
	KeyFrame[9].giro = 5;







	//END NEW//////////////////////////////

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].rotBrIzq = 0;
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotInc = 0;
		KeyFrame[i].rotBrDer = 0;
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].giroMonito = 0;
		KeyFrame[i].giroMonitoInc = 0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
							//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();




	glPushMatrix();


	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Caja cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(180.0, 150.0, 180.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();//rueda
	rueda_fortuna();
	glPopMatrix();//fin rueda


	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//glScalef(0.5, 0.5, 0.5);
	//monito();
	glCallList(ciudad_display_list);
	glTranslatef(posX, posY, posZ);
	glRotatef(giroMonito, 0, 1, 0);
	monito();

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);

	//inicia montaña rusa
	glPushMatrix();


	tienda1();

	tienda2();

	baños();

	tienda3();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -25);
	montana();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(horizontal, vertical, profundidad);
	carrito();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 1.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "FERIA");
	pintaTexto(-11, 8.5, -14, (void *)font, s);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void animacion()
{

	// Calculate the number of frames per one second:
	//dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30)
	{
		juego = (juego - 1) % 360;




		dwLastUpdateTime = dwCurrentTime;
	}

	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;

	if (fig3.text_izq < -1)
		fig3.text_izq = 0;
	if (fig3.text_der < 0)
		fig3.text_der = 1;


	//Movimiento del monito


	if (dwElapsedTime >= 30)
	{
		mundo = (mundo - 10) % 360;
		dwLastUpdateTime = dwCurrentTime;



	}

	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation

								  //Interpolaciones incremento.
								  //el incremento es la distancia entre dos cuadros, el 2 - 1 y se divide entre el 90(i_max_steps)   Se hace la interpolacion


				KeyFrame[playIndex].arribaInc = (KeyFrame[playIndex + 1].arriba - KeyFrame[playIndex].arriba) / i_max_steps;
				KeyFrame[playIndex].horizontalInc = (KeyFrame[playIndex + 1].horizontal - KeyFrame[playIndex].horizontal) / i_max_steps;
				KeyFrame[playIndex].verticalInc = (KeyFrame[playIndex + 1].vertical - KeyFrame[playIndex].vertical) / i_max_steps;
				KeyFrame[playIndex].profundidadInc = (KeyFrame[playIndex + 1].profundidad - KeyFrame[playIndex].profundidad) / i_max_steps;
				KeyFrame[playIndex].giroInc = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;
				KeyFrame[playIndex].descensoInc = (KeyFrame[playIndex + 1].descenso - KeyFrame[playIndex].descenso) / i_max_steps;
				KeyFrame[playIndex].horizontal2Inc = (KeyFrame[playIndex + 1].horizontal2 - KeyFrame[playIndex].horizontal2) / i_max_steps;
				KeyFrame[playIndex].vertical2Inc = (KeyFrame[playIndex + 1].vertical2 - KeyFrame[playIndex].vertical2) / i_max_steps;
				KeyFrame[playIndex].sigueInc = (KeyFrame[playIndex + 1].sigue - KeyFrame[playIndex].sigue) / i_max_steps;
				KeyFrame[playIndex].giro2Inc = (KeyFrame[playIndex + 1].giro2 - KeyFrame[playIndex].giro2) / i_max_steps;
				interpolation();
			}
		}
		else
		{	//Draw information


			arriba += KeyFrame[playIndex].arribaInc;
			horizontal += KeyFrame[playIndex].horizontalInc;
			vertical += KeyFrame[playIndex].verticalInc;
			profundidad += KeyFrame[playIndex].profundidadInc;
			giro += KeyFrame[playIndex].giroInc;
			descenso += KeyFrame[playIndex].descensoInc;
			horizontal2 += KeyFrame[playIndex].horizontal2Inc;
			vertical2 += KeyFrame[playIndex].vertical2Inc;
			sigue += KeyFrame[playIndex].sigueInc;
			giro2 += KeyFrame[playIndex].giro2Inc;

			

			posX+=KeyFrame[playIndex].incX;
			posY+=KeyFrame[playIndex].incY;
			posZ+=KeyFrame[playIndex].incZ;

			rotRodIzq+=KeyFrame[playIndex].rotInc;
			giroMonito+=KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
			
		}

	}

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}





	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 300.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex > 1))
		{

			arriba = KeyFrame[0].arriba;
			horizontal = KeyFrame[0].horizontal;
			vertical = KeyFrame[0].vertical;
			profundidad = KeyFrame[0].profundidad;
			giro = KeyFrame[0].giro;
			descenso = KeyFrame[0].descenso;
			horizontal2 = KeyFrame[0].horizontal2;
			vertical2 = KeyFrame[0].vertical2;
			sigue = KeyFrame[0].sigue;
			giro2 = KeyFrame[0].giro2;


			//First Interpolation


			KeyFrame[playIndex].arribaInc = (KeyFrame[playIndex + 1].arriba - KeyFrame[playIndex].arriba) / i_max_steps;
			KeyFrame[playIndex].horizontalInc = (KeyFrame[playIndex + 1].horizontal - KeyFrame[playIndex].horizontal) / i_max_steps;
			KeyFrame[playIndex].verticalInc = (KeyFrame[playIndex + 1].vertical - KeyFrame[playIndex].vertical) / i_max_steps;
			KeyFrame[playIndex].profundidadInc = (KeyFrame[playIndex + 1].profundidad - KeyFrame[playIndex].profundidad) / i_max_steps;
			KeyFrame[playIndex].giroInc = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;
			KeyFrame[playIndex].descensoInc = (KeyFrame[playIndex + 1].descenso - KeyFrame[playIndex].descenso) / i_max_steps;
			KeyFrame[playIndex].horizontal2Inc = (KeyFrame[playIndex + 1].horizontal2 - KeyFrame[playIndex].horizontal2) / i_max_steps;
			KeyFrame[playIndex].vertical2Inc = (KeyFrame[playIndex + 1].vertical2 - KeyFrame[playIndex].vertical2) / i_max_steps;
			KeyFrame[playIndex].sigueInc = (KeyFrame[playIndex + 1].sigue - KeyFrame[playIndex].sigue) / i_max_steps;
			KeyFrame[playIndex].giro2Inc = (KeyFrame[playIndex + 1].giro2 - KeyFrame[playIndex].giro2) / i_max_steps;
			//KeyFrame[playIndex].tije2Inc = (KeyFrame[playIndex + 1].tije2 - KeyFrame[playIndex].tije2) / i_max_steps;

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
		break;

	case 'y':
	case 'Y':
		posZ++;
		printf("%f \n", posZ);
		break;

	case 'g':
	case 'G':
		posX--;
		printf("%f \n", posX);
		break;

	case 'h':
	case 'H':
		posZ--;
		printf("%f \n", posZ);
		break;

	case 'j':
	case 'J':
		posX++;
		printf("%f \n", posX);
		break;

	case 'b':
		rotRodIzq++;
		printf("%f \n", rotRodIzq);
		break;

	case 'B':
		rotRodIzq--;
		printf("%f \n", rotRodIzq);
		break;

	case 'n':
		rotRodDer++;
		printf("%f \n", rotRodIzq);
		break;

	case 'N':
		rotRodDer--;
		printf("%f \n", rotRodIzq);
		break;


	case 'p':
		giroMonito++;
		break;

	case 'P':
		giroMonito--;
		break;

	case 'i':
		rotBrIzq++;
		break;

	case 'I':
		rotBrIzq--;
		break;
	case 'm':

	case 'M':
		rot_rueda= !rot_rueda;
		break;
	case 'o':
		rotBrDer++;
		break;

	case 'O':
		rotBrDer--;
		break;
	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
	


	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}



int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(800, 800);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto feria"); // Nombre de la Ventana
									 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	//glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();          // 

	return 0;
}
