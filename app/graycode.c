/*
	This file contains defines that change the way the step/dir pins work, such
	that they become interchangable graycode signaling pins. If your stepper 
	driver expects coil polarity signals instead of step/dir, this will allow
	them to work with reprap.

	By default, X Y and Z are graycode, while E remains step/dir. If this isn't what
	you want, edit the lines just below.
*/
#undef X_GREYCODE
#undef Y_GREYCODE
#undef Z_GREYCODE
#undef E_GREYCODE

#undef X_COILPOL
#undef Y_COILPOL

/*
* Full step:
* PHa PHb I0a I1a I0b I1b
* 1    1  0   0   0   0
* 1    1  0   0   1   1
* 1    0  0   0   0   0
* 1    0  1   1   0   0
* 0    0  0   0   0   0
* 0    0  0   0   1   1
* 0    1  0   0   0   0
* 0    1  1   1   0   0
*/

#if defined(X_COILPOL) || defined(Y_COILPOL)
#ifndef TRUTABLE_DEFINED
#define TRUTABLE_DEFINED
#if 0
/* Half step */
static const int trutable[][6] = {
	{1, 1, 1, 1, 1, 0},
	{1, 1, 1, 0, 1, 0},
	{1, 1, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0},
	{0, 0, 1, 1, 1, 0},
	{0, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 1},
	{0, 1, 1, 0, 1, 0},
};
#endif
/* Modified half step */
static const int trutable[][6] = {
	{1, 1, 0, 0, 1, 1},
	{1, 1, 1, 0, 1, 0},
	{0, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 1, 0},
	{0, 0, 0, 0, 1, 1},
	{0, 0, 1, 0, 1, 0},
	{1, 0, 1, 1, 0, 0},
	{1, 0, 1, 0, 1, 0},
};
#if 0
static int trutable[][6] = {
	{1, 1, 0, 0, 0, 0},
	{1, 1, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0},
	{1, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0},
};
#endif
#if 0
static int trutable[][6] = {
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0},
	{1, 0, 1, 1, 0, 0},
	{1, 1, 0, 0, 0, 0},
	{1, 1, 0, 0, 1, 1},
	{0, 1, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0},
};
#endif
#define TRUTABLE_SIZE (sizeof(trutable)/sizeof(trutable[0]))
#endif
#endif

/*
	X Stepper
*/
#ifdef X_GREYCODE
	#undef x_step
	#undef _x_step
	#undef x_direction
	#define x_step()                        {\
												x_greycode+=stored_x_direction;\
												WRITE(X_STEP_PIN,(x_greycode>>1)&1);\
												WRITE(X_DIR_PIN,((x_greycode>>1)^x_greycode)&1);\
											}
	#define _x_step(st)                    
	#define x_direction(dir)                stored_x_direction=(dir)?1:-1
	int8_t stored_x_direction;
	int8_t x_greycode;
#endif
#ifdef X_COILPOL
#undef x_step
#undef _x_step
#undef x_direction
#define x_step() do_x_step()
#define x_direction(dir) stored_x_direction=(dir)?1:-1
#define _x_step(st)                    
#undef x_disable
#undef x_enable
#define x_enable() do_x_enable()
#define x_disable() do_x_disable()
#ifndef DO_X_STEP_DEFINED
#define DO_X_STEP_DEFINED
int stored_x_direction;
int stored_x_index;
void do_x_step(void)
{
	stored_x_index += stored_x_direction;
	if (stored_x_index < 0)
		stored_x_index = TRUTABLE_SIZE - 1;
	if (stored_x_index >= (int)TRUTABLE_SIZE)
		stored_x_index = 0;
	WRITE(X_STEP_PIN, trutable[stored_x_index][0]); /* PH1 */
	WRITE(X_DIR_PIN, trutable[stored_x_index][1]); /* PH2 */
	WRITE(X_I01_PIN, trutable[stored_x_index][2]); /* I01 */
	WRITE(X_I11_PIN, trutable[stored_x_index][3]); /* I11 */
	WRITE(X_I02_PIN, trutable[stored_x_index][4]); /* I02 */
	WRITE(X_I12_PIN, trutable[stored_x_index][5]); /* I12 */
}
void do_x_disable(void)
{
	WRITE(X_STEP_PIN, 0); /* PH1 */
	WRITE(X_DIR_PIN, 1); /* PH2 */
	WRITE(X_I01_PIN, 0); /* I01 */
	WRITE(X_I11_PIN, 1); /* I11 */
	WRITE(X_I02_PIN, 0); /* I02 */
	WRITE(X_I12_PIN, 1); /* I12 */
}
void do_x_enable(void)
{
	WRITE(X_STEP_PIN, trutable[stored_x_index][0]); /* PH1 */
	WRITE(X_DIR_PIN, trutable[stored_x_index][1]); /* PH2 */
	WRITE(X_I01_PIN, trutable[stored_x_index][2]); /* I01 */
	WRITE(X_I11_PIN, trutable[stored_x_index][3]); /* I11 */
	WRITE(X_I02_PIN, trutable[stored_x_index][4]); /* I02 */
	WRITE(X_I12_PIN, trutable[stored_x_index][5]); /* I12 */
}


