#include <iostream>
#include <cstring>

class Chicken {
    private:
        int age = 24;
        char *name = nullptr;
    public:
        Chicken(){};
        Chicken(int _age) : age(_age), name(nullptr) {};
        Chicken(int _age, const char *_name) : age(_age) {
            setName(_name);
        };
        Chicken(const Chicken &_c) {
            age = _c.age;
            setName(_c.name);
        }

        Chicken &operator =(const Chicken &_c) {
            if(this != &_c) {
                age = _c.age;
                setName(_c.name);
            }
            return *this;
        }

        ~Chicken() {
            if (name != nullptr)
                delete[] name;
            // name = nullptr; //not necessary
        }
        void setAge(int _age) {
            age = _age;
        }
        void setName(const char *_name) {
            if(name != nullptr)
                delete [] name;
            if(_name != nullptr) {
                int len = strlen(_name) + 1;
                name = new char[len];
                for (int i = 0; i < len; i++)
                    name[i] = _name[i];
            } else
                name = nullptr;
        }

        const char *getName() const {
            return (name == nullptr) ? "Error : Unnamed" : name;
        }

        const int &getAge() const {
            return age;
        }
        void print(void) const;
};

void Chicken::print(void) const {
    std::cout << "Hi, everyone! My name is " << getName() << ", I am " << getAge() << " years old." << std::endl;
}

int main() {
    Chicken c(24, "Kunkun");
    c.print();
    Chicken d(c);
    d.print();
    c.setName("Zhiyin");
    c.print();
    d.print();
    d = c;
    d.print();
    Chicken a(23);
    a.print();
    a.setName("Jinitaimei");
    c = d = a;
    c.print();
    return 0;
}