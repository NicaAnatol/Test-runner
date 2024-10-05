#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstring>
#include <vector>
// #include "data/classes/Test.h"
#include "data/classes/Test.cpp"
#include "data/classes/Intrebare.cpp"
#include <filesystem>
#include <algorithm>
#include <cmath>

namespace fs = std::filesystem;
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

//Make a string coloured 
string setColour(string str, string colour){
    if(colour == "red"){
        str = "\033[0;31m"+str+"\033[0m";
    } else
    if(colour == "green"){
        str = "\033[0;32m"+str+"\033[0m";
    } else
    if(colour == "yellow"){
        str = "\033[0;33m"+str+"\033[0m";
    } else
    if(colour == "blue"){
        str = "\033[0;34m"+str+"\033[0m";
    } else
    if(colour == "purple"){
        str = "\033[0;35m"+str+"\033[0m";
    } else
    if(colour == "cyan"){
        str = "\033[0;36m"+str+"\033[0m";
    } else
    if(colour == "white"){
        str = "\033[0;37m"+str+"\033[0m";
    } else
    if(colour == "black"){
        str = "\033[0;30m"+str+"\033[0m";
    }
    return str;

}

//Display an interactive Page that returns the selection
int front_hilight;
string InteractivePage(string title, const string menu[], int list_size, bool back_button = false){
    int selection = front_hilight;
    auto showPage = [&](){
        system("cls");
        cout << setColour("---=="+title+"==---\n", "cyan");
        for(int i=0; i<list_size; i++){
            if(selection == i) cout << setColour(">>"+menu[i], "red") << endl;
            else cout << menu[i] << endl;
        }
        if(back_button){
            cout << endl;
            if(selection == list_size) cout << setColour("<--[Back]", "red") << endl;
            else cout << "[Back]" << endl;
        }

        cout << "\n\n";
    };

    showPage(); int ch;
    while ((ch = getch()) != ENTER) {
        if (ch == 0 || ch == 224)
        switch (getch()) {
            case KEY_UP:
                if(selection > 0) {
                    selection--;
                }
                break;
            case KEY_DOWN:
                if(selection < list_size) {
                    selection++;
                    if(!back_button && selection==list_size) selection--;
                }
                break;
        }
        showPage();
    }
    system("cls");
    front_hilight = selection;
    if(selection<list_size) return menu[selection];
    else return "";
}
string RightPanel(string left_title, const string left_menu[], int left_list_size, string title, const string menu[], int list_size){
    int selection = 0;
    auto showPage = [&](){
        int space = 20;
        system("cls");
        cout << setColour("---=="+left_title+"==---", "cyan"); space-=10+left_title.length();
        for(int c=1; c<=space; c++) cout << ' '; cout << "| ";
        cout << setColour("---=="+title+"==---\n", "cyan");

        for(int i=0; i<list_size; i++){
            space = 20;
            
            if(i<left_list_size){
                if(front_hilight == i) cout << setColour(left_menu[i], "green");
                else cout << left_menu[i]; space-=left_menu[i].length();
            } 
            for(int c=1; c<=space; c++) cout << ' '; cout << "| ";
            
            if(selection == i) cout << setColour(">>"+menu[i], "red") << endl;
            else cout << menu[i] << endl;
        }
        for(int c=1; c<=space; c++) cout << ' '; cout << "| \n";
        for(int c=1; c<=space; c++) cout << ' '; cout << "| ";
        if(selection==list_size) cout << setColour("<--[Cancel]", "red");
        else cout << "[Cancel]";

        cout << "\n\n";
    };

    showPage(); int ch;
    while ((ch = getch()) != ENTER) {
        if (ch == 0 || ch == 224)
        switch (getch()) {
            case KEY_UP:
                if(selection > 0) {
                    selection--;
                }
                break;
            case KEY_DOWN:
                if(selection <= list_size) {
                    selection++;
                }
                break;
        }
        showPage();
    }
    system("cls");
    if(selection<list_size) return menu[selection];
    else return "";
}

bool ConfirmationPrompt(string question){
    int ch; 
    int pos=0;
    auto ShowPage = [&](){
        if(pos==0){
            system("cls");
            cout << setColour(question, "cyan") << endl << endl;
            cout << setColour("[No]", "green") << "    [Yes]";
        } else {
            system("cls");
            cout << setColour(question, "cyan") << endl << endl;
            cout  << "[No]    " << setColour("[Yes]", "red");
        }
    };

    ShowPage();
    while ((ch = getch()) != ENTER) {
        switch (getch()) {
            case 75:
                if(pos) {
                    pos = 0;
                }
                break;
            case 77:
                if(!pos) {
                    pos = 1;
                }
                break;
        }
        
        ShowPage();
    }
    return pos;
}


