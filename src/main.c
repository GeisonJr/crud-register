/****************************************************************************
*
* 201910467 - Geison Rodrigo Oriani Junior;
*
* CRUD Register
* This Project is Able to Create, Read, Update, Delete.
*
****************************************************************************/

/*-------------------- Includes --------------------*/
//#include <locale.h> // Don't Use if Your Language is not English
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

/*--------------------- Define ---------------------*/
#define corner_bottom_right 217 //217="┘", 188="╝"
#define corner_bottom_left 192 // 192="└", 200="╚"

#define corner_top_right 191 // 191="┐", 187="╗"
#define corner_top_left 218 // 218="┌", 201="╔"

#define horizontal_bottom 193 // 193="┴", 202="╩"
#define horizontal_top 194 // 194="┬", 203="╦"

#define vertical_rigth 180 // 180="┤", 185="╣"
#define vertical_left 195 // 180="├", 204="╠"

#define horizontal 196 // 196="─", 205="═"
#define vertical 179 // 179="│", 186="║"

#define cross 197 // 197="┼", 206="╬"
#define space 32 // 32="Space - SPC"

#define default_counter 2 // Don't Change Than 2! - Controls the Amount of Text that will be the Basis of the Layout
#define default_value 0 // Dont Change Than 0! - Controls the ID and the Value in Creation of Files

#define string_length 1024 // Number of Characters the variable "char strings[...][string_length]" contains and Maximum Number of Characters Read in One Line;
#define string_amount 34 // Amount of Phrase That Variable "char strings[string_amount][...]" Contains;

#define excluded_length 2 // Don't Change Than 2! - This is a number of Characters Read/Print in List() and Seach()

#define heigth 9 // Don't Change Than 9! - This is a number of Lines Read/Print in List()
#define none -10 // Don't Set none>=0! - This is a Void Parameter

/*-------------------- Function --------------------*/
void _print(int req, int start, int end);
void _layer(int req, int start, int end);
void _pause(int req, int start, int end);

void _verification(int req, int sub);
void _fprint(int req, int sub);
void _fopen(int req, int sub);

void _id_controler(int req);
void _counter(int req);
void _fclose(int req);
void _title(int req);

void _include(void);
void _exclude(void);
void _change(void);
void _choice(void);
void _reboot(void);
void _search(void);
void _clear(void);
void _list(void);

/*---------------------- File ----------------------*/
FILE *file_client;
FILE *file_log;

/*--------------------- Global ---------------------*/
char strings[string_amount][string_length]={
    "      Customer Registration Management      ", // Message 0
    "        Powered by HansoMWarE Corp.        ", // Message 1

    " 1 - Include", // Message 2
    " 2 - Exclude", // Message 3
    " 3 - Change" , // Message 4
    " 4 - Search", // Message 5
    " 5 - List", // Message 6
    " 6 - Exit", // Message 7

    " Date...:", // Message 8
    " Time...:", // Message 9

    " Error 406: Pressed Key is not a Valid Option", // Message 10
    " Press any Key to Continue...", // Message 11

    " Error 404: File Not Found!", // Message 12
    " Press any Key for the Application to Recreate the Local Files and Reboot!", // Message 13

    "   Full Name: ", // Message 14
    "   CPF: ", // Message 15
    "   RG: ", // Message 16
    "   Telephone: ", // Message 17
    "   Birth Date: ", // Message 18
    "   Sex: ", // Message 19
    "   Address: ", // Message 20
    " ID: ", // Message 21

    " Search by ID Registers", // Message 22
    " Error 404: The ID (", // Message 23
    ") Was not Found!", // Message 24

    " List All Registers", // Message 25
    " Error 404: Sorry, But You Have no Registers!", // Message 26

    " Change Registers by ID", //Message 27
    " Error 404: The ID (", // Message 28
    ") Was not Found!", // Message 29

    " Exclude Registers by ID", // Message 30

    "Error 404: Sorry, But This ID Doesn't exist", // Message 31

    " Include Registers", // Message 32

    " Operation Completed Successfully" // Message 33
};

char character[string_length];

