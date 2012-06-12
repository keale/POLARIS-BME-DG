/*----------------------------------------------------------------------------
		Bergmann Messgeraete Entwicklung
		Bahnhofstr. 14
		D-82418 Murnau

		Tel. 08841 - 5487
		Fax. 08841 - 90134

    module:										 Standard definitions
    category:                  
    purpose:

    description:               
                               .

    parameters:                none

    returnvalue:               none

    caution !                  none

    programming language:      Microsoft Visual C/C++  V1.52
    operating system:          MS DOS        
    programmer:                Thorald Bergmann
    Version:                   V1.0
    Update:                    22. December 1998
    copyright:                 (c) 1998 by BME

----------------------------------------------------------------------------*/


#define DisplayMessageBox						0
#define ThrowCStringException				1
#define ReturnValueFalse						2

#define RoundInt(d) ((int)((d) + ((d) > 0 ? 0.5 : -0.5)))
#define RoundInt_64(d) ((_int64)((d) + ((d) > 0 ? 0.5 : -0.5)))
#define sqr(a) (a*a)

