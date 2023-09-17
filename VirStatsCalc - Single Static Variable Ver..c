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
	float a, b, c, d, e, f, g, h, i;
	
	//Opening CSV save file 
	FILE *fptr;
	fptr = fopen("VirCalcSingleResults.txt", "w+");
	
	if(!fptr){
		printf("Error: CSV file could not be created.");   
		exit(1);            
	}
    
	//Variable name table + inputs
	printf("Enter values from 1 to 100 for the variables as they appear...\n\n");
	printf("a = User's Awareness of the computer virus / Sudden anxiety from the attack\n");
	printf("Enter value: ");
	scanf("%f", &a);
	printf("b = Economical state of the user / company\n");
	printf("Enter value: ");
	scanf("%f", &b);
	printf("c = Criticality of the encrypted data / Amount of the critical encrypted data (Percentage)\n");
	printf("Enter value: ");
	scanf("%f", &c);
	printf("d = Amount of data (In memory units)\n");
	printf("Enter value: ");
	scanf("%f", &d);
	printf("e = Amount of data the virus infects (In memory units)\n");
	printf("Enter value: ");
	scanf("%f", &e);
	printf("f = Percentage of infected computers in the network\n");
	printf("Enter value: ");
	scanf("%f", &f);
	printf("g = Known ways of effective disinfection / Any possible ways of data recovery\n");
	printf("Enter value: ");
	scanf("%f", &g);
	printf("h = The effectives of the known disinfection strategies all together (percentage based on the known stategies effectiveness)\n");
	printf("Enter value: ");
	scanf("%f", &h);
	printf("i = Safety of operations during / after the infection (percentage based on the complexity of the operation)\n");
	printf("Enter value: ");
	scanf("%f", &i);
	
	printf("\nThe values printed at the CSV save file will be representing the results of the SF, DP, DC and SS formulas.\n");
	
	fprintf(fptr,"Severity, Disinfection Probability, Disinfection Caliber, Spreadability\n");
				
		//Functions for CSV exports based on concept formulas
		float TSF, TDP, TDC, TSS;
		TSS = Spread_Calc(a, b, c, d, e, f, g, h, i);
		TSF = Severity_Calc(a, b, c, d, e, f, g, h, i, TSS);
		TDP = Dis_Prob_Calc(a, b, c, d, e, f, g, h, i);
		TDC = Dis_Cali_Calc(a, b, c, d, e, f, g, h, i);
		
		fprintf(fptr,"%f , %f , %f , %f\n", TSF, TDP, TDC, TSS);
		
	
	//Close save file
	fclose(fptr);
	
	//Termination messages
	printf("\nProgram terminated succesfuly.\n");
	printf("(C) Dimitris Kostadimas 2022");
	return 0;
}