char import_registers_1[string_length][string_length]; // Import data of client.txt earli line request
char import_registers_2[string_length][string_length]; // Import data of client.txt later line+heigth request

int counter_length[string_amount]; // Controls String Width

int counter_interface; // Controls Interface Width
int counter_function; // Controls List()/Search()

int marker_input; // Controls Change() Reading/Printing
int marker_line; // Controls the Number Lines Reading in List()/Search()/Change()

int id_response; // Control ID Number Saved in Log.txt
int id_counter; // Counts the Amount of Characters in ID
int id_request; // Control ID Number Used by User

int choice;

int reboot=0;

/*--------------------- Struct ---------------------*/
struct cadastro{
    char nascimento[string_length]; // 8
    char endereco[string_length]; // 250
    char nome[string_length]; // 250
    char sexo[string_length]; // 1
    char cpf[string_length]; // 11
    char tel[string_length]; // 10
    char rg[string_length]; // 9
};
struct cadastro client;

/*---------------------- Main ----------------------*/
void main(void) {
    // setlocale(LC_ALL, NULL); // Don't Use if Your Language is not English
    _choice();
    main();
}

/*--------------------- Choice ---------------------*/
void _choice(void) {
    choice=0;
    do {
        _verification(0, none);
        _counter(0);
        _title(0);
        _clear();

        /*---------------------- Informations Date/Time ----------------------*/
        struct tm *data_hora_atual;
        time_t segundos;
        time(&segundos);
        data_hora_atual=localtime(&segundos);

        /*--- Print 1 - Width Message 0/1---*/
        _print(1, 0, 1); // ┌─...─┬─...─┐

        /*--- Print 2 - Message 0/1 ---*/
        printf("\n");
        _print(2, 0, 1); // │ ... │ ... │

        /*--- Print 3 - Width Message 0/1 ---*/
        printf("\n");
        _print(3, 0, 1); // ├─...─┴─...─┤

        /*--- Print 5 - Message 2/7 ---*/
        _print(5, 2, 7); // │    ...    │

        /*--- Print 7 ---*/
        printf("\n");
        _print(7, none, none); // ├────...────┤

        /*--- Print Custom - Message 8 + Hour ---*/
        printf("\n");
        printf("%c", vertical);
        if((data_hora_atual->tm_hour)<=9 && (data_hora_atual->tm_min)<=9 ) {
            printf("%s 0%d:0%d", strings[8], data_hora_atual->tm_hour, data_hora_atual->tm_min);
        } else if((data_hora_atual->tm_hour)<=9 ) {
            printf("%s 0%d:%d", strings[8], data_hora_atual->tm_hour, data_hora_atual->tm_min);
        } else if((data_hora_atual->tm_min)<=9 ) {
            printf("%s %d:0%d", strings[8], data_hora_atual->tm_hour, data_hora_atual->tm_min);
        } else {
            printf("%s %d:%d", strings[8], data_hora_atual->tm_hour, data_hora_atual->tm_min);
        }
        for(int i=0; i<=(counter_interface-counter_length[7]-6); i++) {
            printf("%c", space);
        }
        printf("%c", vertical);

        /*--- Print Custom - Message 9 + Date ---*/
        printf("\n");
        printf("%c", vertical);
        if((data_hora_atual->tm_mday<=9) && (data_hora_atual->tm_mon<9)) {
            printf("%s 0%d/0%d/%d", strings[9], data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900);
        } else if(data_hora_atual->tm_mday<=9) {
            printf("%s 0%d/%d/%d", strings[9], data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900);
        } else if(data_hora_atual->tm_mon<9) {
            printf("%s %d/0%d/%d", strings[9], data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900);
        } else {
            printf("%s %d/%d/%d", strings[9], data_hora_atual->tm_mday, data_hora_atual->tm_mon+1, data_hora_atual->tm_year+1900);
        }
        for(int i=0; i<=(counter_interface-counter_length[8]-11); i++) {
            printf("%c", space);
        }
        printf("%c", vertical);

        /*--- Print 8 ---*/
        printf("\n");
        _print(8, none, none); // └────...────┘

        /*--- Input 1 - Choice ---*/
        choice=getch();

        if(choice==49) { // Include Function
            _verification(0, none);
            _clear();
            _title(1);
            _include();
            _pause(1, 11, 11);
            break;
        } else if(choice==50) { // Exclude Function
            _verification(0, none);
            _clear();
            _title(2);
            _exclude();
            _pause(1, 11, 11);
            break;
        } else if(choice==51) { // Change Function
            _verification(0, none);
            _clear();
            _change();
            _title(3);
            _pause(1, 11, 11);
            break;
        } else if(choice==52) { // Search Function
            _verification(0, none);
            _clear();
            _title(4);
            _search();
            _pause(1, 11, 11);
            break;
        } else if(choice==53) { // List Function
            _verification(0, none);
            _clear();
            _title(5);
            _list();
            _pause(1, 11, 11);
            break;
        } else if(choice==54) { // Exit
            _verification(0, none);
            exit(0);
            break;
        } else {
            _pause(1, 10, 11);
        }
    } while(choice<49 && choice>54);
}

