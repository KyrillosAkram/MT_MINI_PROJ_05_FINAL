/*=============================================================
 * gpio.c
 * 		Module: GPIO
 *
 *  Created on: Oct 8, 2021
 *
 *      Author: Kyrillos
 *
 * Description: the implementation of function of gpio module
 *      Note  : the source implementation for AVR MCU supports
 *      		ports A:Z and the module binary size
 *      		depending on number of supported ports by MCU
 *      		considering number of gpio of any port is 8
 *
 *=============================================================*/

#include "gpio.h"
#include <avr/io.h>

/******************************************************
 *                Functions definitions               *
 *****************************************************/

/*
 * Description:
 */
void GPIO_setupPinDirection(uint8 a_portId,uint8 a_pinId,GPIO_PinDirectionType a_direction){
	uint8*reg_ptr;
	switch(a_portId){


#ifdef DDRA
	case PORTA_ID:
		reg_ptr=(uint8*)&DDRA;
		break;
#endif


#ifdef DDRB
	case PORTB_ID:
		reg_ptr=(uint8*)&DDRB;
		break;
#endif


#ifdef DDRC
	case PORTC_ID:
		reg_ptr=(uint8*)&DDRC;
		break;
#endif


#ifdef DDRD
	case PORTD_ID:
		reg_ptr=(uint8*)&DDRD;
		break;
#endif


#ifdef DDRE
	case PORTE_ID:
		reg_ptr=(uint8*)&DDRE;
		break;
#endif


#ifdef DDRF
	case PORTF_ID:
		reg_ptr=(uint8*)&DDRF;
		break;
#endif


#ifdef DDRG
	case PORTG_ID:
		reg_ptr=(uint8*)&DDRG;
		break;
#endif


#ifdef DDRH
	case PORTH_ID:
		reg_ptr=(uint8*)&DDRH;
		break;
#endif


#ifdef DDRI
	case PORTI_ID:
		reg_ptr=(uint8*)&DDRI;
		break;
#endif


#ifdef DDRJ
	case PORTJ_ID:
		reg_ptr=(uint8*)&DDRJ;
		break;
#endif


#ifdef DDRK
	case PORTK_ID:
		reg_ptr=(uint8*)&DDRK;
		break;
#endif


#ifdef DDRL
	case PORTL_ID:
		reg_ptr=(uint8*)&DDRL;
		break;
#endif


#ifdef DDRM
	case PORTM_ID:
		reg_ptr=(uint8*)&DDRM;
		break;
#endif


#ifdef DDRN
	case PORTN_ID:
		reg_ptr=(uint8*)&DDRN;
		break;
#endif


#ifdef DDRO
	case PORTO_ID:
		reg_ptr=(uint8*)&DDRO;
		break;
#endif


#ifdef DDRP
	case PORTP_ID:
		reg_ptr=(uint8*)&DDRP;
		break;
#endif


#ifdef DDRQ
	case PORTQ_ID:
		reg_ptr=(uint8*)&DDRQ;
		break;
#endif


#ifdef DDRR
	case PORTR_ID:
		reg_ptr=(uint8*)&DDRR;
		break;
#endif


#ifdef DDRS
	case PORTS_ID:
		reg_ptr=(uint8*)&DDRS;
		break;
#endif


#ifdef DDRT
	case PORTT_ID:
		reg_ptr=(uint8*)&DDRT;
		break;
#endif


#ifdef DDRU
	case PORTU_ID:
		reg_ptr=(uint8*)&DDRU;
		break;
#endif


#ifdef DDRV
	case PORTV_ID:
		reg_ptr=(uint8*)&DDRV;
		break;
#endif


#ifdef DDRW
	case PORTW_ID:
		reg_ptr=(uint8*)&DDRW;
		break;
#endif


#ifdef DDRX
	case PORTX_ID:
		reg_ptr=(uint8*)&DDRX;
		break;
#endif


#ifdef DDRY
	case PORTY_ID:
		reg_ptr=(uint8*)&DDRY;
		break;
#endif


#ifdef DDRZ
	case PORTZ_ID:
		reg_ptr=(uint8*)&DDRZ;
		break;
#endif

		default:
			/* In case select unavailable register do nothing  */
			return;
			break;
	}
	*reg_ptr=(a_direction)?(*reg_ptr|(OUTPUT<<a_pinId)):(*reg_ptr&(~(OUTPUT<<a_pinId)));
	return;
}

