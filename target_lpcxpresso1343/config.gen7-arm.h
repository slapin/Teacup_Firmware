/* Notice to developers: this file is intentionally included twice. */

/** \file
	\brief Configuration for Sango-bc v0.1

	\note 
*/

/*
	CONTENTS

	1. Mechanical/Hardware
	2. Acceleration settings
	3. Pinouts
	4. Temperature sensors
	5. Heaters
	6. Communication options
	7. Miscellaneous
	8. Appendix A - PWMable pins and mappings
*/

/***************************************************************************\
*                                                                           *
* 1. MECHANICAL/HARDWARE                                                    *
*                                                                           *
\***************************************************************************/

/*
	Set your microcontroller type in Makefile


*/

/** \def F_CPU
	CPU clock rate
*/
#ifndef	F_CPU
	#define	F_CPU	16000000UL
#endif

/** \def HOST
	This is the motherboard, as opposed to the extruder. See extruder/ directory for GEN3 extruder firmware
*/
#define	HOST


/** \def STEPS_PER_M
	steps per meter ( = steps per mm * 1000 )

	calculate these values appropriate for your machine

	for threaded rods, this is
		(steps motor per turn) / (pitch of the thread) * 1000

	for belts, this is
		(steps per motor turn) / (number of gear teeth) / (belt module) * 1000

	half-stepping doubles the number, quarter stepping requires * 4, etc.

	valid range = 20 to 4'0960'000 (0.02 to 40960 steps/mm)

	all numbers are integers, so no decimal point, please :-)
*/
#define	STEPS_PER_M_X					43790
#define	STEPS_PER_M_Y					43790
#define	STEPS_PER_M_Z					1280000

/// http://blog.arcol.hu/?p=157 may help with this one
#define	STEPS_PER_M_E					1600000


/*
	Values depending on the capabilities of your stepper motors and other mechanics.
		All numbers are integers, no decimals allowed.

		Units are mm/min
*/

/// used for G0 rapid moves and as a cap for all other feedrates
#define	MAXIMUM_FEEDRATE_X		24000
#define	MAXIMUM_FEEDRATE_Y		24000
#define	MAXIMUM_FEEDRATE_Z		24000
#define	MAXIMUM_FEEDRATE_E		24000

/// used when searching endstops and as default feedrate
#define	SEARCH_FEEDRATE_X			900
#define	SEARCH_FEEDRATE_Y			900
#define	SEARCH_FEEDRATE_Z			60
// no SEARCH_FEEDRATE_E, as E can't be searched

/** \def SLOW_HOMING
	wether to search the home point slowly
		With some endstop configurations, like when probing for the surface of a PCB, you can't deal with overrunning the endstop. In such a case, uncomment this definition.
*/
#define	SLOW_HOMING

/// this is how many steps to suck back the filament by when we stop. set to zero to disable
#define	E_STARTSTOP_STEPS			20

/**
	Soft axis limits, in mm.
	Define them to your machine's size relative to what your host considers to be the origin.
*/

#define	X_MIN			-10.0
//#define	X_MAX			200.0

//#define	Y_MIN			0.0
#define	Y_MAX			185.0

//#define	Z_MIN			0.0
//#define	Z_MAX			140.0

/**	\def E_ABSOLUTE
	Some G-Code creators produce relative length commands for the extruder, others absolute ones. G-Code using absolute lengths can be recognized when there are G92 E0 commands from time to time. If you have G92 E0 in your G-Code, define this flag.

	This is the startup default and can be changed with M82/M83 while running.
*/
// #define E_ABSOLUTE



/***************************************************************************\
*                                                                           *
* 2. ACCELERATION                                                           *
*                                                                           *
* IMPORTANT: choose only one! These algorithms choose when to step, trying  *
*            to use more than one will have undefined and probably          *
*            disastrous results!                                            *
*                                                                           *
\***************************************************************************/

/** \def ACCELERATION_REPRAP
	acceleration, reprap style.
		Each movement starts at the speed of the previous command and accelerates or decelerates linearly to reach target speed at the end of the movement.
*/
// #define ACCELERATION_REPRAP

/** \def ACCELERATION_RAMPING
	acceleration and deceleration ramping.
		Each movement starts at (almost) no speed, linearly accelerates to target speed and decelerates just in time to smoothly stop at the target. alternative to ACCELERATION_REPRAP
*/
#define ACCELERATION_RAMPING

