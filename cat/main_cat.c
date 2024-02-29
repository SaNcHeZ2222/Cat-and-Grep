#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(FILE *f) {
  char string[10000];
  while (!feof(f)) {
    fgets(string, 10000, f);
    printf("%s", string);
  }
}

void tab_replace_func(FILE *f, int t) {
  int c = fgetc(f);
  while (c != EOF) {
    if (c == '\t') {
      putc('^', stdout);
      putc('I', stdout);

    } else if (c == '\n')
      putc('\n', stdout);
    else if (((c >= 0 && c <= 31) || c == 127 || (c >= 128 && c <= 159)) &&
             c != 10 && c != 9 && t == 1) {
      if (c == 127)
        printf("^?");
      else if (c >= 128 && c <= 159)
        printf("M-^%c", c - 64);
      else
        printf("^%c", c + 64);

    } else {
      putc(c, stdout);
    }
    c = fgetc(f);
  }
}

void remove_empty_string(FILE *file) {
  int symbol, count = 1, new_str = 0;
  while ((symbol = fgetc(file)) != EOF) {
    if (symbol != '\n') {
      printf("%c", symbol);
      new_str = 0;
      count = 0;
    } else if (new_str < 2 && count != 2) {
      printf("%c", symbol);
      new_str++;
      count++;
    }
  }
}

void print_all_number(FILE *f) {
  int c = fgetc(f);
  int id = 1;

  int flag_new_str = 0;
  int first_string = 1;
  while (c != EOF) {
    if (first_string == 1) {
      first_string = 0;

      printf("%6d\t", id);
      id++;
    }
    if (c == '\n' && flag_new_str == 0) {
      flag_new_str = 1;
    } else if (c == '\n' && flag_new_str == 1) {
      flag_new_str = 1;

      printf("%6d\t", id);
      id++;
    } else if (flag_new_str == 1) {
      flag_new_str = 0;

      printf("%6d\t", id);
      id++;
    }
    putc(c, stdout);
    c = fgetc(f);
  }
}

void print_dollar(FILE *f, int t) {
  int c = fgetc(f);
  while (c != EOF) {
    if (c == '\n') {
      putc('$', stdout);
      putc('\n', stdout);
    } else if (((c >= 0 && c <= 31) || c == 127 || (c >= 128 && c <= 159)) &&
               c != 10 && c != 9 && t == 1) {
      if (c == 127)
        printf("^?");
      else if (c >= 128 && c <= 159)
        printf("M-^%c", c - 64);
      else
        printf("^%c", c + 64);

    } else {
      putc(c, stdout);
    }
    c = fgetc(f);
  }
}

void print_file_number_nonblank(FILE *f) {
  int c = fgetc(f);
  int flag_new_str = 0;
  int id = 1;
  int first_string = 1;
  while (c != EOF) {
    if (first_string == 1 && c != '\n') {
      first_string = 0;
      printf("%6d\t", id);
      id++;
    } else if (c == '\n') {
      flag_new_str = 1;
    } else if (flag_new_str == 1) {
      flag_new_str = 0;
      printf("%6d\t", id);
      id++;
    }
    putc(c, stdout);
    c = fgetc(f);
  }
}

int main(int argc, char **argv) {
  int number_nonblank = 0, dollar_print = 0, number_all_string = 0,
      remove_empty_repetitive = 0, tab_replace = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--number-nonblank") == 0)
      number_nonblank = 1;
    else if (strcmp(argv[i], "-e") == 0)
      dollar_print = 1;
    else if (strcmp(argv[i], "-E") == 0)
      dollar_print = 2;
    else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0)
      number_all_string = 1;
    else if (strcmp(argv[i], "-s") == 0 ||
             strcmp(argv[i], "--squeeze-blank") == 0)
      remove_empty_repetitive = 1;
    else if (strcmp(argv[i], "-t") == 0)
      tab_replace = 1;
    else if (strcmp(argv[i], "-T") == 0)
      tab_replace = 2;
    else {
      FILE *f = fopen(argv[i], "r");
      int summa_flag = number_nonblank + dollar_print + number_all_string +
                       remove_empty_repetitive + tab_replace;
      if (number_nonblank == 1 && f != NULL) {
        print_file_number_nonblank(f);
      } else if ((dollar_print == 1 || dollar_print == 2) && f != NULL)
        print_dollar(f, dollar_print);
      else if (number_all_string == 1 && f != NULL) {
        print_all_number(f);
      } else if (remove_empty_repetitive == 1 && f != NULL)
        remove_empty_string(f);
      else if ((tab_replace == 1 || tab_replace == 2) && f != NULL)
        tab_replace_func(f, tab_replace);
      else if (f != NULL && summa_flag == 0)
        print_file(f);
      else {
        printf("Ты совершил ошибку!");
        break;
      }
      if (f != NULL) fclose(f);
    }
  }
  return 0;
}