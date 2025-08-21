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

//helper func

tinysf_s opTinyAdd(tinysf_s val1, tinysf_s val2){
  if(val1 == 0xF00 || val1 == 0x1F00){
    if (val1 == val2 && val1 == 0xF00){return val1;} //adding pos infinity to infinity
    else if( val1 == val2 && val1 == 0x1F00){return 0x1F00;} // adding neg inf to neg inf
    else if(val2 == 0 || val2 == -0){return val1;} //adding inf to 0
    else if(val2 == 0x1F80 || val2 == 0xF80){return val2;} //adding inf to nan
    else if( val1 == 0x1F00 || val2 == 0x1F00){return 0xF80;} // adding inf to neg inf or vice versa
    else if(val2 != 0 && val2 != -0 && val2 != 0xF00 && val2
    != 0x1F00 && val2 != 0xF80 && val2 != 0x1F80){return val1;}//adding +/-inf to non 0 x
    else{return val1;}
  }
  else if(val1 == 0 || val1 == -0){
    if(val2 == 0 ){return 0;} //adding 0
    else if(val2 == 0x1F80 || val2 == 0xF80){return 0xF80;} //adding 0 to nan
    else if(val2 == -0 || val1 != val2){return 0;} // adding 0 - 0
    else if(val2 == -0 || val1 == val2){return -0;}// adding -0 and -0
    else if(val2 == 0xF00 || val2 == 0x1F00){return val2;} //0 +/- inf
    else if( val2 != 0xF00 && val2 != 0x1F00 && val2 != 0xF80 && val2 != 0x1F80){return val2;}//adding +/-0 to non 0 x
  }
  else if(val1 == 0x1F80 || val1 == 0xF80){return val1;} // if num is nan
  else if(val1 != 0xF00 && val1 != 0x1F00 && val1 != 0xF80 && val1 != 0x1F80){ //if not inf, -inf, nan, -nan
    if(val2 == 0 || val2 == !0){return val1;} //add num to 0
    else if(val2 == 0xF00 || val2 == 0x1F00){return val2;} // add num to inf
    else if(val2 == 0x1F80 || val2 == 0xF80){return 0xF80;} // add num to nan
  }
  int Bias = 7;

  unsigned valueCopy1 = val1;
  unsigned valueCopy2 = val2;
  unsigned  mask;
  mask = (1 << 12) - 1;
  unsigned last12bits1 = valueCopy1 & mask;
  unsigned last12bits2 = valueCopy2 & mask;
  unsigned exp1 = (last12bits1 >> 8);
  unsigned frac1 = ((exp1 <<8)^ last12bits1);  
  unsigned exp2 = (last12bits2 >> 8);
  unsigned frac2 = ((exp2 <<8)^ last12bits2);

  int E1 = exp1 - Bias;
  int E2 = exp2 - Bias;
  unsigned mantissa1 = (1<<8) | frac1;
  unsigned mantissa2 = (1<<8) | frac2;
  int S1 = (valueCopy1 >> (12)) % 2;
  int S2 = (valueCopy2 >> (12)) % 2;
  Number_s *number1;
  Number_s *number2;
  int toNum = toNumber(number1, val1);
  int toNUm = toNumber(number2, val2);
  
  //actual addition time
  if(S1 == S2){
    number1->whole += number2->whole;
    if(frac1 + frac2 >= 254){
      number1->whole +=1;
    }
    number1->fraction = (frac1 + frac2)<<24;
    return toTinySF(number1);
  }
  else{
    if(S1==1){// num1 is neg
      if(number1->whole > number2->whole){ // and greater than num 2 (answer is neg)
        number1->whole =number1->whole - number2->whole;
        number1->fraction =number1->fraction - number2->fraction;
      }
      else{ // and lesser than num 2 (answer is pos)
        number1->whole =number2->whole - number1->whole;
        number1->fraction =number2->fraction - number1->fraction;   
        number1->is_negative = 0;    
      }
    }
    else{ //num 2 is neg
      if(number1->whole > number2->whole){ 
        number1->whole =number1->whole - number2->whole;
        number1->fraction =number1->fraction - number2->fraction;
      }
      else{
        number1->whole =number2->whole - number1->whole;
        number1->fraction =number2->fraction - number1->fraction;   
        number1->is_negative = 0;    
      }
    }
  }
return toTinySF(number1);

}

