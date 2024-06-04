#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <memory>
#include <sstream>
#include <cstdlib>

//! 1. Class & Object
//! 2. Attribute, Property & Method, Behavior
// Kelas yang menyimpan data dari kalkulasi
class Calculation 
{
//! 5. Encapsulation
private:
  //! 8. Access Modifier, Visibility
  double a, b, result; // Angka pertama, kedua, hasil kalkulasi
  std::string operation; // Operator kalkulasi

public:
  //! 3. Constructor
  // Constructor untuk inisialisasi objek Calculation
  Calculation(double a, std::string operation, double b, double result) 
    : a(a), operation(operation), b(b), result(result) {}

  // Fungsi untuk mengubah objek Calculation menjadi string agar dapat dibaca
  std::string toString() 
  {
    if (operation == "sin" || operation == "cos" || operation == "tan") return operation + "(" + std::to_string(a) + "°) = " + std::to_string(result);
    else if (operation == "log" || operation == "sqrt" || operation == "cbrt") return operation + "(" + std::to_string(a) + ") = " + std::to_string(result);
    else if (operation == "!") return std::to_string(a) + "! = " + std::to_string(result);
    else return std::to_string(a) + " " + operation + " " + std::to_string(b) + " = " + std::to_string(result);
  }

  //! 4. Setter & Getter
  // Getter untuk atribut a, b, result, dan operation
  double getA() const { return a; }
  double getB() const { return b; }
  double getResult() const { return result; }
  std::string getOperation() const { return operation; }

  // Setter untuk atribut a, b, result, dan operation
  void setA(double value) { a = value; }
  void setB(double value) { b = value; }
  void setResult(double value) { result = value; }
  void setOperation(std::string value) { operation = value; }
};

//! 9. Abstraction
// Kelas abstrak untuk operasi kalkulasi
class Operation
{
public:
  virtual double execute(double a, double b) = 0; // Fungsi virtual murni untuk eksekusi operasi
  virtual ~Operation() {} // Destructor virtual
};

//! 6. Inheritance
// Kelas turunan untuk operasi penjumlahan
class AddOperation : public Operation
{
public:
  //! 7. Overriding
  double execute(double a, double b) override { return a + b; }
};

// Kelas turunan untuk operasi pengurangan
class SubtractOperation : public Operation
{
public:
  double execute(double a, double b) override { return a - b; }
};

// Kelas turunan untuk operasi perkalian
class MultiplyOperation : public Operation
{
public:
  double execute(double a, double b) override { return a * b; }
};

// Kelas turunan untuk operasi pembagian
class DivideOperation : public Operation
{
public:
  double execute(double a, double b) override 
  { 
    if (b != 0) return a / b; 
    else 
    {
      std::cout << "Error: Division by zero!" << std::endl;
      return 0;
    }
  }
};

// Kelas turunan untuk operasi pangkat
//? Cara yang lebih singkat dari for loop?
// Gunakan pow() dari cmath
class PowerOperation : public Operation
{
public:
  double execute(double a, double b) override { return pow(a, b); }
};

// Kelas turunan untuk operasi modulus
//? Modulus hanya bisa menggunakan int dan tidak bisa menggunakan double?
/*
  1. Menggunakan std::fmod()
  2. Menggunakan static_cast<int>()
*/
class ModulusOperation : public Operation
{
public:
  double execute(double a, double b) override { return std::fmod(a, b); }
};

// Kelas turunan untuk operasi sin
class SinOperation : public Operation
{
public:
  double execute(double a, double b) override 
  { 
    a = a * 3.14159265 / 180;
    return std::sin(a); 
  }
};

// Kelas turunan untuk operasi cos
class CosOperation : public Operation
{
public:
  double execute(double a, double b) override 
  { 
    a = a * 3.14159265 / 180;
    return std::cos(a); 
  }
};

// Kelas turunan untuk operasi tan
class TanOperation : public Operation
{
public:
  double execute(double a, double b) override 
  { 
    a = a * 3.14159265 / 180;
    return std::tan(a); 
  }
};

// Kelas turunan untuk operasi logaritma
class LogOperation : public Operation
{
public:
  double execute(double a, double b) override { return std::log10(a); }
};