void GPIO_setupPortDirection(uint8 a_portId,GPIO_PortDirectionType a_direction){
	switch(a_portId){
#ifdef DDRA
	case PORTA_ID:
		DDRA=a_direction;
		break;
#endif


#ifdef DDRB
	case PORTB_ID:
		DDRB=a_direction;
		break;
#endif


#ifdef DDRC
	case PORTC_ID:
		DDRC=a_direction;
		break;
#endif


#ifdef DDRD
	case PORTD_ID:
		DDRD=a_direction;
		break;
#endif


#ifdef DDRE
	case PORTE_ID:
		DDRE=a_direction;
		break;
#endif


#ifdef DDRF
	case PORTF_ID:
		DDRF=a_direction;
		break;
#endif


#ifdef DDRG
	case PORTG_ID:
		DDRG=a_direction;
		break;
#endif


#ifdef DDRH
	case PORTH_ID:
		DDRH=a_direction;
		break;
#endif


#ifdef DDRI
	case PORTI_ID:
		DDRI=a_direction;
		break;
#endif


#ifdef DDRJ
	case PORTJ_ID:
		DDRJ=a_direction;
		break;
#endif


#ifdef DDRK
	case PORTK_ID:
		DDRK=a_direction;
		break;
#endif


#ifdef DDRL
	case PORTL_ID:
		DDRL=a_direction;
		break;
#endif


#ifdef DDRM
	case PORTM_ID:
		DDRM=a_direction;
		break;
#endif


#ifdef DDRN
	case PORTN_ID:
		DDRN=a_direction;
		break;
#endif


#ifdef DDRO
	case PORTO_ID:
		DDRO=a_direction;
		break;
#endif


#ifdef DDRP
	case PORTP_ID:
		DDRP=a_direction;
		break;
#endif


#ifdef DDRQ
	case PORTQ_ID:
		DDRQ=a_direction;
		break;
#endif


#ifdef DDRR
	case PORTR_ID:
		DDRR=a_direction;
		break;
#endif


#ifdef DDRS
	case PORTS_ID:
		DDRS=a_direction;
		break;
#endif


#ifdef DDRT
	case PORTT_ID:
		DDRT=a_direction;
		break;
#endif


#ifdef DDRU
	case PORTU_ID:
		DDRU=a_direction;
		break;
#endif


#ifdef DDRV
	case PORTV_ID:
		DDRV=a_direction;
		break;
#endif


#ifdef DDRW
	case PORTW_ID:
		DDRW=a_direction;
		break;
#endif


#ifdef DDRX
	case PORTX_ID:
		DDRX=a_direction;
		break;
#endif


#ifdef DDRY
	case PORTY_ID:
		DDRY=a_direction;
		break;
#endif


#ifdef DDRZ
	case PORTZ_ID:
		DDRZ=a_direction;
		break;
#endif
	default:
		/* In case select unavailable register do nothing  */
		return;
		break;
	}
	return;
}

