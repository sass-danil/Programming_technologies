/*
 * dbEngine.h
 *
 *  Created on: 12 мар. 2024 г.
 *      Author: c0nt1nyou
 */

#ifndef DBENGINE_H_
#define DBENGINE_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <errno.h>
#include <vector>

using namespace std;

class Column{
private:
	string _type;
	vector<string> _values;
	string _fileName;

public:
	Column(string fileName){

	}

	Column(string type, vector<string> values, string name){
		_type = type;
		_values = values;
		_fileName = name; //TODO proper filename generation
	}

	Column(){
		_type = new String();
	}
};

class Table{

private:
	vector<Column> _cols;
	string _fileName;

public:

	Table(){

	}

	Table(string fileName){

	}

	void create(string queryStr){

	}

	void destroy(){

	}
};

class DB{

};

class DBtext{

};



#endif /* DBENGINE_H_ */
