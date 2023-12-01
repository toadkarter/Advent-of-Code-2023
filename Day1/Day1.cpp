#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>

class positioned_number {
public:
  positioned_number() : index(-1), value(-1), is_set(false) {};

  void set_values(int in_index, int in_value) {
    index = in_index;
    value = in_value;
    is_set = true;
  }

  [[nodiscard]] int get_index() const {
    return index;
  }

  [[nodiscard]] int get_value() const {
    return value;
  }

  [[nodiscard]] bool value_is_set() const {
    return is_set;
  }

private:
  int index;
  int value;

  bool is_set;
};

std::vector<std::pair<std::string, int>> number_words{
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9},
};

void get_digits_from_words(std::unique_ptr<positioned_number>& left_number,
                           std::unique_ptr<positioned_number>& right_number,
                           const std::string& line) {

  for (const std::pair<std::string, int>& word_pair : number_words) {
    int index = (int)line.find(word_pair.first);

    if (index == -1) {
      continue;
    }

    if (!left_number->value_is_set()) {
      left_number->set_values(index, word_pair.second);
      continue;
    }

    if (index < left_number->get_index()) {
      right_number->set_values(left_number->get_index(), left_number->get_value());
      left_number->set_values(index, word_pair.second);
    } else {
      right_number->set_values(index, word_pair.second);
    }
  }
}

void get_digits_from_numbers(std::unique_ptr<positioned_number>& left_number,
                           std::unique_ptr<positioned_number>& right_number,
                           const std::string& line) {
  for (int i = 0; i < line.length(); i++) {
    const char current_char = line.at(i);
    if (std::isdigit(current_char)) {
      if (!left_number->value_is_set()) {
        left_number->set_values(i, current_char - '0');
        continue;
      }

      if (i < left_number->get_index() && left_number->value_is_set()) {
        if (!right_number->value_is_set()) {
          right_number->set_values(left_number->get_index(), left_number->get_value());
        }
        left_number->set_values(i, current_char - '0');
      } else if (i > right_number->get_index() && right_number->value_is_set()) {
        right_number->set_values(i, current_char - '0');
      }
    }
  }

  if (!right_number->value_is_set()) {
    right_number->set_values(left_number->get_index(),
                             left_number->get_value());
  }
}

int get_double_digit(const std::string& line) {
  std::unique_ptr<positioned_number> left_number =
      std::make_unique<positioned_number>();
  std::unique_ptr<positioned_number> right_number =
      std::make_unique<positioned_number>();

  get_digits_from_words(left_number, right_number, line);
  get_digits_from_numbers(left_number, right_number, line);

  return left_number->get_value() * 10 + right_number->get_value();
}

int main() {
    std::ifstream input_file("input.txt");
    
    int final_sum = 0;
    std::string current_line;
//    while (std::getline(input_file, current_line)) {
//      int double_digit = get_double_digit(current_line);
//      final_sum += double_digit;
//    }

    std::cout << get_double_digit("eightwothree");

//    std::cout << final_sum << std::endl;

    return 0;
}
