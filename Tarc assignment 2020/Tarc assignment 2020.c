#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

//Define variable
#define DATA_FILE_PATH "C:\\Users\\Public\\Documents\\program.txt"

//Global variables declaration
int day, month, year;
int currentDay, currentMonth, currentYear;
bool mainSkip = false;
FILE *fptr;
struct case_record {
	int day;
	int month;
	int year;
	double localCase;
	double importedCase;
	double totalDeath;
	double totalRecovered;
};

//Function declarations
void logo();
void addCase();
void getDate();
void summaryReport();
void reportMake(int day, int month, int year, double localCase, double importedCase, double totalDeath, double totalRecovered);
void getTodayDate();
void dailyReport();
bool checkFileDate(int day, int month, int year);
void fileSort();
void editFileReport(int day, int month, int year, double localCase, double importedCase, double totalDeath, double totalRecovered);
void deleteReport(int day, int month, int year);
void monthlyReport();
bool reportCompare(int day, int month, int year);
void deleteMonthlyReport(int month, int year);

int main()
{
	int option;
	if (mainSkip == false) {
		logo();
		getTodayDate();
		system("cls");
	}
	logo();
	printf("\nToday's date: %d/%d/%d\n\n",currentDay,currentMonth,currentYear);
	printf("Please select one of the options below: \n");
	printf("1) Record cases\n2) Summary report\n3) Change current date\n4) Exit\n\n");
	printf("Options: ");
	rewind(stdin);
	scanf_s("%1d", &option);
	if (option == 1) {
		system("cls");
		addCase();
	}
	else if (option == 2) {
		system("cls");
		summaryReport();
	}
	else if (option == 3) {
		system("cls");
		main();
	}
	else if (option == 4) {
		printf("\n\nThanks for using COVID-19 CASES Tracking System\n");
		system("pause");
		fileSort();
		exit();
	}
	else {
		printf("Please insert only the options available to you\n");
		system("pause");
		system("cls");
		mainSkip = true;
		main();
	}
	system("pause");
}

void logo() {
	// TODO: Logo for the system
	printf("+-----------------------------------------------+\n");
	printf("|   Welcome to COVID-19 CASES Tracking System   |\n");
	printf("+-----------------------------------------------+\n\n");
}

