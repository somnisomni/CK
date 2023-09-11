#include <iostream>
#include "./vendingmachine.hpp"
using namespace std;

/* == Main == */
void initVM(VendingMachine *machine) {
  ProductProcessor *product = new ProductProcessor();
  MoneyProcessor *money = new MoneyProcessor();

  Product *chilledWater = new Product { 500, "차가운 물" };
  Product *crushedIce = new Product { 200, "조각얼음" };
  Product *cubeIce = new Product { 300, "큐브얼음" };

  product->addProduct(chilledWater);
  product->addProduct(crushedIce);
  product->addProduct(cubeIce);

  machine->productProc = product;
  machine->moneyProc = money;
}

int main() {
  // Setup
  VendingMachine *machine = new VendingMachine();
  initVM(machine);

  // Run
  machine->loop();

  // Cleanup
  delete machine;

  return 0;
}
