#include "utils.hpp"

// Linearly Maps a given value within a given range to a new value within a new range */
double l_map(double x, double input_start, double input_end, double output_start, double output_end)
{
  if (input_end == input_start) {

    printf("Error in l_map(), Cannot Map a value when input_end == input_start! \n");
    return -1.0;

  } else {

    double slope = (output_end - output_start) / (input_end - input_start);
    return output_start + slope * (x - input_start);

  }
}

// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
//This function was not written by Skyler Hughes
sf::Color hsv(int hue, float sat, float val)
{
  hue %= 360;
  while(hue<0) hue += 360;

  if(sat<0.f) sat = 0.f;
  if(sat>1.f) sat = 1.f;

  if(val<0.f) val = 0.f;
  if(val>1.f) val = 1.f;

  int h = hue/60;
  float f = float(hue)/60-h;
  float p = val*(1.f-sat);
  float q = val*(1.f-sat*f);
  float t = val*(1.f-sat*(1-f));

  switch(h)
  {
    default:
    case 0:
    case 6: return sf::Color(val*255, t*255, p*255);
    case 1: return sf::Color(q*255, val*255, p*255);
    case 2: return sf::Color(p*255, val*255, t*255);
    case 3: return sf::Color(p*255,   q*255, val*255);
    case 4: return sf::Color(t*255,   p*255, val*255);
    case 5: return sf::Color(val*255, p*255, q*255);
  }
}

unsigned long int_concat(unsigned long a, unsigned long b)
{
  unsigned long pow = 10;
  while(b >= pow)
    pow *= 10;

  return a * pow + b;
}
unsigned long stringtocharval(const char *string)
{
  unsigned long output = *string;
  string++;
  while(*string != '\0')
  {
    output = int_concat(output, *string);
    string++;
  }
  return output;
}