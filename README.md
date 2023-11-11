# BSTs-HASHING

This project is part of the "Data Structures" course in the Computer Science and Informatics Department of the University of Patras.

With the appropriate definition of structs and functions, implement an application (write a program in C) that processes the data in the agn.us.txt file.

(A) The application first reads the file and creates a Binary Lookup Tree (DBT) in which each node maintains the record (Date, Volume). The DBT is ordered with respect to the Date field and is implemented with dynamic memory management. The DBT shall be an AVL tree or red-black tree. After creating the DBT the application displays a menu with the following options. 
1.Display the DBT with internally arranged traversal. Each visualization shall contain a header with the titles of the records being visualized.
2. Search for the stock trading volume value (Volume) based on the date (Date) given by the user. 
3. Modify the stock trading volume value (Volume) corresponding to a specific date given by the user. 
4. Deletion of a record corresponding to a specific date which will be given by the user. 
5. Exit the application.

(B) Modify the code in (A) appropriately so that the file is read into the DBT based on the stock trading volume value (Volume field). The DBT is ordered by Volume value by date and implemented with dynamic memory management. After creating the DBT, the application displays a menu with the following options: 
1. Find day/days with the MINIMUM trading volume value. 
2. Find day/days with the MAXIMUM transaction volume value.