void addCase() {
	double localCase, importedCase, totalDeath, totalRecovered;
	int option;
	char confirmation, useCurrentDate;
	printf("Use current date? (Y/N): ");
	rewind(stdin);
	scanf_s("%c", &useCurrentDate);
	useCurrentDate = toupper(useCurrentDate);
	if (useCurrentDate == 'Y') {
		day = currentDay;
		month = currentMonth;
		year = currentYear;
		if (checkFileDate(day, month, year) == true) {
			printf("The record for this date already exist for this file. Please delete the record or change the date.\n");
			system("pause");
			system("cls");
			addCase();
		}
		system("cls");
	}
	else if (useCurrentDate == 'N') {
		getDate();
		if (checkFileDate(day, month, year) == true) {
			printf("The record for this date already exist for this file. Please delete the record or change the date.\n");
			system("pause");
			system("cls");
			addCase();
		}
	}
	else {
		printf("\nPlease insert a valid option\n");
		system("pause");
		system("cls");
		addCase();
	}

	//Insert details
	insert:
	printf("Report date: %d/%d/%d\n",day, month, year);
	printf("\nKey in today's data:\n");
	printf("\n\tLocal cases: ");
	rewind(stdin);
	scanf_s("%lf",&localCase);
	printf("\n\tImported cases: ");
	rewind(stdin);
	scanf_s("%lf", &importedCase);
	printf("\n\tTotal of deaths: ");
	rewind(stdin);
	scanf_s("%lf", &totalDeath);
	printf("\n\tTotal of recovered: ");
	rewind(stdin);
	scanf_s("%lf", &totalRecovered);
	system("cls");

	//Confirmation report
	confirm:
	printf("----------------------------------------------Report----------------------------------------------\n");
	printf("Date: %d/%d/%d\n", day, month, year);
	printf("+---------------+-----------------++--------------------+-------------------+-------------------+\n");
	printf("|      New cases      |   Total   ||    Total deaths    |  Total recovered  |  Under treatment  |\n");
	printf("|Local     %11.0f|           ||                    |                   |                   |\n", localCase);
	printf("|Imported  %11.0f|           ||                    |                   |                   |\n", importedCase);
	printf("|          %11.0f|%11.0f||%20.0f|%19.0f|%19.0f|\n", localCase + importedCase, localCase + importedCase, totalDeath, totalRecovered, localCase + importedCase - totalDeath - totalRecovered);
	printf("+---------------------+-----------++--------------------+-------------------+-------------------+\n");
	printf("|                     |           ||               %2.1f%%|              %2.1f%%|              %2.1f%%|\n", (totalDeath / (localCase + importedCase))*100, (totalRecovered / (localCase + importedCase))*100, ((localCase + importedCase - totalDeath - totalRecovered) / (localCase + importedCase))*100);
	printf("+---------------------+-----------++--------------------+-------------------+-------------------+\n");

	printf("\nAre the information above correct? (Y/N)");
	rewind(stdin);
	confirmation = toupper(getchar());

	if (confirmation == 'Y') {
		if ((fptr = fopen(DATA_FILE_PATH, "a")) == NULL) {
			perror("\nError reading file.\n");
			system("pause");
		}
		fprintf(fptr,"%d/%d/%d,%.1f,%.1f,%.1f,%.1f\n", day, month, year, localCase, importedCase, totalDeath, totalRecovered);
		fclose(fptr);
		fileSort();
		printf("\nRecord added successfully\n");
		system("pause");
		system("cls");
		mainSkip = true;
		main();
	}
	else if (confirmation == 'N') {
		//Confirmation no
		confirmNo:
		printf("Which detail you would like to edit?\n");
		printf("1) Date\n2) Local cases\n3) Imported cases\n4) Total of deaths\n5) Total of recovered\n6) Reset\n7) Back\n8) Main Menu\n\n");
		printf("Option: ");
		rewind(stdin);
		scanf_s("%1d", &option);
		if (option == 1) {
			getDate();
			goto confirm;
		}
		else if (option == 2) {
			system("cls");
			printf("Old local cases: %.0lf\n", localCase);
			printf("New local cases: ");
			scanf_s("%lf", &localCase);
			system("cls");
			goto confirm;
		}
		else if (option == 3) {
			system("cls");
			printf("Old imported cases: %.0lf\n", importedCase);
			printf("New imported cases: ");
			scanf_s("%lf", &importedCase);
			system("cls");
			goto confirm;
		}
		else if (option == 4) {
			system("cls");
			printf("Old total of deaths: %.0lf\n", totalDeath);
			printf("New total of deaths: ");
			scanf_s("%lf", &totalDeath);
			system("cls");
			goto confirm;
		}
		else if (option == 5) {
			system("cls");
			printf("Old total of recovered: %.0lf\n", totalRecovered);
			printf("New total of recovered: ");
			scanf_s("%lf", &totalRecovered);
			system("cls");
			goto confirm;
		}
		else if (option == 6) {
			system("cls");
			addCase();
		}
		else if (option == 7) {
			system("cls");
			goto confirm;
		}
		else if (option == 8) {
			system("cls");
			mainSkip = true;
			main();
		}
		else {
			printf("\nPlease enter a valid option.\n");
			system("pause");
			system("cls");
			goto confirmNo;
		}
	}
	else {
		printf("\nPlease insert Y for yes or N for no.\n");
		system("pause");
		system("cls");
		goto confirm;
	}
}

void getDate() {
	system("cls");
	printf("Please enter the date(DD/MM/YYYY): ");
	rewind(stdin);
	scanf_s("%2d/%2d/%4d", &day, &month, &year);

	//Check date
	if (day > 0 && day <= 31 && month > 0 && month <= 12) {
		//Do nothing
	}
	else {
		printf("Please insert a valid date.\n");
		system("pause");
		getDate();
	}
	system("cls");
}

