//
// Created by bcat on 2022-03-21.
//

#ifndef LESSON1_TASK2_H
#define LESSON1_TASK2_H

#include <iostream>
#include <map>
#include <ctime>

#define TEST_ONLY //comment when ready to production

class ISellSystem{
public:
    virtual void changePrice(std::string, float) = 0;
    virtual void sellProduct(std::string) = 0;
    virtual void addProduct(std::string, size_t) = 0;
};

//Первоначально планировал наследовать Automaton и AutomatonProxy также
//от интерфейса ILogger: на этапе планирования это выглядело логичным.
//Но в техзадании (ДЗ) методы логирования нам даны как константные для
//членов класса Automaton, а они (эти методы) не должны быть таковыми (const)
//у AutomatonProxy.
/*
class ILogger{
public:
    //virtual double allMoneyReport() const = 0;
    virtual double allMoneyReport() = 0;
    virtual const std::string& getLocationReport() const = 0;
    virtual std::map<std::string, size_t> goodsCountReport() const = 0;
    virtual std::map<std::string, float> goodsPriceReport() const = 0;
};
 */

class Automaton: public ISellSystem {
private:
    std::string location;
    double received_money;
    double spent_money;
    std::map <std::string, float> goods_price;
    std::map <std::string, size_t> goods_count;

public:
    Automaton(const std::string &location, double receivedMoney) :
        location(location), received_money(receivedMoney) {
            spent_money = 0.0;
    }

    void changePrice(std::string name, float newPrice) override {
        goods_price[name] = newPrice;
    }

    void sellProduct(std::string name) override{
        if(goods_count[name] > 0){
            received_money += goods_price[name];
        }
        else{
            std::cerr << "Not enough goods" << std::endl;
        }
    }

    void addProduct(std::string name, size_t count) override{
        goods_count[name] += count;
    }

    double allMoneyReport() const {
        return received_money - spent_money;
    }

    const std::string& getLocationReport() const {
        return location;
    }

    std::map <std::string, size_t> goodsCountReport() const {
        return goods_count;
    };

    std::map <std::string, float> goodsPriceReport() const {
        return goods_price;
    };
};

class AutomatonProxy: public ISellSystem {
private:
    Automaton * _automation;
    std::time_t lastLogTime;

    std::string location;
    double all_money;
    std::map <std::string, float> goods_price;
    std::map <std::string, size_t> goods_count;

    void updateData() {
        std::time_t currentTime { std::time(nullptr) };

#ifdef TEST_ONLY
        if((currentTime - lastLogTime) >= 5) //5 секунд - для тестирования
#else
        if((currentTime - lastLogTime) >= 3600) //3600 секунд == 1 час
#endif //TEST_ONLY

        {

            location = _automation->getLocationReport();
            all_money = _automation->allMoneyReport();
            goods_price = _automation->goodsPriceReport();
            goods_count = _automation->goodsCountReport();
            lastLogTime = currentTime;
        }
    }

public:
    AutomatonProxy(const std::string& arg1, double arg2):
        _automation { new Automaton(arg1, arg2) }, lastLogTime{},
        location { _automation->getLocationReport() },
        all_money { _automation->allMoneyReport() },
        goods_price { _automation->goodsPriceReport() },
        goods_count { _automation->goodsCountReport() }
        {}


    void changePrice(std::string name, float newPrice) override{
            _automation->changePrice(name, newPrice);
    }

    void sellProduct(std::string name) override{
        _automation->sellProduct(name);
    }

    void addProduct(std::string name, size_t count) override{
        _automation->addProduct(name, count);
    }

    double allMoneyReport() {
        updateData();
        return all_money;
    }

    const std::string& getLocationReport() {
        updateData();
        return location;
    }

    std::map <std::string, size_t> goodsCountReport() {
        updateData();
        return goods_count;
    };

    std::map <std::string, float> goodsPriceReport() {
        updateData();
        return goods_price;
    };

};

#endif //LESSON1_TASK2_H
