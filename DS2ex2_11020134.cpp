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

class tree_node {
private:
	std::vector<data_node> school_info; // 學校的資訊 
	tree_node* father = NULL; // 父子樹 
	tree_node* greater_node = NULL; // 右子樹 
	tree_node* smaller_node = NULL; // 左子樹 
	tree_node* middle_node = NULL; // 中子樹 
	

public:
	void find_height(tree_node*& node ) { // smaller_node是private，所以用一個method將node前往左子樹，以計算樹高 
		node = node->smaller_node;
	} 
	
	vector<data_node> get_info() {
		return school_info;
	}
	
	bool is_empty(tree_node* cur_node) { // 檢查傳進來的樹是否為空 
		if (cur_node == NULL) {
			return true;
		}
		else {
			return false;
		}
	};
	
	bool is_full(std::vector<data_node> school_info) { // 確認此節點是不是超過2個，需要做分解
	
		// 檢查isfull & split的錯誤 
	
		int count = 1; // 若是count(vector裡不同數字的數量)達到三，代表高過23樹的限制，需要進行分裂 
		int cur = school_info[0].graduate_count;
		for (int i = 0; i < school_info.size(); i++) {
			if (cur != school_info[i].graduate_count) {
				count++;
				cur = school_info[i].graduate_count;
			}
		}
		
		if (count > 2) {
			return true;
		}
		else {
			return false;
		}
	}
	
	void bubbleSort(std::vector<data_node>& school_info) { // 泡沫排序，讓樹節點中的vector陣列由小排到大 
    	int n = school_info.size();
    	if (school_info.size() == 1) {
    		return;
		}
    	
    	for (int i = 0; i < n-1; ++i) {
        	for (int j = 0; j < n-i-1; ++j) {
            	if (school_info[j].graduate_count > school_info[j+1].graduate_count) {
                	// 交換元素
                	data_node temp = school_info[j];
                	school_info[j] = school_info[j+1];
                	school_info[j+1] = temp;
            	}
        	}
    	}
	}
	
	bool is_root(tree_node* cur_node){ // 檢查目前的node是否為根節點
		if (cur_node->father == NULL) {
			return true;
		}
		else {
			return false;
		}
	};

	void split(tree_node* split_node) { // 分割node
	
		cout << "split start" << endl;
		cout << "all info:" << split_node->school_info[0].major_name << "=" << split_node->school_info[0].graduate_count << ", " << split_node->school_info[1].major_name << "=" << split_node->school_info[1].graduate_count  << ", " << split_node->school_info[2].major_name << "=" << split_node->school_info[2].graduate_count << endl;
		// 分割不同畢業生數的node 
		// 最小 
		std::vector<data_node> smallest;
		smallest.push_back(split_node->school_info[0]);
		
		// 最大 
		std::vector<data_node> greatest;
		greatest.push_back(split_node->school_info[split_node->school_info.size()-1]);
		
		// 中間的可以不設初始值，只要不等於最大或最小就是中間值 
		std::vector<data_node> middle;
		
		for(int i = 0; i < split_node->school_info.size(); i++) { // 因為會有數字重複的情況，所以分裂時可能不只是一個node而是很多node 
			if (split_node->school_info[i].graduate_count == smallest[0].graduate_count) {
				smallest.push_back(split_node->school_info[i]);
			}
			else if (split_node->school_info[i].graduate_count == greatest[0].graduate_count) {
				greatest.push_back(split_node->school_info[i]);
			}
			else{
				middle.push_back(split_node->school_info[i]);
			}
			// 1.從下往上做，small和great都不用動，middle要再考慮 
		}
		
		cout << "check copy:";
		cout << smallest[0].major_name << " & " << middle[0].major_name << " & " << greatest[0].major_name << endl;
		
		// 傳進來的節點是root的情況
		if (split_node->is_root(split_node)) {
			cout << "root" << endl;
			// 新增節點，將節點中最大數作複製
			tree_node* new_great = new tree_node;
			new_great->school_info = greatest;
			cout << "greatest" << new_great->school_info[0].major_name << new_great->school_info[0].school_name << endl;
			
			// 新增節點，設定中間數(中間往上移，所以會是新的root)
			split_node->father = new tree_node;
			split_node->father->school_info = middle;
			cout << "middle" << split_node->father->school_info[0].major_name << split_node->father->school_info[0].school_name << endl;
			
			// 將原本的節點轉換為分割後的節點
			split_node->school_info = smallest;
			cout << "smallest" << split_node->school_info[0].major_name << split_node->school_info[0].school_name << endl;
			
			// 設定各個節點的指標
			new_great->father = split_node->father;
			split_node->father = split_node->father;
			split_node->father->greater_node = new_great;
			split_node->father->smaller_node = split_node; // 此時的split node只會剩下分割時最小的數值 
		} 
		
		else {
			cout << "not root" << endl;
			// 新增節點，將節點中最大數作複製
			tree_node* new_great = new tree_node;
			new_great->school_info = greatest;
			cout << "greatest" << new_great->school_info[0].major_name << new_great->school_info[0].school_name << endl;
			
			// 將分割出來的中間值(middle)給到parent
			split_node->father->school_info.push_back(middle[0]);
			split_node->father->bubbleSort(split_node->father->school_info);
			cout << "middle" << split_node->father->school_info[0].major_name << split_node->father->school_info[0].school_name << endl;
			
			// 將原本的節點轉換為分割後的節點
			split_node->school_info = smallest;
			cout << "smallest" << split_node->school_info[0].major_name << split_node->school_info[0].school_name << endl;
			
			// 設定各個節點的指標
			new_great->father = split_node->father;
			split_node->father->middle_node = new_great;
			
			// 檢查新的parent node有沒有需要進行split的動作
			if (split_node->father->is_full(split_node->father->school_info)) {
				split_node->father->split(split_node->father);
			}
		}
		
	}

