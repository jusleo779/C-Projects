#include <iostream>
#include <cassert>

int main();
void pattern(unsigned int n);
unsigned int log10(unsigned int n);
unsigned int count(unsigned int n, unsigned int bit);
unsigned int swap_bytes(unsigned int n, unsigned int b0, unsigned int b1);

int main()
{
    /* Test for pattern 
   for(int i = 0 ; i <= 5; i++)
   {
     std::cout << "n = " << i << ":" << std::endl;
     pattern(i);
     std::cout << "" << std::endl;//leaves a blank line to seperate it a little
   }
    */ 
   /* Test for log
   std::cout<< "log10(4294967295): " << log10(4294967295) << std::endl;
   std::cout<< "log10(429496729): " << log10(429496729) << std::endl;
   std::cout<< "log10(42949672): " << log10(42949672) << std::endl;
   std::cout<< "log10(4294967): " << log10(4294967) << std::endl;
   std::cout<< "log10(429496): " << log10(429496) << std::endl;
   std::cout<< "log10(429496): " << log10(42949) << std::endl;
   std::cout<< "log10(42949): " << log10(4294) << std::endl;
   std::cout<< "log10(429): " << log10(429) << std::endl;
   std::cout<< "log10(42): " << log10(42) << std::endl;
   std::cout<< "log10(4): " << log10(4) << std::endl;
   std::cout<< "log10(1): " << log10(1) << std::endl;
   std::cout<< "log10(0): " << log10(0) << std::endl;
   return 0; 
   */

   /* Test for counter method */
   std::cout<< "count(2,1): " << count(2,1) << std::endl;
   std::cout<< "count(2,0): " << count(2,0) << std::endl;
   std::cout<< "count(160,1): " <<  count(160,1) << std::endl;
   std::cout<< "count(32,1): " <<  count(32,1) << std::endl;
   std::cout<< "count(32,0): " <<  count(32,0) << std::endl;
   std::cout<< "count(160,0): " <<  count(160,0) << std::endl;
   std::cout<< "count(4294967295,1): " <<  count(4294967295,1) << std::endl;
   std::cout<< "count(4294967295,0): " <<  count(4294967295,0) << std::endl;
   std::cout<< "count(429496729,1): " <<  count(429496729,1) << std::endl;
   std::cout<< "count(429496729,0): " <<  count(429496729,0) << std::endl;
   std::cout<< "count(42949672,1): " <<  count(42949672,1) << std::endl;
   std::cout<< "count(42949672,0): " <<  count(42949672,0) << std::endl;
   std::cout<< "count(4294963199,1): " <<  count(4294963199,1) << std::endl;
   std::cout<< "count(4294963199,0): " <<  count(4294963199,0) << std::endl;
   std::cout<< "count(0,0): " <<  count(0,0) << std::endl;
   std::cout<< "count(0x26a4fbec,1): " <<  count(0x26a4fbec,1) << std::endl;
   std::cout<< "count(0x26a4fbec,0): " <<  count(0x26a4fbec,0) << std::endl;
   std::cout<< "count(2147483647,0): " <<  count(2147483647,0) << std::endl;
   std::cout<< "count(2147483647,1): " <<  count(2147483647,1) << std::endl;
   /*Test for Function 4
   std::cout << "0x01020300U = "  << swap_bytes(0x03020100U, 1, 3);
   */
   return 0;
   
}

