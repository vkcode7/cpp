// Online C++ compiler to run C++ program online
//https://www.interviewbit.com/online-cpp-compiler/
#include <iostream>
#include <memory>

struct Point {
    Point(int x1, int y1) : x(x1), y(y1){}
    int x;
    int y;
};

struct Free {
	void operator()(int *p) {
		free(p) ;
		std::cout << "\nFree class: pointer freed\n" ;
	}
};
void FreeFunc(int* p) {
	free(p);
	std::cout << "\nFreeFunc(): pointer freed\n";
}

int main() {
    using namespace std;

	{
	    std::unique_ptr<Point> uPt(new Point(4,6));
	    auto [x,y] = *uPt; //<-- structured bindings
        cout << "\nx: " << x << "    y: " << y;
        
        uPt.reset(new Point(400, 600));
        
        auto [x1,y1] = *uPt;
        cout << "\nx1: " << x1 << "    y1: " << y1;
        cout << "\nraw pointer: " << uPt.get();
        
		auto p = std::make_unique<int>(5) ;
		auto pt = std::make_unique<Point>(3,5) ;

		auto pArr = std::make_unique<int[]>(5) ;
		pArr[0] = 100;
    }
	{
		auto p = std::make_shared<int>(5) ;
		auto pt = std::make_shared<Point>(3,5) ;

		auto pArr = std::make_shared<int[]>(5) ;
		pArr[0] = 0 ;
	}
	
	{
		std::unique_ptr<int, Free> p1 {(int*) malloc(4), Free{}} ;
		std::unique_ptr<int, void (*)(int *)> p2 {(int*) malloc(4), FreeFunc} ;
	}
	
	//other types are: shared_ptr, weak_ptr
    return 0;
}