	void insert_node(tree_node*& root_node, data_node new_insert_data) { // 插入資料 
		// 建立新節點 
		tree_node* cur_node = root_node;
		
		// 如果傳進來的樹是空子樹
		if (is_empty(root_node)) {
			root_node = new tree_node;
			cur_node = root_node;
			cur_node->father = NULL;
		}
		
		// 先尋找新的插入資料正確的插入位置，從根節點的位置尋找
		else {
			while (!is_empty(cur_node)) {
				if (cur_node->school_info.empty()) { // 空的vector = 插入到這裡 
					break;
				} 
				
				// 在每次移動前，先決定好father的指向，應該要是移動前的自己 
				cur_node->father = cur_node;
				if (new_insert_data.graduate_count < cur_node->school_info[0].graduate_count) { // 比vector裡最小的還小->左子樹 
					if (is_empty(cur_node->smaller_node)) { // 抵達葉子 
						break;
					}
					else {
						cur_node = cur_node->smaller_node;
					}
				}
			
				else if (new_insert_data.graduate_count > cur_node->school_info[cur_node->school_info.size()-1].graduate_count) { // 比vector裡最大的還大->右子樹
					if (is_empty(cur_node->greater_node)) { // 抵達葉子 
						break;
					}
					else {
						cur_node = cur_node->greater_node;
					}
				}
				
				else { // 非左非右->中子樹
					if (is_empty(cur_node->middle_node)) { // 抵達葉子 
						break;
					}
					else {
						cur_node = cur_node->middle_node;
					}
				}
			}
		}
		
		// 上面的程序走完後，cur_node已經是正確的插入位置了 

		cur_node->school_info.push_back(new_insert_data); // 先將資料堆進vector最後方
		
		cur_node->bubbleSort(cur_node->school_info); // 用bubble sort確保vector裡的資料是由小到大排序

		cout << "split check" << endl;
		if (cur_node->is_full(cur_node->school_info)) {
			cur_node->split(cur_node);
			cout << "split done" << endl;
		}
	}
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

void build_tree(vector<data_node> student_count) {
	int cur_num = 0; // 印出幾個node 
    int tree_height = 1; // 樹高
    int node_count = 0; // 節點數
    tree_node* two_three_tree_root = NULL; // 建立根節點 
    vector<data_node> print_node; // 印出來的學校資料 
    
    for (int i = 0; i < student_count.size(); i++) {
        cout << "inserted" << i << endl;
        
        if (two_three_tree_root == NULL) {
            two_three_tree_root = new tree_node;
        }
        
        two_three_tree_root->insert_node(two_three_tree_root, student_count[i]);
        
    	tree_node* temp_root = two_three_tree_root;
    	print_node = temp_root->get_info();
    	cout << "root size: " << print_node.size() << endl;
    }
     
    print_node = two_three_tree_root->get_info();
    cout << "root size: " << print_node.size() << endl;
    
    cout << print_node[0].school_name << ", " << print_node[0].major_name << ", " << print_node[0].student_count << ", " << print_node[0].graduate_count << endl;
    cout << print_node[1].school_name << ", " << print_node[1].major_name << ", " << print_node[1].student_count << ", " << print_node[1].graduate_count << endl;
    cout << print_node[2].school_name << ", " << print_node[2].major_name << ", " << print_node[2].student_count << ", " << print_node[2].graduate_count << endl;
	/*   
	/*   
    tree_node* temp_root = two_three_tree_root;
    print_node = temp_root->get_info();
    
    while(temp_root != nullptr) {
    	tree_height++;
    	temp_root->find_height(temp_root);
	}
	
	cout << "Tree height = " << tree_height << endl; // 印出樹高 
	
	while(cur_num < print_node.size() - 1) {
		cout << cur_num << endl;
		cout << cur_num << ": " << "[" << print_node[cur_num].id << "] " << print_node[cur_num].school_name << ", " << print_node[cur_num].major_name << ", " << print_node[cur_num].day_night_e << " " << print_node[cur_num].day_night_c << ", " << print_node[cur_num].level_e << " " << print_node[cur_num].level_c << ", " << print_node[cur_num].student_count << ", " << print_node[cur_num].graduate_count << endl;
		cur_num++;
	}
	*/ 
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
    		build_tree(student_count);
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
