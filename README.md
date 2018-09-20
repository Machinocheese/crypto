# DES
Implementation of  DES

So, for my program, I implemented a variety of features. The first of which was DES encryption, which is what this entire project was about in the first place. There are two modes for the program: it can either take in 5 parameters, in which case it will send the contents of a file to an indicated IP and PORT number, or it can take in 4 parameters. In that case, it will take in a string and a key. You also get the option of encrypting/decrypting the string from there. I mainly added the decrypt feature as a sort of debugger for myself, so it's a rather unnecessary feature. I also have left a basic usage statement in the case you try to run the program erroneously, so that should cover up all the confusion that you might still have left.

Now in order to fill the 500 words, I'll explain a little bit about how DES works. Fundamentally, there's nothing complex about it. When I tried researching the implementation, people really made it sound a lot harder than it actually is to implement. It's just a series of "permutations", which in this case is simply swapping the bits around in the key, left-shifts, and a rather weird element where you use generated numbers to access hard-coded elements called s-boxes. DES first takes in a 64-bit key, which it then processes it through a PC1 permutation, which transforms it from 64 bits to 56 bits. It then repeatedly shifts the permutation a certain amount to the left, and through that, it generates the other 15 subkeys. Then all subkeys are run through a pc2 permutation. Once the subkeys have been generated, it's time to look at the actual message. The message is run through an ip permutation, before being split into left and right. In order to get to the next round, which also consists of a left and right, the right side must be xor'ed with the previous left side and run through a function that will process the number and link it to a position in an s-table. The left side will be the same as the right side from the last time. This is done 15 more times, until you get to the final step. Then, you swap the position of right and left to form R+L. You then run another permutation on it before finally finishing with the encryption!

Also, a great resource that really helped me out: http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
