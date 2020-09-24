# Caesar Cipher Project #2 - Data Structures, Performance Testing, and Unit Testing

Written in C, this script should take in encrypted text in the stdin and output the decrypted text and the cipher shift that it was encrypted with. This was done by comparing all the combinations of cipher shifts with a known dictionary. The script outputs all the results to a solutions.txt file.

## Build

This was tested on an Ubuntu VM using cmake v3.16.3. In the project directory run the following command:

```bash
cmake .
```
Then run the command: 
```bash
make
```

## Usage

There are 2 main ways to run this script.


#### 1. Manual Input
This method will allow you to input any text into the console and the shift will be calculated against the stored dictionary. 
```bash
./decrypt_cipher
```

#### 2. File Input
This method will allow you to input a file path. This file should be a list of strings separated by line. The script will determine the shift for the line.
**File path for testing = ./encrypted_text.txt**
```bash
cat [file_path] | ./decrypt_cipher
```

## Performance

To fit with the new assignment guidelines we are now improving the program's speed. This was done on a vmware virtual machine given 4 cores of a AMD Ryzen 2600X and 8 GB of 3200mhz RAM. To test the speed of this function I used the following command:

```bash
time cat [file_path] | ./decrypt_cipher
```

| Program Stage | Notes | Run 1 (s)| Run 2 (s)| Run 3 (s)| Average (s)| 
|---------------|-------|-------|-------|-------|---------|
| Assignment 1 submission | Script is unmodified from version initially turned in. | 29.357 |       28.934 | 29.062 | 29.118 | 
|               |       |       |       |       | |
|               |       |       |       |       | |

## Other Files
The python files in the project directory were used by me to develop solutions to the project. I did this because I am much more comfortable in python than C so I was able to better understand how to solve the problem.

Using the text file provided by the TA, I was able to confirm the first 50 solutions generated by my script matched the expected output.