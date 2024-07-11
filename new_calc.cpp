#include <iostream>
#include <print>
#include <span>
#include <string>

int eval(char expr[],int length) {
	
	
	bool hasOp = false;
	for(int i=0; i<length ;i++){
		if (expr[i] == '+'||expr[i]=='-'||expr[i] == '/'||expr[i]=='*') {
			hasOp= true;
			break;
		}
	}
	
	if (hasOp== false){
		int result = 0;
		std::print("expr: {} {}\n", expr,length);
		for (int i=0; i<length ;i++) { 
			if(std::isdigit(expr[i])){
				int digit = expr[i] - '0';
				result = result * 10 + digit;
				std::print("result: {0} = {0} * 10 + {1}\n", result, digit);
			}
			else{
				throw std::exception(std::format("invalid expression: invalid digit {}",expr[i] ).data());
			}
		}
		return result;
	}
    int maxpres{-1};
	int curpres{0};
	int op{};
    for (int i = length - 1; i >= 0; --i) {
       if (expr[i] == '+') {
		   curpres=3; 
       }
	   else if (expr[i] == '-') {
		   curpres=4;
            
       }
	   else if (expr[i] == '/') {
		   curpres=1;
            
       }
	   else if (expr[i] == '*') {
		   curpres=2;
            
       }
	   if (curpres>maxpres){
		   maxpres=curpres;
		   op=i;
	   }
    }
		std::cout<<curpres<<" cp: \n";
		std::cout<<maxpres<<"mp: \n";
		std::cout<<op<<"op: \n";
    
    int j=0;
	int k=0;
	char left[200]{};
	char right[200]{};
	
	for(int i=0; i<length ;i++){
		if (i < op) {
			left[j]= expr[i];
			j++;
		}
		else if (i> op) {
			right[k]= expr[i];
			k++;
		}
	}
    
	
    int leftValue = eval(left, j);
    int rightValue = eval(right,k);
	std::cout<< leftValue << " "<<expr[op]<<" " <<rightValue<<"\n";
    if (expr[op]=='+'){
		return leftValue + rightValue;
	}
    else if (expr[op]=='-'){
		return leftValue - rightValue;
	}
	else if (expr[op]=='/'){
		return leftValue / rightValue;
	}
	else if (expr[op]=='*'){
		return leftValue * rightValue;
	}
	throw std::exception{"incorrect expression"};
}

std::string GetInputFromConsole() {
    std::string expression{};
	std::cout<< "hit me:" << "\n";
	std::getline(std::cin, expression);
	
    return expression;
}