// Kelas turunan untuk operasi akar kuadrat
class SquareRootOperation : public Operation
{
public:
  double execute(double a, double b) override { return std::sqrt(a); }
};

// Kelas turunan untuk operasi akar kubik
class CubeRootOperation : public Operation
{
public:
  double execute(double a, double b) override { return std::cbrt(a); }
};

// Kelas turunan untuk operasi faktorial
//? Cara yang lebih singkat dari for loop?
class FactorialOperation : public Operation
{
public:
  double execute(double a, double b) override 
  { 
    if (a < 0) return 0;
    if (a == 0 || a == 1) return 1;
    double result = 1;
    for (int i = 1; i <= a; ++i) result *= i;
    return result;
  }
};

//! 10. Polymorphism
// Kelas Calculator untuk menjalankan berbagai operasi kalkulasi
class Calculator 
{
private:
  std::vector<Calculation> history; // Vector untuk menyimpan history kalkulasi
  std::map<std::string, std::unique_ptr<Operation>> operations; // Map untuk menyimpan operasi kalkulasi

public:
  // Constructor untuk inisialisasi map operasi
  Calculator() 
  {
    operations["+"] = std::make_unique<AddOperation>();
    operations["-"] = std::make_unique<SubtractOperation>();
    operations["*"] = std::make_unique<MultiplyOperation>();
    operations["/"] = std::make_unique<DivideOperation>();
    operations["^"] = std::make_unique<PowerOperation>();
    operations["%"] = std::make_unique<ModulusOperation>();
    operations["sin"] = std::make_unique<SinOperation>();
    operations["cos"] = std::make_unique<CosOperation>();
    operations["tan"] = std::make_unique<TanOperation>();
    operations["log"] = std::make_unique<LogOperation>();
    operations["sqrt"] = std::make_unique<SquareRootOperation>();
    operations["cbrt"] = std::make_unique<CubeRootOperation>();
    operations["!"] = std::make_unique<FactorialOperation>();
  }

  // Fungsi untuk mengeksekusi operasi kalkulasi
  double executeOperation(double a, std::string operation, double b) 
  {
    if (operations.find(operation) != operations.end()) 
    {
      double result = operations[operation]->execute(a, b);
      history.push_back(Calculation(a, operation, b, result));
      std::cout << "Result: " << result << std::endl;
      return result;
    } 
    else 
    {
      std::cout << "Unknown operation!" << std::endl;
      return 0;
    }
  }

  // Fungsi untuk menampilkan history kalkulasi
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
    else std::cout << "Invalid index." << std::endl;
  }

  // Fungsi untuk memperbarui history berdasarkan index
  void updateHistory(int index, double a, std::string operation, double b) 
  {
    if (index >= 1 && index <= history.size()) 
    {
      double result = operations[operation]->execute(a, b);
      history[index - 1] = Calculation(a, operation, b, result);
      std::cout << "Calculation history updated." << std::endl;
    } 
    else std::cout << "Invalid index." << std::endl;
  }

  // Fungsi untuk menghapus semua history
  void clearHistory() 
  {
    history.clear();
    std::cout << "All calculation history cleared." << std::endl;
  }
};

// Fungsi untuk menampilkan menu
void showMenu() 
{
  std::cout << "++======================++\n";
  std::cout << "|| Calculator\t\t||\n";
  std::cout << "++======================++\n";
  std::cout << "|| Menu:\t\t||\n";
  std::cout << "|| 1. Calculate\t\t||\n";
  std::cout << "|| 2. Show Operations\t||\n"; 
  std::cout << "|| 3. Show History\t||\n"; 
  std::cout << "|| 4. Delete History\t||\n";
  std::cout << "|| 5. Update History\t||\n";
  std::cout << "|| 6. Clear History\t||\n";
  std::cout << "|| 7. Quit\t\t||\n"; 
  std::cout << "++======================++\n";
  std::cout << "Choose: ";
}

// Fungsi untuk menjalankan operasi kalkulasi
void calculate(Calculator& calculator) 
{
  double a, b = 0;
  std::string operation;
  std::cout << "Enter operation (format: a + b or a log b): ";
  std::cin >> a >> operation;
  if (operation != "sin" && operation != "cos" && operation != "tan" && operation != "log" && operation != "sqrt" && operation != "cbrt" && operation != "!")
  {
    std::cin >> b;
  }
  calculator.executeOperation(a, operation, b);
  std::cin.ignore();
}

