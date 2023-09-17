#include <stdio.h>
#include <stdlib.h>

//Global Variables
//SevirityFormulaVal, DisinfectionProbabilityVal, DisinfectionCaliberVal, SpreadabilityFormulaVal, SeverityTempVal
float SF, DP, DC, SS, S, CC;

float Severity_Calc(float a, float b, float c, float d, float e, float f, float g, float h, float i, float TSS){	
	//Severity formula
	SF = e*0.25 + f*0.10 + TSS*0.25 + g*0.3 + c*0.1;
	return SF;
}

float Dis_Prob_Calc(float a, float b, float c, float d, float e, float f, float g, float h, float i){
	//Disinfection probability
	if(g != 0){
		DP = a*0.15 + b*0.2 + (100 - e)*0.1 + (100 - f)*0.15 + h*0.30 + i*0.1;
	}
	else{
		DP = 0;
	}
	
	return DP;
}

float Dis_Cali_Calc(float a, float b, float c, float d, float e, float f, float g, float h, float i){
	//Disinfection caliber
	S = e/d;
	CC = c*0.01;
	
	if(CC <= 0.2 || S < 0.2){
		DC = 0;
	}
	else if(CC > 0.8){
		DC = CC;
	}
	else if(S <= 0.3){
		DC = S*CC;
	}
	else if(S <= 0.5){
		DC = S*CC;
	}
	else if(S <= 0.8){
		DC = S*CC;
	}
	else if(S <= 1){
		DC = CC;
	}
	
	return DC*100;
}

float Spread_Calc(float a, float b, float c, float d, float e, float f, float g, float h, float i){	
	//Spreadability formula
	SS = (100 - a)*0.7 + f*0.3;
	return SS;
}

int main(){
	//Variables
	int j;
	float VarVal, a, b, c, d, e, f, g, h, i;
	char SelectedVar;
	
	//Opening CSV save file 
	FILE *fptr;
	fptr = fopen("VirCalcResults.txt", "w+");
	
	if(!fptr){
		printf("Error: CSV file could not be created.");   
		exit(1);            
	}
    
	//Variable name table
	printf("VARIABLE NAMES BOARD\n\n");
	printf("a = User's Awareness of the computer virus / Sudden anxiety from the attack\n");
	printf("b = Economical state of the user / company\n");
	printf("c = Criticality of the encrypted data / Amount of the critical encrypted data (Percentage)\n");
	printf("d = Amount of data (In memory units)\n");
	printf("e = Amount of data the virus infects (In memory units)\n");
	printf("f = Percentage of infected computers in the network\n");
	printf("g = Known ways of effective disinfection / Any possible ways of data recovery\n");
	printf("h = The effectives of the known disinfection strategies all together (percentage based on the known stategies effectiveness)\n");
	printf("i = Safety of operations during / after the infection (percentage based on the complexity of the operation)\n");
	
	//Inputs
	do{
		printf("\nSelect the variable that you want to input certain values for (a-i): ");
		fflush(stdin);
		scanf("%c", &SelectedVar);
		fflush(stdin);
	}while(SelectedVar != 'a' && SelectedVar != 'b' && SelectedVar != 'c' && SelectedVar != 'd' && SelectedVar != 'e' && SelectedVar != 'f' && SelectedVar != 'g' && SelectedVar != 'h' && SelectedVar != 'i');
	
	do{
		printf("\nEnter the variable value (1-100): ");
		scanf("%f", &VarVal);
	}while(VarVal < 0 || VarVal > 100);
	printf("\n");
	
	printf("The values printed at the CSV save file will be representing the results of the SF, DP, DC and SS formulas while variable '%c' was constant and equal to '%.0f'. The rest of the variables values range from 1 to 100.\n", SelectedVar, VarVal);
	fprintf(fptr,"Itteration, Severity, Disinfection Probability, Disinfection Caliber, Spreadability\n");
	
	for (j = 1; j <= 100; j++){
		
		//Dummy inserts
		a = b = c = d = e = f = g = h = i = j;
		
		//Set the selected value to the selected variable
		switch(SelectedVar){
			case 'a':
				a = VarVal;
			break;
			case 'b':
				b = VarVal;
			break;
			case 'c':
				c = VarVal;
			break;
			case 'd':
				d = VarVal;
			break;
			case 'e':
				e = VarVal;
			break;
			case 'f':
				f = VarVal;
			break;
			case 'g':
				g = VarVal;
			break;
			case 'h':
				h = VarVal;
			break;
			case 'i':
				i = VarVal;
			break;
		}
				
		//Functions for CSV exports based on concept formulas
		float TSF, TDP, TDC, TSS;
		TSS = Spread_Calc(a, b, c, d, e, f, g, h, i);
		TSF = Severity_Calc(a, b, c, d, e, f, g, h, i, TSS);
		TDP = Dis_Prob_Calc(a, b, c, d, e, f, g, h, i);
		TDC = Dis_Cali_Calc(a, b, c, d, e, f, g, h, i);
		
		fprintf(fptr,"%d , %f , %f , %f , %f\n", j, TSF, TDP, TDC, TSS);
		
	}	
	
	//Close save file
	fclose(fptr);
	
	//Termination messages
	printf("\nProgram terminated succesfuly.\n");
	printf("(C) Dimitris Kostadimas 2022");
	return 0;
}