void pattern(unsigned int n)
{
    unsigned int space_Counter = 0;
    for(unsigned int i = 0; i < (2 * n) + 1; i++)
    {
        if(n == 0)//if there n = 0 it will print one star without a space infront of it like it did originally
        {
            std::cout << "*" << std::endl;
            break;
        }
        if(space_Counter < n)//checks to make sure that it's still going down/inward
            for(unsigned int l = 0; l < space_Counter; l++)
            {
                std::cout<<" ";
            }
        else if(space_Counter > 0)//make sure after you place the middle star you start subtracting the amt of spaces
        {                         //to create the hourglass shape
            for(unsigned int l = space_Counter; l > 0; l--)
            {
                std::cout << " ";
            }
        }
        else
        {
            for(unsigned int l = 0; l <= n; l++)//the spacing for the star in the middle by itself
            {
                std::cout<< " ";
            }
        }
        for(unsigned int j = n; j > i ; j--)//starts stars from n which the value given an prints 2 per value of n ex: 2x5 = 10 stars
        {                          //when the value i = n then it won't run anymore
            std::cout<< "**";
        }

        for(unsigned int k = i; k > n ; k--) //when i = n it won't run but when it's greater than n it will run
        {  
            std::cout<< "**";
        }
        std::cout << "*" << std::endl;
        if(i < n)// increases/ decrease amt of spaces after running everything above
        {
            space_Counter++;
        }
        else
        {
            space_Counter--;
        }
    }
}

unsigned int log10(unsigned int n)
{
    assert(n != 0);
    unsigned int largestE_counter = -1;
    for(unsigned int i = 1; i <= n; i *= 10)
    {
        if(largestE_counter == 9)
        {
            break;
        }
        else
        {
            largestE_counter++;
        }
    }
    return largestE_counter;
}

unsigned int count(unsigned int n, unsigned int bit)
{
    assert(bit == 0 || bit == 1);
    unsigned int count = 0;
    if(n == 0 && bit == 0)
    {
        return 32;
    }
    for(unsigned int i {32}; i > 0; i--)
    {
        if((n & 1) == bit)// masking it by checking if the last variable of n is equal to 1 
        {
            count++;
        }
        n >>= 1;
    }
    return count;
}

unsigned int swap_bytes(unsigned int n, unsigned int b0, unsigned int b1)
{
    assert(b0 >= 0 && b0 <= 3 && b1 >= 0 && b1 <= 3);
    unsigned int j = n;
    unsigned int k = n;
    unsigned int shift_by;
    bool larger = (b0 > b1);// false = b0 >  & true  = b1 >
    if(b0 == b1)
    {
        return n;
    }
    //different types of bytes that i need to swap
    unsigned int MASK_0{0xFF};
    unsigned int MASK_1{0xFF00};
    unsigned int MASK_2{0xFF0000};
    unsigned int MASK_3{0xFF000000};
    
    if(b0 == 3)
    {
        j = MASK_3 & n;//mask the values at the byte where it's at in the moment
        n = (~MASK_3) & n;//masks the value at the byte where it's supposed to move to
    }
    else if (b0 == 2)
    {
        j = MASK_2 & n;
        n = (~MASK_2) & n;
    }
    else if(b0 == 1)
    {
        j = MASK_1 & n;
        n = (~MASK_1) & n;
    }
    else
    {
        j = MASK_0 & n;
        n = (~MASK_0) & n;
    }

    if(b1 == 3)
    {
        k = MASK_3 & n;
        n = (~MASK_3) & n;
    }
    else if (b1 == 2)
    {
        k = MASK_2 & n;
        n = (~MASK_2) & n;
    }
    else if(b1 == 1)
    {
        k = MASK_1 & n;
        n = (~MASK_1) & n;
    }
    else
    {
        k = MASK_0 & n;
        n = (~MASK_0) & n;
    }
    
    if(b0 > b1)
    {
        shift_by = (b0 - b1) * 8;
    }
    else
    {
        shift_by = (b1 - b0) * 8;
    }

    if(larger)// if b1 is a larger value
    {
        k <<= shift_by;//shifts the mask of b1 to the left by the amount of bytes asked
        j >>= shift_by;//shifts the mask of b0 to the right by the amount of bytes asked
    }
    else//if b0 is larger
    {
        k >>= shift_by;//shifts the mask of b1 to the right by the amount of bytes asked 
        j <<= shift_by;//shifts the mask of b0 to the left by the amount of bytes asked
    }

    n |= k;//takes the byte that was saved by the mask and combines it with the original 
    n |= j;

    return n;
}

unsigned int swap_bytes2(unsigned int n, unsigned int b0, unsigned int b1){ // a more efficent way of doing it
    
}