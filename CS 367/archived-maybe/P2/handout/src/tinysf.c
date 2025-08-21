/* This is the only file you will be editing.
 * - Copyright of Starter Code: Prof. Kevin Andrea, George Mason University.  All Rights Reserved
 * - Copyright of Student Code: You!  
 * - Restrictions on Student Code: Do not post your code on any public site (eg. Github).
 * -- Feel free to post your code on a PRIVATE Github and give interviewers access to it.
 * -- You are liable for the protection of your code from others.
 * - ASCII Art Adapted from Regular Calculator by Jeremy J. Olson
 * -- Original File: https://www.asciiart.eu/electronics/calculators
 * - Date: Feb 2024
 */

/* CS367 Project 2, Spring Semester, 2024
 * Fill in your Name, GNumber, and Section Number in the following comment fields
 * Name: Nicholas Locklear
 * GNumber: G01090642
 * Section Number: CS367-002         
 */

/* _____________________
  |  _________________  |
  | |     MUAN    3.25| |
  | |_________________| |
  |  ___ ___ ___   ___  |
  | | 7 | 8 | 9 | | + | |
  | |___|___|___| |___| |
  | | 4 | 5 | 6 | | - | |
  | |___|___|___| |___| |
  | | 1 | 2 | 3 | | x | |
  | |___|___|___| |___| |
  | | . | 0 | = | | V | |
  | |___|___|___| |___| |
  |_____________________|
 */

#include <stdio.h>
#include <stdlib.h>
#include "common_structs.h"
#include "common_definitions.h"
#include "common_functions.h"
#include "tinysf.h"
/**TODO
 * 
 * Bugfix tonumber / encoding
*/



/* This is the only file you will be editing.
 * - Copyright of Starter Code: Prof. Kevin Andrea, George Mason University.  All Rights Reserved
 * - Copyright of Student Code: You!  
 * - Restrictions on Student Code: Do not post your code on any public site (eg. Github).
 * -- Feel free to post your code on a PRIVATE Github and give interviewers access to it.
 * -- You are liable for the protection of your code from others.
 * - Date: Jan 2023
 */

/* Fill in your Name and GNumber in the following two comment fields
 * Name: Nicholas Locklear
 * GNumber: G01090642
 */


#include <stdio.h>
#include <stdlib.h>
#include "common_structs.h"
#include "common_definitions.h"
#include "common_functions.h"
#include "tinysf.h"

// Feel free to add many Helper Functions, Consts, and Definitions!

// ----------Public API Functions (write these!)-------------------

/* toTinySF - Converts a Number Struct (whole and fraction parts) into a TINYSF Value
 *  - number is managed by zuon, DO NOT FREE number.
 *  - Follow the project documentation for this function.
 * Return the TINYSF Value.
 */

/**TODO
 * set up mult, add, sub using toNum
 * set up encoding
*/


//helper func


tinysf_s setBit(tinysf_s value, int n){
	int mask = 1<<n;
	return value | mask;
}

tinysf_s clearBits(tinysf_s value, int start, int finish){
	int mask = 0;
	for(int i = start; i <= finish; i ++){
		mask |= (1<<i);
	}
	return (value & (~mask));
}

tinysf_s getBits(tinysf_s val, int start, int numBits){
	tinysf_s returnVal = val >> start;
	int mask = (1<<numBits);
	mask = mask-1;
	returnVal &=mask;
	return returnVal;
}

int isInfinite(tinysf_s *number){
  //check here for any inf, value
  tinysf_s numDummy = *number;
  int Sign = 1<<11;
  int exponentBits = getBits(numDummy, 7, 10);
  int fracBits = getBits(numDummy, 0, 6);

  if(exponentBits != 15 ){
    return 0;
  }
  else if(exponentBits == 15 && fracBits !=0 ){
    return 0;
  }
  else if(Sign == 1 && exponentBits == 15 && fracBits == 0){
    return -1;
  }
  return 1; //1 if inf, 0 if not, -1 if neg inf
}