/*-------------------- includes --------------------*/
void _include(void) {

    /*--- layer 2 - Message 32 ---*/
    _layer(0, 32, 32);

    /*--- ID Controller 1 ---*/
    _id_controler(0); // Import ID and Increment Local

    /*--- Print Custom - Message 14/21 ---*/
    printf("\n");
    printf("\n");
    printf("%s%d {\n", strings[21], id_response);
    for(int i=14; i<=20; i++) {

        /*--- Print 1 - Message 14/20 ---*/
        printf(" %s", strings[i]);

        /*--- Input 1 - Struct client... ---*/
        if(i==14) {
            fflush(stdin);
            gets(client.nome);
        } else if(i==15) {
            gets(client.cpf);
        } else if(i==16) {
            gets(client.rg);
        } else if(i==17) {
            gets(client.tel);
        } else if(i==18) {
            gets(client.nascimento);
        } else if(i==19) {
            gets(client.sexo);
        } else if(i==20) {
            gets(client.endereco);
        }
    }
    printf(" }", strings[21]);
    printf("\n");

    /*--- ID Controller 2 ---*/
    _id_controler(1); // Export ID incremented

    /*------ Exports New Registers ------*/
    if(id_response==1) {
        _fclose(0); // fclose file_client -> client.txt
        _fopen(0, 0); // Write Mode file_client -> client.txt
    } else {
        _fclose(0); // fclose file_client -> client.txt
        _fopen(0, 1); // Append Mode file_client -> client.txt
    }
    _fprint(0, 0); // Write New Registers in file_client -> client.txt
    _fclose(0); // fclose file_client -> client.txt

    /*--- Layer 0 - Message 33 ---*/
    printf("\n");
    _layer(0, 33, 33);
}

/*--------------------- Search ---------------------*/
void _search(void) {

    /*--- Layer 0 - Message 22 ---*/
    _layer(1, 22, 22);

    /*--- Input ---*/
    _id_controler(2); // Import ID

    /*--- Search Result ---*/
    marker_line=0;
    id_request--;

    if(id_request>(id_response) && id_request<1) {

        id_request++;
        /*--- Print 6 - Message 29 ---*/
        _print(6, 28, 29); // ...   ...   │
    } else {
        _fopen(0, 2); // Read Mode file_client -> client.txt
        while (fgets(character, string_length, file_client)) {
            _counter(1);
            if(marker_line>=id_request*9 && marker_line<=((id_request*heigth)+(heigth-1))) {
                if(counter_function>=excluded_length) {
                    if((marker_line%heigth)==0) {

                        /*--- Print 4 ---*/
                        _print(4, none, none); // ┌────...────┐
                        printf("\n");
                    }

                    /*--- Print Custom - Message Custom ---*/
                    printf("%c", vertical);
                    printf("%s", character);

                    if((marker_line%heigth)==(heigth-1)) {

                        /*--- Print 8 ---*/
                        _print(8, none, none); // └────...────┘
                    }
                } else {
                    id_request++;

                    /*--- Print 6 - Message 28/29 ---*/
                    _print(6, 28, 29); // ...   ...   │
                    break;
                }
            }
            marker_line++;
        }
        _fclose(0); // fclose file_client -> client.txt

        /*--- Layer 0 - Message 33 ---*/
        printf("\n");
        _layer(0, 33, 33);
    }
}

