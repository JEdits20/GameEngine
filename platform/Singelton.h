#ifndef SINGELTON_H
#define SINGELTON_H

template <typename T>
class Singleton {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }

protected:
    Singleton() {} // Constructor is protected
    ~Singleton() {} // Destructor is protected

private:
    Singleton(const Singleton&) = delete; // Prevent copying
    Singleton& operator=(const Singleton&) = delete; // Prevent assignment
};

#endif //SINGELTON_H