void dailyReport() {
	int dayReport[101], monthReport[101], yearReport[101], option, maxOption = 1, editOption;
	double localCaseReport[101], importedCaseReport[101], totalDeathReport[101], totalRecoveredReport[101];
	char char1;
	char str[256];
	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		printf("There is no report until now. Please add a report.\n");
		system("pause");
		system("cls");
		mainSkip = true;
		main();
	}
	printf("Which date of report you would like to see?\n");
	printf("1) All\n");

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);
		
		if (got != 7) break; //wrong number - end of file
	}
	for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
		//Print out the option by date
		if (records[i].day > 31 || records[i].day < 1) break;

		printf("%d) %d/%d/%d\n",i+2, records[i].day, records[i].month, records[i].year);
		maxOption++;
	}
	maxOption++;
	printf("%d) Back", maxOption);

	printf("\nOption: ");
	rewind(stdin);
	scanf_s("%d", &option);
	system("cls");
	if (option == 1) {
		allReport:
		for (int x = 0; x < maxOption-1; x++) {
			reportMake(records[x].day, records[x].month, records[x].year, records[x].localCase, records[x].importedCase, records[x].totalDeath, records[x].totalRecovered);
			printf("\n\n");
		}
		printf("\nOptions:\n");
		printf("1) Back\n2) Main Menu\n");
		printf("Option: ");
		scanf_s("%d",&option);
		if (option == 1) {
			system("cls");
			summaryReport();
		}
		else if (option == 2) {
			system("cls");
			mainSkip = true;
			main();
		}
		else {
			printf("\nPlease insert a valid option.\n");
			system("pause");
			system("cls");
			goto allReport;
		}
	}
	else if (option == maxOption) {
		system("cls");
		mainSkip = true;
		main();
	}
	else if (option < maxOption && option > 0) {
		optionReport:
		reportMake(records[option - 2].day, records[option - 2].month, records[option - 2].year, records[option - 2].localCase, records[option - 2].importedCase, records[option - 2].totalDeath, records[option - 2].totalRecovered);
		printf("\nOptions:\n");
		printf("1) Back\n2) Edit Report\n3) Delete Report\n4) Previous Report\n5) Next Report\n6) Compare Report\n7) Main Menu\n");
		printf("Option: ");
		int tempOption;
		rewind(stdin);
		scanf_s("%d", &tempOption);
		if (tempOption == 1) {
			system("cls");
			summaryReport();
		}
		else if (tempOption == 2) {
			double editLocalCase,editImportedCase,editTotalDeath,editTotalRecovered;

			system("cls");
			reportMake(records[option - 2].day, records[option - 2].month, records[option - 2].year, records[option - 2].localCase, records[option - 2].importedCase, records[option - 2].totalDeath, records[option - 2].totalRecovered);
			printf("\n\nWhich detail you would like to edit?\n");
			printf("1) Local cases\n2) Imported cases\n3) Total of deaths\n4) Total of recovered\n5) Reset\n6) Back\n\n");
			printf("Option: ");
			rewind(stdin);
			scanf_s("%1d", &editOption);
			if (editOption == 1) {
				system("cls");
				printf("Old local cases: %.0lf\n", records[option - 2].localCase);
				printf("New local cases: ");
				rewind(stdin);
				scanf_s("%lf", &editLocalCase);
				system("cls");
				editFileReport(records[option - 2].day, records[option - 2].month, records[option - 2].year, editLocalCase, records[option - 2].importedCase, records[option - 2].totalDeath, records[option - 2].totalRecovered);
				goto optionReport;
			}
			else if (editOption == 2) {
				system("cls");
				printf("Old imported cases: %.0lf\n", records[option - 2].importedCase);
				printf("New imported cases: ");
				rewind(stdin);
				scanf_s("%lf", &editImportedCase);
				system("cls");
				editFileReport(records[option - 2].day, records[option - 2].month, records[option - 2].year, records[option - 2].localCase, editImportedCase, records[option - 2].totalDeath, records[option - 2].totalRecovered);
				goto optionReport;
			}
			else if (editOption == 3) {
				system("cls");
				printf("Old total of deaths: %.0lf\n", records[option - 2].totalDeath);
				printf("New total of deaths: ");
				rewind(stdin);
				scanf_s("%lf", &editTotalDeath);
				system("cls");
				editFileReport(records[option - 2].day, records[option - 2].month, records[option - 2].year, records[option - 2].localCase, records[option -2].importedCase, editTotalDeath, records[option - 2].totalRecovered);
				goto optionReport;
			}
			else if (editOption == 4) {
				system("cls");
				printf("Old total of recovered: %.0lf\n", records[option - 2].totalRecovered);
				printf("New total of recovered: ");
				rewind(stdin);
				scanf_s("%lf", &editTotalRecovered);
				system("cls");
				editFileReport(records[option - 2].day, records[option - 2].month, records[option - 2].year, records[option - 2].localCase, records[option - 2].importedCase, records[option - 2].totalDeath, editTotalRecovered);
				goto optionReport;
			}
			
		}
		else if (tempOption == 3) {
			char confirm;
			deleteReportConfirmation:
			system("cls");
			printf("Are you sure to delete this report? (Y/N): ");
			rewind(stdin);
			scanf_s("%c",&confirm);
			confirm = toupper(confirm);
			if (confirm == 'Y') {
				deleteReport(records[option - 2].day, records[option - 2].month, records[option - 2].year);
			}
			else if (confirm == 'N') {
				goto optionReport;
			}
			else {
				printf("\nPlease insert a valid option.\n");
				system("pause");
				goto deleteReportConfirmation;
			}
		}
		else if (tempOption == 4) {
			option--;
			if (option == 1) {
				option = maxOption - 1;
			}
			system("cls");
			goto optionReport;
		}
		else if (tempOption == 5) {
			option++;
			if (option == maxOption) {
				option = 2;
			}
			system("cls");
			goto optionReport;
		}
		else if (tempOption == 6) {
			if (!reportCompare(records[option - 2].day, records[option - 2].month, records[option - 2].year)) goto optionReport;
		}
		else if (tempOption == 7) {
			system("cls");
			mainSkip = true;
			main();
		}
		else {
			printf("\nPlease insert a valid option.\n");
			system("pause");
			system("cls");
			goto optionReport;
		}
	}
	else {
		printf("\nPlease insert a valid option.\n");
		system("pause");
		system("cls");
		summaryReport();
	}
	fclose(fptr);
}