int isNAN(tinysf_s *number){
  tinysf_s numDummy = *number;
  int Sign = 1<<11;
  int exponentBits = getBits(numDummy, 7, 10);
  int fracBits = getBits(numDummy, 0, 6);

  if(exponentBits != 15 ){
    return 0;
  }
  else if(exponentBits == 15 && fracBits ==0 ){
    return 0;
  }
  else if(Sign == 1 && exponentBits == 15 && fracBits != 0){
    return -1;
  }
  return 1; //1 if inf, 0 if not, -1 if neg inf
}

int isNULL(tinysf_s *number){
  if(number == NULL){
    return 1;
  }
  return 0;
}

int isMSBOne(tinysf_s value) { //i feel so stupid having to make this but for some reason I cant get it to work
    unsigned int mask = 1U << 31; 
    // Use bitwise AND to check if the MSB of value is 1
    if (value & mask) {
        return 1; // MSB is 1
    } else {
        return 0; // MSB is not 1
    }
}

/* toTinySF - Converts a Number Struct (whole and fraction parts) into a TINYSF Value
 *  - number is managed by zuon, DO NOT FREE number.
 *  - Follow the project documentation for this function.
 * Return the TINYSF Value.
 */

tinysf_s toTinySF(Number_s *number) {
  //printf("ToTinySF called");
  tinysf_s A = number->whole;
  tinysf_s B = number->fraction;
  int Bias = 7; // (2^3 -1)
  int E = 0;
  int digitCounter = 0;
  tinysf_s returnEncoded = (1 * number->is_negative)<<11;//sets sign bit immediately
  if(number->is_nan == 1){
    returnEncoded = (returnEncoded | (0b11111<<6 ));
    return returnEncoded;
  }
  if(number->is_infinity == 1){
    returnEncoded = (returnEncoded | (0b1111<<7 ));   
    return returnEncoded;
  }
  if(number->whole == 0 && number->fraction == 0){
    return returnEncoded;
  }
  while(A>1){  //START FROM HERE WHEN YOU GET BACK, YOU NEED TO FIX THE ENCODING
    E++;
    //printf("\n\t\t\t\t  A = %x, B = %x, E = %x", A, B, E );
    if((A&1) == 1){ //if A's lsb is 1
      B = B>>1;
      B = setBit(B,31); //sets b's msb to 1
      //printf("\n\t\tA!!");
    }
    else{
      B= B>>1;
      B = ((B>>1) && (~(1<<30)) ); //sets b's msb to 0
      //printf("\n\t\tB!!");
    }
    A = A>>1;
    //printf("\n\t\t\t\t  A = %x, B = %x, E = %x", A, B, E );
  }

  tinysf_s exp = E+ Bias;
  //printf("\n\n\t\t\t\t  frac = %x, exp = %x", B, exp );
  if(exp <= 0){return returnEncoded;}  //if exp <= 0, count as underflow.
  else if(exp>14){//overflow
    returnEncoded = (returnEncoded | (0b1111<<7 ));
    return returnEncoded;
  }
  else{
    exp = exp<<7;
    returnEncoded = returnEncoded | exp; //exp encoded into final val
    //printf("\n\t\t\t\t  exp = %x, returnval = %x", exp, returnEncoded );
  }
  //if digitcount > 
  tinysf_s Mantissa = B;//increment with left shift until 0, add to digit count
  tinysf_s fracHolder = 0;
  //if digit count >7, rounding needs to happen. else, encode result as the fractional piece
  if(Mantissa == 0){//no frac encoding
    return returnEncoded;
    //printf("\n\t\t\tOut: no frac component");
  }
  else{

    while(Mantissa !=0){
      if(digitCounter>8){
        //printf("\n\t\t\tmantissaloop broke at : %x", digitCounter );

        break;
      }
      //printf("\n\n\t\t\t\t  frac = %x, exp = %x", Mantissa, exp ); //MANTISSa IS correct here, start from here <----------
      if(isMSBOne(Mantissa)==1){
        fracHolder = fracHolder <<1;
        fracHolder = fracHolder |1;
      }
      else{
        fracHolder = fracHolder << 1;
      }
      Mantissa = Mantissa <<1;
      digitCounter ++;

    }
    //printf("\n\n\t\t\t returnEncoded: %x fracholder: %x,  mantissa = %x", returnEncoded, fracHolder, Mantissa );

    if(Mantissa == 0 && digitCounter <=7){
      fracHolder = fracHolder << (7-digitCounter); //aligns bits
      returnEncoded = returnEncoded | fracHolder;
      //printf("\n\n\t\t\t fracholder: exit2: mantissa 0 and digits<7 : %x, realdigits: %x, fracholder: %x", returnEncoded, digitCounter, fracHolder );
    }
    else{ //rounding + another check to see if an overflow happens
      //printf("\n\n\t\t\t fracholder: exit3: mantissa 0 and digits>=7 : %x, realdigits: %x, mantissa = %x", returnEncoded, digitCounter, Mantissa );


    }
    return returnEncoded;
  }
}




