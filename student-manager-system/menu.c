//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：menu.c
//___________________________________________________________
#include <stdio.h>
#include "menu.h"

void logo(void)
{
	printf("________________________________LOGO____________________________________\n"
		"               ___\n"
		"      _  _  .-'   '-.	 Student Manager Program\n"
		"     (.)(.)/         \\    Author : YangChao\n" 
		"      /@@             ;  \n"
		"     o_\\\\-mm-......-mm`~~~~~~~~~~~~~~~~~~~~~~~~~~~~`\n"
		"________________________________Welcome_________________________________\n\n");
}

void mainMenu(void)
{
	printf("______________________________Mani Menu_________________________________\n"
		"\t1.Record new record.\n"
		"\t2.Display all records.\n"
		"\t3.Search for records.\n"
		"\t4.Help.\n"
		"\t5.About.\n"
		"\t0.Exit.\n"
		"________________________________________________________________________\n\n");
}

void  disMenu(void)
{
	printf("Pos:Main Menu->Display Menu\n");
	printf("_____________________________Display Menu_______________________________\n"
			"\t1.Display current records.\n"
			"\t2.Display records in the order of Name.\n"
			"\t3.Display records in the order of Gender.\n"
			"\t4.Display records in the order of ID.\n"
			"\t5.Display records in the order of Math score.\n"
			"\t6.Display records in the order of English score.\n"
			"\t7.Display records in the order of C score.\n"
			"\t8.Display records in the order of Total score.\n"
			"\t0.Quit.\n"
		"________________________________________________________________________\n\n");
}

void searchMenu(void)
{
	printf("Pos:Main Menu-> Search Menu\n");
	printf("____________________________Search Menu_________________________________\n"
			"\t1.Search by ID.\n"
			"\t2.Search by Name.\n"
			"\t0.Quit.\n"
		"________________________________________________________________________\n\n");
}


void searchMenu_sub(void)
{
	printf("Pos:Main Menu->Search Menu->Sub Search Menu\n");
	printf("____________________________Sub Search Menu_____________________________\n"
				"\t\t1.Modify.\n"
				"\t\t2.Delet.\n"
				"\t\t0.Quit.\n"
		"________________________________________________________________________\n\n");
}

void modifyMenu(void)
{
	printf("Pos:Main Menu->Search Menu->Sub Search Menu->"
			"Modify Menu\n"
		"_____________________________Modify Menu________________________________\n"
				"\t\t1.Modify all information.\n"
				"\t\t2.Modify Nmae.\n"
				"\t\t3.Modify ID.\n"
				"\t\t4.Modify Gender.\n"
				"\t\t5.Modify Math Score.\n"
				"\t\t0.Quit\n"
		"________________________________________________________________________\n\n");
}

void help(void)
{
	printf("Pos:Main Menu->Help\n");
	printf("_______________________________Help_____________________________________\n"
		"Program Structure:\n"
		"1.Record new record.\n"
		"2.Display all records.\n"
			"\t1.Display current records.\n"
			"\t2.Display records in the order of Name.\n"
			"\t3.DIsplay records in the order of Gender.\n"
			"\t4.Display records in the order of ID.\n"
			"\t5.DIsplay records in the order of Math score.\n"
			"\t6.DIsplay records in the order of English score.\n"
			"\t7.DIsplay records in the order of C score.\n"
			"\t8.Display records in the order of Total score.\n"
			"\t0.Quit\n"
		"3.Search for records:\n"
			"\t1.Search by ID.\n"
					"\t\t1.Modify.\n"
					"\t\t2.Delet.\n"
					"\t\t0.Quit.\n"
			"\t2.Search by Name.\n"
					"\t\t1.Modify.\n"
					"\t\t2.Delet.\n"
					"\t\t0.Quit.\n"
			"\t0.Quit.\n"
		"________________________________________________________________________\n\n");
}

void about(void)
{
	logo();
	printf("________________________________About___________________________________\n"
		"Program Name \"Student Manager Program V.1.0\"\n"
		"\tAuthor: YanagChao.WuHan University\n"
		"\tID:2011302530066\n"
		"\tEmail:1668427705@qq.com.\n"
		"_________________________________________________________________________\n");
}

void printHeader(void)
{
	printBoundary();
	printf("||Num||%-10s||%-16s||%-7s||%-4s||%-7s||%-3s||%-5s||\n","  Name","       ID"," Gender","Math","English","C","Total");
}

void printBoundary(void)
{
	printf("_________________________________________________________________________\n");
}