/** \def ACCELERATION
	how fast to accelerate when using ACCELERATION_RAMPING.
		given in mm/s^2, decimal allowed, useful range 1. to 10'000. Start with 10. for milling (high precision) or 1000. for printing
*/
#define ACCELERATION 750.

/** \def ACCELERATION_TEMPORAL
	temporal step algorithm
		This algorithm causes the timer to fire when any axis needs to step, instead of synchronising to the axis with the most steps ala bresenham.

		This algorithm is not a type of acceleration, and I haven't worked out how to integrate acceleration with it.
		However it does control step timing, so acceleration algorithms seemed appropriate

		The Bresenham algorithm is great for drawing lines, but not so good for steppers - In the case where X steps 3 times to Y's two, Y experiences massive jitter as it steps in sync with X every 2 out of 3 X steps. This is a worst-case, but the problem exists for most non-45/90 degree moves. At higher speeds, the jitter /will/ cause position loss and unnecessary vibration.
		This algorithm instead calculates when a step occurs on any axis, and sets the timer to that value.

		// TODO: figure out how to add acceleration to this algorithm
*/
// #define ACCELERATION_TEMPORAL



/***************************************************************************\
*                                                                           *
* 3. PINOUTS                                                                *
*                                                                           *
\***************************************************************************/

/*
	Machine Pin Definitions
	- make sure to avoid duplicate usage of a pin
	- comment out pins not in use, as this drops the corresponding code and makes operations faster
*/

//! #include	"arduino.h"

/** \def USE_INTERNAL_PULLUPS
	internal pullup resistors

	the MCU may have internal pullup resistors on it's input pins which are 
	counterproductive with the commonly used eletronic endstops, so they should 
	be switched off. For other endstops, like mechanical ones, you may want to 
	uncomment this. */
	 
//#define USE_INTERNAL_PULLUPS

/*
	user defined pins
	adjust to suit your electronics,
	or adjust your electronics to suit this
*/




#define	X_STEP_PIN						PIN_DEF (PIO_1, 5)
#define	X_DIR_PIN							PIN_DEF (PIO_1, 4) x
#define	X_MIN_PIN							PIN_DEF (PIO_1, 8)
//#define	X_MAX_PIN							xxxx
//#define	X_ENABLE_PIN					xxxx
//#define	X_INVERT_DIR
//#define	X_INVERT_MIN
//#define	X_INVERT_MAX
//#define	X_INVERT_ENABLE

#define	Y_STEP_PIN						PIN_DEF (PIO_1, 3) x
#define	Y_DIR_PIN							PIN_DEF (PIO_1, 2) x
//#define	Y_MIN_PIN							PIN_DEF (PIO_0, 8)
#define	Y_MAX_PIN							PIN_DEF (PIO_0, 8) x
//#define	Y_ENABLE_PIN					xxxx
//#define	Y_INVERT_DIR
//#define	Y_INVERT_MIN
//#define	Y_INVERT_MAX
//#define	Y_INVERT_ENABLE

#define	Z_STEP_PIN						PIN_DEF (PIO_0, 1) x
#define	Z_DIR_PIN							PIN_DEF (PIO_0, 2) x
#define	Z_MIN_PIN							PIN_DEF (PIO_0, 9)
//#define	Z_MAX_PIN							xxxx
//#define	Z_ENABLE_PIN					xxxx
//#define	Z_INVERT_DIR
//#define	Z_INVERT_MIN
//#define	Z_INVERT_MAX
//#define	Z_INVERT_ENABLE

#define	E_STEP_PIN						PIN_DEF (PIO_0, 4)
#define	E_DIR_PIN							PIN_DEF (PIO_0, 7)
//#define E_ENABLE_PIN					xxxx
//#define	E_INVERT_DIR
//#define	E_INVERT_ENABLE

#define	PS_ON_PIN							PIN_DEF (PIO_0, 3)
#define	STEPPER_ENABLE_PIN		PIN_DEF (PIO_0, 3)
#define	STEPPER_INVERT_ENABLE



/***************************************************************************\
*                                                                           *
* 4. TEMPERATURE SENSORS                                                    *
*                                                                           *
\***************************************************************************/

/**
	TEMP_HYSTERESIS: actual temperature must be target +/- hysteresis before target temperature can be achieved.
	Unit is degree Celsius.
*/
#define	TEMP_HYSTERESIS				5