void reportMake(int day, int month, int year, double localCase, double importedCase, double totalDeath, double totalRecovered) {
	printf("----------------------------------------------Report----------------------------------------------\n");
	printf("Date: %d/%d/%d\n", day, month, year);
	printf("+---------------+-----------------++--------------------+-------------------+-------------------+\n");
	printf("|      New cases      |   Total   ||    Total deaths    |  Total recovered  |  Under treatment  |\n");
	printf("|Local     %11.0f|           ||                    |                   |                   |\n", localCase);
	printf("|Imported  %11.0f|           ||                    |                   |                   |\n", importedCase);
	printf("|                     |%11.0f||%20.0f|%19.0f|%19.0f|\n", localCase + importedCase, totalDeath, totalRecovered, localCase + importedCase - totalDeath - totalRecovered);
	printf("+---------------------+-----------++--------------------+-------------------+-------------------+\n");
	printf("|                     |           ||               %2.1f%%|              %2.1f%%|              %2.1f%%|\n", (totalDeath / (localCase + importedCase)) * 100, (totalRecovered / (localCase + importedCase)) * 100, ((localCase + importedCase - totalDeath - totalRecovered) / (localCase + importedCase)) * 100);
	printf("+---------------------+-----------++--------------------+-------------------+-------------------+\n");
}

void getTodayDate() {
	printf("Please enter today's date(DD/MM/YYYY): ");
	rewind(stdin);
	scanf_s("%2d/%2d/%4d", &currentDay, &currentMonth, &currentYear);

	//Check date
	if (currentDay > 0 && currentDay <= 31 && currentMonth > 0 && currentMonth <= 12) {
		//Do nothing
	}
	else {
		printf("\nPlease insert a valid date.\n");
		system("pause");
		system("cls");
		main();
	}
}