/*---------------------- List ----------------------*/
void _list(void) {

    /*--- Layer 0 - Message 25 ---*/
    _layer(0, 25, 25);

    /*--- List Result ---*/
    marker_line=0;

    _fopen(0, 2); // Read Mode file_client -> client.txt
    while (fgets(character, string_length, file_client)) {
        _counter(1);
        if(counter_function>=excluded_length) {
            if((marker_line%heigth)==0) {

                /*--- Print 4 ---*/
                printf("\n");
                _print(4, none, none); // ┌────...────┐
                printf("\n");
            }

            /*--- Print Custom - Message Custom ---*/
            printf("%c", vertical);
            printf("%s", character);

            if((marker_line%heigth)==(heigth-1)) {

                /*--- Print 8 ---*/
                _print(8, none, none); // └────...────┘
            }
        }
        marker_line++;
    }
    _fclose(0); // fclose file_client -> client.txt

    /*--- Layer 0 - Message 33 ---*/
    printf("\n");
    _layer(0, 33, 33);
}

/*-------------------- Excludes --------------------*/
void _exclude(void){

    /*--- Layer 0 - Message 30---*/
    _layer(1, 30, 30);

    /*--- ID Controller 1 ---*/
    _id_controler(2); // Import ID

    if(id_request<=id_response && id_request>=1) {

        /*------ Clears the Import Vectors of Registers ------*/
        for(int i=0; i<string_length; i++) {
            import_registers_1[i][string_length]='\0'; // Resets the Variable - import_registers_1[string_length][string_length]
            import_registers_2[i][string_length]='\0'; // Resets the Variable - import_registers_2[string_length][string_length]
        }

        /*------ Import the Registers Before the Required ID  ------*/
        marker_line=0;
        _fopen(0, 2); // Read Mode file_client -> client.txt
        while (fgets(import_registers_1[marker_line], string_length, file_client)) {
            if(marker_line<((id_request*heigth)-heigth)) {
                marker_line++;
            }
        }
        _fclose(0); // fclose file_client -> client.txt

        /*------ Import the Registers After the Required ID  ------*/
        marker_line=0;
        marker_input=0;
        _fopen(0, 2); // Read Mode file_client -> client.txt
        while (fgets(import_registers_2[marker_input], string_length, file_client)) {
            if(marker_line>=(id_request*heigth)) {
                marker_line++;
                marker_input++;
            } else {
                marker_line++;
            }
        }
        _fclose(0); // fclose file_client -> client.txt

        /*------ Exports Changed Registers ------*/
        _fopen(0, 0); // Write Mode file_client -> client.txt
        for(int i=0; import_registers_1[i][string_length]!='\0'; i++) {
            fprintf(file_client, "%s", import_registers_1[i]);
        }
        _fprint(1, none); // Write Excluded Registers in file_client -> client.txt
        for(int i=0; import_registers_2[i][string_length]!='\0'; i++) {
            fprintf(file_client, "%s", import_registers_2[i]);
        }
        _fclose(0); // fclose file_client -> client.txt

        /*--- Layer 0 - Message 33 ---*/
        _layer(0, 33, 33);
    } else {

        /*--- Print 6 - Print 25---*/
        _print(6, 28, 29);
    }
}