/**
	TEMP_RESIDENCY_TIME: actual temperature must be close to target (within
	set temperature +- TEMP_HYSTERESIS) for this long before target is achieved
	(and a M116 succeeds). Unit is seconds.
*/
#define	TEMP_RESIDENCY_TIME		60

/**
  TEMP_EWMA: Smooth noisy temperature sensors. Good hardware shouldn't be
  noisy. Set to 1.0 for unfiltered data (and a 140 bytes smaller binary).

  Instrument Engineer's Handbook, 4th ed, Vol 2 p126 says values of
  0.05 to 0.1 are typical. Smaller is smoother but slower adjusting, larger is
  quicker but rougher. If you need to use this, set the PID parameter to zero
  (M132 S0) to make the PID loop insensitive to noise.

  Valid range: 0.001 to 1.0
*/
#define TEMP_EWMA             1.0

/// which temperature sensors are you using? List every type of sensor you use here once, to enable the appropriate code. Intercom is the gen3-style separate extruder board.
// #define	TEMP_MAX6675
#define	TEMP_THERMISTOR
// #define	TEMP_AD595
// #define	TEMP_PT100
// #define	TEMP_INTERCOM
// #define	TEMP_NONE

/***************************************************************************\
*                                                                           *
* Define your temperature sensors here. One line for each sensor, only      *
* limited by the number of available ATmega pins.                           *
*                                                                           *
* For a GEN3 set temp_type to TT_INTERCOM and temp_pin to 0.                *
*                                                                           *
* Types are same as TEMP_ list above - TT_MAX6675, TT_THERMISTOR, TT_AD595, *
*   TT_PT100, TT_INTERCOM, TT_NONE. See list in temp.c.                     *
*                                                                           *
* The "additional" field is used for TT_THERMISTOR only. It defines the     *
* name of the table(s) in ThermistorTable.h to use. Typically, this is      *
* THERMISTOR_EXTRUDER for the first or only table, or THERMISTOR_BED for    *
* the second table. See also early in ThermistorTable.{single|double}.h.    *
*                                                                           *
* TT_INTERCOM and TT_NONE don't use a pin, insert AIO0 anyways to keep      *
* the compiler happy. The pin won't be used in this case.                   *
*                                                                           *
\***************************************************************************/

#ifndef DEFINE_TEMP_SENSOR
	#define DEFINE_TEMP_SENSOR(...)
#endif

#define PIN_ADC1 PIN_DEF(PIO_1, 0)
#define PIN_ADC2 PIN_DEF(PIO_1, 1)

//                 name       type            pin        additional
DEFINE_TEMP_SENSOR(bed,       TT_THERMISTOR,  PIN_ADC1,      THERMISTOR_BED)
DEFINE_TEMP_SENSOR(extruder,  TT_THERMISTOR,  PIN_ADC2,      THERMISTOR_EXTRUDER)
// "noheater" is a special name for a sensor which doesn't have a heater.
// Use "M105 P#" to read it, where # is a zero-based index into this list.
// DEFINE_TEMP_SENSOR(noheater,  TT_THERMISTOR,  1,            0)



/***************************************************************************\
*                                                                           *
* 5. HEATERS                                                                *
*                                                                           *
\***************************************************************************/

/** \def HEATER_SANITY_CHECK
	check if heater responds to changes in target temperature, disable and spit errors if not
	largely untested, please comment in forum if this works, or doesn't work for you!
*/
// #define	HEATER_SANITY_CHECK

/***************************************************************************\
*                                                                           *
* Define your heaters here.                                                 *
*                                                                           *
* To attach a heater to a temp sensor above, simply use exactly the same    *
* name - copy+paste is your friend. Some common names are 'extruder',       *
* 'bed', 'fan', 'motor', ... names with special meaning can be found        *
* in gcode_process.c. Currently, these are:                                 *
*   HEATER_extruder   (M104)                                                *
*   HEATER_bed        (M140)                                                *
*   HEATER_fan        (M106/M107)                                           *
*                                                                           *
* A milling spindle can also be defined as a heater. Attach it to a         *
* temperature sensor of TT_NONE, then you can control the spindle's rpm     *
* via temperature commands. M104 S1..255 for spindle on, M104 S0 for off.   *
*                                                                           *
* Set 'pwm' to ...                                                          *
*  1  for using PWM on a PWM-able pin and on/off on other pins.             *
*  0  for using on/off on a PWM-able pin, too.                              *
* Using PWM usually gives smoother temperature control but can conflict     *
* with slow switches, like solid state relays. PWM frequency can be         *
* influenced globally with FAST_PWM, see below.                             *
*                                                                           *
\***************************************************************************/

