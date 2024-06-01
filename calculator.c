#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Class yang menyimpan data dari kalkulasi
class Calculation 
{
public:
  double a, b, result;
  char operation;

  // Constructor untuk inisialisasi object Calculation
  Calculation(double a, char operation, double b, double result) : a(a), operation(operation), b(b), result(result) {}

  // Mengubah objek Calculation menjadi string agar dapat dibaca
  std::string toString() 
  {
    return std::to_string(a) + " " + operation + " " + std::to_string(b) + " = " + std::to_string(result);
  }
};

// Class yang mengimplementasikan fungsi kalkulator
class Calculator 
{
  // Vector yang menyimpan data dari kalkulasi sebagai history, untuk fungsi CRUD
  std::vector<Calculation> history;

public:
  // Fungsi penjumlahan
  double add(double a, double b) 
  {
    double result = a + b;

    // menyimpan data kalkulasi ke dalam vector history
    history.push_back(Calculation(a, '+', b, result));

    return result;
  }

  // Fungsi pengurangan
  double subtract(double a, double b) 
  {
    double result = a - b;
    history.push_back(Calculation(a, '-', b, result));
    return result;
  }

  // Fungsi perkalian
  double multiply(double a, double b) 
  {
    double result = a * b;
    history.push_back(Calculation(a, '*', b, result));
    return result;
  }

  // Fungsi pembagian
  double divide(double a, double b) 
  {
    // memastikan agar pembagian tidak membagi dengan 0
    if (b != 0) 
    {
      double result = a / b;
      history.push_back(Calculation(a, '/', b, result));
      return result;
    } 
    else 
    {
      std::cout << "Error: Division by zero!" << std::endl;
      return 0;
    }
  }

  // Fungsi pangkat
  double power(double a, double b)
  {
    double result = 1;
    // menghitung a pangkat b dengan cara mengalikan a dengan a sebanyak b-1 kali (i < b)
    for (int i = 0; i < b; i++) result *= a;
    history.push_back(Calculation(a, '^', b, result));
    return result;
  }

  // Fungsi modulus
  //? Modulus hanya bisa menggunakan int dan tidak bisa menggunakan double?
  /*
    1. Menggunakan std::fmod()
    2. Menggunakan static_cast<int>()
  */
  double modulus(double a, double b)
  {
    int result = std::fmod(a, b); // Fungsi cmath untuk modulus double
    history.push_back(Calculation(a, '%', b, result));
    return result;
  }

  // Fungsi untuk menghapus semua history
  void clearHistory() 
  {
    history.clear(); // Fungsi vector untuk mengosongkan isinya
    std::cout << "All calculation history cleared." << std::endl;
  }

  // Fungsi untuk menjalankan operasi berdasarkan operator
  double executeOperation(double a, char operation, double b) 
  {
    double result = 0;
    switch (operation) 
    {
      case '+': result = add(a, b); break;
      case '-': result = subtract(a, b); break;
      case '*': result = multiply(a, b); break;
      case '/': result = divide(a, b); break;
      case '^': result = power(a, b); break;
      case '%': result = modulus(a, b); break;
      default: std::cout << "Unknown operation!" << std::endl; return 0;
    }
    std::cout << "Result: " << result << std::endl;
    return result;
  }

  // Fungsi untuk menampilkan history
  void showHistory() 
  {
    if (history.empty()) 
    {
      std::cout << "No calculation history." << std::endl;
      return;
    }

    for (int i = 0; i < history.size(); ++i) 
    {
      std::cout << i + 1 << ". " << history[i].toString() << std::endl;
    }
  }

  // Fungsi untuk menghapus history berdasarkan index
  void deleteHistory(int index) 
  {
    if (index >= 1 && index <= history.size()) 
    {
      history.erase(history.begin() + index - 1);
      std::cout << "Calculation history deleted." << std::endl;
    } 
    else 
    {
      std::cout << "Invalid index." << std::endl;
    }
  }

  // Fungsi untuk memperbaharui history berdasarkan index
  void updateHistory(int index, double a, char operation, double b) 
  {
    if (index >= 1 && index <= history.size()) 
    {
      double result;
      switch (operation) 
      {
        case '+':
          result = a + b;
          break;
        case '-':
          result = a - b;
          break;
        case '*':
          result = a * b;
          break;
        case '/':
          if (b != 0) 
          {
            result = a / b;
          }

          else 
          {
            std::cout << "Error: Division by zero!" << std::endl;
            return;
          }
          break;
        case '^':
          result = 1;
          for (int i = 0; i < b; i++) result *= a;
          break;
        case '%':
          result = std::fmod(a, b); 
          break;
        default:
          std::cout << "Unknown operation!" << std::endl;
          return;
      }
      history[index - 1] = Calculation(a, operation, b, result);
      std::cout << "Calculation history updated." << std::endl;
    } 
    else 
    {
      std::cout << "Invalid index." << std::endl;
    }
  }
};

// Fungsi untuk menampilkan menu
void showMenu() 
{
  std::cout << "\nMenu:\n";
  std::cout << "1. Calculate\n";
  std::cout << "2. Show History\n";
  std::cout << "3. Delete History\n";
  std::cout << "4. Update History\n";
  std::cout << "5. Quit\n";
  std::cout << "Choose: ";
}

// Fungsi untuk menjalankan operasi
void calculate(Calculator& calculator) 
{
  double a, b;
  char operation;
  std::cout << "Enter operation (format: a + b): ";
  std::cin >> a >> operation >> b;
  calculator.executeOperation(a, operation, b);
}

int main() 
{
  Calculator calculator; // Deklarasi object calculator
  int choice, index;
  double a, b;
  char operation;

  do 
  {
    showMenu();
    std::cin >> choice;

    switch (choice) 
    {
      case 1:
        calculate(calculator);
        break;
      case 2:
        calculator.showHistory();
        break;
      case 3:
        calculator.showHistory();
        std::cout << "Enter the index of the history to delete: ";
        std::cin >> index;
        calculator.deleteHistory(index);
        break;
      case 4:
        calculator.showHistory();
        std::cout << "Enter the index of the history to update: ";
        std::cin >> index;

        std::cout << "Enter the new operation (format: a + b): ";
        std::cin >> a >> operation >> b;

        calculator.updateHistory(index, a, operation, b);
        break;
      case 5:
        calculator.clearHistory();
        std::cout << "Exiting program." << std::endl;
        break;
      default:
        std::cout << "Invalid choice!" << std::endl;
    }
  } while (choice != 5); // Loop sampai input choice adalah 5

  return 0;
}
