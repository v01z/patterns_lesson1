#include <iostream>
#include "task1.h"
#include "task2.h"
#include <cassert> //для assert()
#include <unistd.h> //sleep()

int main() {
    //************* task 1 *****************

    ChocolateBoiler *boiler1 { ChocolateBoiler::getInstance() };
    ChocolateBoiler *boiler2 { ChocolateBoiler::getInstance() };

    //boiler2 указывает на тот же блок памяти, что и boiler1,
    //т.е. на содержащий один и тот же экземпляр класса ChocolateBoiler
    assert(boiler1 == boiler2);

    //************* task 2 *****************

    AutomatonProxy automatonProxy ("Москва, ул. Воронцовская, 35", 10'000.00);

    //Для удобства вывода информации
    auto lambda_money_report { [&](const std::string& str) {
        std::puts(str.c_str());
        std::printf("Всего денег сейчас: %.2f\n\n", automatonProxy.allMoneyReport());
    }};

    const std::string productKvas { "Квас \'Очаковский\'" };
    const std::string productIceCream { "Мороженное \'Пломбир\'" };

    automatonProxy.addProduct(productKvas, 17);
    automatonProxy.changePrice(productKvas, 112.15);

    automatonProxy.addProduct( productIceCream, 215);
    automatonProxy.changePrice(productIceCream, 83.07);

    lambda_money_report("Ещё ничего не продали.");

    //Продадим одно мороженое
    automatonProxy.sellProduct(productIceCream);

    //Ждём три секунды
    sleep(3);

    //Но три секунды - это меньше заложенных 5 сек. (см. стр.99 в файле task2.h),
    //поэтому общая сумма не изменилась:
    lambda_money_report("Продали одну мороженку, но proxy ещё не обновил логи.");

    //Ждём ещё три секунды
    sleep(3); // (3+3) > 5

    //Теперь видим, что вырученная сумма с продажи добавилась в общую копилку:
    lambda_money_report("Лог обновился, снимайте кассу xD.");

    return 0;
}
