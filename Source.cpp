#include <iostream>


 class Harvest{
  public: 
  Harvest (std::string name, std::string color,int weight) {
     this->name_ = name;
     this->weight_ = weight;
     this->color_ = color;
     ++counter_;
   }
  ~Harvest() {--counter_; };
  
  std::string Name()const { return name_; }
  std::string Color()const { return color_; }
  int Weight()const { return weight_; }
  int Number() { return ++number_; }
  static int Counter() { return counter_; }

 protected:
  std::string  name_;
  int weight_;
  std::string color_;
  static int counter_; 
  int number_ = Harvest::Counter(); // Номер объекта Харвест

};



class Raspberry : public Harvest {
public:
 Raspberry (std::string  name, std::string color, int weight) : Harvest (name, color, weight) {
   this->name_ = "raspberry";
   this-> color_ = "Red";
  }
~Raspberry() {};
};

class Apple : public  Harvest  {
public:
 Apple(std::string  name, std::string color, int weight) : Harvest(name, color, weight) {
   this->name_ = "apple";
   this->color_ = "Green"; 
 } 
    ~Apple() {};
};


class Plant {

 public:
    Plant (std::string plant_size, std::string title, int max)
    {
        this->plant_size_ = plant_size;
        this-> title_ = title;
        this->darr_ = new Harvest * [size_];
        this->size_ = max;
    }
    ~Plant() {}
    
    std::string Plant_size()const { return plant_size_; }
    int size()const { return size_; }
    std::string Title()const { return title_; }
    Harvest** begin()const { return darr_; }
    Harvest** end()const { return (darr_ + size_); }
   
    virtual Harvest* Create() = 0;

    friend void Raspberry_now(Plant& obj) {
        while (Raspberry::Counter() < std::size(obj)) {
            obj.darr_[Raspberry::Counter() - 1] = obj.Create();
        }
    }
    friend void Apple_now(Plant& obj) {
        while (Apple::Counter() < std::size(obj)) {
            obj.darr_[Apple::Counter() - 1] = obj.Create();
        }
    }

    friend void Clean(Plant& obj) {
        if (obj.darr_){
            for (auto& e : obj) {
                e->~Harvest(); 
                e = nullptr; 
            }
        delete[] obj.darr_;
        obj.darr_ = nullptr;
        }   
    }
protected:
    std::string name_;
    std::string title_;
    std::string plant_size_;
    int size_; 	
    Harvest** darr_; 
};

class Raspberry_buch : public Plant {
public:
    Raspberry_buch(std::string plant_size, std::string title, int max_plants) : 
        Plant(plant_size_, title_, max_plants) {
        this->title_ = "Raspberry_buch";
        this->plant_size_ = "Smoll";
        this->title_harvest_ = title.substr(0, title.find('_'));
    }
     ~Raspberry_buch() {};

     Harvest* Create() override {
         return new Raspberry (title_harvest_, "Red", rand() % (7 - 3) + 3);
     }
private:
    std::string title_harvest_;
};

class Apple_tree : public Plant {

public:

    Apple_tree(std::string plant_size, std::string title, int max_plants) : 
        Plant(plant_size_, title_, max_plants) {
        this->title_ = "Apple_tree";
        this->plant_size_ = "Big";
        this->title_harvest_ = title.substr(0, title.find('_'));
    }  
    ~Apple_tree() {};
    Harvest* Create() override {
        return new Apple (title_harvest_, "Green", rand() % (200 - 60) + 60);
    }

private:
    std::string title_harvest_;

  
};

int Harvest::counter_{};

void Print(Plant const& obj) {
    std::cout << "Плод: " << obj.Title() << ' ' << "Размер: " << obj.Plant_size() << ' ' << "Количество плодов : " << Harvest::Counter() << std::endl;
    for (auto& ex : obj)
        std::cout << ex->Number() << ". " << ex->Color() << ' ' << ex->Name() << " weighing " << ex->Weight() << " грамм" << std::endl;
    std::cout << std::endl;
}


int main()
{
    system("chcp 1251>null");
    
    Raspberry_buch one("Smoll", "Raspberry_buch", 20); 
    srand(time(NULL));
    Raspberry_now(one); 
    Print(one); // 
    system("pause");
    system("cls");
    Clean(one);
    one.~Raspberry_buch(); 
   
    
    return 0;
};