void summaryReport() {
	int option;
	printf("Type of report:\n");
	printf("1) Daily Report\n2) Monthly Report\n3) Back to Main Menu\n\n");
	printf("Option: ");
	scanf_s("%d", &option);
	if (option == 1) {
		system("cls");
		dailyReport();
	}
	else if (option == 2) {
		system("cls");
		monthlyReport();
	}
	else  if (option == 3) {
		system("cls");
		mainSkip = true;
		main();
	}
}

bool checkFileDate(int day, int month, int year) {
	bool dateExist = false;
	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);

		if (records[count].day == day && records[count].month == month && records[count].year == year) {
			dateExist = true;
			break;
		}

		if (got != 7) break; //wrong number - end of file
	}
	fclose(fptr);

	return dateExist;
}

void fileSort() {
	//Extract report data from the file
	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);

		if (got != 7) break; //wrong number - end of file
	}
	fclose(fptr);

	//Rewriting the file
	if ((fptr = fopen(DATA_FILE_PATH, "w")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	//Sorting
	for (int localYear = 1; localYear < 10000; localYear++) {
		for (int localMonth = 1; localMonth < 13; localMonth++) {
			for (int localDay = 1; localDay < 32; localDay++) {
				for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
					if (records[i].day > 31 || records[i].day < 1) break;

					if (records[i].year == localYear && records[i].month == localMonth && records[i].day == localDay) {
						fprintf(fptr, "%d/%d/%d,%.1f,%.1f,%.1f,%.1f\n", records[i].day, records[i].month, records[i].year, records[i].localCase, records[i].importedCase, records[i].totalDeath, records[i].totalRecovered);
					}
				}
			}
		}
	}	

	fclose(fptr);
}

void editFileReport(int day, int month, int year, double localCase, double importedCase, double totalDeath, double totalRecovered) {
	//Extract report data from the file
	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);

		if (got != 7) break; //wrong number - end of file
	}
	fclose(fptr);

	//Rewriting the file
	if ((fptr = fopen(DATA_FILE_PATH, "w")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	//Sorting
	for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
		if (records[i].day > 31 || records[i].day < 1) break;

		if (records[i].year == year && records[i].month == month && records[i].day == day) {
			fprintf(fptr, "%d/%d/%d,%.1f,%.1f,%.1f,%.1f\n", records[i].day, records[i].month, records[i].year, localCase, importedCase, totalDeath, totalRecovered);
		}
		else {
			fprintf(fptr, "%d/%d/%d,%.1f,%.1f,%.1f,%.1f\n", records[i].day, records[i].month, records[i].year, records[i].localCase, records[i].importedCase, records[i].totalDeath, records[i].totalRecovered);
		}
	}

	fclose(fptr);
}

void deleteReport(int day, int month, int year) {
	//Extract report data from the file
	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);

		if (got != 7) break; //wrong number - end of file
	}
	fclose(fptr);

	//Rewriting the file
	if ((fptr = fopen(DATA_FILE_PATH, "w")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	//Sorting
	for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
		if (records[i].day > 31 || records[i].day < 1) break;

		if (records[i].year == year && records[i].month == month && records[i].day == day) {
			
		}
		else {
			fprintf(fptr, "%d/%d/%d,%.1f,%.1f,%.1f,%.1f\n", records[i].day, records[i].month, records[i].year, records[i].localCase, records[i].importedCase, records[i].totalDeath, records[i].totalRecovered);
		}
	}

	fclose(fptr);

	printf("\n\nReport deleted successfully\n");
	system("pause");
	system("cls");
	mainSkip = true;
	main();
}

