#include <iostream>
#include <string>

class Aggregate {
    std::string name{};
public:
    const std::string &getName() const {
        return name;
    }

public:
    Aggregate(const std::string &name): name{name}{
        std::cout << "in the agg constructor" << std::endl;
    }
    Aggregate(const Aggregate& rhs){
        std::cout << "in the agg copy ctor" << std::endl;
        name = rhs.name;
    }
};

class Over {
    Aggregate* agg;
    std::string name;

public:
    friend std::ostream &operator<<(std::ostream &os, const Over &over) {
        os << "Object Name - " << over.name << ", Aggregate Name -  " << over.agg->getName() << std::endl;
        return os;
    }

    const std::string &getName() const {
        return name;
    }
    Over(Aggregate *agg, const std::string &name) : agg(agg), name(name) {}

    Over(const Over& rhs){
        agg = rhs.agg;
        name = rhs.name;
        std::cout << "in the copy constructor" << std::endl;
    }

    bool operator==(const Over &rhs) const {
        return agg == rhs.agg &&
               name == rhs.name;
    }

    bool operator!=(const Over &rhs) const {
        return !(rhs == *this);
    }

    Over& operator=(const Over &rhs){
        std::cout << "operator= being called" << std::endl;
        // check to make sure that rhs is not us
        if(this == &rhs){
            return *this;
        }
        // still need to do the assignment, etc. here!
        return *this;
    }
};


int main() {
    Over over(new Aggregate("Over"),"Harry");
    Over roger(new Aggregate("Roger"),"John");
    
    roger = over;
    Over over2 = over;
    std::cout << "Roger Output: " << roger << std::endl;
    std::cout << "Over2 Output: " << over2 << std::endl;
    return 0;
}
