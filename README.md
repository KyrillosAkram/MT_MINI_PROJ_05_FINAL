# Welcome to MiniProject05!
## About the project
This project just implementation for simple Door Locker Security System, two microcontrollers first one is HMI microcontroller which takes user commands using 4x4 keypad
then update 2x16 lcd with readable information and send command and data to the other (CTRL microcontroller) which applies HMI command and manage buzzer , door's dc-motor,and external EEPROM through I2C


# Project architecture


`
MT_MINI_PROJ_05_FINAL
	├─ protues_simulation					( visual simulation directory			)
	│	├─ proteus.pdsprj				( with full debuging information require V8	)
	│	└─ proteus - without debug logging.pdsprj	( reduced logs for faster simulation
	└─ workspace 						( elcipse workspace directory			)
		├─ MiniProject5-Control				( elcipse project directory  			)
		│	├─ Debug				( project debuging binary directory		)
		│	│	├─ MiniProject5-Control.elf 	( binary for debuging        			)
		│	│	└─ MiniProject5.hex 		( just binary                			)
		│	├─ main.c 				( Application code and the entry point		)
		│	├─ std_types.h
		│	├─ common_macros.h
		│	├─ driver01.c
		│	├─ driver01.h
		│	...
		│	├─ driverxx.c
		│	└─ driverxx.h
		└─ MiniProject5-HMI				( elcipse project directory  			)
			├─ Debug				( project debuging binary directory		)
			│	├─ MiniProject5-HMI.elf 	( binary for debuging        			)
			│	└─ MiniProject5-HMI.hex 	( just binary                			)
			├─ main.c 				( Application code and the entry point		)
			├─ std_types.h
			├─ common_macros.h
			├─ driver01.c
			├─ driver01.h
			...
			├─ driverxx.c
			└─ driverxx.h

`