/* toNumber - Converts a TINYSF Value into a Number Struct (whole and fraction parts)
 *  - number is managed by zuon, DO NOT FREE or re-Allocate number.
 *    - (It is already allocated)
 *  - Follow the project documentation for this function.
 * Return .
 */
int toNumber(Number_s *number, tinysf_s value) {
  if(number == NULL){
    return -1;
  }
  int bias = 7;
  tinysf_s copyNum = value;
  //printf("\n\t\t\t\t  copynum = %x", value );
  tinysf_s fracMask = getBits(copyNum,0,7);
  copyNum = copyNum >>7;
  tinysf_s expoMask = getBits(copyNum,0,4);
  copyNum = copyNum >>4;
  number->is_negative = copyNum;
  //printf("\n\t\t\t\t  frac = %x, exp = %x", fracMask, expoMask );

  if(isInfinite(&copyNum) != 0){
    number->is_infinity = 1;
    number->whole = 0;
    number->fraction = 0; 
    return 0;
  }

  if(isNAN(&value) != 0){
    number->is_nan = 1;
    number->is_infinity = 0;
    number->whole = 0;
    number->fraction = 0;
    return 0;
  }
  if(expoMask == 0){//denormalized

  }
  int bigE = expoMask - bias;
    //printf("\n\t\t\t\t E= %d, frac = %x, exp = %x",bigE, fracMask, expoMask );
  number->whole = fracMask;

  while(number->whole != 0){
   // number->whole = number->whole >>1;
   // number->fraction = number->fraction >>1
    if(number->whole && 1 == 1){
      number->fraction = number->fraction>>1;
      number->fraction = setBit(number->fraction, 31);
    }

  }
  number->whole = 1;
  //printf("\n\t\t\t\t E= %d, frac = %x, exp = %x",bigE, number->fraction, number->whole );
  tinysf_s msbMask = 1<<31;
  if(bigE >= 0){
    while(bigE != 0){
      number->whole = number->whole <<1;
      number->whole = number->whole | (number->fraction && msbMask);
      number->fraction = number->fraction <<1;
      bigE--;
    }

  }
  //ignore this until the above is sorted
  if(bigE<0){

    number->fraction>>(bigE*-1);
    number->whole = 0;
    number->is_negative = copyNum;
    number->is_infinity, number->is_nan = 0;
  }
  return 0;
}
tinysf_s generate_tinysf_s(int sign, int exp, int frac) {
    return ((sign & 0x1) << 11) | ((exp & 0xF) << 7) | (frac & 0x7F);
}

// Adjusts the fraction by the difference in exponents to align them
int adjustFraction(int frac, int expDiff) {
    while (expDiff > 0 && frac > 0) {
        frac >>= 1;
        expDiff--;
    }
    return frac;
}


