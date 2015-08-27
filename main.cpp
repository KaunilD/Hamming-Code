#include<iostream>
#include<cmath>
#include<cstdlib>
#include<vector>
using namespace std;

void printVector(vector<int> v, string a){
	cout << a << " : ";
	for (int i = 0; i < v.size(); ++i)
	{	
		cout << v[i];
	}
	cout << endl;
}
int main(){
	vector<int> input, recieverCode, hammingDW, powersOfTwo;
	int numberOfInputs = 0;
	cout << "Hamming Code Generation and Error Correction for 1 bit. "<<endl;
	cout << "Version : Release." << endl;
	cout <<"Number of input bits : ";
	cin >> numberOfInputs;
	cout << endl;
	//Randomly push 1's or 0's to the input vector
	for(int i = 0; i < numberOfInputs; ++i)
	{
		int temp = rand()%2;
		input.push_back(temp);
	}
	int powerOfTwo = 0;
	int hammingDWIndex = 0;
	int inputDWIndex = 0;
	//calculate parity bit positions and push 0 at the respective positions
	while(numberOfInputs != 0){
		
		if(hammingDWIndex + 1 == pow(2, powerOfTwo)){
			hammingDW.push_back(0);
			++hammingDWIndex;
			++powerOfTwo;
		}else{
			hammingDW.push_back(input[inputDWIndex]);
			++inputDWIndex;
			++hammingDWIndex;
			--numberOfInputs;
		}
	}
	
	printVector(hammingDW, "Intermediate Hamming Data Word");
	//Calculate the value of pairty bits and push it at their respective positions in the intermediate hamming data word
	for(int i = 0; i < powerOfTwo; ++i){
		int sum = 0;
		for(int j = pow(2,i); j <= hammingDW.size(); j = j+2*pow(2, i)){
			for(int k = 0; k < pow(2,i); k++){
				if(j+k <= hammingDW.size() && j+k != pow(2,i)){
					sum^=hammingDW[ j+k - 1];
				}
			}
		}
		cout<< "Parity Bit : " << pow(2,i) << " = " << sum <<endl;
		hammingDW[pow(2,i) - 1] = sum;
	}

	printVector(hammingDW, "Hamming Data Word");
	
	int error = 8;
	cout<<"Select a bit to flip : ";
	cin>>error;
	cout<<endl;
	//send the hamming codee to the reciever 
	for(int i = 0; i < hammingDW.size(); ++i){
		recieverCode.push_back(hammingDW[i]);
	}
	// flip the selected bit to signal and errorneous transmission on the reciever station
	recieverCode[error]=!recieverCode[error];
	printVector(recieverCode, "Incorrect Data Word");
	cout<<"Error = "<<error << endl;
	
	//calculate pairty bits again but this time on the recieved packet
	cout<<"Parity Bit calculation for Reciever Code." << endl;
	for(int i = 0; i < powerOfTwo; ++i){
		int sum = 0;
		for(int j = pow(2,i); j <= recieverCode.size(); j = j+2*pow(2, i)){
			for(int k = 0; k < pow(2,i); k++){
				if(j+k <= recieverCode.size() && j+k != pow(2,i)){
					sum^=recieverCode[ j+k - 1];
				}
			}
		}
		cout<< "Parity Bit : " << pow(2,i) << " = " << sum <<endl;
		recieverCode[pow(2,i) - 1] = sum;
	}

	//parity bit sum for the location of errorenous bit
	int paritySum = 0;
	//match the calculated parity bits against the transmitting stations calculations and select the mismatches
	for(int i = 0; i < powerOfTwo; i++){
		if(hammingDW[pow(2,i) - 1]!=recieverCode[pow(2,i) -1]  ){
			paritySum = paritySum + pow(2, i);	
		}
	}
	cout<<"Parity Sum : " << paritySum - 1 << endl;
	if(paritySum == 0){
		cout<<"Correct Transmission."<<endl;
	}else{
		cout<<"Error at bit : "<<paritySum - 1<<" .";
		recieverCode[paritySum-1]=!recieverCode[paritySum-1];
		printVector(hammingDW, "Correct Hamming Code");
	}
	return 0;
}
