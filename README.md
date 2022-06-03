# MTP

## Basic Info:
    Author      : Aditya Jain
    Department  : M. Tech CSE 2nd Year
    Roll. No.   : 203050003
    College     : IIT Bombay
    Guide       : Prof. Bernard Menezes 

## MTP Title: 
    Privacy Preserving Cloud Computing

## Pre-requisite to run code:

   ### GNU MP Library
        Reference: https://gmplib.org/manual/
        Steps to Install: (Ref.: https://gmplib.org/manual/Installing-GMP)
        1. Download "gmp-6.2.1.tar.lz" from https://gmplib.org/.
        2. Extract the file. You will get a directory "gmp-6.2.1". 
        3. Open a terminal and enter this directory using "cd" command.
        4. Then run the following commands:
            a) To Build:
                i)  $ ./configure
                ii) $ make 
            b) To verify whether built is proper or not
                i)  $ make check
            c) To install
                i)  $ sudo make install

   ### Paillier Library
        Reference: https://acsc.cs.utexas.edu/libpaillier/#general
        Steps to Install: 
        1. Download "libpaillier-0.8.tar.gz" from https://acsc.cs.utexas.edu/libpaillier/#general
        2. Extract the file. You will get a directory "libpaillier-0.8".
        3. Open a terminal and enter this directory using "cd" command.
        4. Then run the following commands:
            $ ./configure
            $ make
            $ sudo make install 

## To test Paillier Encryption Timing Overhead
    1. $ cd MTP_CODE
    2. $ cd PaillierEncTimeMeasurement
    3. $ Run the following command based on what to find:
        i.  To find Paillier Encryption Time on QU side (in C)
            a. Open the file "paillierQU.c" and set the value of d. 
            b. $ gcc paillierQU.c paillier.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp -lpaillier
            c. $ ./a.out   
        ii. To find Paillier Decryption Time on QU side and Execution Time on DO (in C)
            a. Open the file "paillierDO.c" and set the value of d. 
            b. $ gcc paillierDO.c paillier.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp -lpaillier
            c. $ ./a.out 
        iii.To find Paillier Encryption Time on QU side (in Python)
            a. Open the file "paillierQU.py" and set the value of d. 
            b. $ python3 paillierQU.py
        iv. To find Paillier Decryption Time on QU side and Execution Time on DO (in Python)
            a. Open the file "paillierDO.py" and set the value of d. 
            b. $ python3 paillierDO.py 

   ### Google Sheet Link containing Paillier Encryption/Decryption Timing Overhead
       https://docs.google.com/spreadsheets/d/1u6Rli-x2XHccJYhr5Fbjk3tGbP--gAqFOm9xybhxE0E/edit#gid=0

## To run Zhu's Design
    1. $ cd MTP_CODE
    2. $ cd ZHUsDesign
    3. Run the following commands in this order:
        i.  To generate random (synthetic) Database
            a. $ gcc gen_rand_database.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out
        ii. Generation of Keys by DO for encrypting database
            a. $ gcc KeyGen.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out 
        iii. Generate M inverse using python
            a. python3 genInvM.py
        iv. Encrypting DataBase by Data Owner
            a. $ gcc DBEnc.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out
        v. Query encryption by QU and encryption by DO and again decryption by QU
            a. $ gcc QueryEnc.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out
        vi. kNN computation by CS and result return
            a. $ gcc kNNComp.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out

        The final result (indices of k nearest neighbor in DB) is present in "TopK.txt" file

## Reference:
   ### Website Reference for coding:
    a. https://stackoverflow.com/questions/30942413/c-gmp-generating-random-number
    b. Paillier Library for Python:
       https://python-paillier.readthedocs.io/en/develop/usage.html#usage
    c. https://en.wikipedia.org/wiki/Paillier_cryptosystem
    d. https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
    e. https://cse.iitkgp.ac.in/~goutam/cnt/reading/gmp-man-5.0.2.pdf
    f. https://www.programiz.com/dsa/heap-sort

   ### Papers Reads for MTP:
    a. https://www.sciencedirect.com/science/article/pii/S0743731515002105