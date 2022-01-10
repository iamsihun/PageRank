#DEMO VIDEO: https://youtu.be/Etoyz4WbSOg?t=560
USAGE:  
Type 'make' in the terminal to build the program
To run only pagerank, type 'make pagerank'.
To run only unit tests, type 'make test'.

Floyd-Warshall Usage:  
    1. To generate and print the shortest distances between all the subreddits, type ' ./printfw ' in the terminal  
       Please allow for a couple seconds as the data set is fairly large.  
    2. The terminal will print all the pairs of subreddits and the distance between them (if there is a path).     
        If there is no path, it will print 'no path'
    3. Then, type ' ./fwpath ' and input a starting node and an ending node. The terminal will then generate the  
       path between them as well as the distance.  

    Test Case Usage: 
    (Usage of these work the same as the main data set above ^) 
        1. Type ' ./fw_test1 ' to execute the first test case  
        2. Type ' ./fw_test2 ' to execute the second test case  
        3. Type ' ./fw_test3 ' to execute the third test case

Pagerank Usage:
    1. To generate and print the pagerank distributions of the subreddits, type './pagerank' in the terminal.
       Please allow for a couple seconds as the data set is fairly large.
    2. The terminal will print out all of the connected components in the graph, labelling each component as "component: i" where
       i starts from 0. Then, under each component label, it will print out the subreddit and its calculated probability.
       Ex:
       component: 0
       sub1: 0.25
       sub2: 0.5
       sub3: 0.25

       component: 1
       sub4: 0.1
       sub5: 0.6
       sub6: 0.3

    3. You can also print out the graph by uncommenting the line 'r.printData()' inside of pagerank.cpp, or adding 'r.printData()'     
       inside any main function.

Unit Testing
    1. To run unit tests, type './test'. All the data files used in the tests are inside the data folder.
