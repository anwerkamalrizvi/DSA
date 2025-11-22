Task # 1
Suppose you are working on a program that needs to store a large number of strings, with the possibility of
duplicate strings. You decide to use chain hashing to efficiently store and retrieve the strings, but you want
to ensure that collisions are avoided as much as possible. Your hash function simply takes the sum of the
ASCII values of the characters in the string and returns the remainder after dividing by the number of
buckets. You decide to implement the hash table using a linked list for each bucket.
Input and output:
HashTable myhash;
[hine: key is A]
myhash.insert(&quot;A&quot;,&quot;aaaaa&quot;);
myhash.insert(&quot;B&quot;,&quot;bbbbb&quot;);
myhash.insert(&quot;C&quot;,&quot;ccccc&quot;);
myhash.insert(&quot;A&quot;,&quot;zzzzz&quot;);

Task # 2:
Some ABC university students want to develop an ASCII code-based dictionary app for their Final Year
Project. This app should allow the users to perform the following operations:
a) Add_Record () This function will take a string input from user and add into the dictionary. For adding
the string user will use a unique hash function k MOD 100 (table size must be 100, for k user will calculate
the SUM of ASCII character of that word).
b) Word_Search () User will only pass a single string. If string is not available then generate an error
message.
c) Print_Dictionary () Users can also display the complete dictionary.
Note: Use Separate Chaining in case of collisions.
Output:
 search key AB: FASTNU
 key EF deleted successfully !
 index 31: (AB, FASTNU)
 index 35: (CD, CS)
Task # 3

Implement the class Hash class having the functionality of insert, delete, search and display using list (built
in library for linked list in C++).

Task # 4
Given an array of distinct integers, find using hashing if there are two pairs (a, b) and (c, d) such that
a+b = c+d, and a, b, c, and d are distinct elements. If there are multiple answers, then print any of
them.
Input: {3, 4, 7, 1, 2, 9, 8}
Output: (3, 8) and (4, 7)
Explanation: 3+8 = 4+7
Input: {3, 4, 7, 1, 12, 9};
Output: (4, 12) and (7, 9)
Explanation: 4+12 = 7+9
Input: {65, 30, 7, 90, 1, 9, 8};
Output: No pairs found
Task # 5:
Implement a C++ class StudentHashTable to manage student records in a hash table with a size of 15. Use
quadratic probing for collision resolution with the formula (index + attempt^2) % table size.Implement the
function InsertRecord that takes a student&#39;s roll number and name, inserting the record into the hash table
using quadratic probing.Implement the function SearchRecord that takes a roll number, searches for the
corresponding record using quadratic probing, and prints the student&#39;s name if found; otherwise, print a
&quot;Record not found&quot; message.
