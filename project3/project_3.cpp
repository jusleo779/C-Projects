#include <iostream>
#include <cassert>
int main();

//main helper functions
double *geometric(double a, double ratio, std::size_t cap);
double *cross_correlation(double array0[], std::size_t cap0, double array1[], std::size_t cap1);
std::size_t shift_duplicates(int array[], std::size_t capacity);
void deallocate(double *&ptr, bool is_array, std::size_t capacity = 0);

//test
bool test_geometric( double array[], std::size_t capacity, double a, double ratio );
void test_shift();

int main()
{
    //std::cout << test_geometric(geometric(1, 5, 10), 10, 1 , 5) << std::endl; //true = 1
    //std::cout << test_geometric(geometric(1, 4, 10), 10, 1 , 5) << std::endl; //false = 0
    test_shift();
    return 0;
}

double *geometric(double a, double ratio, std::size_t cap)
{
    double *p_array;//creates pointer
    p_array = new double[cap];//makes it an array
    double pow_of = 1;
    for(int i = 0; i < cap; i++)
    {
        for(int j = 0; j < i; j++)
        {
            pow_of *= ratio;
        }
        p_array[i] = a * pow_of;//calls value but when you say *p_array it's the address (opposite for non array vals)
        pow_of = 1;
    }
    return p_array;
}

double *cross_correlation(double array0[], std::size_t cap0, double array1[], std::size_t cap1)
{
    assert(cap0 + cap1 >= 1);
    double *p_array;
    p_array = new double[cap0 + cap1 - 1]{};
    if(cap0 == 0 || cap1 == 0)
    {
        return p_array;
    }
    for(int i = 0; i < cap0; i++)
    {
        for(int j = 0; j < cap1; j++)
        {
            p_array[i + j] += (array0[i] * array1[j]);//must add it on because then it will override
        }
    }
    return p_array;
}

std::size_t shift_duplicates(int array[], std::size_t capacity)
{
    int lastI = capacity - 1;//last untouched value that can be changed to the duplicate
    for(int i = capacity - 1; i > 0; i--)//goes from the right because the unique numbers stay in the front
    {
        for(int j = 0; j < i; j++){//goes forward to check the values in order for a duplicate
            if(array[i] == array[j])//checks if there is a duplicate
            {
                int temp = array[i];//saves the value later so i can shift everything
                int index = i;//save the index so I don't need to swap and so i can shift
                for(int k = i + 1; k <= lastI; k++)//shifts all the values all the way to the LastI that hasn't been touched
                {
                    array[index] = array[k];//shifts the values
                    index++;
                }
                array[lastI] = temp;//updates the last value 
                lastI--;//makes sure that the last index that hasn't been changed is not the same one
                break;
            }
        }
    }
    return lastI + 1;//returns the correct value of unique numbers
}

void deallocate(double *&ptr, bool is_array, std::size_t capacity)
{
    if(is_array)
    {
        for(int i = 0; i < capacity; i++)
        {
            ptr[i]= 0;
        }
        delete []ptr;
        ptr = nullptr;
    }
    else
    {
        *ptr = 0;
        delete ptr;
        ptr = nullptr;
    }
}

bool test_geometric( double array[], std::size_t capacity, double a, double ratio )
{
    double check = a;
    if(array[0] != check)
    {
        return false;
    }
    for(int i = 1; i < capacity; i++)
    {
        check = check * ratio;
        if(check != array[i])
        {
            return false;
        }
    }
    return true;
}

void test_shift()
{
    int data[10]{ 5, 4, 2, 2, 2, 4, 5, 1, 4, 3 };
    std::cout<< "before" << std::endl;
    for ( std::size_t k{ 0 }; k < 10; ++k ) {
        std::cout << data[k] << " ";
    }
    shift_duplicates(data, 10);
    std::cout<< "\nafter shifting: " << std::endl;
    for ( std::size_t k{ 0 }; k < 10; ++k ) {
        std::cout << data[k] << " ";
    }
}
