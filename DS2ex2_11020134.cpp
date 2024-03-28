#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct data_node {
	int id; // 第幾個加進vector的資料 
	int student_count; // 學生數
	int graduate_count; // 畢業生數 
	string school_name; // 學校名稱
	string major_name; // 科系名稱
	string day_night_e; // 日夜別
	string day_night_c;
	string level_e; // 等級別 
	string level_c;
};

void Infile(string fileName, vector<data_node>& student_count) { // 讀入資料，student_count為vector陣列，裡面的資料及讀入的資料
	// 用vector陣列儲存學校資料
	int data_num = 0; 
    string garbage;
	std::string line;
	
    data_node cur_data_node;
    // cur_data_node是infile的對象 ，在infile之後再將資料帶入vector
    int graduate = 0; // 先在這裡宣告，藉由infile獲得資料再複製進data_node裡 
    
    std::ifstream infile(fileName.c_str());
    
    // 資料開啟失敗 
    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    
    std::getline(infile, line);
    std::getline(infile, line);
    std::getline(infile, line); // 跳過排頭*3 
    
    int tokenCount = 0;
    
    while (infile >> garbage) {
    	// 學校代碼不需要 
        infile >> cur_data_node.school_name; // 學校名稱 
        infile >> garbage; // 科系代碼不需要 
        infile >> cur_data_node.major_name; // 科系名稱 
        infile >> cur_data_node.day_night_e; // 日夜 
        infile >> cur_data_node.day_night_c;
        infile >> cur_data_node.level_e; // 等級 
        infile >> cur_data_node.level_c;
    	infile >> cur_data_node.student_count; // 學生數 
        infile >> garbage; // 教師數量不需要 
        infile >> graduate; // 畢業生數 
        
        data_num = data_num + 1;
        	
		cur_data_node.id = data_num; // id = 序號(第幾個讀進的資料) 
        cur_data_node.graduate_count = graduate; // 畢業生數 
        	
        student_count.push_back(cur_data_node); // pushback到vector最後方就算完成一筆資料的讀入 
            
		// 讀到要的資料後跳過剩下的 
        std::getline(infile, line);
            
        // 些許條件的初始化 
        tokenCount = 0;
                        
        // 下一行重新開始
    }
}

void two_three_tree(vector<data_node> student_count) {
	int cur_num = 0; // 目前印了幾個?
	while (cur_num < student_count.size()) {
		cout << "[" << student_count[cur_num].id << "] " << student_count[cur_num].school_name << student_count[cur_num].major_name << ", " << student_count[cur_num].day_night_e << " " << student_count[cur_num].day_night_c << ", " << student_count[cur_num].level_e << " " << student_count[cur_num].level_c << ", " << student_count[cur_num].student_count << endl;
		cur_num++;
	} 
}

int main() {
	
	int command = 0;
    
    std::vector<data_node> student_count;
    
    do {
    	cout << endl;
		cout << "********** Heap Construction **********" << endl;
		cout << "* 0. QUIT                             *" << endl;
		cout << "* 1. Build 23 tree                    *" << endl;
		cout << "* 2. Build AVL tree                   *" << endl;
		cout << "***************************************" << endl;
    
    	cout << "Input a choice(0, 1, 2):";
    	
    	cin >> command;
    	cout << endl;
    
    	std::string fileName;
    	if (command == 1) {
    		cout << "Input a file number ([0] Quit):";

    		// 從使用者輸入中讀取檔案編號
    		cin >> fileName;
    		// 組合檔案名稱	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		Infile(fileName, student_count);
    		two_three_tree(student_count);
		}
		
		/*
		if (command == 2) {
			cout << "Input a file number ([0] Quit):";
			
			// 從使用者輸入中讀取檔案編號
    		cin >> fileName;
    		// 組合檔案名稱	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		student_count = student_count(fileName);
		}
		*/
				
		if (command == 0) {
			break;
		}
	} while (command != 0);

	return 0;
}
