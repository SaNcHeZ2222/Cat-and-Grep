#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct my_struct {
  int default_search;
  int ignore_register_search;
  int inverse_search;
  int count_search;
  int name_file_search;
  int number_print_search;
  int file_patern_search;
  int sting_no_file_search;
  int ignore_exist_file;
  int get_find_elem;
};

void find_default_search(FILE *f, char *text_find, int count_file,
                         char *file_name) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char line[10000];
  while (fgets(line, 10000, f) != NULL) {
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      if (count_file > 1) {
        printf("%s:%s", file_name, line);
      } else {
        printf("%s", line);
      }
    }
  }
  regfree(&regex);
}

void find_ignore_register_search(FILE *f, char *text_find, int count_file,
                                 char *file_name) {
  regex_t regex;
  for (int i = 0; text_find[i]; i++) {
    text_find[i] = tolower(text_find[i]);
  }
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char line[10000];
  char copy_lower_line[10000];
  char last_string_done[10000];
  int count_search = 0;
  while (fgets(line, 10000, f) != NULL) {
    strcpy(copy_lower_line, line);
    for (int i = 0; line[i]; i++) {
      line[i] = tolower(line[i]);
    }
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      strcpy(last_string_done, line);
      count_search++;
      if (count_file > 1) {
        printf("%s:%s", file_name, copy_lower_line);
      } else {
        printf("%s", copy_lower_line);
      }
    }
  }
  if (strstr(last_string_done, "\0") != NULL &&
      strstr(last_string_done, "\n") == NULL && count_search > 0)
    printf("\n");
  regfree(&regex);
}

void find_inverse_search(FILE *f, char *text_find, int count_file,
                         char *file_name) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char line[10000];
  char last_string_done[10000];
  while (fgets(line, 10000, f)) {
    if (regexec(&regex, line, 0, NULL, 0) != 0) {
      strcpy(last_string_done, line);
      if (count_file > 1) {
        printf("%s:%s", file_name, line);

      } else {
        printf("%s", line);
      }
    }
  }
  if (strstr(last_string_done, "\0") != NULL &&
      strstr(last_string_done, "\n") == NULL)
    printf("\n");
  regfree(&regex);
}

void find_count_search(FILE *f, char *text_find, char *name, int count_file) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  int count = 0;
  char line[10000];
  while (fgets(line, 10000, f) != NULL) {
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      count++;
    }
  }
  if (count_file > 1)
    printf("%s:%d\n", name, count);
  else
    printf("%d\n", count);
  regfree(&regex);
}

void find_name_search(FILE *f, char *text_find, char *name) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char line[255];
  int count = 0;
  while (fgets(line, sizeof(line), f) != NULL) {
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      count++;
      printf("%s", name);
      break;
    }
  }
  if (count > 0) printf("\n");
  regfree(&regex);
}

void find_num_string_search(FILE *f, char *text_find, char *name,
                            int count_file) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char last_string_done[10000];
  int id_string = 1;
  char line[10000];
  while (fgets(line, 10000, f)) {
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      strcpy(last_string_done, line);
      if (count_file > 1)
        printf("%s:%d:%s", name, id_string, line);
      else
        printf("%d:%s", id_string, line);
    }
    id_string++;
  }
  if (strstr(last_string_done, "\0") != NULL &&
      strstr(last_string_done, "\n") == NULL)
    printf("\n");
  regfree(&regex);
}

void sting_no_file_search_func(FILE *f, char *text_find) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char line[10000];
  char last_string_done[10000];

  while (fgets(line, 10000, f) != NULL) {
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      strcpy(last_string_done, line);

      printf("%s", line);
    }
  }
  if (strstr(last_string_done, "\0") != NULL &&
      strstr(last_string_done, "\n") == NULL)
    printf("\n");
  regfree(&regex);
}

void file_patern_search_func(FILE *f, char *text_find, char *name,
                             int count_file) {
  FILE *patternFile = fopen(text_find, "r");
  char line[10000];
  char pattern[10000];
  while (fgets(line, 10000, f) != NULL) {
    line[strcspn(line, "\n")] = '\0';
    regex_t regex;
    while (fgets(pattern, 10000, patternFile) != NULL) {
      pattern[strcspn(pattern, "\n")] = '\0';
      if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        continue;
      }
      if (regexec(&regex, line, 0, NULL, 0) == 0) {
        if (count_file > 1)
          printf("%s:%s\n", name, line);
        else
          printf("%s\n", line);
        break;
      }
    }
    fseek(patternFile, 0, SEEK_SET);
    regfree(&regex);
  }
  fclose(patternFile);
}

