# hashDNS
My first Data Structures homework

A C hashtable implementation which is supposed to simulate the lookup operations made by a DNS server. 

Basically key = website_name and value = ip_address.

Besides the "find" operation, the hashtable also supports the usual "put"/"remove" operations.

#How to compile

Simply run "make build"

#How to run

Call the program using the following syntax: "./tema1 N file.in file.out" where: 
* N - the number of buckets within the hastable
* file.in - input file name
* file.out - output file name

Operation syntax:
* put \<key\> \<value\> (eg: put www.google.com 8.8.8.8) - adds the \<key,value\> pair in the hashtable
* remove \<key\> (eg: remove www.google.com) - removes the \<key,value\> pair
* get \<key\> (eg: get www.google.com) - gets the value for the given key
* print - prints all the buckets in the following format: \<bucket_index\> : \<value_1\>, ... ,\<value_n\>
* print_bucket \<bucket_index\> - prints all values for the given bucket