/*--------------------- Change ---------------------*/
void _change(void) {

    /*--- Layer 0 - Message 27 ---*/
    _layer(1, 27, 27);

    /*--- ID Controller 1 ---*/
    _id_controler(2); // Import ID

    /*--- Change Result ---*/
    if(id_request<=id_response && id_request>=1) {

        /*------ Clears the Import Vectors of Registers ------*/
        for(int i=0; i<string_length; i++) {
            import_registers_1[i][string_length]='\0'; // Resets the Variable - import_registers_1[string_length][string_length]
            import_registers_2[i][string_length]='\0'; // Resets the Variable - import_registers_2[string_length][string_length]
        }

        /*------ Import the Registers Before the Required ID  ------*/
        marker_line=0;
        _fopen(0, 2); // Read Mode file_client -> client.txt
        while (fgets(import_registers_1[marker_line], string_length, file_client)) {
            if(marker_line<((id_request*heigth)-heigth)) {
                marker_line++;
            }
        }
        _fclose(0); // fclose file_client -> client.txt

        /*------ Import the Registers After the Required ID  ------*/
        marker_line=0;
        marker_input=0;
        _fopen(0, 2); // Read Mode file_client -> client.txt
        while (fgets(import_registers_2[marker_input], string_length, file_client)) {

            if(marker_line>=(id_request*heigth)) {
                marker_line++;
                marker_input++;
            } else {
                marker_line++;
            }
        }
        _fclose(0); // fclose file_client -> client.txt

        /*------ Exports Changed Registers ------*/
        _fopen(0, 0); // Write Mode file_client -> client.txt
        for(int i=0; import_registers_1[i][string_length]!='\0'; i++) {
            fprintf(file_client, "%s", import_registers_1[i]);
        }
        printf("\n");
        printf("%s%d {\n", strings[21], id_request);
        for(int i=14; i<=20; i++) {
            /*--- Print 1 - Message 14/20 ---*/
            printf(" %s", strings[i]);

            /*--- Input 1 - Struct client... ---*/
            if(i==14) {
                fflush(stdin);
                gets(client.nome);
            } else if(i==15) {
                gets(client.cpf);
            } else if(i==16) {
                gets(client.rg);
            } else if(i==17) {
                gets(client.tel);
            } else if(i==18) {
                gets(client.nascimento);
            } else if(i==19) {
                gets(client.sexo);
            } else if(i==20) {
                gets(client.endereco);
            }
        }
        printf(" }");
        printf("\n");
        _fprint(0, 1); // Write Changed Registers in file_client -> client.txt
        for(int i=0; import_registers_2[i][string_length]!='\0'; i++) {
            fprintf(file_client, "%s", import_registers_2[i]);
        }
        _fclose(0); // fclose file_client -> client.txt

        /*--- Layer 0 - Message 33 ---*/
        printf("\n");
        _layer(0, 33, 33);
    } else {

        /*--- Print 6 - Message 28/29 ---*/
        _print(6, 28, 29);
    }
}

/*---------------------- Fopen ---------------------*/
void _fopen(int req, int sub) {
    if(req==0) {
        if(sub==0) { // Write Mode file_client -> client.txt
            file_client=fopen("../files/client.txt", "w");
        } else if(sub==1) { // Append Mode file_client -> client.txt
            file_client=fopen("../files/client.txt", "a");
        } else if(sub==2) { // Read Mode file_client -> client.txt
            file_client=fopen("../files/client.txt", "r");
        }
    }
    if(req==1) {
        if(sub==0) { // Write Mode file_log -> log.txt
            file_log=fopen("../files/log.txt", "w");
        } else if(sub==1) { // Append Mode file_log -> log.txt
            file_log=fopen("../files/log.txt", "a");
        } else if(sub==2) { // Read Mode file_log -> log.txt
            file_log=fopen("../files/log.txt", "r");
        }
    }
}

/*--------------------- Fclose ---------------------*/
void _fclose(int req) {
    if(req==0) { // fclose file_client -> client.txt
        fclose(file_client);
    } else if(req==1) { // fclose file_log -> log.txt
        fclose(file_log);
    }
}

/*-------------------- Counters --------------------*/
void _counter(int req) {
    if(req==0) { // Count the Amount of Characters in the Interface
        for(int i=0; i<string_length; i++) {
            counter_length[i]=0;
            for(int x=0; strings[i][x]!='\0'; x++) {
                counter_length[i]++;
            }
        }
        counter_interface=0;
        for(int i=0; i<default_counter; i++) {
            counter_interface+=counter_length[i];
        }
    } else if(req==1) {
        counter_function=0;
        for(int i=0; character[i]!='\0'; i++) {
            counter_function++;
        }
    } else if(req==2) { // Counts the Amount of Characters in ID
        id_counter=id_request;
        counter_function=0;
        for ( counter_function=0; id_counter!=0; counter_function++){
            id_counter=id_counter/10;
        }
    }
}