tinysf_s opTinySub(tinysf_s val1, tinysf_s val2){
  if(val1 == 0xF00 || val1 == 0x1F00){
    if (val1 == val2 && val1 == 0xF00){return val1;} //adding pos infinity to infinity
    else if( val1 == val2 && val1 == 0x1F00){return 0x1F00;} // adding neg inf to neg inf
    else if(val2 == 0 || val2 == -0){return val1;} //adding inf to 0
    else if(val2 == 0x1F80 || val2 == 0xF80){return val2;} //adding inf to nan
    else if( val1 == 0x1F00 || val2 == 0x1F00){return 0xF80;} // adding inf to neg inf or vice versa
    else if(val2 != 0 && val2 != -0 && val2 != 0xF00 && val2
    != 0x1F00 && val2 != 0xF80 && val2 != 0x1F80){return val1;}//adding +/-inf to non 0 x
    else{return val1;}
  }
  else if(val1 == 0 || val1 == -0){
    if(val2 == 0 ){return 0;} //adding 0
    else if(val2 == 0x1F80 || val2 == 0xF80){return 0xF80;} //adding 0 to nan
    else if(val2 == -0 || val1 != val2){return 0;} // adding 0 - 0
    else if(val2 == -0 || val1 == val2){return -0;}// adding -0 and -0
    else if(val2 == 0xF00 || val2 == 0x1F00){return val2;} //0 +/- inf
    else if( val2 != 0xF00 && val2 != 0x1F00 && val2 != 0xF80 && val2 != 0x1F80){return val2;}//adding +/-0 to non 0 x
  }
  else if(val1 == 0x1F80 || val1 == 0xF80){return val1;} // if num is nan
  else if(val1 != 0xF00 && val1 != 0x1F00 && val1 != 0xF80 && val1 != 0x1F80){ //if not inf, -inf, nan, -nan
    if(val2 == 0 || val2 == !0){return val1;} //add num to 0
    else if(val2 == 0xF00 || val2 == 0x1F00){return val2;} // add num to inf
    else if(val2 == 0x1F80 || val2 == 0xF80){return 0xF80;} // add num to nan
  }
  int Bias = 7;

  unsigned valueCopy1 = val1;
  unsigned valueCopy2 = val2;
  unsigned  mask;
  mask = (1 << 12) - 1;
  unsigned last12bits1 = valueCopy1 & mask;
  unsigned last12bits2 = valueCopy2 & mask;
  unsigned exp1 = (last12bits1 >> 8);
  unsigned frac1 = ((exp1 <<8)^ last12bits1);  
  unsigned exp2 = (last12bits2 >> 8);
  unsigned frac2 = ((exp2 <<8)^ last12bits2);

  int E1 = exp1 - Bias;
  int E2 = exp2 - Bias;
  unsigned mantissa1 = (1<<8) | frac1;
  unsigned mantissa2 = (1<<8) | frac2;
  int S1 = (valueCopy1 >> (12)) % 2;
  int S2 = (valueCopy2 >> (12)) % 2;
  Number_s *number1;
  Number_s *number2;
  int toNum = toNumber(number1, val1);
  int toNUm = toNumber(number2, val2);
  
  //actual subtraction time
  if(S1 != S2){
    if(S1==1){// num1 is neg
      if(number1->whole > number2->whole){ // and greater than num 2 (answer is neg)
        number1->whole =number1->whole - number2->whole;
        number1->fraction =number1->fraction - number2->fraction;
      }
      else{ // and lesser than num 2 (answer is pos)
        number1->whole =number2->whole + number1->whole;
        if(frac1 + frac2 >= 254){
          number1->whole +=1;
        }
        number1->fraction = (frac1 + frac2)<<24;
        number1->is_negative = 0;    
      }
    }
    else{ //num 2 is neg
      if(number1->whole > number2->whole){ 
        number1->whole =number1->whole - number2->whole;
        number1->fraction =number1->fraction - number2->fraction;
      }
      else{
        number1->whole =number2->whole - number1->whole;
        number1->fraction =number2->fraction - number1->fraction;   
        number1->is_negative = 0;    
      }
    }
  }
  else{
    if(S1 == 0){//pos - pos 
      if(number1->whole > number2->whole){  //answer is pos
        number1->whole =number1->whole - number2->whole;
        number1->fraction =number1->fraction - number2->fraction;
      }
      else{ //answer is neg
        number1->whole =number2->whole - number1->whole;
        number1->fraction =number2->fraction - number1->fraction;
        number1->is_negative = 1;
      }
    }
    else{ //neg - neg
      if(number1->whole > number2->whole){ //answer is neg
        number1->whole =number1->whole - number2->whole;
        number1->fraction =number1->fraction - number2->fraction;
      }
      else{
        number1->whole =number2->whole - number1->whole; //answer is pos
        number1->fraction =number2->fraction - number1->fraction;
        number1->is_negative = 0;
      }
    }
  }
return toTinySF(number1);
}