#ifndef DEFINE_HEATER
	#define DEFINE_HEATER(...)
#endif

//            name      port_pin              pwm   config flags (1 = inverted)
DEFINE_HEATER(extruder, PIN_DEF(PIO_0, 10),   0,    1)
DEFINE_HEATER(bed,      PIN_DEF(PIO_0, 11),   0,    1)
// DEFINE_HEATER(fan,      PINB4, 1)
// DEFINE_HEATER(chamber,  PIND7, 1)
// DEFINE_HEATER(motor,    PIND6, 1)

/// and now because the c preprocessor isn't as smart as it could be,
/// uncomment the ones you've listed above and comment the rest.
/// NOTE: these are used to enable various capability-specific chunks of code, you do NOT need to create new entries unless you are adding new capabilities elsewhere in the code!
/// so if you list a bed above, uncomment HEATER_BED, but if you list a chamber you do NOT need to create HEATED_CHAMBER
/// I have searched high and low for a way to make the preprocessor do this for us, but so far I have not found a way.

#define	HEATER_EXTRUDER HEATER_extruder
#define HEATER_BED HEATER_bed
// #define HEATER_FAN HEATER_fan
// #define HEATER_CHAMBER HEATER_chamber
// #define HEATER_MOTOR HEATER_motor



/***************************************************************************\
*                                                                           *
* 6. COMMUNICATION OPTIONS                                                  *
*                                                                           *
\***************************************************************************/

/** \def REPRAP_HOST_COMPATIBILITY
	RepRap Host changes it's communications protocol from time to time and intentionally avoids backwards compatibility. Set this to the date the source code of your Host was fetched from RepRap's repository, which is likely also the build date.
	See the discussion on the reprap-dev mailing list from 11 Oct. 2010.

	Undefine it for best human readability, set it to an old date for compatibility with hosts before August 2010
*/
// #define REPRAP_HOST_COMPATIBILITY 19750101
// #define REPRAP_HOST_COMPATIBILITY 20100806
// #define REPRAP_HOST_COMPATIBILITY 20110509
// #define REPRAP_HOST_COMPATIBILITY <date of next RepRap Host compatibility break>

/**
	Baud rate for the connection to the host. Usually 115200, other common values are 19200, 38400 or 57600.
*/
#define	BAUD	115200

/** \def XONXOFF
	Xon/Xoff flow control.
		Redundant when using RepRap Host for sending GCode, but mandatory when sending GCode files with a plain terminal emulator, like GtkTerm (Linux), CoolTerm (Mac) or HyperTerminal (Windows).
		Can also be set in Makefile
*/
// #define	XONXOFF



/***************************************************************************\
*                                                                           *
* 7. MISCELLANEOUS OPTIONS                                                  *
*                                                                           *
\***************************************************************************/

/** \def DEBUG
	DEBUG
		enables /heaps/ of extra output, and some extra M-codes.
		WARNING: this WILL break most host-side talkers that expect particular responses from firmware such as reprap host and replicatorG
		use with serial terminal or other suitable talker only.
*/
// #define	DEBUG

/** \def BANG_BANG
BANG_BANG
drops PID loop from heater control, reduces code size significantly (1300 bytes!)
may allow DEBUG on '168
*/
#define	BANG_BANG
/** \def BANG_BANG_ON
BANG_BANG_ON
PWM value for 'on'
*/
#define	BANG_BANG_ON	200
/** \def BANG_BANG_OFF
BANG_BANG_OFF
PWM value for 'off'
*/
#define	BANG_BANG_OFF	45

/**
	move buffer size, in number of moves
		note that each move takes a fair chunk of ram (69 bytes as of this writing) so don't make the buffer too big - a bigger serial readbuffer may help more than increasing this unless your gcodes are more than 70 characters long on average.
		however, a larger movebuffer will probably help with lots of short consecutive moves, as each move takes a bunch of math (hence time) to set up so a longer buffer allows more of the math to be done during preceding longer moves
*/
#define	MOVEBUFFER_SIZE	8