void get_find_elem_func(FILE *f, char *text_find, char *name, int count_file) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char line[10000];
  while (fgets(line, 10000, f)) {
    regmatch_t matches[1];
    int start = 0;
    while (regexec(&regex, line + start, 1, matches, 0) == 0) {
      if (count_file > 1) printf("%s:", name);

      for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
        printf("%c", line[start + i]);
      }
      printf("\n");
      start += matches[0].rm_eo;
    }
  }
  regfree(&regex);
}

void find_ingore_register_or_inverse_search_more_flag(FILE *f, char *text_find,
                                                      int count_file,
                                                      char *name,
                                                      struct my_struct info) {
  regex_t regex;
  if (info.ignore_register_search == 1) {
    if (regcomp(&regex, text_find, REG_ICASE) != 0) {
      printf("Ошибка компиляции регулярного выражения.\n");
      exit(1);
    }
  } else {
    if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
      printf("Ошибка компиляции регулярного выражения.\n");
      exit(1);
    }
  }
  char line[10000];
  char last_string_done[10000];
  int count_search = 0;
  int id = 0;
  while (fgets(line, 10000, f)) {
    id++;
    if (regexec(&regex, line, 0, NULL, 0) == info.inverse_search) {
      strcpy(last_string_done, line);
      count_search++;
      if (info.default_search == 1 ||
          (info.inverse_search == 1 && info.sting_no_file_search == 0 &&
           info.count_search == 0 && info.name_file_search == 0 &&
           info.number_print_search == 0) ||
          info.ignore_exist_file == 1) {
        if (count_file > 1) {
          printf("%s:%s", name, line);
        } else {
          printf("%s", line);
        }
      }
      if (info.number_print_search == 1) {
        if (count_file > 1) {
          printf("%s:%d:%s", name, id, line);
        } else {
          printf("%d:%s", id, line);
        }
      }
      if (info.sting_no_file_search == 1) printf("%s", line);
    }
  }
  if (strstr(last_string_done, "\0") != NULL &&
      strstr(last_string_done, "\n") == NULL && count_search > 0 &&
      info.count_search == 0)
    printf("\n");
  if (info.count_search == 1) {
    if (count_file > 1)
      printf("%s:%d\n", name, count_search);
    else
      printf("%d\n", count_search);
  }
  if (info.name_file_search) printf("%s\n", name);
  regfree(&regex);
}

void find_count_search_more_flag(FILE *f, char *text_find, int count_file,
                                 char *name, struct my_struct info) {
  regex_t regex;
  if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
    printf("Ошибка компиляции регулярного выражения.\n");
    exit(1);
  }
  char line[10000];
  int count_search = 0;
  int id = 0;
  while (fgets(line, 10000, f) != NULL) {
    id++;
    if (regexec(&regex, line, 0, NULL, 0) == info.inverse_search) {
      count_search++;
      if (info.sting_no_file_search == 1 && info.number_print_search == 1) {
        printf("%d:%s", id, line);
      } else if (info.ignore_exist_file == 1 && info.default_search == 1) {
        if (count_file > 1)
          printf("%s:%s", name, line);
        else
          printf("%s", line);
      } else if (info.number_print_search == 1 && info.default_search == 1) {
        if (count_file > 1)
          printf("%d:%s:%s", id, name, line);
        else
          printf("%d:%s", id, line);
      }
    }
  }

  if (info.name_file_search == 1 && info.count_search == 1) {
    if (count_file > 1)
      printf("%s:%d\n", name, 1);
    else
      printf("%d\n", 1);
    printf("%s\n", name);
  } else if (info.name_file_search == 1 && info.count_search == 0) {
    printf("%s\n", name);
  } else if (info.sting_no_file_search == 0 && info.number_print_search == 0 &&
             (info.ignore_exist_file == 0 && info.default_search == 0)) {
    if (count_file > 1)
      printf("%s:%d\n", name, count_search);
    else
      printf("%d\n", count_search);
  }

  regfree(&regex);
}

