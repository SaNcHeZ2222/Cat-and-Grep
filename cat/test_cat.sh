#!/bin/bash

TEST_DATA_FOLDER="test_files"


passed_tests=0
failed_tests=0
failed_scenarios=()
passed_scenarios=()

for file in $TEST_DATA_FOLDER/*; do
  for flag in -b -e -n -s -t ; do
    for file2 in $TEST_DATA_FOLDER/*; do
      echo "Тест с флагом $flag в файлах $file $file2"

      # Вывод команды cat
      cat_command="cat $flag $file $file2"
      echo " "
      echo "Команда: $cat_command"
      cat_output=$(cat $flag $file $file2)
      echo "cat вывод:"
      echo "$cat_output"

      # Вывод команды s21_cat
      s21_cat_command="./s21_cat $flag $file $file2"
      echo " "
      echo "Команда: $s21_cat_command"
      s21_cat_output=$(./s21_cat $flag $file $file2)
      echo "s21_cat вывод:"
      echo "$s21_cat_output"

      # Сравнение выводов
      if [ "$cat_output" == "$s21_cat_output" ]; then
        echo " "
        echo "Тест Выполнен"
        passed_tests=$((passed_tests + 1))
        passed_scenarios+=("Фалг $flag в файлах $file ")
      else
        echo " "
        echo "Тест Не Выполнен"
        failed_tests=$((failed_tests + 1))
        failed_scenarios+=("Фалг $flag в файлах $file")
      fi

      echo "-------------------------"
    done
  done
done

for file in $TEST_DATA_FOLDER/*; do


  echo "Тест с флагом  --number-nonblank в файлах $file"

  # Вывод команды cat
  cat_command="cat -b $file"
  echo " "
  echo "Команда: $cat_command"
  cat_output=$(cat -b $file)
  echo "cat вывод:"
  echo "$cat_output"

  # Вывод команды s21_cat
  s21_cat_command="./s21_cat --number-nonblank $file"
  echo " "
  echo "Команда: $s21_cat_command"
  s21_cat_output=$(./s21_cat --number-nonblank $file)
  echo "s21_cat вывод:"
  echo "$s21_cat_output"

  # Сравнение выводов
  if [ "$cat_output" == "$s21_cat_output" ]; then
    echo " "
    echo "Тест Выполнен"
    passed_tests=$((passed_tests + 1))
    passed_scenarios+=("Фалг --number-nonblank в файлах $file")
  else
    echo " "
    echo "Тест Не Выполнен"
    failed_tests=$((failed_tests + 1))
    failed_scenarios+=("Фалг --number-nonblank в файлах $file")
  fi

  echo "-------------------------"

  echo "Тест с флагом  --number в файлах $file"

  # Вывод команды cat
  cat_command="cat -n $file"
  echo " "
  echo "Команда: $cat_command"
  cat_output=$(cat -n $file)
  echo "cat вывод:"
  echo "$cat_output"

  # Вывод команды s21_cat
  s21_cat_command="./s21_cat --number $file"
  echo " "
  echo "Команда: $s21_cat_command"
  s21_cat_output=$(./s21_cat --number $file)
  echo "s21_cat вывод:"
  echo "$s21_cat_output"

  # Сравнение выводов
  if [ "$cat_output" == "$s21_cat_output" ]; then
    echo " "
    echo "Тест Выполнен"
    passed_tests=$((passed_tests + 1))
    passed_scenarios+=("Фалг --number в файлах $file")
  else
    echo " "
    echo "Тест Не Выполнен"
    failed_tests=$((failed_tests + 1))
    failed_scenarios+=("Фалг --number в файлах $file")
  fi

  echo "-------------------------"

  

  echo "Тест с флагом  --number в файлах $file"

  # Вывод команды cat
  cat_command="cat -s $file"
  echo " "
  echo "Команда: $cat_command"
  cat_output=$(cat -s $file)
  echo "cat вывод:"
  echo "$cat_output"

  # Вывод команды s21_cat
  s21_cat_command="./s21_cat --squeeze-blank $file"
  echo " "
  echo "Команда: $s21_cat_command"
  s21_cat_output=$(./s21_cat --squeeze-blank $file)
  echo "s21_cat вывод:"
  echo "$s21_cat_output"

  # Сравнение выводов
  if [ "$cat_output" == "$s21_cat_output" ]; then
    echo " "
    echo "Тест Выполнен"
    passed_tests=$((passed_tests + 1))
    passed_scenarios+=("Фалг --squeeze-blank в файлах $file")
  else
    echo " "
    echo "Тест Не Выполнен"
    failed_tests=$((failed_tests + 1))
    failed_scenarios+=("Фалг --squeeze-blank в файлах $file")
  fi

  echo "-------------------------"

 

done



for file in $TEST_DATA_FOLDER/*; do
  for flag in -b -e -n -s -t; do
    echo "Тест с флагом $flag в файле $file"

    # Вывод команды cat
    cat_command="cat $flag $file"
    echo " "
    echo "Команда: $cat_command"
    cat_output=$(cat $flag "$file")
    echo "cat вывод:"
    echo "$cat_output"

    # Вывод команды s21_cat
    s21_cat_command="./s21_cat $flag $file"
    echo " "
    echo "Команда: $s21_cat_command"
    s21_cat_output=$(./s21_cat $flag "$file")
    echo "s21_cat вывод:"
    echo "$s21_cat_output"

    # Сравнение выводов
    if [ "$cat_output" == "$s21_cat_output" ]; then
      echo " "
      echo "Тест Выполнен"
      passed_tests=$((passed_tests + 1))
      passed_scenarios+=("Флаг $flag в файле $file")
    else
      echo " "
      echo "Тест Не Выполнен"
      failed_tests=$((failed_tests + 1))
      failed_scenarios+=("Флаг $flag в файле $file")
    fi

    echo "-------------------------"
  done
done

# Вывод краткого результата
echo "Итог:"
echo "Выполненных тестов: $passed_tests"
echo "Ошибочных тестов: $failed_tests"
echo " "
echo "Ошибки:"
for scenario in "${failed_scenarios[@]}"; do
  echo "$scenario"
done
echo " "
echo "Выполнились:"
for scenario in "${passed_scenarios[@]}"; do
  echo "$scenario"
done
