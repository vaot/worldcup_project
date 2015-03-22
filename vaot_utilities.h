// By Victor Andrey Oliveira Teles(vaot)
// Meant to support project implementation, providing
// handy functions.
#ifndef VAOT_UTILITIES
#define VAOT_UTILITIES

namespace vaot {

  int toInt(string numericString) {
    int temp;
    int decimalPlace(1);
    int total(0);
    for (int i = numericString.size() - 1; i >= 0 ; --i) {
      // We now that adding 48 to digits we can get their ascii,
      // so we do the following:
      temp = static_cast<int>(numericString[i]) - '0';
      total += (temp*decimalPlace);
      // Move to next decimal place
      decimalPlace *= 10;
    }
    return total;
  }

}

#endif
