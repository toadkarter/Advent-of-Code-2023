#include <iostream>
#include <fstream>

int get_double_digit(const std::string& line) {
  char first_digit = '\0';
  char second_digit = '\0';

  for (const char current_char : line) {
    if (std::isdigit(current_char)) {
      if (first_digit == '\0') {
        first_digit = current_char;
      } else {
        second_digit = current_char;
      }
    }
  }

  return (first_digit - '0') * 10 + (second_digit - '0');
}

int main() {
    std::ifstream input_file("input.txt");
    
    int final_sum = 0;
    std::string current_line;
    while (getline(input_file, current_line)) {
      final_sum += get_double_digit(current_line);
    }

    std::cout << final_sum << std::endl;

    return 0;
}