bool testExists(string test_name){
    ifstream f("data/config.txt");
    string line;
    while(getline(f, line)){
        if(line == test_name) return true;
    }
    return false;
}

void vizualizare_teste(){
    int n;
    string line;
    ifstream f("data/config.txt");
    f >> n; f.ignore();
    for(int i=1; i<=n; i++){
        getline(f, line);
        cout << i << ".) "+line << endl;
    }

    f.close();
}

void help(){

    cout << "-" << setColour("vizualizare_teste","green") << endl;
    cout << "-" << setColour("creare_test","green") << " <nume test>" << endl;
    cout << "-" << setColour("stergere_test","green") << " <nume test>" << endl;
    cout << "-" << setColour("editare_nume_test","green") << " <nume test> " << "<nume nou test>" << endl;
    cout << "-" << setColour("adauga_intrebare_text","green") << " <nume test> <\"intrebare\"> <\"raspuns corect\">" << endl;
    cout << "-" << setColour("adauga_intrebare_grila","green") << " <nume test> <\"intrebare\"> <nr raspuns corect> <\"varianta 1\"> <\"varianta 2\"> <\"varianta 3\"> <\"varianta 4\">" << endl;
    cout << "-" << setColour("elimina_intrebare","green") << " <nume test> <numarul itrebarii>" << endl;
    cout << "-" << setColour("vizualizare_statistici","green") << endl;
    cout << "-" << setColour("vizualizare_statistici_test","green") << " <nume test>" << endl;
}

void creare_test(string nume){
    ifstream check("data/teste/"+nume+"/test.txt");
    if(!check.is_open()){
        string cmd = "mkdir data\\teste\\\""+nume+"\"";
        system(cmd.c_str());

        ofstream ff("data/teste/"+nume+"/test.txt"); ff << 0;
        ofstream f("data/teste/"+nume+"/stats.txt");
        ff.close();
        f.close();

        ofstream config("data/config.txt", std::ios::app);
        config << endl << nume;
        config.close();

        string data[100], line; int i=1, numar;

        ifstream config1("data/config.txt");
        config1 >> numar; config1.ignore();
        while(getline(config1, line)){
            data[i] = line;
            i++;
        }
        config1.close();

        ofstream config_out("data/config.txt");
        config_out << numar+1; config_out << endl;
        for(int j=1; j<i; j++){
            config_out << data[j];
            if(j!=i-1) config_out << endl;
        }
        config_out.close();
    } else cout << setColour("Exista deja un test cu acest nume!", "red");

    check.close();
}

void stergere_test(string nume){
    ifstream check("data/teste/"+nume+"/test.txt");
    if(check.is_open()){
        check.close();
        string cmd = "rmdir /S /Q \"data\\teste\\"+nume+"\"";
        system(cmd.c_str());

        string data[100], line; int i=1, numar;

        ifstream config("data/config.txt");
        config >> numar; config.ignore();
        while(getline(config, line)){
            if(line!=nume){
                data[i] = line;
                i++;

            }
        }
        config.close();

        ofstream config_out("data/config.txt");
        config_out << numar-1; config_out << endl;
        for(int j=1; j<i; j++){
            if(data[j]!=nume) config_out << data[j];
            if(j!=i-1) config_out << endl;
        }
        config_out.close();

    } else cout << setColour("Nu exista nici un test cu acest nume!", "red");

    
}

void adauga_intrebare_text(string nume, string intrebare, string raspuns){
    Test test(nume);
    test.addQuestion(intrebare, raspuns);
}

void adauga_intrebare_grila(string nume, string intrebare, int raspuns, string varianta1, string varianta2, string varianta3, string varianta4){
    Test test(nume);
    string variante[5];
    variante[1] = varianta1;
    variante[2] = varianta2;
    variante[3] = varianta3;
    variante[4] = varianta4;
    variante[0] = variante[raspuns];
    test.addQuestion(intrebare, raspuns, variante);
}

void elimina_intrebare(string nume, int index){
    Test test(nume);
    test.removeQuestion(index);
}