void GPIO_setupFirstNPins(uint8 a_portId,uint8 a_firstNPins,GPIO_PinDirectionType a_direction){
	switch(a_portId){
#ifdef PORTA
	case PORTA_ID:
		DDRA =(a_direction)?(DDRA|(1<<(a_firstNPins-1))):DDRA&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTB
	case PORTB_ID:
		DDRB =(a_direction)?(DDRB|(1<<(a_firstNPins-1))):DDRB&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTC
	case PORTC_ID:
		DDRC =(a_direction)?(DDRC|(1<<(a_firstNPins-1))):DDRC&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTD
	case PORTD_ID:
		DDRD =(a_direction)?(DDRD|(1<<(a_firstNPins-1))):DDRD&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTE
	case PORTE_ID:
		DDRE =(a_direction)?(DDRE|(1<<(a_firstNPins-1))):DDRE&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTF
	case PORTF_ID:
		DDRF =(a_direction)?(DDRF|(1<<(a_firstNPins-1))):DDRF&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTG
	case PORTG_ID:
		DDRG =(a_direction)?(DDRG|(1<<(a_firstNPins-1))):DDRG&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTH
	case PORTH_ID:
		DDRH =(a_direction)?(DDRH|(1<<(a_firstNPins-1))):DDRH&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTI
	case PORTI_ID:
		DDRI =(a_direction)?(DDRI|(1<<(a_firstNPins-1))):DDRI&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTJ
	case PORTJ_ID:
		DDRJ =(a_direction)?(DDRJ|(1<<(a_firstNPins-1))):DDRJ&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTK
	case PORTK_ID:
		DDRK =(a_direction)?(DDRK|(1<<(a_firstNPins-1))):DDRK&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTL
	case PORTL_ID:
		DDRL =(a_direction)?(DDRL|(1<<(a_firstNPins-1))):DDRL&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTM
	case PORTM_ID:
		DDRM =(a_direction)?(DDRM|(1<<(a_firstNPins-1))):DDRM&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTN
	case PORTN_ID:
		DDRN =(a_direction)?(DDRN|(1<<(a_firstNPins-1))):DDRN&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTO
	case PORTO_ID:
		DDRO =(a_direction)?(DDRO|(1<<(a_firstNPins-1))):DDRO&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTP
	case PORTP_ID:
		DDRP =(a_direction)?(DDRP|(1<<(a_firstNPins-1))):DDRP&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTQ
	case PORTQ_ID:
		DDRQ =(a_direction)?(DDRQ|(1<<(a_firstNPins-1))):DDRQ&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTR
	case PORTR_ID:
		DDRR =(a_direction)?(DDRR|(1<<(a_firstNPins-1))):DDRR&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTS
	case PORTS_ID:
		DDRS =(a_direction)?(DDRS|(1<<(a_firstNPins-1))):DDRS&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTT
	case PORTT_ID:
		DDRT =(a_direction)?(DDRT|(1<<(a_firstNPins-1))):DDRT&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTU
	case PORTU_ID:
		DDRU =(a_direction)?(DDRU|(1<<(a_firstNPins-1))):DDRU&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTV
	case PORTV_ID:
		DDRV =(a_direction)?(DDRV|(1<<(a_firstNPins-1))):DDRV&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTW
	case PORTW_ID:
		DDRW =(a_direction)?(DDRW|(1<<(a_firstNPins-1))):DDRW&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTX
	case PORTX_ID:
		DDRX =(a_direction)?(DDRX|(1<<(a_firstNPins-1))):DDRX&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTY
	case PORTY_ID:
		DDRY =(a_direction)?(DDRY|(1<<(a_firstNPins-1))):DDRY&(~(1<<(a_firstNPins-1)));
		break;
#endif

#ifdef PORTZ
	case PORTZ_ID:
		DDRZ =(a_direction)?(DDRZ|(1<<(a_firstNPins-1))):DDRZ&(~(1<<(a_firstNPins-1)));
		break;
#endif
	default:
		break;
	}
}