tinysf_s opTinyMult(tinysf_s val1, tinysf_s val2){
  int Bias = 7;
  unsigned valueCopy1 = val1;
  unsigned valueCopy2 = val2;
  unsigned  mask = (1 << 12) - 1;
  unsigned last12bits1 = valueCopy1 & mask;
  unsigned last12bits2 = valueCopy2 & mask;
  unsigned exp1 = (last12bits1 >> 8);
  unsigned frac1 = ((exp1 <<8)^ last12bits1);  
  unsigned exp2 = (last12bits2 >> 8);
  unsigned frac2 = ((exp2 <<8)^ last12bits2);
  int E1 = exp1 - Bias;
  int E2 = exp2 - Bias;
  unsigned mantissa1 = (1<<8) | frac1;
  unsigned mantissa2 = (1<<8) | frac2;
  Number_s *number1;
  Number_s *number2;
  int toNum = toNumber(number1, val1);
  int toNUm = toNumber(number2, val2);
  if(val1 == 0 || val1 == -0){
    if(val2 == 0x1F80 && val2 == 0xF80){
      return val2;
    }
    if(val2 == 0xF00 || val2 == 0x1F00){
      return 0xF80|0xF00;
    }

    if(val1==val2){
      return val2;
    }
    return val1;
  }
  if(val1 == 0xF00 || val1 == 0x1F00){
    if(val2 != 0x1F80 && val2 != 0xF80){
      return 0xF00;
    }
    if(val2 == 0xF00 || val2 == 0x1F00){
      return val1^0b1000000000000;
    }
    if(val2 == 0 || val2 == -0){
      return val1|val2;
    }
  }
  if(val1 == 0x1F80 || val1 == 0xF80){
    return val1;
  }
  if(E1!=E2){
    if(E1>E2){
      mantissa1 >>=1;
      E1 +=1;
    }
    else{
      mantissa2 >>=1;
      E2 += 1;
    }
  }
  mantissa1 *=mantissa2;
  int Sign = (val1 & 0b1000000000000) ^(val2 & 0b1000000000000);
  exp1 += exp2;
  tinysf_s returnVal = Sign;
  returnVal|=mantissa1;
  returnVal|=exp1;
  return returnVal;
}

tinysf_s roundUp(Number_s *number,unsigned int roundUp){
  unsigned int mask = 1; // start with lsb mask
  int found_zero = 0; // flag to track if we've found a zero bit
  int count = 0;
  while (mask != 0 && count < 8) { // continue until we've checked all bits
      if ((roundUp & mask) != 0) { // bit is a 1
          roundUp &= ~mask; // set bit to 0
          mask <<= 1; // move to next bit
      } else { // bit is a 0
          roundUp |= mask; // set bit to 1
          found_zero = 1; // mark that we've found a zero bit
          break; // exit loop
      }
      count ++;
  }
  if (!found_zero) {
      //printf("No zero bits found\n");
    if(number->is_negative == 1){roundUp =0x1F00;}
    else{roundUp = 0xF00;}
  } else {
  //    printf("Modified number: %u\n", roundUp);
    }
  return roundUp;
}

tinysf_s rounding(Number_s *number, unsigned int roundMe){
  /*
  * truncate most signifigant 8 digits of the original frac
  * if remaining is greater than 8388608, round up
  *   if lsb = 1, set to 0, set next least to 1, repeat. 
  * else, truncate
  *   if you truncate and lsb is a 1, round up. 
  */
  unsigned int newFrac = number->fraction ^ roundMe; //gets rid of 8 most sig
  if(newFrac>8388608 || roundMe&1 == 1){return roundUp(number,roundMe);}// if rounding up or lsb of sig 8 is 1 
  else{return roundMe;}
}