vector<string> split(string str,   char* delimiter)
{
    vector<string> v;
     char *token = strtok(const_cast<char*>(str.c_str()), delimiter);
    while (token != nullptr)
    {
        v.push_back(string(token));
        token = strtok(nullptr, delimiter);
    }
   
  return v;
}
void textBox(string text){
// 186.) ║
// 187.) ╗
// 188.) ╝
// 201.) ╔
// 200.) ╚
// 205.) ═
// 209.) ╤
// 207.) ╧
// 179.) │
    int n = 0;
    int max = 0;
    for(int i=0; i<text.length(); i++) if(text[i]=='\n'){
        if(max<n) max = n;
        n = 0;
    } else {
        n++;
    }
    if(max < n) max = n;
    max+=2;


    vector<string> lines = split(text, string("\n").data());

    cout << char(201);  for(int i=0; i<max; i++) cout << char(205); cout << char(187) << endl; 
    for(auto line: lines){
        n = max - line.length() - 2;
        cout << char(186) << ' ' << line; 
        while(n>0){
            n--;
            cout << ' ';
        }
        cout << ' ' << char(186) << endl;
    }
    cout << char(200);  for(int i=0; i<max; i++) cout << char(205); cout << char(188) << endl; 
}
void table(vector<vector<string>> text, string title){
// 186.) ║
// 186.) ║
// 187.) ╗
// 188.) ╝
// 201.) ╔
// 200.) ╚
// 205.) ═
// 209.) ╤
// 207.) ╧
// 179.) │
// 196.) ─
// 197.) ┼
// 199.) ╟
// 182.) ╢
    int n = 0, nr_collumns = 0;
    vector<int> row_len;
    for(auto cell : text[0]){row_len.emplace_back(cell.length()); nr_collumns++;}
    for(auto row : text){
        for(int i=0; i<nr_collumns; i++){
            if(row[i][0]=='\033'){
                if(row[i].length()-11 > row_len[i]) {
                    row_len[i] = row[i].length() - 11;
                }        
            } else {
                if(row[i].length()> row_len[i]) row_len[i] = row[i].length();
            }
        }
    }
    // cout << setColour("["+title+"]", "yellow") << endl;
    cout << "["+title+"]" << endl;

    cout << char(201);
    for(int i=0; i<nr_collumns; i++){
        for(int j=0; j<row_len[i]+2; j++) cout << char(205);
        if(i == nr_collumns-1) cout << char(187) << endl;
        else cout << char(209);
    }

    int p=0, pp=0;
    for(auto row : text){
        cout << char(186);
        pp=0;
        for(auto cell : row){
            cout << ' ' << cell;
            if(cell[0]=='\033') for(int i=0; i<=row_len[pp] - (cell.length() - 11); i++) cout << ' ';
            else for(int i=0; i<=row_len[pp] - cell.length(); i++) cout << ' ';
            if(pp != nr_collumns-1) cout << char(179);
            pp++;
        }
        cout << char(186) << endl;
        if(p==0){
            cout << char(199);
            for(int i=0; i<nr_collumns; i++){
                for(int j=0; j<row_len[i]+2; j++) cout << char(196);
                if(i == nr_collumns-1) cout << char(182) << endl;
                else cout << char(197);
            }
        }
        p++;
    }

    cout << char(200);
    for(int i=0; i<nr_collumns; i++){
        for(int j=0; j<row_len[i]+2; j++) cout << char(205);
        if(i == nr_collumns-1) cout << char(188) << endl;
        else cout << char(207);
    }
    
}