uint8 GPIO_readPin(uint8 a_portId,uint8 a_pinId){
	switch(a_portId){

#ifdef PORTA
	case PORTA_ID:
		return PINA>>a_pinId&(1);
		break;
#endif

#ifdef PORTB
	case PORTB_ID:
		return PINB>>a_pinId&(1);
		break;
#endif

#ifdef PORTC
	case PORTC_ID:
		return PINC>>a_pinId&(1);
		break;
#endif

#ifdef PORTD
	case PORTD_ID:
		return PIND>>a_pinId&(1);
		break;
#endif

#ifdef PORTE
	case PORTE_ID:
		return PINE>>a_pinId&(1);
		break;
#endif

#ifdef PORTF
	case PORTF_ID:
		return PINF>>a_pinId&(1);
		break;
#endif

#ifdef PORTG
	case PORTG_ID:
		return PING>>a_pinId&(1);
		break;
#endif

#ifdef PORTH
	case PORTH_ID:
		return PINH>>a_pinId&(1);
		break;
#endif

#ifdef PORTI
	case PORTI_ID:
		return PINI>>a_pinId&(1);
		break;
#endif

#ifdef PORTJ
	case PORTJ_ID:
		return PINJ>>a_pinId&(1);
		break;
#endif

#ifdef PORTK
	case PORTK_ID:
		return PINK>>a_pinId&(1);
		break;
#endif

#ifdef PORTL
	case PORTL_ID:
		return PINL>>a_pinId&(1);
		break;
#endif

#ifdef PORTM
	case PORTM_ID:
		return PINM>>a_pinId&(1);
		break;
#endif

#ifdef PORTN
	case PORTN_ID:
		return PINN>>a_pinId&(1);
		break;
#endif

#ifdef PORTO
	case PORTO_ID:
		return PINO>>a_pinId&(1);
		break;
#endif

#ifdef PORTP
	case PORTP_ID:
		return PINP>>a_pinId&(1);
		break;
#endif

#ifdef PORTQ
	case PORTQ_ID:
		return PINQ>>a_pinId&(1);
		break;
#endif

#ifdef PORTR
	case PORTR_ID:
		return PINR>>a_pinId&(1);
		break;
#endif

#ifdef PORTS
	case PORTS_ID:
		return PINS>>a_pinId&(1);
		break;
#endif

#ifdef PORTT
	case PORTT_ID:
		return PINT>>a_pinId&(1);
		break;
#endif

#ifdef PORTU
	case PORTU_ID:
		return PINU>>a_pinId&(1);
		break;
#endif

#ifdef PORTV
	case PORTV_ID:
		return PINV>>a_pinId&(1);
		break;
#endif

#ifdef PORTW
	case PORTW_ID:
		return PINW>>a_pinId&(1);
		break;
#endif

#ifdef PORTX
	case PORTX_ID:
		return PINX>>a_pinId&(1);
		break;
#endif

#ifdef PORTY
	case PORTY_ID:
		return PINY>>a_pinId&(1);
		break;
#endif

#ifdef PORTZ
	case PORTZ_ID:
		return PINZ>>a_pinId&(1);
		break;
#endif
	default:
		return 0;
		break;
	}
	return 0 ;
}

uint8 GPIO_readPort(uint8 a_portId){
	switch(a_portId){
#ifdef PORTA
	case PORTA_ID:
		return PINA;
		break;
#endif

#ifdef PORTB
	case PORTB_ID:
		return PINB;
		break;
#endif

#ifdef PORTC
	case PORTC_ID:
		return PINC;
		break;
#endif

#ifdef PORTD
	case PORTD_ID:
		return PIND;
		break;
#endif

#ifdef PORTE
	case PORTE_ID:
		return PINE;
		break;
#endif

#ifdef PORTF
	case PORTF_ID:
		return PINF;
		break;
#endif

#ifdef PORTG
	case PORTG_ID:
		return PING;
		break;
#endif

#ifdef PORTH
	case PORTH_ID:
		return PINH;
		break;
#endif

#ifdef PORTI
	case PORTI_ID:
		return PINI;
		break;
#endif

#ifdef PORTJ
	case PORTJ_ID:
		return PINJ;
		break;
#endif

#ifdef PORTK
	case PORTK_ID:
		return PINK;
		break;
#endif

#ifdef PORTL
	case PORTL_ID:
		return PINL;
		break;
#endif

#ifdef PORTM
	case PORTM_ID:
		return PINM;
		break;
#endif

#ifdef PORTN
	case PORTN_ID:
		return PINN;
		break;
#endif

#ifdef PORTO
	case PORTO_ID:
		return PINO;
		break;
#endif

#ifdef PORTP
	case PORTP_ID:
		return PINP;
		break;
#endif

#ifdef PORTQ
	case PORTQ_ID:
		return PINQ;
		break;
#endif

#ifdef PORTR
	case PORTR_ID:
		return PINR;
		break;
#endif

#ifdef PORTS
	case PORTS_ID:
		return PINS;
		break;
#endif

#ifdef PORTT
	case PORTT_ID:
		return PINT;
		break;
#endif

#ifdef PORTU
	case PORTU_ID:
		return PINU;
		break;
#endif

#ifdef PORTV
	case PORTV_ID:
		return PINV;
		break;
#endif

#ifdef PORTW
	case PORTW_ID:
		return PINW;
		break;
#endif

#ifdef PORTX
	case PORTX_ID:
		return PINX;
		break;
#endif

#ifdef PORTY
	case PORTY_ID:
		return PINY;
		break;
#endif

#ifdef PORTZ
	case PORTZ_ID:
		return PINZ;
		break;
#endif

	default:
		return 0;
		break;
	}
}

