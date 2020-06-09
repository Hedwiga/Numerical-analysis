/*
Filename : constants.h
*/
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define EQUATION(X) tan((X) - 0.5) - sin(5 * (X))
#define DIFFERENTIAL(X) (1 / (cos((X) - 0.5)) * (cos((X) - 0.5))) - (5 * cos (5 * (X)))
#define DIFFERENTIAL_2(X) ( (2 * sin( (X) - 0.5 ) ) / ( cos( (X) - 0.5) ) ) + ( 25 * sin ( 5 * (X) ) )
#define SKIP_VALUE while(getchar() != '\n') continue; printf("\nIncorrect value! Try again: _\b");


#endif
