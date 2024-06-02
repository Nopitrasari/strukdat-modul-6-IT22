#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <memory>

// Kelas yang menyimpan data dari kalkulasi
class Calculation 
{
private:
  double a, b, result; // Angka pertama, kedua, hasil kalkulasi
  char operation;      // Operator kalkulasi

public:
  // Constructor untuk inisialisasi objek Calculation
  Calculation(double a, char operation, double b, double result) 
    : a(a), operation(operation), b(b), result(result) {}

  // Fungsi untuk mengubah objek Calculation menjadi string agar dapat dibaca
  std::string toString() 
  {
    return std::to_string(a) + " " + operation + " " + std::to_string(b) + " = " + std::to_string(result);
  }

  // Getter untuk atribut a, b, result, dan operation
  double getA() const { return a; }
  double getB() const { return b; }
  double getResult() const { return result; }
  char getOperation() const { return operation; }

  // Setter untuk atribut a, b, result, dan operation
  void setA(double value) { a = value; }
  void setB(double value) { b = value; }
  void setResult(double value) { result = value; }
  void setOperation(char value) { operation = value; }
};

// Kelas abstrak untuk operasi kalkulasi
class Operation
{
public:
  virtual double execute(double a, double b) = 0; // Fungsi virtual murni untuk eksekusi operasi
  virtual ~Operation() {} // Destructor virtual
};

// Kelas turunan untuk operasi penjumlahan
class AddOperation : public Operation
{
public:
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
    if (b != 0) 
      return a / b; 
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
  double execute(double a, double b) override
  {
    return pow(a, b);
  }
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
  double execute(double a, double b) override 
  { 
    return std::fmod(a, b); 
  }
};

// Kelas Calculator untuk menjalankan berbagai operasi kalkulasi
class Calculator 
{
private:
  std::vector<Calculation> history; // Vector untuk menyimpan history kalkulasi
  std::map<char, std::unique_ptr<Operation>> operations; // Map untuk menyimpan operasi kalkulasi

public:
  // Constructor untuk inisialisasi map operasi
  Calculator() 
  {
    operations['+'] = std::make_unique<AddOperation>();
    operations['-'] = std::make_unique<SubtractOperation>();
    operations['*'] = std::make_unique<MultiplyOperation>();
    operations['/'] = std::make_unique<DivideOperation>();
    operations['^'] = std::make_unique<PowerOperation>();
    operations['%'] = std::make_unique<ModulusOperation>();
  }

  // Fungsi untuk mengeksekusi operasi kalkulasi
  double executeOperation(double a, char operation, double b) 
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
  void updateHistory(int index, double a, char operation, double b) 
  {
    if (index >= 1 && index <= history.size()) 
    {
      double result = operations[operation]->execute(a, b);
      history[index - 1] = Calculation(a, operation, b, result);
      std::cout << "Calculation history updated." << std::endl;
    } 
    else 
    {
      std::cout << "Invalid index." << std::endl;
    }
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
  std::cout << "\nMenu:\n";
  std::cout << "1. Calculate\n";
  std::cout << "2. Show History\n";
  std::cout << "3. Delete History\n";
  std::cout << "4. Update History\n";
  std::cout << "5. Clear History\n";
  std::cout << "6. Quit\n";
  std::cout << "Choose: ";
}

// Fungsi untuk menjalankan operasi kalkulasi
void calculate(Calculator& calculator) 
{
  double a, b;
  char operation;
  std::cout << "Enter operation (format: a + b): ";
  std::cin >> a >> operation >> b;
  calculator.executeOperation(a, operation, b);
}

// Fungsi utama
int main() 
{
  Calculator calculator; // Membuat objek calculator
  int choice, index;
  double a, b;
  char operation;

  do 
  {
    showMenu(); // Menampilkan menu
    std::cin >> choice; // Memasukkan pilihan

    switch (choice) 
    {
      case 1:
        calculate(calculator); // Menjalankan kalkulasi
        break;
      case 2:
        calculator.showHistory(); // Menampilkan history kalkulasi
        break;
      case 3:
        calculator.showHistory();
        std::cout << "Enter the index of the history to delete: ";
        std::cin >> index;
        calculator.deleteHistory(index); // Menghapus history berdasarkan index
        break;
      case 4:
        calculator.showHistory();
        std::cout << "Enter the index of the history to update: ";
        std::cin >> index;
        std::cout << "Enter the new operation (format: a + b): ";
        std::cin >> a >> operation >> b;
        calculator.updateHistory(index, a, operation, b); // Memperbarui history berdasarkan index
        break;
      case 5:
        calculator.clearHistory(); // Menghapus semua history
        break;
      case 6:
        std::cout << "Exiting program." << std::endl; // Keluar dari program
        break;
      default:
        std::cout << "Invalid choice!" << std::endl; // Pilihan tidak valid
    }
  } while (choice != 6); // Loop sampai input choice adalah 6 (Keluar)

  return 0;
}