#endif
#endif


/*
	Y Stepper
*/

#ifdef Y_GREYCODE
	#undef y_step
	#undef _y_step
	#undef y_direction
	#define y_step()                        {\
												y_greycode+=stored_y_direction;\
												WRITE(Y_STEP_PIN,(y_greycode>>1)&1);\
												WRITE(Y_DIR_PIN,((y_greycode>>1)^y_greycode)&1);\
											}
	#define _y_step(st)                     
	#define y_direction(dir)                stored_y_direction=(dir)?1:-1
	int8_t stored_y_direction;
	int8_t y_greycode;
#endif
#ifdef Y_COILPOL
#undef y_step
#undef _y_step
#undef y_direction
#define y_step() do_y_step()
#define y_direction(dir) stored_y_direction=(dir)?1:-1
#define _y_step(st)                    
#undef y_disable
#undef y_enable
#define y_enable() do_y_enable()
#define y_disable() do_y_disable()
#ifndef DO_Y_STEP_DEFINED
#define DO_Y_STEP_DEFINED
int stored_y_direction;
int stored_y_index;
void do_y_step(void)
{
	stored_y_index += stored_y_direction;
	if (stored_y_index < 0)
		stored_y_index = TRUTABLE_SIZE - 1;
	if (stored_y_index >= (int)TRUTABLE_SIZE)
		stored_y_index = 0;
	WRITE(Y_STEP_PIN, trutable[stored_y_index][0]); /* PH1 */
	WRITE(Y_DIR_PIN, trutable[stored_y_index][1]); /* PH2 */
	WRITE(Y_I01_PIN, trutable[stored_y_index][2]); /* I01 */
	WRITE(Y_I11_PIN, trutable[stored_y_index][3]); /* I11 */
	WRITE(Y_I02_PIN, trutable[stored_y_index][4]); /* I02 */
	WRITE(Y_I12_PIN, trutable[stored_y_index][5]); /* I12 */
}
void do_y_disable(void)
{
	WRITE(Y_STEP_PIN, 0); /* PH1 */
	WRITE(Y_DIR_PIN, 1); /* PH2 */
	WRITE(Y_I01_PIN, 0); /* I01 */
	WRITE(Y_I11_PIN, 1); /* I11 */
	WRITE(Y_I02_PIN, 0); /* I02 */
	WRITE(Y_I12_PIN, 1); /* I12 */
}
void do_y_enable(void)
{
	WRITE(Y_STEP_PIN, trutable[stored_y_index][0]); /* PH1 */
	WRITE(Y_DIR_PIN, trutable[stored_y_index][1]); /* PH2 */
	WRITE(Y_I01_PIN, trutable[stored_y_index][2]); /* I01 */
	WRITE(Y_I11_PIN, trutable[stored_y_index][3]); /* I11 */
	WRITE(Y_I02_PIN, trutable[stored_y_index][4]); /* I02 */
	WRITE(Y_I12_PIN, trutable[stored_y_index][5]); /* I12 */
}


#endif
#endif

/*
	Z Stepper
*/

#ifdef Z_GREYCODE
	#undef z_step
	#undef _z_step
	#undef z_direction
	#define z_step()                        {\
												z_greycode+=stored_z_direction;\
												WRITE(Z_STEP_PIN,(z_greycode>>1)&1);\
												WRITE(Z_DIR_PIN,((z_greycode>>1)^z_greycode)&1);\
											}
	#define _z_step(st)                    
	#define z_direction(dir)                stored_z_direction=(dir)?1:-1
	int8_t stored_z_direction;
	int8_t z_greycode;
#endif

/*
	Extruder
*/

#ifdef E_GREYCODE
	#undef e_step
	#undef _e_step
	#undef e_direction
	#define e_step()                        {\
												e_greycode+=stored_e_direction;\
												WRITE(E_STEP_PIN,(e_greycode>>1)&1);\
												WRITE(E_DIR_PIN,((e_greycode>>1)^e_greycode)&1);\
											}
	#define _e_step(st)                     
	#define e_direction(dir)                stored_e_direction=(dir)?1:-1
	int8_t stored_e_direction;
	int8_t e_greycode;
#endif


