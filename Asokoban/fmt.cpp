#include <stdint.h>
#include "fmt.h"

#define MAX_SECONDS 5999
void uint_to_str(uint8_t* str, uint8_t *len, uint8_t n);

void FmtMMSS(uint16_t seconds, uint8_t* str, bool leading_zero) {
  // Return seconds in format mm:ss (minutes:seconds).
  // Maximum: 99:59
  uint8_t mm, ss;
  uint8_t length, position;

  if (seconds > MAX_SECONDS) {
    seconds = MAX_SECONDS;
  }

  mm = seconds / 60;
  ss = seconds % 60;

  uint_to_str(str, &position, mm);
  if (leading_zero && (position == 1)) {
    str[1] = str[0];
    str[0] = '0';
    position++;
  }
  str[position++] = ':';

  uint_to_str(str + position, &length, ss);

  if (length == 1) {
    str[position + 1] = str[position];
    str[position] = '0';
  }
  str[position + 2] = 0;
}

void FmtTime(uint16_t seconds, uint8_t* str) {
  /* Format milliseconds (ms) into minutes:seconds.decisecond
     Max length of str: 1:2:2.1 = 10 characters. */
  uint8_t hours, l=0;

  hours = seconds / 3600;
  uint_to_str(str, &l, hours);
  str[l] = ':';

  seconds = seconds % 3600;

  FmtMMSS(seconds, str + l + 1, true);
}

void uint_to_str(uint8_t* str, uint8_t *len, uint8_t n) {
  /* Transform one byte integer  to string. str must have at least 6 places */
  uint8_t buffer[3];
  int i;

  if (n == 0) {
    str[0] = '0';
    *len = 1;
    return;
  }
  for (*len=0; (*len<5) && (n!=0); (*len)++) {
    buffer[*len] = '0' + (n % 10);
    n /= 10;
  }
  for (i = *len - 1; i >=0; i--) {
    str[i] = buffer[*len - 1 - i];
  }
}
