#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct SymbolInfo {
  unordered_map<char, int> char_to_value;
  vector<char> value_to_char;
  int maxD;
};

SymbolInfo read_symbols(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    throw runtime_error("Could not open file " + filename);
  }

  string line;
  getline(file, line);
  istringstream iss(line);
  vector<char> symbols;
  unordered_set<char> seen_chars;
  string token;

  while (iss >> token) {
    if (token.size() != 1) {
      throw runtime_error("Invalid symbol (must be single character): " +
			  token);
    }
    char c = token[0];
    if (seen_chars.count(c)) {
      throw runtime_error("Duplicate character found: " + string(1, c));
    }
    seen_chars.insert(c);
    symbols.push_back(c);
  }

  if (symbols.empty()) {
    throw runtime_error("No symbols provided in the file.");
  }

  unordered_map<char, int> char_to_value;
  vector<char> value_to_char(symbols.size());
  for (int i = 0; i < symbols.size(); ++i) {
    char_to_value[symbols[i]] = i;
    value_to_char[i] = symbols[i];
  }

  return {char_to_value, value_to_char, static_cast<int>(symbols.size())};
}

long long str_to_decimal(const string &num_str, int base,
			 const unordered_map<char, int> &char_to_value) {
  long long result = 0;
  for (char c : num_str) {
    auto it = char_to_value.find(c);
    if (it == char_to_value.end()) {
      throw runtime_error("Character not found in symbol map: " + string(1, c));
    }
    int digit = it->second;
    result = result * base + digit;
  }
  return result;
}

string decimal_to_str(long long num, int base,
		      const vector<char> &value_to_char) {
  if (num == 0) {
    return string(1, value_to_char[0]);
  }

  vector<char> digits;
  while (num > 0) {
    int rem = num % base;
    digits.push_back(value_to_char[rem]);
    num = num / base;
  }

  reverse(digits.begin(), digits.end());
  return string(digits.begin(), digits.end());
}

void trim(string &s) {
  size_t end = s.find_last_not_of(" \t\n\r\f\v");
  if (end != string::npos) {
    s = s.substr(0, end + 1);
  } else {
    s.clear();
  }

  size_t start = s.find_first_not_of(" \t\n\r\f\v");
  if (start != string::npos) {
    s = s.substr(start);
  } else {
    s.clear();
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <symbols_file> <instructions_file>"
	 << endl;
    return 1;
  }

  SymbolInfo symbols;
  try {
    symbols = read_symbols(argv[1]);
  } catch (const exception &e) {
    cerr << "Error reading symbols: " << e.what() << endl;
    return 1;
  }

  ifstream instructions_file(argv[2]);
  if (!instructions_file.is_open()) {
    cerr << "Could not open instructions file: " << argv[2] << endl;
    return 1;
  }

  string line;
  while (getline(instructions_file, line)) {
    trim(line);
    if (line.empty()) {
      continue;
    }

    istringstream iss(line);
    vector<string> parts;
    string part;
    while (iss >> part) {
      parts.push_back(part);
    }

    if (parts.size() != 4) {
      cerr << "Invalid instruction line: " << line << endl;
      continue;
    }

    string operation = parts[0];
    string num1_str = parts[1];
    string num2_str = parts[2];
    string base_str = parts[3];

    int base;
    try {
      base = stoi(base_str);
    } catch (const exception &e) {
      cerr << "Invalid base: " << base_str << " in line: " << line << endl;
      continue;
    }

    if (base < 1 || base > symbols.maxD) {
      cerr << "Base out of range (1 to " << symbols.maxD << "): " << base
	   << " in line: " << line << endl;
      continue;
    }

    bool valid = true;
    for (char c : num1_str) {
      if (!symbols.char_to_value.count(c)) {
	cerr << "Invalid character '" << c << "' in num1 of line: " << line
	     << endl;
	valid = false;
	break;
      }
      int value = symbols.char_to_value.at(c);
      if (value >= base) {
	cerr << "Digit '" << c << "' in num1 exceeds base " << base
	     << " in line: " << line << endl;
	valid = false;
	break;
      }
    }
    if (!valid) {
      continue;
    }

    for (char c : num2_str) {
      if (!symbols.char_to_value.count(c)) {
	cerr << "Invalid character '" << c << "' in num2 of line: " << line
	     << endl;
	valid = false;
	break;
      }
      int value = symbols.char_to_value.at(c);
      if (value >= base) {
	cerr << "Digit '" << c << "' in num2 exceeds base " << base
	     << " in line: " << line << endl;
	valid = false;
	break;
      }
    }
    if (!valid) {
      continue;
    }

    long long num1, num2;
    try {
      num1 = str_to_decimal(num1_str, base, symbols.char_to_value);
      num2 = str_to_decimal(num2_str, base, symbols.char_to_value);
    } catch (const exception &e) {
      cerr << "Conversion error in line: " << line << " - " << e.what() << endl;
      continue;
    }

    long long result;
    if (operation == "ADD") {
      result = num1 + num2;
    } else if (operation == "SUBTRACT") {
      result = num1 - num2;
      if (result < 0) {
	cerr << "Negative result in subtraction in line: " << line << endl;
	continue;
      }
    } else {
      cerr << "Invalid operation: " << operation << " in line: " << line
	   << endl;
      continue;
    }

    string result_str;
    try {
      result_str = decimal_to_str(result, base, symbols.value_to_char);
    } catch (const exception &e) {
      cerr << "Error converting result to base " << base << ": " << e.what()
	   << endl;
      continue;
    }

    cout << result_str << endl;
  }

  return 0;
}
