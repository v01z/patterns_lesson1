//
// Created by bcat on 2022-03-21.
//

#ifndef LESSON1_TASK1_H
#define LESSON1_TASK1_H

class ChocolateBoiler{
private:
    bool _empty;
    bool _boiled;
//public: //"Прячем" конструктор
    ChocolateBoiler(){
        _empty = true;
        _boiled = false;
    }

    ~ChocolateBoiler(){
        if (_instance != nullptr)
            delete _instance;
    }

    //Будет хранить указатель на единственный экземпляр
    static ChocolateBoiler * _instance;

public:
    //Статик-метод, возвращающий единственный экземпляр, либо
    //создающий новый, если его не было
    static ChocolateBoiler *getInstance() {
        if (_instance == nullptr)
            _instance = new ChocolateBoiler;

        return _instance;
    }

    bool isEmpty() const{
        return _empty;
    }

    bool isBoiled() const{
        return _boiled;
    }

    void fill(){
        if (isEmpty()){
            _empty = false;
            _boiled = false;
        }
    }

    void drain(){
        if (!isEmpty() && isBoiled()){
            _empty = true;
        }
    }

    void boil(){
        if (!isEmpty() && !isBoiled()){
            _boiled = true;
        }
    }
};

//У нас пока нет объекта ChocolateBoiler
ChocolateBoiler *ChocolateBoiler::_instance = nullptr;

#endif //LESSON1_TASK1_H
