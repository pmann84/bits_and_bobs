#include <iostream>
#include <bitset>
#include <limits>

int main()
{
   //************************************************************************//
   // General bit definitions
   //************************************************************************//  
   // Define an int and print in its binary format - output '0000 1000'
   // Note here I have truncated the output to only 8 bits since my number
   // is small enough. Here we have used a 1 byte unsigned integer type, 
   // which gives us 8 bits.
   const uint8_t my_bits = 8;
   std::cout << "Bit representation of uint8_t value 8: ";
   std::cout << std::bitset<8>(my_bits) << std::endl;

   // Another example here max int for an 8-bit int - output '1111 1111'
   const uint8_t max_bits = std::numeric_limits<uint8_t>::max();
   std::cout << "Bit representation of uint8_t value 255: ";
   std::cout << std::bitset<8>(max_bits) << std::endl;

   // Example with an unsigned char type. Also a 1 byte (8 bit data type)
   // Output - 01100001
   const unsigned char char_bits = 'a';
   std::cout << "Bit representation of unsigned char value 'a': ";
   std::cout << std::bitset<8>(char_bits) << std::endl;

   // Final example with std::byte
   std::byte new_byte{ 12 };
   std::cout << "Bit representation of integer 12 through std::byte: ";
   std::cout << std::bitset<8>(std::to_integer<uint8_t>(new_byte)) << std::endl;


   std::cout << std::endl;
   //************************************************************************//
   // Basic bit operations - &, |, ~, ^
   //************************************************************************//  
   // AND - bitwise logical AND. This is applied to each bit in the collection
   // and 'AND-ed' with the corresponding bit on the otherside of the operator
   // 0000 0001 & 0000 1101 = 0000 0001
   const uint8_t first_bits = 1;
   const uint8_t second_bits = 13;
   std::cout << "Bitwise & (AND) operator - ";
   std::cout << std::bitset<8>(first_bits) << " & " << std::bitset<8>(second_bits) << ": ";
   std::cout << std::bitset<8>(first_bits & second_bits) << std::endl;

   // OR - bitwise logical OR. This is applied to each bit in the collection
   // and 'OR-ed' with the corresponding bit on the otherside of the operator
   // 0000 0001 | 0000 1101 = 0000 1101
   std::cout << "Bitwise | (OR) operator - ";
   std::cout << std::bitset<8>(first_bits) << " | " << std::bitset<8>(second_bits) << ": ";
   std::cout << std::bitset<8>(first_bits | second_bits) << std::endl;

   // NOT - the complement operator. This flips all the bits in a collection
   // ~(0000 1101) = 1111 0010
   std::cout << "Bitwise ~ (NOT) operator - ";
   std::cout << "~" << std::bitset<8>(second_bits) << ": ";
   std::cout << std::bitset<8>(~second_bits) << std::endl;

   // XOR - exclusive OR. Basically a regular OR but with 1 ^ 1 = 0 as opposed
   // to 1 | 1 = 1.
   // 0000 0001 ^ 0000 1101 = 0000 1100
   std::cout << "Bitwise ^ (XOR) operator - ";
   std::cout << std::bitset<8>(first_bits) << " ^ " << std::bitset<8>(second_bits) << ": ";
   std::cout << std::bitset<8>(first_bits ^ second_bits) << std::endl;

   std::cout << std::endl;
   //************************************************************************//
   // Bit shifting - <<, >>
   //************************************************************************// 
   // Basic left shift
   // 0000 0001 -> 0000 0010
   std::cout << "Bitwise << (left shift) operator - ";
   std::cout << std::bitset<8>(1) << " << " << 1 << ": ";
   std::cout << std::bitset<8>(1 << 1) << std::endl;
   // 0000 0001 -> 0010 0000
   std::cout << "Bitwise << (left shift) operator - ";
   std::cout << std::bitset<8>(1) << " << " << 5 << ": ";
   std::cout << std::bitset<8>(1 << 5) << std::endl;
   
   // Basic right shift
   // 0000 0010 -> 0000 0001
   std::cout << "Bitwise << (right shift) operator - ";
   std::cout << std::bitset<8>(2) << " >> " << 1 << ": ";
   std::cout << std::bitset<8>(2 >> 1) << std::endl;

   // Comparison with multiplication and division - << means that we are multiplying
   // by 2^N where N is the right hand operand of <<.
   // Prints: 64 64
   std::cout << "Multiplication Equivalent - ";
   std::cout << std::bitset<8>(2) << " << " << 5 << " = ";
   std::cout << (2 << 5) << " <=> " << 2 * std::pow(2, 5) << " = 2 * 2 ^ 5" << std::endl;

   // Similarly with a right shift (power calculation left in for illustration)
   // Prints: 16 16
   std::cout << "Division Equivalent - ";
   std::cout << std::bitset<8>(32) << " >> " << 1 << " = ";
   std::cout << (32 >> 1) << " <=> " << 32 / std::pow(2, 1) << " = 32 / 2 ^ 1" << std::endl;

   // Bits are lost off the end once they are shifted out of the number
   // 1100 1010 -> 1001 0100
   uint8_t shifted_bits = 202 << 1;
   std::cout << "Lost bits with a shift - ";
   std::cout << std::bitset<8>(202) << " << " << 1 << ": ";
   std::cout << std::bitset<8>(shifted_bits) << std::endl;
   std::cout << "Actual value is garbage: ";
   std::cout << shifted_bits << std::endl; // Garbage!

   // 1001 0100 -> 0100 1010
   std::cout << "Can't recover bits with a shift - ";
   std::cout << std::bitset<8>(shifted_bits) << " >> " << 1 << ": ";
   uint8_t try_to_recover_bits = shifted_bits >> 1;
   std::cout << std::bitset<8>(try_to_recover_bits) << std::endl;
   std::cout << "Actual value is still garbage: ";
   std::cout << try_to_recover_bits << std::endl; // Still garbage!

   std::cout << std::endl;
   //************************************************************************//
   // Tips and tricks
   //************************************************************************// 
   // Set 5th bit - first with integer type
   {
      uint8_t bits = 202;
      uint8_t bit_pos = 4;
      std::cout << "Set " << bit_pos+1 << "th bit, ";
      std::cout << std::bitset<8>(bits) << " |= (1 << " << (int)(bit_pos) << "): ";
      bits |= (1 << bit_pos);
      std::cout << std::bitset<8>(bits) << std::endl;

      // Next with bitset
      std::bitset<8> bits_bs(202);
      bits_bs.set(bit_pos); // Sets the bit in position 4

      // Finally with std::byte
      std::byte bits_b{ 202 };
      bits_b |= std::byte{ 1 << bit_pos };
   }

   // Unset 7th bit - first with integer type
   {
      uint8_t bits = 202;
      uint8_t bit_pos = 6;
      std::cout << "Unset " << bit_pos + 1 << "th bit, ";
      std::cout << std::bitset<8>(bits) << " &= (~(1 << " << (int)(bit_pos) << ")): ";
      bits &= (~(1 << bit_pos));
      std::cout << std::bitset<8>(bits) << std::endl;

      // Next with bitset
      std::bitset<8> bits_bs(202);
      bits_bs.set(bit_pos, false); // Sets the bit in position 4

      // Finally with std::byte
      std::byte bits_b{ 202 };
      bits_b &= ~std::byte{ 1 << bit_pos };
   }

   // Toggling bits
   {
      // Example for toggling a bit that is currently off
      uint8_t off_bits = 202;
      uint8_t bit_pos = 4;
      std::cout << "Toggle " << bit_pos + 1 << "th (off) bit: ";
      std::cout << std::bitset<8>(off_bits) << " ^= (1 << " << (int)(bit_pos) << "): ";
      off_bits ^= (1 << bit_pos);
      std::cout << std::bitset<8>(off_bits) << std::endl;

      // Example for toggling a bit that is currently on
      uint8_t on_bits = 202;
      bit_pos = 7;
      std::cout << "Toggle " << bit_pos + 1 << "th (on) bit: ";
      std::cout << std::bitset<8>(on_bits) << " ^= (1 << " << (int)(bit_pos) << "): ";
      on_bits ^= (1 << bit_pos);
      std::cout << std::bitset<8>(on_bits) << std::endl;

      // Toggling using std::bitset
      std::bitset<8> bits_bs(202);
      bits_bs.flip(bit_pos);
   }

   // Checking set bits
   {
      uint8_t bits = 202;
      uint8_t bit_pos = 4;
      std::cout << "Check " << bit_pos + 1 << "th bit is set: ";
      std::cout << std::bitset<8>(bits) << " & (1 << " << (int)(bit_pos) << "): ";
      bool is_set = bits & (1 << bit_pos);
      std::cout << bit_pos + 1 << "th bit " << (is_set ? "IS" : "IS NOT") << " set" << std::endl;
   }

   // Flip all bits
   {
      uint8_t bits = 202;
      std::cout << "Flip all bits in " << std::bitset<8>(bits) << " - ";
      std::cout << "~" << std::bitset<8>(bits) << ": ";
      bits = ~bits;
      std::cout << std::bitset<8>(bits) << std::endl;
   }

   // Strip lowest set bit
   {
      uint8_t bits = 202;
      std::cout << "Strip lowest set bit - ";
      std::cout << std::bitset<8>(bits) << " & " << std::bitset<8>(bits-1) << ": ";
      std::cout << std::bitset<8>(bits & (bits - 1)) << std::endl;
   }

   // Get lowest set bit
   {
      uint8_t bits = 202;
      uint8_t count = 0;
      while(bits)
      {
         bits &= bits - 1;
         ++count;
      }
      std::cout << "Counted " << (int)count << " set bits in " << std::bitset<8>(202) << std::endl;
   }

   // ENDSSS
   std::cin.get();

   return 0;
}
