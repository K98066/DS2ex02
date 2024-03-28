#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct data_node {
	int id; // �ĴX�ӥ[�ivector����� 
	int student_count; // �ǥͼ�
	int graduate_count; // ���~�ͼ� 
	string school_name; // �ǮզW��
	string major_name; // ��t�W��
	string day_night_e; // ��]�O
	string day_night_c;
	string level_e; // ���ŧO 
	string level_c;
};

void Infile(string fileName, vector<data_node>& student_count) { // Ū�J��ơAstudent_count��vector�}�C�A�̭�����Ƥ�Ū�J�����
	// ��vector�}�C�x�s�Ǯո��
	int data_num = 0; 
    string garbage;
	std::string line;
	
    data_node cur_data_node;
    // cur_data_node�Oinfile����H �A�binfile����A�N��Ʊa�Jvector
    int graduate = 0; // ���b�o�̫ŧi�A�ǥ�infile��o��ƦA�ƻs�idata_node�� 
    
    std::ifstream infile(fileName.c_str());
    
    // ��ƶ}�ҥ��� 
    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    
    std::getline(infile, line);
    std::getline(infile, line);
    std::getline(infile, line); // ���L���Y*3 
    
    int tokenCount = 0;
    
    while (infile >> garbage) {
    	// �ǮեN�X���ݭn 
        infile >> cur_data_node.school_name; // �ǮզW�� 
        infile >> garbage; // ��t�N�X���ݭn 
        infile >> cur_data_node.major_name; // ��t�W�� 
        infile >> cur_data_node.day_night_e; // ��] 
        infile >> cur_data_node.day_night_c;
        infile >> cur_data_node.level_e; // ���� 
        infile >> cur_data_node.level_c;
    	infile >> cur_data_node.student_count; // �ǥͼ� 
        infile >> garbage; // �Юv�ƶq���ݭn 
        infile >> graduate; // ���~�ͼ� 
        
        data_num = data_num + 1;
        	
		cur_data_node.id = data_num; // id = �Ǹ�(�ĴX��Ū�i�����) 
        cur_data_node.graduate_count = graduate; // ���~�ͼ� 
        	
        student_count.push_back(cur_data_node); // pushback��vector�̫��N�⧹���@����ƪ�Ū�J 
            
		// Ū��n����ƫ���L�ѤU�� 
        std::getline(infile, line);
            
        // �ǳ\���󪺪�l�� 
        tokenCount = 0;
                        
        // �U�@�歫�s�}�l
    }
}

void two_three_tree(vector<data_node> student_count) {
	int cur_num = 0; // �ثe�L�F�X��?
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

    		// �q�ϥΪ̿�J��Ū���ɮ׽s��
    		cin >> fileName;
    		// �զX�ɮצW��	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		Infile(fileName, student_count);
    		two_three_tree(student_count);
		}
		
		/*
		if (command == 2) {
			cout << "Input a file number ([0] Quit):";
			
			// �q�ϥΪ̿�J��Ū���ɮ׽s��
    		cin >> fileName;
    		// �զX�ɮצW��	 ex:"input401.txt"
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
