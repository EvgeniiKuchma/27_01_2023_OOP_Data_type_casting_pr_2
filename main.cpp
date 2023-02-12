#include <iostream>
class Parent {
public: 
	 virtual void sleep() {
		std::cout << "sleep()" << std::endl;
	}
};
class Child : public Parent {

public: 
	void sleep() override {
		std::cout << "child sleep()" << std::endl;
	}
	void gotoSchool() {
		std::cout << "gotoSchool()" << std::endl;
	}
};
void func(Parent& other) {
	other.sleep();
}
int main() {
	Parent parent;
	Child child;//нелья сразу даункастить Parent в Child так как Parent не знает о существовании Child и его функции и в С -Style это UB
	//upcast (не¤вное преобразование типов разрешено)
	//варианты создани¤ в стэке и куче(в стеке может удалитьс¤)после выхода за размер кода автоматически вызоветс¤ и нструктор
	Parent* pParent = &child;//стэк
	Parent* pParent2 = new Child;//куча
	pParent->sleep();
	//downcast он работате только потому что pParent указывает на Child
	Child* pChild = (Child*)pParent;
	//C- style каст выполн¤ет первый успешный каст в пор¤лк:
	//cost_cast - снимает константность
	//static_cast - когда выполн¤ет не обращает внимание на модификаторы public, private  и т.д. если пытатьс¤ скоставать не св¤занные между собой классы это UB
	//static_cast -> const_cast
	//reinterpret_cast
	//reinterpret_cast -> const_cast
	Child* pChild2 = static_cast<Child*>(pParent);//если классы в иерархии наследовани¤ не виртуальные 
	//то можно  и нужно кастовать(upcast/downcast) через static_cast
	//downcast UB
	//Child* pChild = (Child*)&pParent;

	pParent->sleep();//sleep()/ non virtual // child slepp() virtual
	pChild->sleep();//child slepp()/non virtual // child slepp() virtual
	//pChild2 ->sleep(); //UB 
	//в монмент добавлени¤ ключевых слов virtual / override происходит по¤вление vptr 
	//который который хранитс¤ внутри  каждого класса который казывает на виртуальную таблицу соответствующую классу 
	delete pParent2;

	//STATIC CAST

	//static_cast<new_type>(expression) - операторы
	int a = 5;
	std::cout << "a: " << a << std::endl;
	double b = static_cast<double>(a);//–аньше: double(a)
	//или (double)a
	std::cout << "b: " << b << std::endl;

	int c = 6; //если данные изначально const то снятие константы с указателя привело бы к UB, 
	//c this константность можно снять если она не была константной
	const int* pC = &c;
	int* ppC = const_cast<int*> (pC);
	std::cout << "=============\n";
	std::cout << *ppC << std::endl;
	*ppC = 4;
	std::cout << *ppC << " " << c << std::endl;
	//dynamic cast<new type> - для работы с виртуальными классами, при отсутствии наследования UB
	//Здесь нет UB так как dynamic cast ведет себя определенным образом, проверяет что UB не возможно и сообщает 
	//об этом< через private и protected не ходит только через public
	Child* pChild3 = dynamic_cast<Child*>(&parent);//UB в dynamic_cast когды мы пытаемся кастить 1 класс во 2 если 
	//эти касты не наследуют другу и быть виртуальными
	if (pChild3 == nullptr) {
		std::cout << "pChild is nullptr" << std::endl;
	}
	try{
		Child& pChild5 = dynamic_cast<Child&>(parent);
	}
	catch (std::bad_cast& e) {
		std::cout << "cast parent to child result in bad_cast" << std::endl;
		std::cout << e.what() << std::endl;
	}
	//reinterpret_cast = пытается скастить чего бы это не стоило, лучше избегать, 100 % можно скастить 1 
	//тип в другой и потом обратно, используют в чтении в байтовом режиме (наприме в чар)
	return 0;
}
