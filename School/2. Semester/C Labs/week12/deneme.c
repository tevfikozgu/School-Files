#include <stdio.h>
#include <stdlib.h>

typedef struct student_data{
	char name[26];
	char id[5];
	int exams[3];
	int hws[3];
	char grade;
} STUDENT_DATA;

typedef enum bool { //enumaration: 0 1 ..
	FALSE,
	TRUE
} BOOL;


//Function Declarations

BOOL read_from_text_file    (FILE* text_file,   STUDENT_DATA* a_student);
BOOL write_into_binary_file (FILE* binary_file, STUDENT_DATA* a_student);

BOOL read_from_binary_file  (FILE* binary_file,   STUDENT_DATA* a_student);
BOOL write_into_text_file   (FILE* text_file, STUDENT_DATA* a_student);


int main(int argc, char* argv[]){
	
	char* src_text_file_name = argv[1];
	char* dst_text_file_name = argv[2];
	char* binary_file_name   = argv[3];  // binary file uzantisi yine .txt !!!
	
	STUDENT_DATA a_student;

	FILE* binary_file;
	FILE* text_file;

	printf("\nRead from text and Write to binary STARTING\n");
	if(!(text_file = fopen(src_text_file_name, "r"))){
		printf("ERROR OPENING FILE\n");
		return 0;
	}
	if(!(binary_file = fopen(binary_file_name, "wb"))){  // r de dosya yoksa hata verir w de vermez
		printf("ERROR OPENING FILE -2\n");
		return 0;
	}

	while(read_from_text_file(text_file, &a_student)){
		write_into_binary_file(binary_file, &a_student);
	}

	fclose(text_file);
	fclose(binary_file);
	printf("COMPLETED\n");

	printf("\nRead from binary and Write to text STARTING\n");
	if(!(text_file = fopen(dst_text_file_name, "w"))){
		printf("ERROR OPENING FILE -3\n");
		return 0;
	}
	if(!(binary_file = fopen(binary_file_name, "rb"))){
		printf("ERROR OPENING FILE -4\n");
		return 0;
	}

	while(read_from_binary_file(binary_file, &a_student)){
		write_into_text_file(text_file, &a_student);
	}

	fclose(text_file);
	fclose(binary_file);
	printf("COMPLETED\n");
	return 0;
}


BOOL read_from_text_file(FILE* text_file, STUDENT_DATA* a_student){
	char buffer[100];
	int amount_read;

	fgets(buffer, sizeof(buffer), text_file); //stops when reads \n ama \n gormezse 100 byte okuyor

	amount_read = sscanf(buffer, "%s %s %d %d %d %d %d %d %c", // sscanf bufferdan aliyor!!  sscanf ayrimi da bosluklara gore yapiyor!!
		a_student->name, a_student->id,
		&a_student->exams[0], &a_student->exams[1], &a_student->exams[2],
		&a_student->hws[0], &a_student->hws[1], &a_student->hws[2],
		&a_student->grade);

	if(amount_read == 9)
		return TRUE;
	else	
		return FALSE;
}

BOOL write_into_binary_file (FILE* binary_file, STUDENT_DATA* a_student){
	int amount_written;
	amount_written = fwrite(a_student, sizeof(STUDENT_DATA), 1, binary_file);  // fwrite direk verdigin byte kadar yazar ama fprintf sona gelince bitirir avantaji bu!!!   1 kac tane sizeof(STUDENT_DATA) byte'i oldugu

	if(amount_written != 1)
		return FALSE;
	else
		return TRUE;
// BOOL yerine void yapsak daha  mantikli!!

}

BOOL read_from_binary_file  (FILE* binary_file,   STUDENT_DATA* a_student){  
	int amount_read;

	amount_read = fread(a_student, sizeof(STUDENT_DATA), 1, binary_file); // bu da byte byte okuyor!!
	if(amount_read == 1)
		return TRUE;
	else
		return FALSE;
}


BOOL write_into_text_file   (FILE* text_file, STUDENT_DATA* a_student){
	int amount_written;

	amount_written = fprintf(text_file, "%-26s %-5s %3d %3d %3d %3d %3d %3d %c\n", // 
		a_student->name, a_student->id,
		a_student->exams[0], a_student->exams[1], a_student->exams[2],
		a_student->hws[0], a_student->hws[1], a_student->hws[2],
		a_student->grade);

	if(amount_written == 9)
		return TRUE;
	else
		return FALSE;
		
// BOOL yerine void yapsak daha  mantikli!!

}

// fputs \0 gorene kadar okur ama fwrite verdigin boyut kadar okur!!