void find_get_find_elem_more_flag(FILE *f, char *text_find, int count_file,
                                  char *name, struct my_struct info) {
  regex_t regex;
  if (info.ignore_register_search == 1) {
    if (regcomp(&regex, text_find, REG_ICASE) != 0) {
      printf("Ошибка компиляции регулярного выражения.\n");
      exit(1);
    }
  } else {
    if (regcomp(&regex, text_find, REG_EXTENDED) != 0) {
      printf("Ошибка компиляции регулярного выражения.\n");
      exit(1);
    }
  }
  char line[10000];
  int id = 0;
  while (fgets(line, 10000, f)) {
    regmatch_t matches[1];
    int start = 0;
    id++;
    while (regexec(&regex, line + start, 1, matches, 0) ==
           info.inverse_search) {
      if (count_file > 1 && info.sting_no_file_search == 0) printf("%s:", name);
      if (info.number_print_search == 1) printf("%d:", id);
      for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
        printf("%c", line[start + i]);
      }
      printf("\n");
      start += matches[0].rm_eo;
    }
  }
  regfree(&regex);
}

void find_pattern_more_flag(FILE *f, char *text_find, int count_file,
                            char *name, struct my_struct info) {
  FILE *patternFile = fopen(text_find, "r");
  char line[10000];
  char pattern[10000];
  int id = 0;
  int count_find = 0;
  while (fgets(line, 10000, f) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    id++;
    int find = 0;
    regex_t regex;

    while (fgets(pattern, 10000, patternFile) != NULL) {
      pattern[strcspn(pattern, "\n")] = '\0';
      if (info.ignore_exist_file == 1) {
        if (regcomp(&regex, pattern, REG_ICASE) != 0) {
          continue;
        }
      } else {
        if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
          continue;
        }
      }
      if (regexec(&regex, line, 0, NULL, 0) == 0 && info.inverse_search == 0) {
        find = 1;
        if (info.name_file_search == 0) {
          if (info.number_print_search == 1) {
            if (count_file > 1)
              printf("%s:%d:%s\n", name, id, line);
            else
              printf("%d:%s\n", id, line);
          } else if (info.sting_no_file_search == 1) {
            printf("%s\n", line);
          } else {
            if (count_file > 1)
              printf("%s:%s\n", name, line);
            else
              printf("%s\n", line);
          }
        }
        break;
      }
      if (regexec(&regex, line, 0, NULL, 0) == 0 && info.inverse_search == 1) {
        find = 1;
        break;
      }
      regfree(&regex);
    }
    regfree(&regex);

    if (info.inverse_search == 1 && find == 0) {
      if (count_file > 1)
        printf("%s:%s\n", name, line);
      else
        printf("%s\n", line);
    }
    if (find == 1) count_find++;
    fseek(patternFile, 0, SEEK_SET);
  }
  if (patternFile != NULL) fclose(patternFile);
  if (count_file > 1 && info.count_search == 1)
    printf("%s:%d\n", name, count_find);
  else if (count_file == 0 && info.count_search == 1)
    printf("%d\n", count_find);
  if (id > 0 && info.name_file_search) printf("%s\n", name);
}

void grep_more_flag(char *name, char *text_find, int default_search,
                    int count_file, int ignore_register_search,
                    int inverse_search, int count_search, int name_file_search,
                    int number_print_search, int file_patern_search,
                    int sting_no_file_search, int ignore_exist_file,
                    int get_find_elem) {
  FILE *f = fopen(name, "r");
  if (f == NULL && ignore_exist_file != 1) {
    printf("Файла нет");
  } else {
    struct my_struct info;
    info.default_search = default_search;
    info.ignore_register_search = ignore_register_search;
    info.inverse_search = inverse_search;
    info.count_search = count_search;
    info.name_file_search = name_file_search;
    info.number_print_search = number_print_search;
    info.file_patern_search = file_patern_search;
    info.sting_no_file_search = sting_no_file_search;
    info.ignore_exist_file = ignore_exist_file;
    info.get_find_elem = get_find_elem;
    if (file_patern_search == 1)
      find_pattern_more_flag(f, text_find, count_file, name, info);
    else if ((ignore_register_search == 1 || inverse_search == 1) &&
             get_find_elem == 0)
      find_ingore_register_or_inverse_search_more_flag(f, text_find, count_file,
                                                       name, info);
    else if ((count_search == 1 || name_file_search == 1 ||
              number_print_search == 1 || default_search == 1) &&
             get_find_elem == 0)
      find_count_search_more_flag(f, text_find, count_file, name, info);
    else if (get_find_elem == 1)
      find_get_find_elem_more_flag(f, text_find, count_file, name, info);
  }
  if (f != NULL) fclose(f);
}

