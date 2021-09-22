#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    
    for ( i = len-1; i >= 0; i--)
        printf(" %.2x", start[i]);
	
    return;
}

int main(int argc, char *argv[]) {

    if ( argc < 2 ) {
        printf("Forgot the argment! Try again!\n");
        return 1;
    }

	short aShort = atoi(argv[1]);

	printf("\nAs a short data type, the variable aShort has the value %hd (hex: 0x", aShort);
    show_bytes((byte_pointer) &aShort, sizeof(short)); 
    printf(")\n\n");


	/* Convert - size - implicitly */
    printf("Converting SIZE implicitly: short -> integer *** Sign extension ***\n");
    printf("This is done by issuing the statement: int anInt = aShort;\n");
    int anInt = aShort;
    printf("As a int data type, the variable anInt has the value %d (hex: 0x", anInt);
    show_bytes((byte_pointer) &anInt, sizeof(int)); 
    printf(")\n\n");

	/* Convert - size - implicitly */
    printf("Converting SIZE implicitly: short -> char *** Truncation ***\n");
    printf("This is done by issuing the statement: signed char aChar = aShort;\n");
    signed char aChar = aShort;
    printf("As a char data type, the variable aChar has the value %hhi (hex: 0x", aChar);
    show_bytes((byte_pointer) &aChar, sizeof(signed char)); 
    printf(")\n\n");

	/* Convert - sign - implicitly*/
    printf("Converting SIGN implicitly: short -> unsigned short\n");
    printf("This is done by issuing the statement: unsigned short aUShort = aShort;\n");
    unsigned short aUShort = aShort;  
    printf("As an unsigned short data type, the variable aUShort has the value %hu (hex: 0x", aUShort);
    show_bytes((byte_pointer) &aUShort, sizeof(unsigned short)); 
    printf(")\n\n");

    /* Convert - sign - implicitly*/
    printf("Converting SIGN implicitly: unsigned short -> short\n");
    printf("This is done by issuing the statement: short aShort1 = aUShort;\n");
    short aShort1 = aUShort;  
    printf("As a signed short data type, the variable aShort1 has the value %hi (hex: 0x", (signed short) aShort1);
    show_bytes((byte_pointer) &aShort1, sizeof(signed short)); 
    printf(")\n\n");

	/* Convert - both: 1) size, 2) sign */
    printf("Converting both SIZE and SIGN: short -> unsigned int\n");
    printf("This is done by issuing the statement: unsigned aUInt = aShort;\n");
    unsigned aUInt = aShort;
    printf("As an unsigned int data type, the variable aUInt has the value %u (hex: 0x", aUInt);
    show_bytes((byte_pointer) &aUInt, sizeof(unsigned)); 
    printf(")\n\n"); 

    /* One step at a time */
    printf("One step at a time - First conversion is SIZE: (int) aShort = %d\n", (int) aShort);
    printf("One step at a time - Second conversion is SIGN: (unsigned) (int) aShort = %u\n\n", (unsigned) (int) aShort);

    /* Reverse the process and see what happens ... */ 
    printf("What if ... First conversion is SIGN: (unsigned short) aShort = %hu\n", (unsigned short) aShort);
    printf("What if ... Second conversion is SIZE: (unsigned int) (unsigned short) aShort = %d\n\n",  (unsigned int) (unsigned short) aShort);

	/* Convert - both: 1) size, 2) sign */
    printf("Converting both SIZE and SIGN: short -> unsigned char\n");
    printf("This is done by issuing the statement: unsigned char anUChar = aShort;\n");
    unsigned char anUChar = aShort;
    printf("As an unsigned char data type, the variable anUChar has the value %hhu (hex: 0x", anUChar);
    show_bytes((byte_pointer) &anUChar, sizeof(unsigned char)); 
    printf(")\n\n");  

    /* One step at a time */
    printf("One step at a time - First conversion is SIZE: (signed char) aShort = %hhi\n", (signed char) aShort);
    printf("One step at a time - Second conversion is SIGN: (unsigned char) (signed char) aShort = %hhu\n\n", (unsigned char) (signed char) aShort);

    /* Reverse the process and see what happens ... */ 
    printf("What if ... First conversion is SIGN: (unsigned short) aShort = %hu\n", (unsigned short) aShort);
    printf("What if ... Second conversion is SIZE: (unsigned char) (unsigned short) aShort = %hhu\n\n",  (unsigned char) (unsigned short) aShort);

    return 0;
    
}