/*--------------------- Titles ---------------------*/
void _title(int req) {
    if(req==0) {
        system("title Cadastro de clients");
    } else if(req==1) {
        system("title Include Mode");
    } else if(req==2) {
        system("title Exclude Mode");
    } else if(req==3) {
        system("title Change Mode");
    } else if(req==4) {
        system("title Search Mode");
    } else if(req==5) {
        system("title List Mode");
    }
}

/*---------------------- Pause ---------------------*/
void _pause(int req, int start, int end) {
    if(req==0) {
        /*--- System Command ---*/
        system("pause>null");
    } else if(req==1) {
        /*--- Print 4 ---*/
        printf("\n");
        _print(4, none, none);

        /*--- Print 5 - Message Custom---*/
        _print(5, start, end);

        /*--- Print 8 ---*/
        printf("\n");
        _print(8, none, none);

        /*--- Recursion ---*/
        _pause(0, none, none);
    }
}

/*---------------------- Clear ---------------------*/
void _clear(void) {
    /*--- System Command ---*/
    system("cls");
}

/*--------------------- Reboot ---------------------*/
void _reboot(void) {
    /*--- System Command ---*/
    system("start reboot.exe");
    /*--- Exit - Status 0 ---*/
    exit(0);
}

/*------------------ Verification ------------------*/
void _verification(int req, int sub) {
    _counter(0);
    if(req==0) {
        for(int i=0; i<2; i++) {
            _fopen(i, 2); // Read Mode file_client/file_log -> client.txt/log.txt
            if(i==0) {
                if(file_client==NULL) {
                    _verification(1, i);
                }
            } else if(i==1) {
                if(file_log==NULL){
                    _verification(1, i);
                }
            }
            _fclose(i); // fclose file_client/file_log -> client.txt/log.txt
        }
        if(reboot==1) {
            _reboot();
        }
    } else if(req==1) {
        /*--- Print 1 - Message 12/13 - pause ---*/
        _pause(1, 12, 13);

        _fclose(sub); // fclose file_client/file_log -> client.txt/log.txt
        _fopen(sub, 0); // Write Mode file_client/file_log -> client.txt/log.txt
        if(sub==0) {
            fprintf(file_client, "%i", default_value);
        } else if(sub==1) {
            fprintf(file_log, "%i", default_value);
        }
        _fclose(sub); // fclose file_client/file_log -> client.txt/log.txt
        reboot=1;
    }
}

/*--------------------- Prints ---------------------*/
void _print(int req, int start, int end) {
    if(req==1) { // ┌─...─┬─...─┐

        printf("%c", corner_top_left);
        for(int i=start; i<=end; i++) {
            for(int x=0; x<counter_length[i]; x++) {
                printf("%c", horizontal);
            }
            if(i==start) {
                printf("%c", horizontal_top);
            }
        }
        printf("%c", corner_top_right);
    } else if(req==2) { // │ ... │ ... │

        for(int i=start; i<=end; i++) {
            if(i==start) {
                printf("%c", vertical);
            }
            printf("%s", strings[i]);
            if(i==start) {
                printf("%c", vertical);
            }
            if(i==end) {
                printf("%c", vertical);
            }
        }
    } else if(req==3) { // ├─...─┴─...─┤

        printf("%c", vertical_left);
        for(int i=start; i<=end; i++) {
            for(int x=0; x<counter_length[i]; x++) {
                printf("%c", horizontal);
            }
            if(i==start) {
                printf("%c", horizontal_bottom);
            }
        }
        printf("%c", vertical_rigth);
    } else if(req==4) { // ┌────...────┐

        printf("%c", corner_top_left);
        for(int i=0; i<=counter_interface; i++) {
            printf("%c", horizontal);
        }
        printf("%c", corner_top_right);
    } else if(req==5) { // │    ...    │

        for(int i=start; i<=end; i++) {
            printf("\n");
            printf("%c", vertical);
            printf("%s", strings[i]);
            for(int x=0; x<=(counter_interface-counter_length[i]); x++) {
                printf("%c", space);
            }
            printf("%c", vertical);
        }
    } else if(req==6) { // ...   ...   │

        /*--- Print 4 ---*/
        _print(4, none, none);

        /*--- Print 2 - Message start/end ---*/
        printf("\n");
        printf("%c", vertical);
        printf("%s%d%s", strings[start], id_request, strings[end]);

        /*--- Print 3 - Message start/end ---*/
        _counter(2);
        for(int i=0; i<=(counter_interface-counter_length[start]-counter_function-counter_length[end]); i++) {
            printf("%c", space);
        }
        printf("%c", vertical);

        /*--- Print 8 ---*/
        printf("\n");
        _print(8, none, none);
    } else if(req==7) { // ├────...────┤

        printf("%c", vertical_left);
        for(int i=0; i<=counter_interface; i++) {
            printf("%c", horizontal);
        }
        printf("%c", vertical_rigth);
    } else if(req==8) { // └────...────┘

        printf("%c", corner_bottom_left);
        for(int i=0; i<=counter_interface; i++) {
            printf("%c", horizontal);
        }
        printf("%c", corner_bottom_right);
    }
}

