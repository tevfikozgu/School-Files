#include <iostream> 

using namespace std;

int main() {
	int grades1[10][3] = {{50,55,45}, {86,13,60}, {55,45,75}, {45,45,10},{70,65,76},{12,13,10},{43,45,80},{12,30,35}, {76,55,65},{90,95,98}};
	int grades2[3][10] = {{50,86,55,45,70,12,43,12,76,90}, {55,13,45,45,65,13,45,30,55,95},{45,60,75,10,76,10,80,35,65,98}};
	double exam_average = 0;
	double student_average = 0; 
	int exam = 1;
	int student = 1;
	
	for (int i=0;i<3;i++) {  // Average of each Exam!!
		for (int j=0;j<10;j++){
			exam_average += grades2[i][j];
		}
		exam_average = exam_average/10;
		//cout << exam << ". Exam Average: " << exam_average << endl;
		exam += 1;
	}
	
	for (int i=0;i<10;i++){
		
		for (int j=0;j<3;j++){
			
			student_average += grades2[j][i];
			
		}
		student_average /= 3;
		//cout << student << ". Student Average: " << student_average << endl;
		student+=1;
	}
	
	cout << grades2[1][1];
	
	return 0;
}
