#ifndef NODE_NODE_WEIGHT_HPP
#define NODE_NODE_WEIGHT_HPP


#include<iostream>
#include<vector> 
#include<fstream>
#include<sstream>
#include <string>
#include<map>
#include "check_type.hpp"
#include "exceptions.hpp"
#include "structure_defs.hpp"
#include "unary_set_operations.hpp"
using namespace std;

/****List of Functions ******
 == Default graph_file graphXX
 == Default map_file mapXX
 ==Default error; printed on screen
 ==Calls 
 check_int
 check_double
 execption_weight_string()
 node_node_wt
 --Overloaded as; 
 (input file); DONE 
***** End of Description*****/


/******** Start of Functions ************/
/*
 Input: Edge List from File (Node Node Weight) \n
 Translates Edgelist from String to Numbers \n
 Stores EdgeList as Numbers to graphXX \n
 Stores Map of String to Number in nodemap \n
 */

void node_node_wt(char *file, char* gfile, char* mapfile)
{
	
	//Activity1: Translate Strings to Numbers 
	string st1, st2, wt;//wt stands for weight
    map_st_int nodemap;
	std::pair<std::map<string,int>::iterator,bool> ret;
	string line;
	stringstream linestream;
   	int i=0;//not sure what this stands for yet
	
    vector<Edge> myEdges;
    myEdges.clear();
    Edge myedge;
    
    ifstream dataFile(file, ios::in); //Open input(network) file, argument 1 of the method above
	while(getline(dataFile, line))//getting data from the network file
	{
	    //Readline
		linestream.clear();
		linestream << line;//getting the line form the network file

		linestream >> st1 >> st2 >> wt;//translating the numbers from the input file to strings
		//cout << st1 << " " << st2 << " " << wt << endl;
		//Add strings st1, st2 to map if it does not yet exist
		//Delete all self loops here--otherwise disconnected nodes with self loops cause errors
		
		if(st1.compare(st2)!=0)//if s1 and s2 are not the same
		{
         	ret=nodemap.insert ( std::pair<string,int>(st1,i) );
            if(ret.second==true){i++;}
			ret=nodemap.insert ( std::pair<string,int>(st2,i) );
           	if(ret.second==true){i++;}
    
			//Check if wt is not a int and double
			if(!check_int(wt) && !check_double(wt)) //If it is string--raise exception 
			{ exception_weight_string(); break;}
            
			myedge.node1 = stoi(st1);
			myedge.node2 = stoi(st2);
			myedge.edge_wt = atof(wt.c_str());
			myEdges.push_back(myedge);

			//add the other edge
			myedge.node1 = stoi(st2);
			myedge.node2 = stoi(st1);
			myedge.edge_wt = atof(wt.c_str());
			myEdges.push_back(myedge);
			
			
            myedge.node1=nodemap.find(st1)->second;
            myedge.node2=nodemap.find(st2)->second;
            myedge.edge_wt=atof(wt.c_str());
            myEdges.push_back(myedge);//add the edge to the myEdges edge vector
            
            //Also add the other edge
            myedge.node1=nodemap.find(st2)->second;
            myedge.node2=nodemap.find(st1)->second;
            myedge.edge_wt=atof(wt.c_str());
            myEdges.push_back(myedge);
			
    	}//end of if
		
    } //end of reading file
    dataFile.close();
	//========= Done Activity 1 =============//
	
	
	//Activity2: Store Map for Back Translation
	ofstream myfile1;
	myfile1.open (mapfile, ios::trunc); //Open map file
	
	//Output to mapfile
	std::map<string,int>::iterator it;
	for (it=nodemap.begin(); it!=nodemap.end(); ++it)
		myfile1 << it->first << " " << it->second << "\n";
	
	//Close File
	myfile1.close();
	//========= Done Activity 2 =============//
    
    //Activity 3: Writes Edges in Ordered Form to New File
    sort(&myEdges, inc_node1);//from ../basic_setops/unary_set_operations.hpp, works
    //Run unique to remove duplicates
    vector<Edge> thisEdges=unique(myEdges);//works
    ofstream myfile;
    myfile.open (gfile, ios::trunc); //Open graph_file
    for(int x=0;x<thisEdges.size();x++)
    {myfile << thisEdges[x].node1<<"  "<<thisEdges[x].node2<<"  "<<thisEdges[x].edge_wt << "\n";}//outputting the sorted graph with the edgeweight to output.txt
    myfile.close();
    
    
    //========= Done Activity 2 =============//

	
	return ;	
}
	
/******** End of All  Functions ************/		
#endif