bool reportCompare(int day,int month, int year) {
	int maxOption = 0, option, firstDate;
	
	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		printf("There is no report until now. Please add a report.\n");
		system("pause");
		system("cls");
		mainSkip = true;
		main();
	}
	printf("\nWhich date of report you would like to compare with?\n");

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);

		if (got != 7) break; //wrong number - end of file
	}
	for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
		//Print out the option by date
		if (records[i].day > 31 || records[i].day < 1) break;

		if (records[i].day == day && records[i].month == month && records[i].year == year) {
			firstDate = i;
		}
		else {
			printf("%d) %d/%d/%d\n", maxOption + 1, records[i].day, records[i].month, records[i].year);
		}
		maxOption++;
	}
	maxOption++;
	printf("%d) Back", maxOption);

	printf("\nOption: ");
	rewind(stdin);
	scanf_s("%d", &option);
	system("cls");
	if (option > 0 && option < maxOption) {
		printf("+------------------------------+-----------------+-----------------+-----------------+\n");
		printf("|                              |                 |                 |    DIFFERENCE   |\n");
		printf("|                              |    %2d/%2d/%2d   |     %2d/%2d/%2d  |                 |\n", day, month, year, records[option - 1].day, records[option - 1].month, records[option - 1].year);
		printf("+------------------------------+-----------------+-----------------+-----------------+\n");
		printf("|Total Cases                   |%17.0lf|%17.0lf|%17.0lf|\n", records[firstDate].localCase + records[firstDate].importedCase, records[option - 1].localCase + records[option - 1].importedCase, (records[option - 1].localCase + records[option - 1].importedCase) - (records[firstDate].localCase + records[firstDate].importedCase));
		printf("|Total Deaths                  |%17.0lf|%17.0lf|%17.0lf|\n", records[firstDate].totalDeath, records[option - 1].totalDeath, records[option - 1].totalDeath - records[firstDate].totalDeath);
		printf("|Total Recovered               |%17.0lf|%17.0lf|%17.0lf|\n", records[firstDate].totalRecovered, records[option - 1].totalRecovered, records[option - 1].totalRecovered - records[firstDate].totalRecovered);
		printf("|Total Under Treatment         |%17.0lf|%17.0lf|%17.0lf|\n", records[firstDate].localCase + records[firstDate].importedCase - records[firstDate].totalDeath - records[firstDate].totalRecovered, records[option - 1].localCase + records[option - 1].importedCase - records[option - 1].totalDeath - records[option - 1].totalRecovered, (records[option - 1].localCase + records[option - 1].importedCase - records[option - 1].totalDeath - records[option - 1].totalRecovered) - (records[firstDate].localCase + records[firstDate].importedCase - records[firstDate].totalDeath - records[firstDate].totalRecovered));
		printf("+------------------------------+-----------------+-----------------+-----------------+\n");
		return true;
	}
	else if (option == maxOption) {
		return false;
	}
	else {
		printf("\nPlease insert a valid option.\n");
		system("pause");
		system("cls");
		reportCompare(day, month, year);
	}
}