/*--------------------- Layers ---------------------*/
void _layer(int req, int start, int end) {
    if(req==0) {
        /*--- Print 4 ---*/
        _print(4, none, none); // ┌────...────┐

        /*--- Print 5 - Message Custom ---*/
        _print(5, start, end); // │    ...    │

        /*--- Layer 8 ---*/
        printf("\n");
        _print(8, none, none); // └────...────┘
    } else if(req==1) {
        /*--- Print 4 ---*/
        _print(4, none, none); // ┌────...────┐

        /*--- Print 5 - Message Custom ---*/
        _print(5, start, end); // │    ...    │

        /*--- Print 8 ---*/
        printf("\n");
        _print(8, none, none); // └────...────┘
        printf("\n");

        /*--- Layer Custom ---*/
        printf("\n");
        printf("%s", strings[21]);

        /*--- Input Custom ---*/
        scanf("%d", &id_request);
        printf("\n");
    }
}

/*--------------------- Fprint ---------------------*/
void _fprint(int req, int sub) {
    if(req==0) {
        if(sub==0) { // Write New Registers in file_client -> client.txt
            fprintf(file_client, "%s%d {\n", strings[21], id_response);
        }
        if(sub==1) { // Write Changed Registers in file_client -> client.txt
            fprintf(file_client, "%s%d {\n", strings[21], id_request);
        }
        fprintf(file_client, "%s%s,\n", strings[14], client.nome);
        fprintf(file_client, "%s%s,\n", strings[15], client.cpf);
        fprintf(file_client, "%s%s,\n", strings[16], client.rg);
        fprintf(file_client, "%s%s,\n", strings[17], client.tel);
        fprintf(file_client, "%s%s,\n", strings[18], client.nascimento);
        fprintf(file_client, "%s%s,\n", strings[19], client.sexo);
        fprintf(file_client, "%s%s\n", strings[20], client.endereco);
        fprintf(file_client, " }\n");
        if(sub==1) {
            for(int i=0; import_registers_2[i][string_length]!='\0'; i++) {
                fprintf(file_client, "%s", import_registers_2[i]);
            }
        }
    }
    if(req==1) { // Write Excluded Registers in file_client -> client.txt
        for(int i=0; i<heigth; i++) {
            fprintf(file_client, "\n");
        }
    }
}

/*----------------- ID Controller ------------------*/
void _id_controler(int req) {
    if(req==0) { // Import ID and Increment Local
        _fopen(1, 2); // Read Mode file_log -> log.txt
        fscanf(file_log, "%d", &id_response);
        id_response++;
        _fclose(1); // fclose file_log -> log.txt
    } else if(req==1) { // Export ID
        _fopen(1, 0); // Write Mode file_log -> log.txt
        fprintf(file_log, "%i", id_response);
        _fclose(1); // fclose file_log -> log.txt
    } else if(req==2) { // Import ID
        _fopen(1, 2); // Write Mode file_log -> log.txt
        fscanf(file_log, "%d", &id_response);
        _fclose(1); // fclose file_log -> log.txt
    }
}