void vizualizare_statistici_test(string nume_test){
    Test test(nume_test);
    ifstream f(test.getPath()+"/stats.txt");

    vector<pair<string, int>> persoane; int nr_persoane=0;
    int nr_answers[test.getNumarIntrebari()+1];
    for(int i=0; i<=test.getNumarIntrebari(); i++)nr_answers[i]=0;

    vector<vector<vector<string>>> statistici(test.getNumarIntrebari()+1);
    for(int i=1; i<=test.getNumarIntrebari(); i++){
        statistici[i].emplace_back(vector<string>());
        statistici[i][0].emplace_back("Nr");
        statistici[i][0].emplace_back("Nume, Prenume");
        statistici[i][0].emplace_back("Raspuns");
        statistici[i][0].emplace_back("Corect");
    }

    string line, rsp;
    int right_answers, it=0, nr_intrebare;
    char tip;
    while(getline(f, line)){
        it++;
        f >> right_answers; f.ignore();
        persoane.emplace_back(line, right_answers);

        for(int i=1; i<=test.getNumarIntrebari(); i++){
            statistici[i].emplace_back(vector<string>());
            
            f >> tip; f >> right_answers;
            f.ignore(); getline(f, rsp);
            
            if(right_answers){
                nr_answers[i]++;
                statistici[i][it].emplace_back(setColour(to_string(it), "green"));
                statistici[i][it].emplace_back(setColour(line, "green"));
                statistici[i][it].emplace_back(setColour(rsp, "green"));
                statistici[i][it].emplace_back(setColour("Da", "green"));
            } else {
                statistici[i][it].emplace_back(setColour(to_string(it), "red"));
                statistici[i][it].emplace_back(setColour(line, "red"));
                statistici[i][it].emplace_back(setColour(rsp, "red"));
                statistici[i][it].emplace_back(setColour("Nu", "red"));
            }
        }

        nr_persoane++;
    } 
    if(nr_persoane==0) {
            cout << setColour("Nu exista statistici pentru acest test!", "red");
            return;
    }
    cout << setColour("---== Statistici pentru testul ["+nume_test+"] ==---", "cyan") << endl;

    //medie
    int sum_right_answers = 0;
    for(auto p : persoane){
        sum_right_answers += p.second;
    }
    cout << "Punctaj mediu: " << fixed << setprecision(2) << sum_right_answers/nr_persoane << '/' << test.getNumarIntrebari() << " puncte" << endl;
    cout << "Punctaj mediu (in %): " << fixed << setprecision(2) << (float(sum_right_answers)/float(test.getNumarIntrebari()*nr_persoane))*100 << "%" << endl << endl;

    //clasament
    sort(persoane.begin(), persoane.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    }); 
    vector<vector<string>> clasament;
    int index = 0;
    clasament.emplace_back(vector<string>());
    clasament[index].emplace_back("Nr");
    clasament[index].emplace_back("Nume, Prenume");  
    clasament[index].emplace_back("Punctaj");
    clasament[index].emplace_back("(%)");
    for(auto l : persoane){
        index++;
        clasament.emplace_back(vector<string>());
        clasament[index].emplace_back(to_string(index));
        clasament[index].emplace_back(l.first);
        clasament[index].emplace_back(to_string(l.second) + "/" + to_string(test.getNumarIntrebari()));
        clasament[index].emplace_back(to_string(int((float(l.second)/float(test.getNumarIntrebari()))*100)) + "%");
    } 
    table(clasament, "Clasament");
    cout << endl;


    textBox("<<Statistici Intrebari>>");

    for(int i=1; i<=test.getNumarIntrebari(); i++){
        // cout << i << ".)" << test.intrebari[i-1]->getQuestion() << "\nRaspunsuri corecte: " << nr_answers[i] << '/' << nr_persoane << "\n";
        table(statistici[i], "("+to_string(i)+") "+test.intrebari[i-1]->getQuestion());
    }
    f.close();

}
void vizualizare_statistici(){
    cout << setColour("---== Statistici pentru toate testele ==--- ", "cyan") << endl;

}

int main(int argc, char* argv[]){
    system("cls");
    if(argc == 1){ 
        help();
        return 0;
    }
    string exe(argv[1]);
    if(exe=="help") help(); 
    else if(exe=="editare_nume_test"){
        char a[100], b[100];
        strcpy(a, "data/teste/");
        strcat(a, argv[2]);
        strcpy(b, "data/teste/");
        strcat(b, argv[3]);
        if(rename(a, b)){
            cout << setColour("Nu exista nici un test cu asa nume!", "red");
        } else {
            cout << setColour("Numele testului a fost editat cu succes!", "green");
        }

        ifstream config1("data/config.txt");
        string data[100], line; int i=0, j=0;
        while(getline(config1, line)){
            data[i] = line;
            i++;
        }
        config1.close();
        ofstream config2("data/config.txt");
        while (j<i)
        {
            if(data[j]==argv[2]) config2 << argv[3];
            else config2 << data[j];
            if(j!=i-1) config2 << endl;
            j++;
        }
        config2.close();
    } 
    else if(exe=="vizualizare_teste") vizualizare_teste();
    else if(exe=="creare_test") creare_test(argv[2]);
    else if(exe=="stergere_test") stergere_test(argv[2]);
    else if(exe=="adauga_intrebare_text") adauga_intrebare_text(argv[2], argv[3], argv[4]);
    else if(exe=="adauga_intrebare_grila") adauga_intrebare_grila(argv[2], argv[3], atoi(argv[4]), argv[5], argv[6], argv[7], argv[8]);
    else if(exe=="elimina_intrebare") elimina_intrebare(argv[2], atoi(argv[3]));
    else if(exe=="vizualizare_statistici_test") vizualizare_statistici_test(argv[2]);
    else if(exe=="vizualizare_statistici") vizualizare_statistici();
    

    return 0;
}

/*
vizualizare_teste
creare_test
stergere_test
editare_nume_test
adauga_intrebare_text
adauga_intrebare_grila
elimina_intrebare
vizualizare_statistici
vizualizare_statistici_test
*/