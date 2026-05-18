#include <list>
#include <vector>


template <typename T, typename U>
class Pair{
    private: 
        T a;
        U b;
    public:
        Pair(const T& A, const U& B): a(A), b(B){};

        T getA(){
            return a;
        }

        U getB(){
            return b;
        }

        void setA(const T& A){
            this->a = A;
        }

        void setA(nst U& B){
            this->b = B;
        }
}

int main(){
    Pair* a = new Pair(2.2, 2);
    Pair* b = new Pair()

}



// Stack<T>


template<typename T> class stack
{
    private:
        std::vector<T> stack;
    public:
        stack() = default;
        void push(const T& in){
            stack.push_back(in);
        }
        void pop(){
            stack.pop_back();
        }
        const T& peek(){
            return stack.back();
        }
        bool is_empty(){
            return stack.empty();
        }
};