void GPIO_writePin(uint8 a_portId,uint8 a_pinId,boolean a_data){
	uint8* reg_ptr;
	switch(a_portId){
#ifdef PORTA
   case PORTA_ID:
       reg_ptr=(uint8*)&PORTA;
       break;
#endif

#ifdef PORTB
   case PORTB_ID:
       reg_ptr=(uint8*)&PORTB;
       break;
#endif

#ifdef PORTC
   case PORTC_ID:
       reg_ptr=(uint8*)&PORTC;
       break;
#endif

#ifdef PORTD
   case PORTD_ID:
       reg_ptr=(uint8*)&PORTD;
       break;
#endif

#ifdef PORTE
   case PORTE_ID:
       reg_ptr=(uint8*)&PORTE;
       break;
#endif

#ifdef PORTF
   case PORTF_ID:
       reg_ptr=(uint8*)&PORTF;
       break;
#endif

#ifdef PORTG
   case PORTG_ID:
       reg_ptr=(uint8*)&PORTG;
       break;
#endif

#ifdef PORTH
   case PORTH_ID:
       reg_ptr=(uint8*)&PORTH;
       break;
#endif

#ifdef PORTI
   case PORTI_ID:
       reg_ptr=(uint8*)&PORTI;
       break;
#endif

#ifdef PORTJ
   case PORTJ_ID:
       reg_ptr=(uint8*)&PORTJ;
       break;
#endif

#ifdef PORTK
   case PORTK_ID:
       reg_ptr=(uint8*)&PORTK;
       break;
#endif

#ifdef PORTL
   case PORTL_ID:
       reg_ptr=(uint8*)&PORTL;
       break;
#endif

#ifdef PORTM
   case PORTM_ID:
       reg_ptr=(uint8*)&PORTM;
       break;
#endif

#ifdef PORTN
   case PORTN_ID:
       reg_ptr=(uint8*)&PORTN;
       break;
#endif

#ifdef PORTO
   case PORTO_ID:
       reg_ptr=(uint8*)&PORTO;
       break;
#endif

#ifdef PORTP
   case PORTP_ID:
       reg_ptr=(uint8*)&PORTP;
       break;
#endif

#ifdef PORTQ
   case PORTQ_ID:
       reg_ptr=(uint8*)&PORTQ;
       break;
#endif

#ifdef PORTR
   case PORTR_ID:
       reg_ptr=(uint8*)&PORTR;
       break;
#endif

#ifdef PORTS
   case PORTS_ID:
       reg_ptr=(uint8*)&PORTS;
       break;
#endif

#ifdef PORTT
   case PORTT_ID:
       reg_ptr=(uint8*)&PORTT;
       break;
#endif

#ifdef PORTU
   case PORTU_ID:
       reg_ptr=(uint8*)&PORTU;
       break;
#endif

#ifdef PORTV
   case PORTV_ID:
       reg_ptr=(uint8*)&PORTV;
       break;
#endif

#ifdef PORTW
   case PORTW_ID:
       reg_ptr=(uint8*)&PORTW;
       break;
#endif

#ifdef PORTX
   case PORTX_ID:
       reg_ptr=(uint8*)&PORTX;
       break;
#endif

#ifdef PORTY
   case PORTY_ID:
       reg_ptr=(uint8*)&PORTY;
       break;
#endif

#ifdef PORTZ
   case PORTZ_ID:
       reg_ptr=(uint8*)&PORTZ;
       break;
#endif

   default:
	   return;
	   break;
	}
	*reg_ptr=(a_data)?(*reg_ptr|(1<<a_pinId)):(*reg_ptr&(~(1<<a_pinId)));
	return;
}