tinysf_s binary(Number_s *number){
  int Bias = 7;
  int E = 0;
  tinysf_s returnVal;
  if(number->is_negative == 0){
   // printf("val: %u, %u\n", number->whole, number->fraction);
    unsigned int newWhole = number->whole;
    unsigned int newFrac = number->fraction;
   // printf("New val: %u, %u\n", newWhole, newFrac);
    while(newWhole >1){
      printf("---------------\n");
      unsigned LSB = newWhole & 1;
      //newFrac |= LSB << (sizeof(newFrac) * 8 - 1);
      newFrac = (newFrac >> 1) | (LSB << 31);
      newWhole = newWhole >>1;
      E++;
   //   printf("LSB: %u, Count: %d\n", LSB, E);
    //  printf("New val: %u, %u\n", newWhole, newFrac);
    }
    int EXP = E + Bias;
    if (EXP > 14){
      if(number->fraction > 0){
        if(number->is_negative == 1){returnVal =0x1F80;}
        else{returnVal = 0xF80;}
      }
      else{
        if(number->is_negative == 1){returnVal =0x1F00;}
        else{returnVal = 0xF00;}
      }
    }
    //copies 8 most sig. bits
    unsigned workingFrac = (newFrac >> 24) & 0xFF;
    //printf("Init Whole: %u, Frac: %u\n", EXP, workingFrac);

    if((workingFrac << 24) != newFrac){
      //rounding
      return rounding(number, workingFrac);
    }
    else{
      //workingFrac = (workingFrac >> 24) & 0xFF;
      returnVal = 0;
    //  printf("Whole: %u, Frac: %u\n", EXP, workingFrac);
      if(number->is_negative==1){returnVal |= 0b1000000000000;}
      //printf("Returning: %u\n", returnVal);
      //printf("Is Neg?: %d", number->is_negative);
      returnVal |= EXP;
      returnVal = returnVal<< 8;
      returnVal |= workingFrac;
    }
   // printf("Returning: %u\n", returnVal);
    return returnVal;
  }
}

tinysf_s binaryDenormCheck(Number_s *number){
  unsigned Bias = 7;
  unsigned E = 0;
  unsigned MSB = 0;
  tinysf_s returnVal;
  if(number->is_negative == 0){
    unsigned newWhole = number->whole;
    unsigned newFrac = number->fraction;
    MSB = 1<<31;
    while (newFrac & MSB != MSB){
      E++;
      newFrac = newFrac << 1;
     // printf("newFrac: %u, MSB: %u\n", newFrac, MSB);
    }
    E++;
    newFrac = newFrac << 1;
    //printf("newFrac: %u, MSB: %u\n", newFrac, MSB);
    //loop, check msb of frac to see if its 1. if not, left shift. Increment E.  
    // when 1 is found, exit loop and do one more increment + left shift. 
    int EXP = Bias - E;
    //printf("EXP: %d\n", EXP);
    //copies 8 most sig. bits
    unsigned workingFrac = (newFrac >> 24) & 0xFF;
    //printf("Init Whole: %u, Frac: %u\n", EXP, workingFrac);
    if((workingFrac << 24) != newFrac){
      //rounding
    //  printf("Rounding error? orig: %u, new: %u\n", newFrac, workingFrac);
      workingFrac = workingFrac<<24;
      return rounding(number, workingFrac);
    }
    else{
      //workingFrac = (workingFrac >> 24) & 0xFF;
      returnVal = 0;
     // printf("Whole: %u, Frac: %u\n", EXP, workingFrac);
      if(number->is_negative==1){returnVal |= 0b1000000000000;}
      //printf("Returning: %u\n", returnVal);
      //printf("Is Neg?: %d", number->is_negative);
      returnVal |= EXP;
      returnVal = returnVal<< 8;
      returnVal |= workingFrac;
    }
    //printf("Returning: %u\n", returnVal);
    return returnVal;
  }
}

/* toTinySF - Converts a Number Struct (whole and fraction parts) into a TINYSF Value
 *  - number is managed by zuon, DO NOT FREE number.
 *  - Follow the project documentation for this function.
 * Return the TINYSF Value.
 */