void monthlyReport() {
	int option, monthLast=0, yearLast=0, counter=0,monthRecord[1001],yearRecord[1001];

	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		printf("There is no report until now. Please add a report.\n");
		system("pause");
		system("cls");
		mainSkip = true;
		main();
	}
	printf("Which month of report you would like to see?\n");

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);

		if (got != 7) break; //wrong number - end of file
	}
	for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
		//Print out the option by date
		if (records[i].day > 31 || records[i].day < 1) break;

		if (records[i].month == monthLast && records[i].year == yearLast) {
			
		}
		else {
			printf("%d) %d/%d\n", counter + 1, records[i].month, records[i].year);
			monthRecord[counter] = records[i].month;
			yearRecord[counter] = records[i].year;
			monthLast = records[i].month;
			yearLast = records[i].year;
			counter++;
		}
	}
	counter++;
	printf("%d) Back", counter);
	fclose(fptr);

	printf("\nOption: ");
	rewind(stdin);
	scanf_s("%d", &option);
	monthReport:
	system("cls");
	if (option > 0 && option < counter) {
		bool startDayFound = false;
		double localCaseTotal = 0, importedCaseTotal = 0, totalDeathTotal = 0, totalRecoveredTotal = 0;
		int startDay, endDay;

		for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
			if (records[i].month == monthRecord[option - 1] && records[i].year == yearRecord[option - 1]) {
				if (startDayFound == false) {
					startDay = records[i].day;
					startDayFound = true;
				}
				localCaseTotal += records[i].localCase;
				importedCaseTotal += records[i].importedCase;
				totalDeathTotal += records[i].totalDeath;
				totalRecoveredTotal += records[i].totalRecovered;
				endDay = records[i].day;
			}
		}
		printf("Monthly Report\n");
		printf("---------------\n\n");
		printf("Date: %d/%d\n", monthRecord[option - 1], yearRecord[option - 1]);
		printf("+---------------------+-----------++--------------------+-------------------+-------------------+\n");
		printf("|      New cases      |   Total   ||    Total deaths    |  Total recovered  |  Under treatment  |\n");
		printf("|Local     %11.0f|           ||                    |                   |                   |\n", localCaseTotal);
		printf("|Imported  %11.0f|           ||                    |                   |                   |\n", importedCaseTotal);
		printf("|                     |%11.0f||%20.0f|%19.0f|%19.0f|\n", localCaseTotal + importedCaseTotal, totalDeathTotal, totalRecoveredTotal, localCaseTotal + importedCaseTotal - totalDeathTotal - totalRecoveredTotal);
		printf("+---------------------+-----------++--------------------+-------------------+-------------------+\n");
		printf("|                     |           ||               %2.1f%%|              %2.1f%%|              %2.1f%%|\n", (totalDeathTotal / (localCaseTotal + importedCaseTotal)) * 100, (totalRecoveredTotal / (localCaseTotal + importedCaseTotal)) * 100, ((localCaseTotal + importedCaseTotal - totalDeathTotal - totalRecoveredTotal) / (localCaseTotal + importedCaseTotal)) * 100);
		printf("+---------------------+-----------++--------------------+-------------------+-------------------+\n");
		printf("\nOptions:\n");
		printf("1) Back\n2) Delete Monthly Report\n3) Previous Report\n4) Next Report\n5) Main Menu\n");
		printf("Option: ");
		int tempOption;
		rewind(stdin);
		scanf_s("%d", &tempOption);
		if (tempOption == 1) {
			system("cls");
			monthlyReport();
		}
		else if (tempOption == 2) {
			// TODO: Delete monthly report
			deleteMonthlyReport(monthRecord[option - 1], yearRecord[option - 1]);
		}
		else if (tempOption == 3) {
			option--;
			if (option == 0) {
				option = counter - 1;
			}
			goto monthReport;
		}
		else if (tempOption == 4) {
			option++;
			if (option == counter) {
				option = 1;
			}
			goto monthReport;
		}
		else if (tempOption == 5) {
			system("cls");
			mainSkip = true;
			main();
		}
	}
	else if (option == counter) {
		system("cls");
		summaryReport();
	}
	else {
		printf("\nPlease insert a valid option.\n");
		system("pause");
		system("cls");
		monthlyReport();
	}
}

void deleteMonthlyReport(int month, int year) {
	//Extract report data from the file
	if ((fptr = fopen(DATA_FILE_PATH, "r")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	struct case_record records[101];
	size_t count = 0;

	for (; count < sizeof(records) / sizeof(records[0]); count++) {
		//Read the file line by line
		int got = fscanf(fptr, "%d/%d/%d,%lf,%lf,%lf,%lf", &records[count].day, &records[count].month, &records[count].year, &records[count].localCase, &records[count].importedCase, &records[count].totalDeath, &records[count].totalRecovered);

		if (got != 7) break; //wrong number - end of file
	}
	fclose(fptr);

	//Rewriting the file
	if ((fptr = fopen(DATA_FILE_PATH, "w")) == NULL) {
		perror("\nError reading file.\n");
		system("pause");
		mainSkip = true;
		main();
	}

	//Sorting
	for (int i = 0; i < sizeof(records) / sizeof(records[0]); i++) {
		if (records[i].day > 31 || records[i].day < 1) break;

		if (records[i].year == year && records[i].month == month) {

		}
		else {
			fprintf(fptr, "%d/%d/%d,%.1f,%.1f,%.1f,%.1f\n", records[i].day, records[i].month, records[i].year, records[i].localCase, records[i].importedCase, records[i].totalDeath, records[i].totalRecovered);
		}
	}

	fclose(fptr);

	printf("\n\nMonthly Report deleted successfully\n");
	system("pause");
	system("cls");
	mainSkip = true;
	main();
}