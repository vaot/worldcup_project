#include <cstdlib>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

// By Victor Andrey Oliveira Teles(vaot)
// Meant to support project implementation, providing
// handy functions.

#ifndef VAOT_UTILITIES_H_
#define VAOT_UTILITIES_H_

namespace vaot {

  static float clockToSeconds(clock_t temp) {
    return (((float)temp)/CLOCKS_PER_SEC);
  }

  static bool include(int list[], int el, int size) {
    for (int i = 0; i < size; ++i) {
      if (list[i] == el) {
        return true;
      }
    }
    return false;
  }

  static void swapValues(int list[], int pos1, int pos2) {
    int temp = list[pos1];
    list[pos1] = list[pos2];
    list[pos2] = temp;
  }

  static int toInt(string numericString) {
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

  static int randomInt(int from, int to) {
    return (from + rand() % (to - from + 1));
  }

  static double randomDouble(double from, double to) {
    return ((to - from) * ( (double)rand() / (double)RAND_MAX ) + from);
  }

  static void bubbleSort(int list[], int size) {
    // In bubble sort, we just need to iterate
    // again, provided that there is a swap.
    bool flag = true;
    for (int i = 0; (i < size) && flag; ++i) {
      flag = false;
      for (int j = 0; j < size - 1; ++j) {
        if (list[j] > list[j + 1]) {
          swapValues(list, j, j+1);
          flag = true;
        }
      }
    }
  }

  static void selectionSort(int list[], int size) {
    int smallest;
    for (int i = 0; i < size; ++i) {
      smallest = i;

      // Find the smallest
      for (int j = i + 1; j < size; ++j) {
        if (list[smallest] > list[j]) smallest = j;
      }

      swapValues(list, smallest, i);
    }
  }

  static void insertionSort(int list[], int size) {
    for (int i = 1; i < size; ++i) {
      int outerIndex = i;
      // Move to left side of array
      while (outerIndex > 0 && list[outerIndex - 1] > list[outerIndex]) {
        swapValues(list, outerIndex-1, outerIndex);
        outerIndex--;
      }
    }
  }

  static void reverseArray(int list[], int size) {
    for (int l = 0, r = size - 1; l < r; l++, r--) {
      swapValues(list, r, l);
    }
  }

  static void reverseArrayRec(int list[], int left, int right) {
    if (left > right) return;
    swapValues(list, left, right);
    reverseArrayRec(list, left+1, right-1);
  }

  static void openUrl(string url) {
    // You are welcome KJ :)
    #ifdef _WIN32
      ShellExecute(NULL, TEXT("open"), TEXT(url.c_str()), NULL, NULL, SW_SHOWNORMAL);
    #endif
    // Mac users
    #ifdef __APPLE__
      system(("open " + url).c_str());
    #endif
  }

  static void playSound(string name) {
     // You are welcome KJ :)
    #ifdef _WIN32
      PlaySound(TEXT(name.c_str()), NULL, SND_ASYNC);
    #endif
    // Mac users
    #ifdef __APPLE__
      system(("open " + name).c_str());
    #endif
  }

}

#endif