tinysf_s mulTinySF(tinysf_s val1, tinysf_s val2){
/**
 * -1S1 * M1 *2E1   *   -1S2 *M2 *2E2
 * S = S1^S2 // M = M1 * M2 E = E1 + E2
 * if E is out of range, overflow
 */

//check if values or null, nan, or inf, treat accordingly

  int signA, expA, fracA;
  int signB, expB, fracB;
  signA = (val1 >>11) &1;
  signB = (val2 >>11) &1;
  expA = (val1 >> 7) & 0xF;
  expB = (val2 >> 7) & 0xF;
  fracA = val1 & 0x7F;
  fracB = val2 & 0x7F;

    // Calculate the new sign
  int newSign = signA ^ signB;
  int newExp = expA + expB - 7;
  int newFrac = ((fracA + 0x80) * (fracB + 0x80)) >> 7;

  if (isNAN(&val1) != 0|| isNAN(&val2) !=0 ){ return generate_tinysf_s(newSign, 0xF, 0x01);}  // NaN
  if (isInfinite(&val1) != 0 || isInfinite(&val2) != 0) {
      if ( val1 == 0 || (val1 == (1<<11)) ||  val2 == 0 || (val2 == (1<<11))){ return generate_tinysf_s(newSign, 0xF, 0x01);} // NaN due to 8 * 0
      // 8 * X (with X not being 0)
      return generate_tinysf_s(newSign, 0xF, 0x00); // Infinity with proper sign
  }
  if ( val1 == 0 || (val1 == (1<<11)) ||  val2 == 0 || (val2 == (1<<11))){ return generate_tinysf_s(newSign, 0, 0);}  // 0 * 




  if (newExp > 15){
    return ((newSign & 0x1) << 11) | (0b1111 << 7);
  } 
  else if (newExp <= 0) {//underflows
    return (newSign<<11);
  }
  return ((newSign & 0x1) << 11) | ((newExp & 0xF) << 7) | (newFrac & 0x7F);

}

tinysf_s addTinySF(tinysf_s val1, tinysf_s val2){
  int signA, expA, fracA;
  int signB, expB, fracB;
  if (isNAN(&val1)!=0){ return val1;}  // NaN + Anything = NaN
  if (isNAN(&val2)!=0){ return val2;} 
  if (isInfinite(&val1)!=0){ return val1;}  //Inf + Any non NAN val = inf
  if (isInfinite(&val2)!=0){ return val2;} 
  if(val1 == 0 || val1 == (1<<11)){
    if(val2 == 0 ){ return val2;} //0 + 0
    else if(val2 == (1<<11) && val1 == val2){return val1;} //-0 + -0
    else{return val2;}
  }
  signA = (val1 >>11) &1;
  signB = (val2 >>11) &1;
  expA = (val1 >> 7) & 0xF;
  expB = (val2 >> 7) & 0xF;
  fracA = val1 & 0x7F;
  fracB = val2 & 0x7F;
  // Align exp if necessary
  int expDiff = expA - expB;
  if (expDiff > 0){
    fracB = adjustFraction(fracB, expDiff);
    expB = expA;
  } 
  else if (expDiff < 0){
    fracA = adjustFraction(fracA, -expDiff);
    expA = expB;
  }
  int resultSign, resultExp, resultFrac;    // Perform addition or subtraction based on signs
  if (signA == signB){// Same sign add the frac
      resultFrac = fracA + fracB;
      resultSign = signA;
      resultExp = expA; 
  } 
  else {// Different signs, subtract the smaller from the larger
    if (fracA > fracB) {
      resultFrac = fracA - fracB;
      resultSign = signA;
    } 
    else {
      resultFrac = fracB - fracA;
      resultSign = signB;
    }
    resultExp = expA; // Exp have been aligned
  }
  // Normalizeif necessary
  while (resultFrac >= (1 << 7)) { // Check if frac needs to be normalized
    resultFrac >>= 1;
    resultExp++;
  }
  if (resultExp >= 0xF) { // overflow
    return generate_tinysf_s(resultSign, 0xF, 0);
  }
  
  if (resultExp <= 0) {//underflow
    return generate_tinysf_s(resultSign, 0, 0);
  }
  return generate_tinysf_s(resultSign, resultExp, resultFrac);
}

tinysf_s subTinySF(tinysf_s val1, tinysf_s val2){
  return addTinySF(val1, negTinySF(val2));
  //its all the same rules, so im just gonna negate the 2nd val and call it good
}



/* negateTINYSF - Negates a TINYSF Value.
 *  - Follow the project documentation for this function.
 * Return the resulting TINYSF Value
 */
tinysf_s negTinySF(tinysf_s value) {
  tinysf_s returnVal = ((value ^  0x800));
  return  returnVal;
  //printf("NUM: %u\n", returnVal);

}