void grep_one_flag(char *name, char *text_find, int default_search,
                   int count_file, int ignore_register_search,
                   int inverse_search, int count_search, int name_file_search,
                   int number_print_search, int file_patern_search,
                   int sting_no_file_search, int ignore_exist_file,
                   int get_find_elem) {
  FILE *f = fopen(name, "r");
  if (ignore_exist_file == 0 && f == NULL)
    printf("Файла нет");
  else if ((default_search == 1 || ignore_exist_file == 1) && f != NULL)
    find_default_search(f, text_find, count_file, name);
  else if (ignore_register_search == 1 && f != NULL)
    find_ignore_register_search(f, text_find, count_file, name);
  else if (inverse_search == 1 && f != NULL)
    find_inverse_search(f, text_find, count_file, name);
  else if (count_search == 1 && f != NULL)
    find_count_search(f, text_find, name, count_file);
  else if (name_file_search == 1 && f != NULL)
    find_name_search(f, text_find, name);
  else if (number_print_search == 1 && f != NULL)
    find_num_string_search(f, text_find, name, count_file);
  else if (file_patern_search == 1 && f != NULL)
    file_patern_search_func(f, text_find, name, count_file);
  else if (sting_no_file_search == 1 && f != NULL)
    sting_no_file_search_func(f, text_find);
  else if (get_find_elem == 1 && f != NULL)
    get_find_elem_func(f, text_find, name, count_file);
  if (f != NULL) fclose(f);
}

int main(int argc, char **argv) {
  char *text_find = NULL;
  int default_search = 0, ignore_register_search = 0, inverse_search = 0,
      count_search = 0, name_file_search = 0, number_print_search = 0,
      patern = 1, count_file = 0, file_patern_search = 0,
      sting_no_file_search = 0, ignore_exist_file = 0, c, get_find_elem = 0;
  int first_file = 1;
  static struct option long_options[] = {{0, 0, 0, 0}};
  while ((c = getopt_long(argc, argv, "eivclnfhso", long_options, NULL)) !=
         -1) {
    if (c == 'e')
      default_search = 1;
    else if (c == 'i')
      ignore_register_search = 1;
    else if (c == 'v')
      inverse_search = 1;
    else if (c == 'c')
      count_search = 1;
    else if (c == 'l')
      name_file_search = 1;
    else if (c == 'n')
      number_print_search = 1;
    else if (c == 'f')
      file_patern_search = 1;
    else if (c == 'h')
      sting_no_file_search = 1;
    else if (c == 's')
      ignore_exist_file = 1;
    else if (c == 'o')
      get_find_elem = 1;
  }
  if (inverse_search == 1 &&
      (get_find_elem == 1 || name_file_search == 1 || count_search == 1))
    get_find_elem = 0;
  if (file_patern_search == 1) ignore_exist_file = 0;
  for (int i = 2; i < argc; i++) {
    if (patern == 1) {
      patern = 0;
      text_find = argv[i];
      count_file = argc - i - 1;
      continue;
    }
    int summa_flag = default_search + ignore_register_search + inverse_search +
                     count_search + name_file_search + number_print_search +
                     file_patern_search + sting_no_file_search +
                     ignore_exist_file + get_find_elem;
    if (summa_flag == 1) {
      if (first_file == 1 && (count_search == 1)) first_file = 0;
      grep_one_flag(argv[i], text_find, default_search, count_file,
                    ignore_register_search, inverse_search, count_search,
                    name_file_search, number_print_search, file_patern_search,
                    sting_no_file_search, ignore_exist_file, get_find_elem);
    } else {
      grep_more_flag(argv[i], text_find, default_search, count_file,
                     ignore_register_search, inverse_search, count_search,
                     name_file_search, number_print_search, file_patern_search,
                     sting_no_file_search, ignore_exist_file, get_find_elem);
    }
  }
  return 0;
}