void GPIO_writePort(uint8 a_portId,uint8 a_data){
	switch(a_portId){

#ifdef PORTA
	case PORTA_ID:
		PORTA=a_data;;
		break;
#endif

#ifdef PORTB
	case PORTB_ID:
		PORTB=a_data;;
		break;
#endif

#ifdef PORTC
	case PORTC_ID:
		PORTC=a_data;;
		break;
#endif

#ifdef PORTD
	case PORTD_ID:
		PORTD=a_data;;
		break;
#endif

#ifdef PORTE
	case PORTE_ID:
		PORTE=a_data;;
		break;
#endif

#ifdef PORTF
	case PORTF_ID:
		PORTF=a_data;;
		break;
#endif

#ifdef PORTG
	case PORTG_ID:
		PORTG=a_data;;
		break;
#endif

#ifdef PORTH
	case PORTH_ID:
		PORTH=a_data;;
		break;
#endif

#ifdef PORTI
	case PORTI_ID:
		PORTI=a_data;;
		break;
#endif

#ifdef PORTJ
	case PORTJ_ID:
		PORTJ=a_data;;
		break;
#endif

#ifdef PORTK
	case PORTK_ID:
		PORTK=a_data;;
		break;
#endif

#ifdef PORTL
	case PORTL_ID:
		PORTL=a_data;;
		break;
#endif

#ifdef PORTM
	case PORTM_ID:
		PORTM=a_data;;
		break;
#endif

#ifdef PORTN
	case PORTN_ID:
		PORTN=a_data;;
		break;
#endif

#ifdef PORTO
	case PORTO_ID:
		PORTO=a_data;;
		break;
#endif

#ifdef PORTP
	case PORTP_ID:
		PORTP=a_data;;
		break;
#endif

#ifdef PORTQ
	case PORTQ_ID:
		PORTQ=a_data;;
		break;
#endif

#ifdef PORTR
	case PORTR_ID:
		PORTR=a_data;;
		break;
#endif

#ifdef PORTS
	case PORTS_ID:
		PORTS=a_data;;
		break;
#endif

#ifdef PORTT
	case PORTT_ID:
		PORTT=a_data;;
		break;
#endif

#ifdef PORTU
	case PORTU_ID:
		PORTU=a_data;;
		break;
#endif

#ifdef PORTV
	case PORTV_ID:
		PORTV=a_data;;
		break;
#endif

#ifdef PORTW
	case PORTW_ID:
		PORTW=a_data;;
		break;
#endif

#ifdef PORTX
	case PORTX_ID:
		PORTX=a_data;;
		break;
#endif

#ifdef PORTY
	case PORTY_ID:
		PORTY=a_data;;
		break;
#endif

#ifdef PORTZ
	case PORTZ_ID:
		PORTZ=a_data;;
		break;
#endif
	default:
		break;
	}
	return;
}

void GPIO_writeFirstNPins(uint8 a_portId,uint8 a_firstNPins,uint8 a_data){
	/*TODO make this function safer or make good warning*/
	/*hello comment*/
	GPIO_writePort(a_portId,((GPIO_readPort(a_portId)&(~((1<<a_firstNPins)-1))))|a_data);
}
