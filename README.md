# MD5-Password-cracker
Program written for the course "Operating Systems" at the Wroclaw University of Science and Technology

## Table of contents
* [Summary](#summary-information)
* [Tech stack](#technology)

## Summary
The programme was created to learn multithreaded programming in the POSIX standard.
Password craker was designed to search all hashed passwords by MD5 algorithm.

## Tech stack
* C
* pthread (POSIX thread)
* openssl

## Before start
To use this program you need to files in the specific format - see /test folder
* data_base - file contains (MD5 hash, mail and username)
* dictionary - potencial passwords (typical passwords like: flower)

This program will check all posible potencial passwords in original form and also:
* its uppercase format
* its first uppercase letter
* numerical preffixes and suffiexs
* and combinations of these three things


## How to use
First you need to compile app:

```
$ make
```
Then run the app by following formula:
```
$ ./MD5cracker <data_base_file> <dictionary_file>
```
