#include <iostream>

class EvaluationOrder
{
public:
    EvaluationOrder &First(int)
    {
        std::cout << "EvaluationOrder &First(int)" << std::endl;
        return *this;
    }
    EvaluationOrder &Second(int)
    {
        std::cout << "EvaluationOrder &Second(int)" << std::endl;
        return *this;
    }
};
int FirstSubExpression(int)
{
    std::cout << "FirstSubExpression(int)" << std::endl;
    return 0;
}
int SecondSubExpression(int)
{
    std::cout << "SecondSubExpression(int)" << std::endl;
    return 0;
}
int main()
{
    EvaluationOrder eo;
    eo.First(FirstSubExpression(0)).Second(SecondSubExpression(0));
}