/** \def DC_EXTRUDER
	DC extruder
		If you have a DC motor extruder, configure it as a "heater" above and define this value as the index or name. You probably also want to comment out E_STEP_PIN and E_DIR_PIN in the Pinouts section above.
*/
// #define	DC_EXTRUDER HEATER_motor
// #define	DC_EXTRUDER_PWM	180

/** \def USE_WATCHDOG
	Teacup implements a watchdog, which has to be reset every 250ms or it will reboot the controller. As rebooting (and letting the GCode sending application trying to continue the build with a then different Home point) is probably even worse than just hanging, and there is no better restore code in place, this is disabled for now.
*/
// #define USE_WATCHDOG

/**
	analog subsystem stuff
	REFERENCE - which analog reference to use. see analog.h for choices
*/
#define	REFERENCE			REFERENCE_AVCC

/** \def STEP_INTERRUPT_INTERRUPTIBLE
	this option makes the step interrupt interruptible (nested).
	this should help immensely with dropped serial characters, but may also make debugging infuriating due to the complexities arising from nested interrupts
	\note disable this option if you're using a '168 or for some reason your ram usage is above 90%. This option hugely increases likelihood of stack smashing.
*/
#define		STEP_INTERRUPT_INTERRUPTIBLE	1

/**
	temperature history count. This is how many temperature readings to keep in order to calculate derivative in PID loop
	higher values make PID derivative term more stable at the expense of reaction time
*/
#define	TH_COUNT					8

/** \def FAST_PWM
	Teacup offers two PWM frequencies, 76(61) Hz and 78000(62500) Hz on a
	20(16) MHz electronics. The slower one is the default, as it's the safer
	choice. Drawback is, in a quiet environment you might notice the heaters
	and your power supply humming.

	Uncomment this option if you want to get rid of this humming or want
	faster PWM for other reasons.

	See also: http://reprap.org/wiki/Gen7_Research#MOSFET_heat_and_PWM
*/
// #define	FAST_PWM

/// this is the scaling of internally stored PID values. 1024L is a good value
#define	PID_SCALE						1024L

/** \def ENDSTOP_STEPS
	number of steps to run into the endstops intentionally
		As Endstops trigger false alarm sometimes, Teacup debounces them by counting a number of consecutive positives. Valid range is 1...255. Use 4 or less for reliable endstops, 8 or even more for flaky ones.
*/
#define	ENDSTOP_STEPS	4



/***************************************************************************\
*                                                                           *
* 8. APPENDIX A - PWMABLE PINS AND MAPPINGS                                 *
*                                                                           *
*                                                                           *
* list of PWM-able pins and corresponding timers                            *
* timer1 is used for step timing so don't use OC1A/OC1B                     *
* they are omitted from this listing for that reason                        *
*                                                                           *
* For the atmega168/328, timer/pin mappings are as follows                  *
*                                                                           *
* OCR0A - PD6  - DIO6                                                       *
* OCR0B - PD5  - DIO5                                                       *
* OCR2A - PB3  - DIO11                                                      *
* OCR2B - PD3  - DIO3                                                       *
*                                                                           *
* For the atmega644, timer/pin mappings are as follows                      *
*                                                                           *
* OCR0A - PB3  - DIO3                                                       *
* OCR0B - PB4  - DIO4                                                       *
* OCR2A - PD7  - DIO15                                                      *
* OCR2B - PD6  - DIO14                                                      *
*                                                                           *
* For the atmega1280, timer/pin mappings are as follows                     *
*                                                                           *
* OCR0A  - PB7 - DIO13                                                      *
* OCR0B  - PG5 - DIO4                                                       *
* OCR2A  - PB4 - DIO10                                                      *
* OCR2B  - PH6 - DIO9                                                       *
* OCR3AL - PE3 - DIO5                                                       *
* OCR3BL - PE4 - DIO2                                                       *
* OCR3CL - PE5 - DIO3                                                       *
* OCR4AL - PH3 - DIO6                                                       *
* OCR4BL - PH4 - DIO7                                                       *
* OCR4CL - PH5 - DIO8                                                       *
* OCR5AL - PL3 - DIO46                                                      *
* OCR5BL - PL4 - DIO45                                                      *
* OCR5CL - PL5 - DIO44                                                      *
*                                                                           *
\***************************************************************************/