// Fungsi untuk memperbaharui history kalkulasi
void update(Calculator& calculator) 
{
  double a, b = 0;
  std::string operation, input1;
  int index;
  calculator.showHistory();
  std::cout << "Enter the index of the history to update: ";
  std::cin >> input1;
  std::cin.ignore();
  index = std::stoi(input1);
  std::cout << "Enter the new operation (format: a + b or a log b): ";
  std::cin >> a >> operation;
  if (operation != "sin" && operation != "cos" && operation != "tan" && operation != "log" && operation != "sqrt" && operation != "cbrt" && operation != "!")
  {
    std::cin >> b;
  }
  calculator.updateHistory(index, a, operation, b);
  std::cin.ignore();
}

// Fungsi untuk menunjukkan operasi yang tersedia
void showOperations()
{
  std::cout << "++======================================++\n";
  std::cout << "|| Regular operations:\t\t\t||\n";
  std::cout << "++===++=================================++\n";
  std::cout << "|| + || Addition (a + b)\t\t||\n";
  std::cout << "|| - || Subtraction (a - b)\t\t||\n";
  std::cout << "|| * || Multiplication (a * b)\t\t||\n";
  std::cout << "|| / || Division (a / b)\t\t||\n";
  std::cout << "|| ^ || Power (a ^ b)\t\t\t||\n";
  std::cout << "|| % || Modulus (a % b)\t\t\t||\n";
  std::cout << "++===++=================================++\n";
  std::cout << "|| example: a + b\t\t\t||\n";
  std::cout << "++======================================++\n\n";
  std::cout << "++======================================++\n";
  std::cout << "|| Special operations:\t\t\t||\n";
  std::cout << "++======++==============================++\n";
  std::cout << "|| sin  || Sine (sin(a))\t\t||\n";
  std::cout << "|| cos  || Cosine (cos(a))\t\t||\n";
  std::cout << "|| tan  || Tangent (tan(a))\t\t||\n";
  std::cout << "|| log  || Logarithm base 10 (log(a))\t||\n";
  std::cout << "|| sqrt || Square root (sqrt(a))\t||\n";
  std::cout << "|| cbrt || Cube root (cbrt(a))\t\t||\n";
  std::cout << "|| !    || Factorial (a!)\t\t||\n";
  std::cout << "++======++==============================++\n";
  std::cout << "|| example: a sin b (equals to sin(a))\t||\n";
  std::cout << "++======================================++\n";
}

// Fungsi utama
int main() 
{
  Calculator calculator; // Membuat objek calculator
  int choice, index;
  std::string operation, input1, input2;

  do 
  {
    showMenu(); // Menampilkan menu
    std::cin >> input1; // Memasukkan pilihan
    std::cin.ignore(); // Menghapus spasi yang ada di antara input dan pilihan
    choice = std::stoi(input1);
    
    std::system("cls");
    std::system("clear");

    switch (choice) 
    {
      case 1:
        calculate(calculator); // Menjalankan kalkulasi
        break;
      case 2:
        showOperations(); // Menampilkan daftar operasi
        break;
      case 3:
        calculator.showHistory(); // Menampilkan history kalkulasi
        break;
      case 4:
        calculator.showHistory();
        std::cout << "Enter the index of the history to delete: ";
        std::cin >> input2;
        std::cin.ignore();
        calculator.deleteHistory(std::stoi(input2)); // Menghapus history berdasarkan index
        break;
      case 5:
        update(calculator); // Memperbarui history berdasarkan index
        break;
      case 6:
        calculator.clearHistory(); // Menghapus semua history
        break;
      case 7:
        std::cout << "Exiting program." << std::endl; // Keluar dari program
        break;
      default:
        std::cout << "Invalid choice!" << std::endl; // Pilihan tidak valid
    }

    if (choice != 7)
    {
      std::cout << "Press enter to continue...";
      std::cin.ignore();
      std::system("cls");
      std::system("clear");
    }
  } while (choice != 7); // Loop sampai input choice adalah 7 (Keluar)

  return 0;
}
