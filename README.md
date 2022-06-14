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

   ### GNU MP Library [Multiprecision Arithmetic Library for C/C++]
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

   ### Paillier Library [For C]
        Reference: https://acsc.cs.utexas.edu/libpaillier/#general
        Steps to Install: 
        1. Download "libpaillier-0.8.tar.gz" from https://acsc.cs.utexas.edu/libpaillier/#general
        2. Extract the file. You will get a directory "libpaillier-0.8".
        3. Open a terminal and enter this directory using "cd" command.
        4. Then run the following commands:
            $ ./configure
            $ make
            $ sudo make install 

   ### Paillier Library [For Python]
        Reference: https://python-paillier.readthedocs.io/en/develop/
        Steps to Install: https://python-paillier.readthedocs.io/en/develop/installation.html
        1. pip install phe

   ### PyCryptodome Library [AES Library for Python]
        Reference: https://pycryptodome.readthedocs.io/en/latest/src/introduction.html
        Steps to Install: https://pycryptodome.readthedocs.io/en/latest/src/installation.html
        1. Open a terminal and run the following commands:
            a. sudo apt-get install build-essential python3-dev
            b. pip install pycryptodome  
            c. pip install pycryptodomex
        2. To test everything is installed perfectly or not
            a. pip install pycryptodome-test-vectors
            b. python -m Crypto.SelfTest
            c. python -m Cryptodome.SelfTest

   ### tiny-AES-c Library [AES library for C]
        Reference: https://github.com/kokke/tiny-AES-c
        Steps to use: 
        1. Open a terminal and change the directory where to download the library. 
        2. Then run the following commands:
            a. $ git clone "https://github.com/kokke/tiny-AES-c"
            b. $ cd tiny-AES-c
            c. $ make 

   ### intel/sgx-gmp Library [Multiprecision Arithmetic Trusted Library for SGX]
        References: https://github.com/intel/sgx-gmp
        We may have to install "texinfo" (https://www.gnu.org/software/texinfo/) and "make" (https://ftp.gnu.org/gnu/make/) if not installed earlier
        Steps to Install: https://github.com/intel/sgx-gmp/blob/github/INSTALL
        1. $ git clone "https://github.com/intel/sgx-gmp"
        2. $ cd sgx-gmp
        3. $ sudo ./configure --enable-sgx --enable-static --disable-shared --enable-assembly
        4. $ sudo ./sgx-configure
        4. $ sudo make
        5. $ sudo make install
        6. $ sudo ./sgx-configure

   ### Intel SGX Installation Setup
        Refer this doc: [Shared by Suraj and Rohan (TAs of CS741 (Spring 2021) course in IIT Bombay)]
        https://docs.google.com/document/d/1lqDPNEk2pKePhnNfdsUBi0X1Zj-tL0Dti740ZC-XgGA/edit

## To test Paillier Encryption/Decryption Timing Overhead for d-sized query
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

## To test AES Encryption/Decryption Timing Overhead for d-sized query
    1. $ cd MTP_CODE
    2. $ cd AES_Enc_Decr_Time_Measurement
    3. $ Run the following commands based on in which language to find:
        i.  To find AES Encryption Time on QU side and AES Decryption Time on Enclave 1 side (in Python)
            a. Open the file "AES_Encr_Decr_overhead.py" and set the value of d. 
            b. $ python3 AES_Encr_Decr_overhead.py
        ii. To find AES Encryption Time on QU side and AES Decryption Time on Enclave 1 side (in C)
            a. Open the file "AES_Encr_Decr_overhead.c" and set the value of d.
            b. $ gcc AES_Encr_Decr_overhead.c aes.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            c. $ ./a.out

   ### Google Sheet Link containing Paillier Encryption/Decryption Timing Overhead and AES Encryption/Decryption Timing Overhead
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
            a. $ gcc QueryEnc.c paillier.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp -lpaillier
            b. $ ./a.out
        vi. kNN computation by CS and result return
            a. $ gcc kNNComp.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out

        The final result (indices of k nearest neighbor in DB) is present in "TopK.txt" file

## To run IBM's Design (Modification of Zhu's Work)
    1. $ cd MTP_CODE
    2. $ cd IBM_Work_On_Zhus_Paper
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
        v.  Query encryption by QU and encryption by DO and again decryption by QU
            a. $ gcc QueryEnc.c paillier.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp -lpaillier
            b. $ ./a.out
        vi. kNN computation by CS and result return
            a. $ gcc kNNComp.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out

        The final result (indices of k nearest neighbor in DB) is present in "TopK.txt" file

## Attack on Zhu's Design
    1. Follow steps 1 to 3 above (of "To run Zhu's Design"). 
    2. Then follow the following steps in this order.
        i.  Run Attack 1: "Obtaining the secret betaQ"
            a. $ gcc attack1.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out
            c. Output printed on terminal
        ii. Run Attack 2: "Obtaining the secret M"
            a. $ gcc attack2.c paillier.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp -lpaillier
            b. $ ./a.out
            c. The output of attack 2 (extracted M) is in file "calcMbyQU.txt". It can be matched with "M.txt" (Actual Matrix used by Data Owner)
        iii.Run Attack 3: "Extracting the complete DataBase in clear"
            a. $ python3 attack3.py
            b. The output of attack 3 (extracted DataBase) is in file "Calculated_DataBase_by_QU". It can be matched with "DataBase.txt" (Actual DataBase of Data Owner)
        iv. Run Attack 4: "Obtaining the query in the clear"
            a. $ python3 attack4.py
            b. The output of attack 4 (extracted query) is printed on terminal. It can be matched with "queryByQU.txt" (Actual Query by QU)

## Attack on IBM's Design
    1. Follow steps 1 to 3 above (of "To run IBM's Design (Modification of Zhu's Work)"). 
    2. Then follow the following steps in this order.
        i.  Run Attack 1: "Trying to obtain the secret betaQ"  [Same code gave betaQ in Zhu's work but fails in IBM's work]
            a. $ gcc attack1.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp
            b. $ ./a.out
            c. Output printed on terminal. [Incorrect Output as betaQ is not gcd of query points. Run attack 2 for obtaining betaQ]
        ii. Run Attack 2: "Obtaining the secret betaQ and the secret M"
            a. $ gcc attack2.c paillier.c -o a.out -L/usr/local/lib/ -I/usr/local/include/ -lgmp -lpaillier
            b. $ ./a.out
            c. The output of attack 2 (extracted M) is in file "calcMbyQU.txt". It can be matched with "M.txt" (Actual Matrix used by Data Owner)
            d. betaQ is printed on terminal for each queries. Total eta ( = d + 1 + c + epsilon) queries are needed to obtain both betaQ and M
        iii.Run Attack 3: "Extracting the complete DataBase in clear"
            a. $ python3 attack3.py
            b. The output of attack 3 (extracted DataBase) is in file "Calculated_DataBase_by_QU". It can be matched with "DataBase.txt" (Actual DataBase of Data Owner)
        iv. Run Attack 4: "Obtaining the query in the clear"
            a. $ python3 attack4.py
            b. The output of attack 4 (extracted query) is printed on terminal. It can be matched with "queryByQU.txt" (Actual Query by QU)

## Reference:
   ### Website Reference for coding:
    a. https://stackoverflow.com/questions/30942413/c-gmp-generating-random-number
    b. Paillier Library for Python:
       https://python-paillier.readthedocs.io/en/develop/usage.html#usage
    c. https://en.wikipedia.org/wiki/Paillier_cryptosystem
    d. https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
    e. https://cse.iitkgp.ac.in/~goutam/cnt/reading/gmp-man-5.0.2.pdf
    f. https://www.programiz.com/dsa/heap-sort
    g. https://discuss.python.org/t/converting-integer-to-byte-string-problem-in-python-3/5058
    h. https://stackoverflow.com/questions/50254710/c-encrypt-and-decrypt-a-string-with-aes
    i. https://www.includehelp.com/c/convert-ascii-string-to-byte-array-in-c.aspx
    j. https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
    k. https://askubuntu.com/questions/27677/cannot-find-install-sh-install-sh-or-shtool-in-ac-aux
    l. https://github.com/intel/sgx-gmp-demo

   ### Papers Reads for MTP:
    a. “Secure and controllable k-NN query over encrypted cloud data with key confidentiality” 
        (by Youwen Zhu, Zhiqiu Huang, Tsuyoshi Takagi; 2016)
        https://www.sciencedirect.com/science/article/pii/S0743731515002105
    b. “Secure k-NN as a Service over Encrypted Data in Multi-User Setting” 
        (by Gagandeep Singh; Akshar Kaul; Sameep Mehta; 2018)
        https://ieeexplore.ieee.org/document/8457795
    c. "Privacy preserving k-nearest neighbor classification over encrypted database in outsourced cloud environments"
        (By Wei Wu, Udaya Parampalli, Jian Liu, 2018)
        https://link.springer.com/article/10.1007/s11280-018-0539-4
    d. “Privacy-Preserving Multi-Keyword Ranked Search over Encrypted Cloud Data” 
        (by Ning Cao, Cong Wang, Ming Li, Kui Ren, Wenjing Lou; 2014)
        https://ieeexplore.ieee.org/document/6674958
    e. “Revisiting Security Risks of Asymmetric Scalar Product Preserving Encryption and Its Variants” 
        (by Weipeng Lin; Ke Wang; Zhilin Zhang; Hong Chen; 2017)
        https://ieeexplore.ieee.org/document/7980052
    f. “Practical Multi-keyword Ranked Search with Access Control over Encrypted Cloud Data” 
        (by Jiayi Li; Jianfeng Ma; Yinbin Miao; Yang Ruikang; Ximeng Liu; Kim-Kwang Raymond Choo; 2020)
        https://ieeexplore.ieee.org/document/9198140
    g. “Shielding Applications from an Untrusted Cloud with Haven” 
        (by Andrew Baumann, Marcus Peinado, and Galen Hunt; 2015)
        https://dl.acm.org/doi/10.1145/2799647
    h. “Use of Intel SGX to ensure the confidentiality of data of cloud users” 
        (by D. P. Zegzhda, E. S. Usov, A. V. Nikol’skii. Yu. Pavlenko; 2017)
        https://link.springer.com/article/10.3103/S0146411617080284
    i. "Intel SGX Explained"
        (by Victor Costan and Srinivas Devadas, 2016)
        https://eprint.iacr.org/2016/086.pdf