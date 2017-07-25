#ifndef MD5_H
#define MD5_H

//  Order is from low-order byte to high-order byte of digest.
//   Each byte is printed with high-order hexadecimal digit first.
struct MD5Output
{
   unsigned int dWord_0;   // [0][1][2][3]      // lowest byte
   unsigned int dWord_1;
   unsigned int dWord_2;
   unsigned int dWord_3;   // [12][13][14][15]  // highest order byte
};

// take a raw buffer and find a hash number (16-bytes) see above)
void MD5Buffer (unsigned char *buffer, unsigned int buffLen, MD5Output &out);

#endif