tinysf_s toTinySF(Number_s *number) {
  unsigned int A = number->whole;
  unsigned int B = number->fraction;
  unsigned int frac = 0;
  int i;
  //printf("Is Neg?: %d", number->is_negative);
  tinysf_s returnVal = 0;
  if(number->is_nan == 1){ //also check if number is an overflow/underflow
  //Case: whole and frac are 0
    if(number->is_negative == 1){returnVal =0x1F80;}
    else{returnVal = 0xF80;}
    return returnVal;
  }
  else if(number->is_infinity == 1 && number->is_nan == 0){
    if(number->is_negative == 1){returnVal =0x1F00;}
    else{returnVal = 0xF00;}
    return returnVal;
  }
  else{
      //printf("Ping1\n");

      if (A == 0 && B == 0) {
       // printf("Ping2\n");
        if(number->is_negative == 0){returnVal = 0;}
        else{returnVal |= 1 << 13;}//set 13th bit
        return returnVal;
    } 
      else if(A==0 && B > 0){
        //printf("Ping3\n");
       // printf("Is it 0?: %u\n", number->whole);
       // printf("Is it frac?: %u\n", number->fraction);
        return binaryDenormCheck(number);
      }
      else{
       // printf("Ping4\n");
        return binary(number);
      }
  }
}

/* toNumber - Converts a TINYSF Value into a Number Struct (whole and fraction parts)
 *  - number is managed by zuon, DO NOT FREE or re-Allocate number.
 *    - (It is already allocated)
 *  - Follow the project documentation for this function.
 * Return .
 */
int toNumber(Number_s *number, tinysf_s value) {
  //reverse of toTinySF
  //make a helper for decoding frac and mantissa
  int Bias = 7;
 // printf("val: %u\n", value);
  unsigned valueCopy = value;
  number->is_negative = (valueCopy >> (12)) % 2;
  unsigned  mask;
  //inf and nan
  mask = (1 << 12) - 1;
  unsigned last12bits = valueCopy & mask;
  if(number->is_negative == 1){
    if(last12bits == 0x1F00){number->is_infinity = 1; }
    if(last12bits == 0x1F80){number->is_nan = 1; }
  }
  else{
    if(last12bits == 0xF00){number->is_infinity = 1; }
    if(last12bits == 0xF80){number->is_nan = 1; }
  }
  unsigned exp = (last12bits >> 8);
  unsigned frac = ((exp <<8)^ last12bits);
  //this can be set directly to frac
  //printf("Exp: %u, Frac: %u\n", exp, frac);
  int E = exp - Bias;
  unsigned mantissa = (1<<8) | frac;
 // printf("Exp: %u, Frac: %u\n", exp, frac);
 // printf("E: %u, Mantissa: %u\n", E, mantissa);
  number->fraction = frac<<24;
  number->whole =1;
  frac = number->fraction;
  int count = E;
  while(count >0){
    //printf("---------------\n");
    unsigned MSB =  frac & 0x80000000;
    //newFrac |= LSB << (sizeof(newFrac) * 8 - 1);
    number->whole = (number->whole << 1) | (MSB >> 31);
    number->fraction <<= 1;
    frac = frac <<1;
    count--;
 //   printf("LSB: %u, Count: %d\n", LSB, E);
  }
 // printf("New val: %u, %u\n", number->whole, number->fraction);
  return 1;
}

/* opTinySF - Performs an operation on two tinySF values
 *  - Follow the project documentation for this function.
 * Return the resulting tinysf_s value or -1 if operator was invalid.
 */
tinysf_s opTinySF(char operator, tinysf_s val1, tinysf_s val2) { // Replace this Line with your Code!
  // make 3 helper functions, one for each of the operations. 
  if(operator == '+'){return opTinyAdd(val1, val2);}
  else if(operator == '-'){return opTinySub(val1, val2);}
  else if(operator == '*'){return opTinyMult(val1, val2);}
  else{ return -1;}
}

/* negateTINYSF - Negates a TINYSF Value.
 *  - Follow the project documentation for this function.
 * Return the resulting TINYSF Value
 */
tinysf_s negateTinySF(tinysf_s value) {
  unsigned int mask = 1 << 12; // create mask with 13th bit set to 1
  tinysf_s returnVal = value ^ mask;
  //printf("NUM: %u\n", returnVal);
  return returnVal;
}
